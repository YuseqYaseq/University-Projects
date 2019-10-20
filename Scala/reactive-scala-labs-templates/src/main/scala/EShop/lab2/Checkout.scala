package EShop.lab2

import akka.actor.{Actor, ActorRef, Cancellable, Props}
import akka.event.Logging

import scala.concurrent.duration._
import scala.language.postfixOps

import CartActor._
import Checkout._
import scala.concurrent.ExecutionContext.Implicits.global

object Checkout {

  sealed trait Data
  case object Uninitialized                               extends Data
  case class SelectingDeliveryStarted(timer: Cancellable) extends Data
  case class ProcessingPaymentStarted(timer: Cancellable) extends Data

  sealed trait Command
  case object StartCheckout                       extends Command
  case class SelectDeliveryMethod(method: String) extends Command
  case object CancelCheckout                      extends Command
  case object ExpireCheckout                      extends Command
  case class SelectPayment(payment: String)       extends Command
  case object ExpirePayment                       extends Command
  case object ReceivePayment                      extends Command

  sealed trait Event
  case object CheckOutClosed
    extends Event
  case class PaymentStarted(payment: ActorRef) extends Event

  def props(cart: ActorRef) = Props(new Checkout())
}

class Checkout extends Actor {

  private val scheduler = context.system.scheduler
  private val log       = Logging(context.system, this)

  val checkoutTimerDuration = 1 seconds
  val paymentTimerDuration  = 1 seconds

  def receive: Receive = {
    case Checkout.StartCheckout =>
      context become selectingDelivery(scheduler.scheduleOnce(checkoutTimerDuration, self, Checkout.ExpireCheckout))
  }

  def selectingDelivery(timer: Cancellable): Receive = {
      case (Checkout.CancelCheckout | Checkout.ExpireCheckout) =>
        context become cancelled
      case SelectDeliveryMethod(_) =>
        context become selectingPaymentMethod(scheduler.scheduleOnce(checkoutTimerDuration, self, Checkout.ExpireCheckout))
  }

  def selectingPaymentMethod(timer: Cancellable): Receive = {
    case Checkout.SelectPayment(_) =>
      timer.cancel()
      context become processingPayment(scheduler.scheduleOnce(paymentTimerDuration, self, Checkout.ExpirePayment))
    case (Checkout.CancelCheckout | Checkout.ExpireCheckout) =>
      timer.cancel()
      context become cancelled
  }

  def processingPayment(timer: Cancellable): Receive = {
    case Checkout.ReceivePayment =>
      timer.cancel()
      context become closed
    case (Checkout.CancelCheckout | Checkout.ExpirePayment) =>
      timer.cancel()
      context become cancelled
  }

  def cancelled: Receive = {
    case _ =>
  }

  def closed: Receive = {
    case _ =>
  }

}

import CartActor.CancelCheckout
