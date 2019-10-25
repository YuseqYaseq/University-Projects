package EShop.lab2

import EShop.lab2.CartFSM.Status
import akka.actor.{ActorRef, LoggingFSM, PoisonPill, Props}

import scala.concurrent.duration._
import scala.language.postfixOps
import CartActor._

object CartFSM {

  object Status extends Enumeration {
    type Status = Value
    val Empty, NonEmpty, InCheckout = Value
  }

  def props(orderManager: ActorRef) = Props(new CartFSM(orderManager))

}

class CartFSM(
 orderManager: ActorRef
             ) extends LoggingFSM[Status.Value, (Cart, ActorRef)] {
  import EShop.lab2.CartFSM.Status._

  // useful for debugging, see: https://doc.akka.io/docs/akka/current/fsm.html#rolling-event-log
  override def logDepth = 12

  val cartTimerDuration: FiniteDuration = 1 seconds

  startWith(Empty, (Cart.empty, null))

  when(Empty) {
    case Event(c:CartActor.AddItem, (cart, _)) =>
      goto(NonEmpty).using( (cart.addItem(c.item), null) )
  }

  when(NonEmpty, stateTimeout = cartTimerDuration) {
    case Event(c:CartActor.AddItem, (cart, _)) =>
      stay.using( (cart.addItem(c.item), null) )
    case Event(c:CartActor.RemoveItem, (cart, _)) =>
      val new_cart = cart.removeItem(c.item)
      if(new_cart.items.isEmpty) {
        goto(Empty).using( (Cart.empty, null) )
      } else {
        stay.using( (new_cart, null) )
      }
    case Event(CartActor.StartCheckout, (cart, _)) =>
      goto(InCheckout).using((cart, context.system.actorOf(CheckoutFSM.props(self, orderManager))))
    case Event(CartActor.ExpireCart, _) =>
      goto(Empty).using( (Cart.empty, null) )
  }

  when(InCheckout) {
    case Event(CartActor.CancelCheckout, (cart, checkout)) =>
      checkout ! PoisonPill
      goto(NonEmpty).using((cart, null))
    case Event(CartActor.CloseCheckout, _) =>
      goto(Empty).using((Cart.empty, null))
  }

  whenUnhandled {
    case Event(StateTimeout, (_, checkout)) =>
      if(checkout != null) {
        checkout ! PoisonPill
      }
      goto(Empty).using((Cart.empty, null))
    case Event(e, s) =>
      log.warning("received unhandled request {} in state {}/{}", e, stateName, s)
      stay
  }

}
