package zad2;

public class Customer implements Runnable {
    private Shop shop;
    private int id;

    public Customer(Shop shop, int id) {
        this.shop = shop;
        this.id = id;
    }

    public void goToShop() {
        shop.TakeBasket();
        System.out.println("Customer " + id + " goes to the shop");
    }

    public void leaveShop() {
        System.out.println("Customer " + id + " leaves the shop");
        shop.Leave();
    }

    public void run() {
        try {
            goToShop();
            Thread.sleep(3000);
            leaveShop();
        } catch(Exception e) {
            System.out.println(e.toString());
        }
    }
}
