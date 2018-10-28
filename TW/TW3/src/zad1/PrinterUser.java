package zad1;

public class PrinterUser implements Runnable{
    private PrinterMonitor monitor;
    private int id;

    PrinterUser(PrinterMonitor monitor, int id) {
        this.monitor = monitor;
        this.id = id;
    }

    @Override
    public void run() {
        System.out.println(id + " user prepares documents.");
        int printerId = monitor.acquire();
        System.out.println(id + " user acquired printer " + printerId + ".");
        try {
            Thread.sleep(1000);
        } catch(Exception e) {
            System.err.println(e.toString());
            e.printStackTrace();
        }

        System.out.println(id + "user stopped using printer.");
        monitor.free(printerId);
    }
}
