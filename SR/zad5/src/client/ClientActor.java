package client;

import akka.actor.AbstractActor;
import akka.event.Logging;
import akka.event.LoggingAdapter;
import utils.Request;
import utils.Response;

public class ClientActor extends AbstractActor {

    private final LoggingAdapter log = Logging.getLogger(getContext().getSystem(), this);

    @Override
    public Receive createReceive() {
        return receiveBuilder()
                .match(Request.class, req -> getContext().actorSelection("akka.tcp://book_store@127.0.0.1:2552/user/book_store").tell(req, getSelf()))
                .match(Response.class, res -> System.out.println("Received from server: " +
                        res.getContent() + ". Value: " + res.getValue() + "\n"))
                .matchAny(o -> log.info("received unknown message"))
                .build();
    }
}
