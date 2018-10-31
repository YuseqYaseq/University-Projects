package zad2;

import java.util.Map;
import java.util.TreeMap;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

class Waiter {
    private boolean tableIsTaken = false;
    private boolean onePersonLeft = false;

    private Map<Integer, Condition> oneOfPairIsWaiting = new TreeMap<>();
    private Lock lock = new ReentrantLock();
    private Condition tableTaken = lock.newCondition();

    void takeTable(int pairNum) {
        lock.lock();
        try {
            if (oneOfPairIsWaiting.containsKey(pairNum)) {
                Condition condition = oneOfPairIsWaiting.get(pairNum);
                oneOfPairIsWaiting.remove(pairNum);

                if (tableIsTaken) {
                    tableTaken.await();
                }

                condition.signal();
            } else {
                Condition condition = lock.newCondition();
                oneOfPairIsWaiting.put(pairNum, condition);
                condition.await();
            }
        } catch(Exception e) {
            System.err.println(e.toString());
            e.printStackTrace();
        } finally {
            lock.unlock();
        }
    }

    void leaveTable() {
        lock.lock();
        if (onePersonLeft) {
            tableIsTaken = false;
            onePersonLeft = false;

            tableTaken.signal();
        } else {
            onePersonLeft = true;
        }
        lock.unlock();
    }
}
