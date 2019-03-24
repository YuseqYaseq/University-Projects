

public class Main {

    private static final String GROUP_NAME = "name";
    private static final int NUM = 5;

    public static void main(String[] args) throws Exception {
        System.setProperty("java.net.preferIPv4Stack","true");
        DistributedMap[] map = new DistributedMap[NUM];
        for(int i = 0; i < NUM; ++i) {
            map[i] = new DistributedMap(GROUP_NAME);
            //map[i].put(Integer.toString(i), i);
        }

        for(int i = 0; i < NUM; ++i) {
            map[i].put(Integer.toString(i), i);
        }

        Thread.sleep(1000 * 10);
        for(int i = 0; i < NUM; ++i) {
            System.out.println(map[i].get(Integer.toString(NUM - 1 - i)));
        }

        System.out.println("\n\n");
        for(int i = 0; i < NUM; ++i) {
            System.out.println(i + ": " + map[3].get(Integer.toString(i)));
        }
    }
}
