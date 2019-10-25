package EShop.lab2

import java.util.concurrent.TimeUnit

import EShop.lab2.CartActor.Command
import akka.actor.{Actor, ActorRef, Cancellable, Props}
import akka.event.Logging
import CartActor._

import scala.concurrent.ExecutionContext.Implicits.global
import scala.concurrent.duration._
import scala.language.postfixOps

object CartActor {

  sealed trait Command
  case class AddItem(item: Any)    extends Command
  case class RemoveItem(item: Any) extends Command
  case object ExpireCart           extends Command
  case object StartCheckout        extends Command
  case object CancelCheckout       extends Command
  case object CloseCheckout        extends Command

  sealed trait Event
  case class CheckoutStarted(checkoutRef: ActorRef) extends Event
  case object ItemAdded                             extends Event
  case object ItemRemoved                           extends Event
  case object CheckoutCanceled                      extends Event
  case object CheckoutClosed                        extends Event

  def props(orderManager: ActorRef) = Props(new CartActor(orderManager))
}

class CartActor(
   orderManager: ActorRef) extends Actor {

  import CartActor.AddItem, CartActor.RemoveItem, CartActor.ExpireCart, CartActor.StartCheckout,
    CartActor.CancelCheckout, CartActor.CloseCheckout


  private val log       = Logging(context.system, this)
  val cartTimerDuration: FiniteDuration = 5 seconds

  val send_back = false
  var Checkout: ActorRef = _

  private def scheduleTimer: Cancellable = context.system.scheduler.scheduleOnce(cartTimerDuration, self, ExpireCart)

  def receive: Receive = {
    case c:AddItem =>
      context become nonEmpty(Cart(Seq(c.item)), scheduleTimer)
      if(send_back)
			  sender ! ItemAdded
  }

  def empty: Receive = {
    case c:AddItem =>
      context become nonEmpty(Cart(Seq(c.item)), scheduleTimer)
      if(send_back)
			  sender ! ItemAdded
  }

  def nonEmpty(cart: Cart, timer: Cancellable): Receive = {
    case c:AddItem =>
      val cart2 = cart.addItem(c.item)
      timer.cancel()
      context become nonEmpty(cart2, scheduleTimer)
      if(send_back)
			  sender ! ItemAdded
    case c:RemoveItem =>
      val cart2 = cart.removeItem(c.item)
      if(cart2.items == Nil) {
        context become empty
      }
      timer.cancel()
      if(send_back)
			  sender ! ItemRemoved
    case ExpireCart =>
      context become empty
      timer.cancel()
    case StartCheckout =>
      context become inCheckout(cart)
      timer.cancel()
      if(send_back)
			  sender ! CheckoutStarted(context.system.actorOf(Props[Checkout]))
  }

  def inCheckout(cart: Cart): Receive = {
    case CancelCheckout =>
      context become nonEmpty(cart, scheduleTimer)
      if(send_back)
			  sender ! CheckoutCanceled
    case CloseCheckout =>
      context become empty
      if(send_back)
			  sender ! CheckoutClosed
  }

}
