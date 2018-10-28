package zad2;

import java.util.ArrayList;
import java.util.List;

public class Main {

    private static final int numOfBaskets = 10;
    private static final int numOfCustomers = 20;

    public static void main(String[] args) {
        Shop shop = new Shop(numOfBaskets);
        List<Thread> customers = new ArrayList<>();
        for(int i = 0; i < numOfCustomers; ++i) {
            customers.add(new Thread(new Customer(shop, i)));
        }

        for(int i = 0; i < numOfCustomers; ++i) {
            customers.get(i).start();
        }

        for(int i = 0; i < numOfCustomers; ++i) {
            try {
                customers.get(i).join();
            } catch(Exception e) {
                System.out.println(e.toString());
            }
        }

    }
}
