
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.List;
import java.util.function.BiConsumer;

import org.apache.zookeeper.KeeperException;
import org.apache.zookeeper.WatchedEvent;
import org.apache.zookeeper.ZooKeeper;
import org.apache.zookeeper.Watcher;

public class Main {

    private static ZooKeeper client;
    private static Process externalProgram = null;
    private static boolean isZ = false;
    private static String path;

    public static void main(String[] args) throws IOException, KeeperException, InterruptedException {

        String zkConnString = "127.0.0.1:2181";
        path = args[0];

        ZooKeeperWatcher zkWatcher = new ZooKeeperWatcher();
        client = new ZooKeeper(zkConnString, 1000000, zkWatcher);
        new Thread(Main::nudge).start();

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String line;
        do {
            line = br.readLine();
            if(line.startsWith("print")) {
                applyToRoot(Main::printTree);
            }
        } while(!line.startsWith("q"));

    }

    public static class ZooKeeperWatcher implements Watcher {

        @Override
        public void process(WatchedEvent event) {
            try {
                System.out.println(event.toString());
                //init
                if (event.getType().name().equals("None")) {
                    List<String> zkNodes = client.getChildren("/", true);
                    for (String node : zkNodes) {
                        if (node.equals("z")) {
                            isZ = true;
                        }
                    }
                }
                if (event.getType().name().equals("NodeChildrenChanged")) {
                    if(event.getPath().equals("/z")) {
                        System.out.println("Currently there are " + client.getChildren("/z", true).size() + " z children");
                        return;
                    }
                    if(!isZ) {
                        List<String> zkNodes = client.getChildren("/", true);
                        for (String node : zkNodes) {
                            if (node.equals("z")) {
                                try {
                                    externalProgram = new ProcessBuilder(path).start();
                                    isZ = true;
                                } catch (Exception e) {
                                    System.err.println("Failed to open the external program!");
                                    System.err.println(e.toString());
                                }
                            }
                        }
                    } else {
                        List<String> zkNodes = client.getChildren("/", true);
                        for (String node : zkNodes) {
                            if (node.equals("z"))
                                return;
                        }
                        isZ = false;
                        if(externalProgram != null) {
                            externalProgram.destroy();
                            externalProgram = null;
                        }
                    }
                }
                applyToRoot(Main::doNothing);
            } catch (Exception e) {
                System.err.println(e.toString());
            }

            //client.register(new ZooKeeperWatcher());
        }
    }

    private static void nudge() {
        while(true) {
            client.getState();
            try {
                Thread.sleep(5000);
            } catch(Exception e){}
        }
    }

    private static void doNothing(String s, int i) {

    }

    private static void applyToRoot(BiConsumer<String, Integer> c) throws InterruptedException, KeeperException {
        Utils.applyToTree(client, "/z", c, 0, false);
    }

    public static void printTree(String nodeName, int indent) {
        System.out.println("|".repeat(indent) + nodeName);
    }
}