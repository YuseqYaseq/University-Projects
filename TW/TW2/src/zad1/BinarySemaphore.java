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
        this.notifyAll();
    }

    synchronized void release() {
        while(!taken) {
            try {
                this.wait();
            } catch(InterruptedException e) {
                System.out.println(e.toString());
                e.printStackTrace();
            }
        }
        taken = false;
        this.notifyAll();
    }

    boolean taken = false;

}
