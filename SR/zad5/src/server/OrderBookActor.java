package server;

import akka.actor.AbstractActor;
import akka.actor.ActorRef;
import akka.actor.Props;
import akka.event.Logging;
import akka.event.LoggingAdapter;
import utils.Request;
import utils.Response;

public class OrderBookActor extends AbstractActor {

    private final LoggingAdapter log = Logging.getLogger(getContext().getSystem(), this);

    private ActorRef sender;

    @Override
    public Receive createReceive() {
        return receiveBuilder()
                .match(Request.class, req -> {
                    sender = getSender();
                    ActorRef bookFinder = getContext().actorOf(Props.create(FindBookActor.class));
                    bookFinder.tell(req, getSelf());
                })
                .match(Response.class, res -> {
                    if(!res.getContent().equals("not_found"))
                        res.setContent("Book ordered!");


                    sender.tell(res, getSelf());
                })
                .matchAny(o -> log.info("received unknown message"))
                .build();
    }
}
