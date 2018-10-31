package zad2;

public class Client implements Runnable {
    private int id;
    private Waiter waiter;

    Client(int id, Waiter waiter) {
        this.id = id;
        this.waiter = waiter;
    }

    @Override
    public void run() {
        try {
            System.out.println(id + " waiting for the table.");
            waiter.takeTable(id);
            System.out.println(id + " eating.");
            waiter.leaveTable();
            System.out.println(id + " left the table");
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}
