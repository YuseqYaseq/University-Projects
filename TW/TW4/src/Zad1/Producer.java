package Zad1;

public class Producer implements Runnable {
    private int[] buffer;
    private int id;
    private int position;
    private BufferMonitor monitor;
    private int numOfIterations;

    Producer(int id, int[] buffer, BufferMonitor monitor) {
        this.id = id;
        this.buffer = buffer;
        this.monitor = monitor;
        this.position = 0;
        this.numOfIterations = 5;//10 * buffer.length;
    }

    @Override
    public void run() {
        for(int i = 0; i < numOfIterations; ++i) {
            monitor.take(id);
            System.out.println(id + " writes at " + position + ".");
            buffer[position]++;
            monitor.release(id);
            position = (position + 1) % buffer.length;
        }
    }
}
