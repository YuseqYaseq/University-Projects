package server;

import akka.actor.*;
import akka.event.Logging;
import akka.event.LoggingAdapter;
import akka.japi.pf.DeciderBuilder;
import scala.concurrent.duration.Duration;
import utils.Request;
import utils.Response;

import java.nio.file.NoSuchFileException;

public class FindBookActor extends AbstractActor {

    private final LoggingAdapter log = Logging.getLogger(getContext().getSystem(), this);

    private static final String DB_ADDRESS1 = "./src/server/db1.txt";
    private static final String DB_ADDRESS2 = "./src/server/db2.txt";

    private int results;
    private boolean resultFound;
    private ActorRef sender;
    private ActorRef dbSearcher1;
    private ActorRef dbSearcher2;

    @Override
    public AbstractActor.Receive createReceive() {
        return receiveBuilder()
                .match(Request.class, req -> {
                    results = 0;
                    resultFound = false;
                    sender = getSender();

                    dbSearcher1 = getContext().actorOf(Props.create(DBSearchActor.class));
                    dbSearcher2 = getContext().actorOf(Props.create(DBSearchActor.class));

                    dbSearcher1.tell(DB_ADDRESS1, getSelf());
                    dbSearcher2.tell(DB_ADDRESS2, getSelf());

                    dbSearcher1.tell(req, getSelf());
                    dbSearcher2.tell(req, getSelf());
                })
                .match(Response.class, res -> {
                    if(!resultFound) {
                        resultFound = true;
                        sender.tell(res, getSelf());
                        getContext().stop(dbSearcher1);
                        getContext().stop(dbSearcher2);
                    }
                })
                .matchAny(o -> log.info("received unknown message"))
                .build();
    }

    private SupervisorStrategy strategy = new OneForOneStrategy(1, Duration.create("1 minute"),
            DeciderBuilder
                    .match(BookNotFoundException.class, e -> {
                        if(results == 0) {
                            results++;
                        } else {
                            sender.tell(new Response("not_found", 0), getSelf());
                        }
                        return SupervisorStrategy.stop();
                    })
                    .matchAny(o -> SupervisorStrategy.restart())
                    .build());

    @Override
    public SupervisorStrategy supervisorStrategy() {
        return strategy;
    }


}