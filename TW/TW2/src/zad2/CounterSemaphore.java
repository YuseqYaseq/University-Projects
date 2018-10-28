package zad2;

public class CounterSemaphore {

    public CounterSemaphore(int start, int limit) {
        this.counter = start;
        this.limit = limit;
    }

    synchronized void take() {
        while(counter == 0) {
            try {
                this.wait();
            } catch(InterruptedException e) {
                System.out.println(e.toString());
            }
        }

        counter--;
        this.notifyAll();
    }

    synchronized void release() {
        while(counter == limit) {
            try {
                this.wait();
            } catch(InterruptedException e) {
                System.out.println(e.toString());
            }
        }

        counter++;
        this.notifyAll();
    }

    private int counter;
    private int limit;

}
