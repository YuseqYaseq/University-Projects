import java.awt.image.BufferedImage;

public class Task implements Runnable {

    private int startX;
    private int finishX;
    private int startY;
    private int finishY;
    private static final int MAX_ITER = 570;
    private static final double ZOOM = 150;
    private BufferedImage I;
    private double zx, zy, cX, cY, tmp;

    Task(int startX, int finishX, int startY, int finishY, BufferedImage image) {
        this.startX = startX;
        this.finishX = finishX;
        this.startY = startY;
        this.finishY = finishY;
        this.I = image;
    }

    @Override
    public void run() {
        for (int y = startY; y < finishY; y++) {
            for (int x = startX; x < finishX; x++) {
                zx = zy = 0;
                cX = (x - 400) / ZOOM;
                cY = (y - 300) / ZOOM;
                int iter = MAX_ITER;
                while (zx * zx + zy * zy < 4 && iter > 0) {
                    tmp = zx * zx - zy * zy + cX;
                    zy = 2.0 * zx * zy + cY;
                    zx = tmp;
                    iter--;
                }
                I.setRGB(x, y, iter | (iter << 8));
            }
        }
    }
}
