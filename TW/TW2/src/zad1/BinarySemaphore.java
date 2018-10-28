package zad1;

public class BinarySemaphore {
    synchronized void take() {
        while(taken) {
            try {
                this.wait();
            } catch(InterruptedException e) {
                System.out.println(e.toString());
                e.printStackTrace();
            }
        }
        taken = true;
    }

    synchronized void release() {
        taken = false;
        this.notify();
    }

    boolean taken = false;

}
