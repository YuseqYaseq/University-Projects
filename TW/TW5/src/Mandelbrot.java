import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Executor;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
import javax.swing.JFrame;

public class Mandelbrot extends JFrame {

    private BufferedImage I;
    private static final int JEDEN_WATEK = 1;
    private static final int TYLE_SAMO = 4;
    private static final int DWA_RAZY_WIECEJ = 8;

    //1 watek, tyle samo zadan co watkow
    private long task1_1() throws InterruptedException {
        long time;

        //Jeden watek
        time = System.nanoTime();
        ExecutorService executor = Executors.newFixedThreadPool(JEDEN_WATEK);
        Task full = new Task(0, getWidth(), 0, getHeight(), I);
        executor.execute(full);

        executor.shutdown();
        while(!executor.awaitTermination(24L, TimeUnit.HOURS));
        time = System.nanoTime() - time;
        System.out.println("1 watek, tyle samo zadan co watkow: " + (time / 1000));
        return time;
    }

    //1 watek, 10x wiecej zadan co watkow
    private long task1_2() throws InterruptedException {
        long time;
        int num = 10 * JEDEN_WATEK;
        int tileLength = getWidth() / num;

        //Jeden watek
        time = System.nanoTime();
        ExecutorService executor = Executors.newFixedThreadPool(JEDEN_WATEK);
        for(int i = 0; i < num; ++i) {
            executor.execute(new Task(i * tileLength, (i + 1) * tileLength, 0, getHeight(), I));

        }

        executor.shutdown();
        while(!executor.awaitTermination(24L, TimeUnit.HOURS));
        time = System.nanoTime() - time;
        System.out.println("1 watek, 10x zadan co watkow: " + (time / 1000));
        return time;
    }

    //1 watek, kazde zadanie to jeden piksel
    private long task1_3() throws InterruptedException {
        long time;

        time = System.nanoTime();
        ExecutorService executor = Executors.newFixedThreadPool(JEDEN_WATEK);
        for(int i = 0; i < getHeight(); ++i) {
            for(int j = 0; j < getWidth(); ++j) {
                executor.execute(new Task(j, j+1, i, i+1, I));
            }
        }

        executor.shutdown();
        while(!executor.awaitTermination(24L, TimeUnit.HOURS));
        time = System.nanoTime() - time;
        System.out.println("1 watek, kazde zadanie to jeden piksel: " + (time / 1000));
        return time;
    }

    //tyle samo watkow co rdzeni, tyle samo zadan co watkow
    private long task2_1() throws InterruptedException {
        long time;
        int num = TYLE_SAMO;
        int tileLength = getWidth() / num;

        time = System.nanoTime();
        ExecutorService executor = Executors.newFixedThreadPool(TYLE_SAMO);
        for(int i = 0; i < num; ++i) {
            executor.execute(new Task(i * tileLength, (i + 1) * tileLength, 0, getHeight(), I));

        }

        executor.shutdown();
        while(!executor.awaitTermination(24L, TimeUnit.HOURS));
        time = System.nanoTime() - time;
        System.out.println("tyle samo watkow co rdzeni, tyle samo zadan co watkow: " + (time / 1000));
        return time;
    }

    //tyle samo watkow co rdzeni, 10x wiecej zadan co watkow
    private long task2_2() throws InterruptedException {
        long time;
        int num = TYLE_SAMO * 10;
        int tileLength = getWidth() / num;

        //Jeden watek
        time = System.nanoTime();
        ExecutorService executor = Executors.newFixedThreadPool(TYLE_SAMO);
        for(int i = 0; i < num; ++i) {
            executor.execute(new Task(i * tileLength, (i + 1) * tileLength, 0, getHeight(), I));

        }

        executor.shutdown();
        while(!executor.awaitTermination(24L, TimeUnit.HOURS));
        time = System.nanoTime() - time;
        System.out.println("tyle samo watkow co rdzeni, 10x zadan co watkow: " + (time / 1000));
        return time;
    }

