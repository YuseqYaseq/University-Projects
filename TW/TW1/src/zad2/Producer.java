package zad2;

public class Producer implements Runnable {

    private static final int ILOSC = 10;

    private Buffer buffer;
    private int num;

    public Producer(Buffer buffer, int num) {
        this.buffer = buffer;
        this.num = num;
    }

    public void run() {

        for(int i = 0;  i < ILOSC; i++) {
            buffer.put("message " + i);
            System.out.println("Producer " + num + ": message " + i);
        }

    }
}
