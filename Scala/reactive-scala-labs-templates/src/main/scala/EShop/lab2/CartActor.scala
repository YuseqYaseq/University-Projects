package EShop.lab2

import java.util.concurrent.TimeUnit

import EShop.lab2.CartActor.Command
import akka.actor.{Actor, ActorRef, Cancellable, Props}
import akka.event.Logging

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

  def props = Props(new CartActor())
}

class CartActor extends Actor {

  import CartActor.AddItem, CartActor.RemoveItem, CartActor.ExpireCart, CartActor.StartCheckout,
    CartActor.CancelCheckout, CartActor.CloseCheckout

  private val z = context.system

  private val log       = Logging(context.system, this)
  val cartTimerDuration = 5 seconds

  private def scheduleTimer: Cancellable = context.system.scheduler.scheduleOnce(cartTimerDuration, self, ExpireCart)

  def receive: Receive = {
    case c:AddItem =>
      context become nonEmpty(Cart(Seq(c.item)), scheduleTimer)
  }

  def empty: Receive = {
    case c:AddItem =>
      context become nonEmpty(Cart(Seq(c.item)), scheduleTimer)
  }

  def nonEmpty(cart: Cart, timer: Cancellable): Receive = {
    case c:AddItem =>
      val cart2 = cart.addItem(c.item)
      timer.cancel()
      context become nonEmpty(cart2, scheduleTimer)
    case c:RemoveItem =>
      val cart2 = cart.removeItem(c.item)
      if(cart2.items == Nil) {
        context become empty
      }
      timer.cancel()
    case ExpireCart =>
      context become empty
      timer.cancel()
    case StartCheckout =>
      context become inCheckout(cart)
      timer.cancel()
  }

  def inCheckout(cart: Cart): Receive = {
    case CancelCheckout =>
      context become nonEmpty(cart, scheduleTimer)
    case CloseCheckout =>
      context become empty
  }

}
