package server;

import akka.actor.AbstractActor;
import akka.event.Logging;
import akka.event.LoggingAdapter;
import utils.Request;
import utils.Response;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;

public class DBSearchActor extends AbstractActor {

    private final LoggingAdapter log = Logging.getLogger(getContext().getSystem(), this);
    private String dbAddress;

    @Override
    public Receive createReceive() {
        return receiveBuilder()
                .match(Request.class, req-> {
                    BufferedReader br = new BufferedReader(new FileReader(new File(dbAddress)));
                    String title;
                    int value = 0;
                    do {
                        title = br.readLine();
                        if(title == null)
                            break;
                        value = Integer.valueOf(br.readLine());
                    } while(!title.equals(req.getBookName()));
                    if(title != null) {
                        getSender().tell(new Response("found " + title, value), getSelf());
                    } else {
                        throw new BookNotFoundException(req.getBookName() + " not found");
                    }

                })
                .match(String.class, s -> dbAddress = s)
                .matchAny(o -> log.info("received unknown message"))
                .build();
    }
}
