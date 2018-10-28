package zad1;

import java.util.concurrent.locks.*;

public class PrinterMonitor {
    private Lock lock;
    private Lock[] printerXVacant;
    private Condition anyPrinterVacant;
    private int vacantPrinters;

    PrinterMonitor(int numOfPrinters) {
        lock = new ReentrantLock();
        printerXVacant = new Lock[numOfPrinters];
        anyPrinterVacant = lock.newCondition();
        vacantPrinters = numOfPrinters;
        for(int i = 0; i < numOfPrinters; ++i) {
            printerXVacant[i] = new ReentrantLock();
        }
    }

    int acquire() {
        lock.lock();
        try {
            while(vacantPrinters == 0) {
                anyPrinterVacant.await();
            }
            for(int i = 0; i < printerXVacant.length; ++i) {
                if(printerXVacant[i].tryLock()) {
                    vacantPrinters--;
                    return i;
                }
            }
        } catch (Exception e) {
            System.err.println(e.toString());
            e.printStackTrace();
        } finally {
            lock.unlock();
        }
        return -1;
    }

    void free(int id) {
        lock.lock();
        printerXVacant[id].unlock();
        vacantPrinters++;
        anyPrinterVacant.signal();
        lock.unlock();
    }
}
