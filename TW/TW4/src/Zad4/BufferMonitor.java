package Zad4;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class BufferMonitor {

    private int availableElems;
    private int elemsToConsume;
    private Lock accessLock;
    private Condition firstProd;
    private Condition restProd;
    private Condition firstCons;
    private Condition restCons;

    private List<Integer> elemsInFirstProd;
    private List<Integer> elemsInFirstCons;

    BufferMonitor(int buffSize) {
        accessLock = new ReentrantLock();
        elemsToConsume = 0;
        availableElems = buffSize;
        firstProd = accessLock.newCondition();
        restProd = accessLock.newCondition();
        firstCons = accessLock.newCondition();
        restCons = accessLock.newCondition();
        elemsInFirstProd = new ArrayList<>();
        elemsInFirstCons = new ArrayList<>();
    }

    long produce(int i, int elems) {
        long time = System.nanoTime();
        try {
            accessLock.lock();
            if(!elemsInFirstProd.isEmpty()) {
                restProd.await();
            }

            elemsInFirstProd.add(i);
            while(availableElems < elems) {
                firstProd.await();
            }

            time = System.nanoTime() - time;
            System.out.println("prod " + i + " creates " + elems + " elems.");
            System.out.println("available: " + availableElems + "; toConsume: " + elemsToConsume);
            elemsToConsume += elems;
            availableElems -= elems;

            elemsInFirstProd.remove(new Integer(i));

            if(elemsInFirstProd.isEmpty())
                restProd.signalAll();

            firstCons.signal();

        } catch (Exception e) {
            System.err.println(e.toString());
            e.printStackTrace();
        } finally {
            accessLock.unlock();
        }
        return time;
    }

    long consume(int i, int elems) {
        long time = System.nanoTime();
        try {
            accessLock.lock();
            if(!elemsInFirstCons.isEmpty()) {
                restCons.await();
            }

            elemsInFirstCons.add(i);
            while(elemsToConsume < elems) {
                firstCons.await();
            }

            time = System.nanoTime() - time;

            System.out.println("cons " + i + " takes " + elems + " elems.");
            System.out.println("available: " + availableElems + "; toConsume: " + elemsToConsume);
            elemsToConsume -= elems;
            availableElems += elems;

            elemsInFirstCons.remove(new Integer(i));

            if(elemsInFirstCons.isEmpty())
                restCons.signalAll();

            firstProd.signal();

        } catch (Exception e) {
            System.err.println(e.toString());
            e.printStackTrace();
        } finally {
            accessLock.unlock();
        }
        return time;
    }

    //private Lock accessLock;
    //private Condition PierwszyProd;

}
