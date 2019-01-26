package Zad3;

import java.util.ArrayList;
import java.util.List;

public class Main {

    private static final int NUM_OF_THREADS = 10;
    private static final int M = 20;
    private static final int BUFF_SIZE = 2 * M;

    private static List<Producer> producers = new ArrayList<>();
    private static List<Consumer> consumers = new ArrayList<>();
    private static List<Thread> threads = new ArrayList<>();
    private static BufferMonitor monitor = new BufferMonitor(BUFF_SIZE);

    public static void main(String[] args) throws InterruptedException {

        for(int i = 0; i < NUM_OF_THREADS; ++i) {
            producers.add(new Producer(i, monitor, M));
            consumers.add(new Consumer(i, monitor, M));
            threads.add(new Thread(producers.get(i)));
            threads.add(new Thread(consumers.get(i)));
        }

        for(int i = 0; i < NUM_OF_THREADS * 2; ++i) {
            threads.get(i).start();
        }

        for(int i = 0; i < NUM_OF_THREADS * 2; ++i) {
            threads.get(i).join();
        }

    }
}
