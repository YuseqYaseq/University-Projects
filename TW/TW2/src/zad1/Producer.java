package zad1;

public class Producer implements Runnable {

    private static final int ILOSC = 10;

    private BinarySemaphore semaphore_modify;
    private Buffer buffer;

    public Producer(BinarySemaphore modify, Buffer buffer) {
        this.semaphore_modify = modify;
        this.buffer = buffer;
    }

    public void run() {
        for(int i = 0; i < ILOSC; ++i) {
            semaphore_modify.take();
            buffer.value++;
            System.out.println("Producer: value = " + buffer.value);
            semaphore_modify.release();
        }
    }
}
