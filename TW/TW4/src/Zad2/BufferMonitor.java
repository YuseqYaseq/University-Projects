package Zad2;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class BufferMonitor {

    private int availableElems;
    private int elemsToConsume;
    private Lock accessLock;
    private Condition emptyBuffer;
    private Condition elemsReadyToConsume;

    BufferMonitor(int buffSize) {
        accessLock = new ReentrantLock();
        elemsToConsume = 0;
        availableElems = buffSize;
        emptyBuffer = accessLock.newCondition();
        elemsReadyToConsume = accessLock.newCondition();
    }

    long produce(int i, int elems) {
        long time = System.nanoTime();
        try {
            accessLock.lock();
            while(availableElems < elems) {
                emptyBuffer.await();
            }
            time = System.nanoTime() - time;

            availableElems -= elems;
            elemsToConsume += elems;
            //System.out.println(i + " producer creates " + elems + " elements.");
            //System.out.println("availableElems = " + availableElems + "; elemsToConsume = " + elemsToConsume);
            elemsReadyToConsume.signalAll();
            return time;

        } catch(Exception e) {
            System.err.println(e.toString());
            e.printStackTrace();
        } finally {
            accessLock.unlock();
        }
        return Long.MIN_VALUE;
    }

    long consume(int i, int elems) {
        long time = System.nanoTime();
        try {
            accessLock.lock();
            while(elemsToConsume < elems) {
                elemsReadyToConsume.await();
            }
            time = System.nanoTime() - time;

            availableElems += elems;
            elemsToConsume -= elems;
            //System.out.println(i + " consumer takes " + elems + " elements.");
            //System.out.println("availableElems = " + availableElems + "; elemsToConsume = " + elemsToConsume);
            emptyBuffer.signalAll();
            return time;
        } catch (Exception e) {
            System.err.println(e.toString());
            e.printStackTrace();
        } finally {
            accessLock.unlock();
        }
        return Long.MIN_VALUE;
    }
}
