package server;

import akka.actor.*;
import akka.event.Logging;
import akka.event.LoggingAdapter;
import akka.japi.pf.DeciderBuilder;
import scala.concurrent.duration.Duration;
import utils.Request;
import utils.Response;

import java.nio.file.NoSuchFileException;

public class BookStoreActor extends AbstractActor {

    private final LoggingAdapter log = Logging.getLogger(getContext().getSystem(), this);

    BookStoreActor() {
        log.info(getSelf().path().toString());
    }

    @Override
    public Receive createReceive() {
        return receiveBuilder()
                .match(Request.class, this::requestResponse)
                .match(Response.class, res -> getSender().tell(res, getSelf()))
                .matchAny(o -> log.info("received unknown message"))
                .build();
    }

    private void requestResponse(Request req) {
        log.info("request");
        ActorRef actor;
        switch(req.getType()) {
            case 0:
                actor = getContext().actorOf(Props.create(FindBookActor.class));
                break;
            case 1:
                actor = getContext().actorOf(Props.create(OrderBookActor.class));
                break;
            default:
                throw new RuntimeException("Bad request type");
        }
        //req.setClient(actor);
        actor.tell(req, getSender());
    }

    private SupervisorStrategy strategy = new OneForOneStrategy(10, Duration.create("1 minute"),
            DeciderBuilder
                    .match(BookNotFoundException.class, e -> {
                        getSender().tell("Book not found!", getSelf());
                        return SupervisorStrategy.stop();
                    })
                    .matchAny(o -> SupervisorStrategy.restart())
                    .build());

    @Override
    public SupervisorStrategy supervisorStrategy() {
        return strategy;
    }
}
