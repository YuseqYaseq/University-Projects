package Zad3;

import java.util.concurrent.ThreadLocalRandom;

public class Producer implements Runnable {
    private int id;
    private int M;
    private BufferMonitor monitor;
    private int numOfIterations;

    Producer(int id, BufferMonitor monitor, int M) {
        this.id = id;
        this.monitor = monitor;
        this.numOfIterations = 5;//10 * buffer.length;
        this.M = M;
    }

    @Override
    public void run() {
        for(int i = 0; i < numOfIterations; ++i) {
            int randomNum = ThreadLocalRandom.current().nextInt(0, M + 1);
            long time = monitor.produce(id, randomNum);
            //System.out.println("P " + randomNum + " " + time);
        }
    }
}
