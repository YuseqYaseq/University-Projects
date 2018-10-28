package zad2;

public class Shop {
    CounterSemaphore sem;

    public Shop(int numOfBaskets) {
        sem = new CounterSemaphore(numOfBaskets, numOfBaskets);
    }

    public void TakeBasket() {
        sem.take();
    }

    public void Leave() {
        sem.release();
    }
}
