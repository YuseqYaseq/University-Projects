package zad2;

/**
 * Created by student11 on 2018-10-03.
 */
class Buffer {
    private String s;
    private boolean isEmpty = true;

    synchronized void put(String elem) {
        while(!isEmpty){
            try {
                this.wait();
            } catch(Exception e) {
                e.printStackTrace();
                System.out.println(e.getMessage());
                return;
            }
        }
        s = elem;
        isEmpty = false;
        this.notifyAll();
    }

    synchronized String get() {
        while(isEmpty) {
            try {
                this.wait();
            } catch(Exception e) {
                e.printStackTrace();
                System.out.println(e.getMessage());
                return null;
            }
        }
        isEmpty = true;
        this.notifyAll();
        return s;
    }
}