    //tyle samo watkow co rdzeni, kazde zadanie to jeden piksel
    private long task2_3() throws InterruptedException {
        long time;

        time = System.nanoTime();
        ExecutorService executor = Executors.newFixedThreadPool(TYLE_SAMO);
        for(int i = 0; i < getHeight(); ++i) {
            for(int j = 0; j < getWidth(); ++j) {
                executor.execute(new Task(j, j+1, i, i+1, I));
            }
        }

        executor.shutdown();
        while(!executor.awaitTermination(24L, TimeUnit.HOURS));
        time = System.nanoTime() - time;
        System.out.println("tyle samo watkow co rdzeni, kazde zadanie to jeden piksel: " + (time / 1000));
        return time;
    }

    //dwa razy wiecej watkow co rdzeni, tyle samo zadan co watkow
    private long task3_1() throws InterruptedException {
        long time;
        int num = DWA_RAZY_WIECEJ;
        int tileLength = getWidth() / num;

        time = System.nanoTime();
        ExecutorService executor = Executors.newFixedThreadPool(DWA_RAZY_WIECEJ);
        for(int i = 0; i < num; ++i) {
            executor.execute(new Task(i * tileLength, (i + 1) * tileLength, 0, getHeight(), I));
        }

        executor.shutdown();
        while(!executor.awaitTermination(24L, TimeUnit.HOURS));
        time = System.nanoTime() - time;
        System.out.println("dwa razy wiecej watkow co rdzeni, tyle samo zadan co watkow: " + (time / 1000));
        return time;
    }

    //dwa razy wiecej watkow co rdzeni, 10x wiecej zadan co watkow
    private long task3_2() throws InterruptedException {
        long time;
        int num = DWA_RAZY_WIECEJ * 10;
        int tileLength = getWidth() / num;

        time = System.nanoTime();
        ExecutorService executor = Executors.newFixedThreadPool(DWA_RAZY_WIECEJ);
        for(int i = 0; i < num; ++i) {
            executor.execute(new Task(i * tileLength, (i + 1) * tileLength, 0, getHeight(), I));
        }

        executor.shutdown();
        while(!executor.awaitTermination(24L, TimeUnit.HOURS));
        time = System.nanoTime() - time;
        System.out.println("dwa razy wiecej watkow co rdzeni, 10x zadan co watkow: " + (time / 1000));
        return time;
    }

    //dwa razy wiecej watkow co rdzeni, kazde zadanie to jeden piksel
    private long task3_3() throws InterruptedException {
        long time;

        time = System.nanoTime();
        ExecutorService executor = Executors.newFixedThreadPool(DWA_RAZY_WIECEJ);
        for(int i = 0; i < getHeight(); ++i) {
            for(int j = 0; j < getWidth(); ++j) {
                executor.execute(new Task(j, j+1, i, i+1, I));
            }
        }

        executor.shutdown();
        while(!executor.awaitTermination(24L, TimeUnit.HOURS));
        time = System.nanoTime() - time;
        System.out.println("dwa razy wiecej watkow co rdzeni, kazde zadanie to jeden piksel: " + (time / 1000));
        return time;
    }

    public Mandelbrot() throws InterruptedException {
        super("Mandelbrot Set");
        setBounds(100, 100, 800, 600);
        setResizable(false);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        I = new BufferedImage(getWidth(), getHeight(), BufferedImage.TYPE_INT_RGB);
        long[][] times = new long[3][3];
        for(int i = 0; i < 5; ++i) {
            times[0][0] += task1_1() / 1000;
            times[0][1] += task1_2() / 1000;
            times[0][2] += task1_3() / 1000;
            times[1][0] += task2_1() / 1000;
            times[1][1] += task2_2() / 1000;
            times[1][2] += task2_3() / 1000;
            times[2][0] += task3_1() / 1000;
            times[2][1] += task3_2() / 1000;
            times[2][2] += task3_3() / 1000;
        }

        int i_min = -1;
        int j_min = -1;
        long min = Long.MAX_VALUE;
        long max = 0;
        for(int i = 0; i < 3; ++i) {
            for(int j = 0; j < 3; ++j) {
                if(times[i][j] < min) {
                    min = times[i][j];
                    i_min = i;
                    j_min = j;
                }
            }
        }
        min /= 5;
        System.out.println("Najlepszy średni wynik dla " + i_min + " " + j_min + ": " + min);
    }

    @Override
    public void paint(Graphics g) {
        g.drawImage(I, 0, 0, this);
    }

    public static void main(String[] args) throws InterruptedException {
        new Mandelbrot().setVisible(true);
    }
}