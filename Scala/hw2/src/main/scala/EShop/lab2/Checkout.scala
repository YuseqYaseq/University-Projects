package EShop.lab2

import akka.actor.{Actor, ActorRef, Cancellable, Props}
import akka.event.Logging

import scala.concurrent.duration._
import scala.language.postfixOps
import CartActor._
import Checkout._
import EShop.lab3.Payment

import scala.concurrent.ExecutionContext.Implicits.global

object Checkout {

  /*sealed trait Data
  case object Uninitialized                               extends Data
  case class SelectingDeliveryStarted(timer: Cancellable) extends Data
  case class ProcessingPaymentStarted(timer: Cancellable) extends Data*/

  sealed trait Command
  case object StartCheckout                       extends Command
  case class SelectDeliveryMethod(method: String) extends Command
  case object CancelCheckout                      extends Command
  case object ExpireCheckout                      extends Command
  case class SelectPayment(payment: String)       extends Command
  case object ExpirePayment                       extends Command
  case object ReceivePayment                      extends Command

  sealed trait Event
  case object CheckOutClosed                      extends Event
  case class PaymentSelected(payment: ActorRef)   extends Event
  case class DeliverySelected(delivery: ActorRef) extends Event

  def props(orderManager: ActorRef, cart: ActorRef) = Props(new Checkout(orderManager, cart))
}

class Checkout(
  orderManager: ActorRef,
  cart: ActorRef) extends Actor {

  private val scheduler = context.system.scheduler
  private val log       = Logging(context.system, this)

  val checkoutTimerDuration: FiniteDuration = 1 seconds
  val paymentTimerDuration: FiniteDuration  = 1 seconds
  var payment: ActorRef = _

  val send_back = false

  def receive: Receive = {
    case Checkout.StartCheckout =>
      if(send_back)
			  sender ! CheckoutStarted
      context become selectingDelivery(scheduler.scheduleOnce(checkoutTimerDuration, self, Checkout.ExpireCheckout))
  }

  def selectingDelivery(timer: Cancellable): Receive = {
      case (Checkout.CancelCheckout | Checkout.ExpireCheckout) =>
        context become cancelled
        if(send_back)
			    sender ! CheckoutCanceled
      case SelectDeliveryMethod(_) =>
        context become selectingPaymentMethod(scheduler.scheduleOnce(checkoutTimerDuration, self, Checkout.ExpireCheckout))
        if(send_back)
			    sender ! DeliverySelected(null)
  }

  def selectingPaymentMethod(timer: Cancellable): Receive = {
    case Checkout.SelectPayment(method) =>
      timer.cancel()
      payment = context.system.actorOf(Payment.props(method, orderManager, self))
      context become processingPayment(scheduler.scheduleOnce(paymentTimerDuration, self, Checkout.ExpirePayment))
      if(send_back)
			  sender ! PaymentSelected(payment)
    case (Checkout.CancelCheckout | Checkout.ExpireCheckout) =>
      timer.cancel()
      context become cancelled
      if(send_back)
			  sender ! CheckoutCanceled
  }

  def processingPayment(timer: Cancellable): Receive = {
    case Checkout.ReceivePayment =>
      timer.cancel()
      context become closed
      if(send_back)
			  sender ! CheckoutClosed
    case (Checkout.CancelCheckout | Checkout.ExpirePayment) =>
      timer.cancel()
      context become cancelled
      if(send_back)
			  sender ! CheckoutCanceled
  }

  def cancelled: Receive = {
    case _ =>
  }

  def closed: Receive = {
    case _ =>
  }

}

import CartActor.CancelCheckout
