import org.apache.zookeeper.KeeperException;
import org.apache.zookeeper.ZooKeeper;

import java.util.List;
import java.util.function.BiConsumer;

public class Utils {

    public static final String DELIMITER = "/";

    public static void applyToTree(ZooKeeper client, String path, BiConsumer<String, Integer> c,
                                   int indent, boolean onlyThisLevel) throws InterruptedException, KeeperException {
        List<String> zkNodes = client.getChildren(path, true);
        for (String node : zkNodes) {
            c.accept(node, indent);
            String nextPath = path;
            if(!path.equals(DELIMITER)) nextPath += DELIMITER;
            nextPath += node;
            if(!onlyThisLevel)
                applyToTree(client, nextPath, c, indent+1, false);
        }
    }

    public static String getNodeName(String fullPath) {
        String[] list = fullPath.split(DELIMITER);
        return list[list.length - 1];
    }
}
