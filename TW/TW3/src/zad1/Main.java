package zad1;

import java.util.ArrayList;
import java.util.List;

public class Main {
    private static final int NUM_OF_PRINTERS = 10;
    private static final int NUM_OF_USERS = 50;

    public static void main(String[] args) {
        PrinterMonitor monitor = new PrinterMonitor(NUM_OF_PRINTERS);
        List<Thread> users = new ArrayList<>();
        for(int i = 0; i < NUM_OF_USERS; ++i) {
            users.add(new Thread(new PrinterUser(monitor, i)));
        }

        for(int i = 0; i < NUM_OF_USERS; ++i) {
            users.get(i).start();
        }

        for(int i = 0; i < NUM_OF_USERS; ++i) {
            try {
                users.get(i).join();
            } catch(Exception e) {
                System.err.println(e.toString());
                e.printStackTrace();
            }
        }


    }
}
