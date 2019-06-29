package client;

import akka.actor.ActorRef;
import akka.actor.ActorSystem;
import akka.actor.Props;
import com.typesafe.config.Config;
import com.typesafe.config.ConfigFactory;
import utils.Request;

import java.io.BufferedReader;
import java.io.File;
import java.io.InputStreamReader;

public class Client {

    public static void main(String[] args) throws Exception {

        // config
        File configFile = new File("./src/client/client.conf");
        Config config = ConfigFactory.parseFile(configFile);

        // create actor system & actors
        final ActorSystem system = ActorSystem.create("client", config);
        final ActorRef local = system.actorOf(Props.create(ClientActor.class), "local");

        // interaction
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        while(true) {
            String line = br.readLine();
            if(line.equals("q")) {
                break;
            } else if(line.startsWith("find")) {
                String bookName = line.split(" ")[1];
                local.tell(new Request(0, bookName), null);
            } else if(line.startsWith("order")) {
                String bookName = line.split(" ")[1];
                local.tell(new Request(1, bookName), null);
            } else if(line.startsWith("stream")) {
                String bookName = line.split(" ")[1];
                local.tell(new Request(2, bookName), null);
            }
        }

        system.terminate();
    }
}