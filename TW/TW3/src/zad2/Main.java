package zad2;

import java.util.ArrayList;
import java.util.List;

public class Main {

    public static void main(String[] args) {
        try {
            Waiter waiter = new Waiter();
            List<Thread> threads = new ArrayList<>();
            for (int i = 0; i < 50; i++) {
                Thread thread1 = new Thread(new Client(i, waiter));
                Thread thread2 = new Thread(new Client(i, waiter));
                threads.add(thread1);
                threads.add(thread2);
                thread1.start();
                thread2.start();
            }

            for (Thread t : threads) {
                t.join();
            }
        } catch (Exception e) {
            System.err.println(e.toString());
            e.printStackTrace();
        }
    }
}
