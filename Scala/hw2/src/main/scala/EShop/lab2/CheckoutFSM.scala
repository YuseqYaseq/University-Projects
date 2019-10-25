package EShop.lab2

import EShop.lab2.CheckoutFSM.Status
import akka.actor.{ActorRef, Cancellable, LoggingFSM, Props}

import scala.concurrent.ExecutionContext.Implicits.global
import scala.concurrent.duration._
import scala.language.postfixOps
import Checkout._
import CartActor._
import EShop.lab2.CartActor.CheckoutStarted
import CheckoutFSM._

object CheckoutFSM {

  object Status extends Enumeration {
    type Status = Value
    val NotStarted, SelectingDelivery, SelectingPaymentMethod, Cancelled, ProcessingPayment, Closed = Value
  }

  case class CheckoutFSMParams(
                                deliveryMethod: Option[String],
                                paymentMethod:  Option[String],
                                payment:        Option[ActorRef],
                                timer:          Option[Cancellable]) {
    def cancelTimer: Option[Boolean] = timer.map(timer => timer.cancel)
  }

  val Uninitialized = CheckoutFSMParams(None, None, None, None)

  def props(cartActor: ActorRef, orderManager: ActorRef) =
    Props(new CheckoutFSM(cartActor, orderManager))
}



class CheckoutFSM(
  cart:           ActorRef,
  orderManager:   ActorRef) extends LoggingFSM[Status.Value, CheckoutFSMParams] {
  import EShop.lab2.CheckoutFSM.Status._

  // useful for debugging, see: https://doc.akka.io/docs/akka/current/fsm.html#rolling-event-log
  override def logDepth = 12

  val checkoutTimerDuration: FiniteDuration = 1 seconds
  val paymentTimerDuration: FiniteDuration  = 1 seconds

  private val scheduler = context.system.scheduler
  private def assignCheckoutTimer = Option(scheduler.scheduleOnce(checkoutTimerDuration, self, ExpireCheckout))
  private def assignPaymentTimer  = Option(scheduler.scheduleOnce(paymentTimerDuration, self, ExpirePayment))

  startWith(NotStarted, Uninitialized)

  when(NotStarted) {
    case Event(Checkout.StartCheckout | CartActor.StartCheckout, p) =>
      val new_p = p.copy(timer = assignCheckoutTimer)
      goto(SelectingDelivery).using(new_p)
  }

  when(SelectingDelivery) {
    case Event(SelectDeliveryMethod(method), p) =>
      p.cancelTimer
      val new_p = p.copy(
        timer = assignCheckoutTimer,
        deliveryMethod = Option(method)
      )
      goto(SelectingPaymentMethod).using(new_p)
    case Event(CartActor.CancelCheckout | Checkout.CancelCheckout | ExpireCheckout, p) =>
      p.cancelTimer
      val new_p = p.copy(
        timer = None
      )
      goto(Cancelled).using(new_p)
  }

  when(SelectingPaymentMethod) {
    case Event(SelectPayment(method), p) =>
      p.cancelTimer
      val new_p = p.copy(
        timer = assignPaymentTimer,
        paymentMethod = Option(method)
      )
      goto(ProcessingPayment).using(new_p)
    case Event(CartActor.CancelCheckout | Checkout.CancelCheckout | ExpireCheckout, p) =>
      p.cancelTimer
      goto(Cancelled).using(p)
  }

  when(ProcessingPayment) {
    case Event(ReceivePayment, p) =>
      p.cancelTimer
      goto(Closed).using(p)
    case Event(CartActor.CancelCheckout | Checkout.CancelCheckout | ExpirePayment, p) =>
      goto(Cancelled).using(p)
  }

  when(Cancelled) {
    case _ => stay()
  }

  when(Closed) {
    case _ => stay()
  }

}
