package EShop.lab3

import EShop.lab3.PaymentFSM._
import EShop.lab3.PaymentFSM.State.State
import akka.actor.{ActorRef, FSM, Props}

object PaymentFSM {
  def props(method: String, orderManager: ActorRef, checkout: ActorRef) =
    Props(new PaymentFSM(method, orderManager, checkout))

  sealed trait Event
  case object PaymentConfirmed  extends Event
  case object PaymentReceived   extends Event

  sealed trait Command
  case object DoPayment extends Command

  sealed trait State
  case object WaitingForPayment extends State

}

class PaymentFSM(
  method: String,
  orderManager: ActorRef,
  checkout: ActorRef
) extends FSM[State, null] {

  startWith(WaitingForPayment, _)

  when(WaitingForPayment) {
    case Event(DoPayment, _) =>
      orderManager ! PaymentConfirmed
      checkout ! PaymentReceived
      stay()
  }
}
