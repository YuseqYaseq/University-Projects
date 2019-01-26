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
            System.out.println(System.nanoTime()/1000 + " " + id + " waiting for the table.");
            waiter.takeTable(id);
            System.out.println(System.nanoTime()/1000 + " " + id + " eating.");
            //Thread.sleep(100);

            waiter.leaveTable();
            System.out.println(System.nanoTime()/1000 + " " + id + " left the table");
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}
