package zad2;

public class Consumer implements Runnable {

    private static final int ILOSC = 10;

    private Buffer buffer;
    private int num;

    public Consumer(Buffer buffer, int num) {
        this.buffer = buffer;
        this.num = num;
    }

    public void run() {

        for(int i = 0;  i < ILOSC; i++) {
            String message = buffer.get();
            System.out.println("Consumer " + num + ": " + message);
        }

    }
}
