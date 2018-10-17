package zad1;

import java.util.ArrayList;
import java.util.List;

public class Main {

    private static final int NUM = 10;

    public static void main(String[] args) {
        Buffer buf = new Buffer();
        BinarySemaphore modifySem = new BinarySemaphore();
        List<Thread> threads1 = new ArrayList<Thread>();
        List<Thread> threads2 = new ArrayList<Thread>();
        for(int i = 0; i < NUM; ++i) {
            threads1.add(new Thread(new Producer(modifySem, buf)));
            threads2.add(new Thread(new Consumer(modifySem, buf)));
        }
        for(int i = 0; i < NUM; ++i) {
            threads1.get(i).start();
            threads2.get(i).start();
        }

        try {
            for(int i = 0; i < NUM; ++i) {
                threads1.get(i).join();
                threads2.get(i).join();
            }
        } catch(Exception e) {
            e.printStackTrace();
            System.err.println(e.getMessage());
        }
    }

}