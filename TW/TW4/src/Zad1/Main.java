package Zad1;

import java.util.ArrayList;
import java.util.List;

public class Main {

    private static final int NUM_OF_THREADS = 10;
    private static final int BUFF_SIZE = 50;

    private static int[] buffer = new int[BUFF_SIZE];

    private static List<Producer> producers = new ArrayList<>();
    private static List<Thread> threads = new ArrayList<>();
    private static BufferMonitor monitor = new BufferMonitor(NUM_OF_THREADS, BUFF_SIZE);

    public static void main(String[] args) throws InterruptedException {

        for(int i = 0; i < NUM_OF_THREADS; ++i) {
            producers.add(new Producer(i, buffer, monitor));
            threads.add(new Thread(producers.get(i)));
        }

        for(int i = 0; i < NUM_OF_THREADS; ++i) {
            threads.get(i).start();
        }

        for(int i = 0; i < NUM_OF_THREADS; ++i) {
            threads.get(i).join();
        }

        for(int i = 0; i < BUFF_SIZE; ++i) {
            System.out.print(buffer[i] + " ");
        }
    }
}
