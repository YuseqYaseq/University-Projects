

public class Main {

    private static final String GROUP_NAME = "name";

    public static void main(String[] args) throws Exception {
        System.setProperty("java.net.preferIPv4Stack","true");
        DistributedMap map = new DistributedMap(GROUP_NAME);
        map.print();
        map.put("a", 5);
        map.put("b", 9);
        map.print();
        Thread.sleep(1000 * 30);
    }
}
