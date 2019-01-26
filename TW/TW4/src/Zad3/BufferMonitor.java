package Zad3;

import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.SynchronousQueue;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class BufferMonitor {

    private int availableElems;
    private int elemsToConsume;
    private Lock accessLock;
    private Condition emptyBuffer;
    private Condition elemsReadyToConsume;
    private Queue<Integer> producerQueue;
    private Queue<Integer> consumerQueue;

    BufferMonitor(int buffSize) {
        accessLock = new ReentrantLock();
        elemsToConsume = 0;
        availableElems = buffSize;
        emptyBuffer = accessLock.newCondition();
        elemsReadyToConsume = accessLock.newCondition();
        producerQueue = new LinkedList<>();
        consumerQueue = new LinkedList<>();
    }

    long produce(int i, int elems) {
        long time = System.nanoTime();
        try {
            accessLock.lock();
            producerQueue.add(i);
            while(availableElems < elems || !(new Integer(i).equals(producerQueue.peek()))) {
                emptyBuffer.await();
            }
            time = System.nanoTime() - time;

            producerQueue.poll();
            availableElems -= elems;
            elemsToConsume += elems;
            System.out.println(i + " producer creates " + elems + " elements.");
            System.out.println("availableElems = " + availableElems + "; elemsToConsume = " + elemsToConsume);
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
            consumerQueue.add(i);
            while(elemsToConsume < elems || !(new Integer(i).equals(consumerQueue.peek()))) {
                elemsReadyToConsume.await();
            }
            time = System.nanoTime() - time;

            consumerQueue.poll();
            availableElems += elems;
            elemsToConsume -= elems;
            System.out.println(i + " consumer takes " + elems + " elements.");
            System.out.println("availableElems = " + availableElems + "; elemsToConsume = " + elemsToConsume);
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

    //private Lock accessLock;
    //private Condition PierwszyProd;

}
