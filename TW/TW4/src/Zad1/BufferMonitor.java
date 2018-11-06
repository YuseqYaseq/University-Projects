package Zad1;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class BufferMonitor {

    private int[] elemsAhead;
    private List<Lock> locks;
    private List<Condition> conditions;

    BufferMonitor(int numOfThreads, int buffSize) {
        locks = new ArrayList<>();
        conditions = new ArrayList<>();
        elemsAhead = new int[numOfThreads];
        for(int i = 0; i < numOfThreads; ++i) {
            elemsAhead[i] = 0;
            locks.add(new ReentrantLock());
            conditions.add(locks.get(i).newCondition());
        }
        elemsAhead[0] = buffSize;
    }

    void take(int i) {
        try {
            locks.get(i).lock();
            while (elemsAhead[i] == 0) {
                conditions.get(i).await();
            }
            elemsAhead[i]--;
        } catch(Exception e) {
            System.err.println(e.toString());
            e.printStackTrace();
        } finally {
            locks.get(i).unlock();
        }
    }

    void release(int i) {
        int nextId = (i + 1) % elemsAhead.length;
        try {
            locks.get(nextId).lock();
            elemsAhead[nextId]++;
            conditions.get(nextId).signal();
        } catch (Exception e) {
            System.err.println(e.toString());
            e.printStackTrace();
        } finally {
            locks.get(nextId).unlock();
        }
    }
}
