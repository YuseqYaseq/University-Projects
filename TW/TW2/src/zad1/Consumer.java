package zad1;

public class Consumer implements Runnable{

    private static final int ILOSC = 10;

    private BinarySemaphore semaphore_modify;
    private Buffer buffer;

    public Consumer(BinarySemaphore modify, Buffer buffer) {
        this.semaphore_modify = modify;
        this.buffer = buffer;
    }

    public void run() {
        for(int i = 0; i < ILOSC; ++i) {
            semaphore_modify.take();
            if(buffer.value == 0) {
                semaphore_modify.release();
                i--;
                continue;
            }
            buffer.value--;
            System.out.println("consumer: value = " + buffer.value);
            semaphore_modify.release();
        }
    }
}