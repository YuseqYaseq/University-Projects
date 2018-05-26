#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>

#define FILE_NAME_READ  ("file1")
#define FILE_NAME_EMPTY ("file2")
#define FILE_NAME_FULL  ("file3")

#include "squeue.h"

void QInit(struct SQueue* q, int size){
    q->size = size;
    q->queueIn = q->queueOut = 0;
    q->read = sem_open(FILE_NAME_READ, O_CREAT | O_RDWR, 0666, 1);
    if(q->read == SEM_FAILED){
        fprintf(stderr, "Failed to create a semaphore. Error code: %d.\n", errno);
        exit(0);
    }
    q->empty = sem_open(FILE_NAME_EMPTY, O_CREAT | O_RDWR, 0666, size);
    if(q->empty == SEM_FAILED){
        fprintf(stderr, "Failed to create a semaphore. Error code: %d.\n", errno);
        exit(0);
    }
    q->full = sem_open(FILE_NAME_FULL, O_CREAT | O_RDWR, 0666, 0);
    if(q->full == SEM_FAILED){
        fprintf(stderr, "Failed to create a semaphore. Error code: %d.\n", errno);
        exit(0);
    }
}

int QPut(struct SQueue* q, char* e){
    sem_wait(q->empty);
    sem_wait(q->read);
    if(q->queueIn == ((q->queueOut -1 + q->size) % q->size)){
        sem_post(q->read);
        sem_post(q->full);
        return -1; //Queue full
    }
    
    q->elems[q->queueIn] = e;
    q->queueIn = (q->queueIn + 1) % q->size;
    sem_post(q->read);
    sem_post(q->full);
    return 0;
}

char* QGet(struct SQueue* q){
    sem_wait(q->full);
    sem_wait(q->read);
    char* e = q->elems[q->queueOut];
    q->queueOut = (q->queueOut + 1) % q->size;
    sem_post(q->read);
    sem_post(q->empty);
    return e;
}

char* QTimedGet(struct SQueue* q, const struct timespec* timer){
    sem_timedwait(q->full, timer);
    sem_wait(q->read);
    char* e = q->elems[q->queueOut];
    q->queueOut = (q->queueOut + 1) % q->size;
    sem_post(q->read);
    sem_post(q->empty);
    return e;
}

char* QTryGet(struct SQueue* q){
    sem_trywait(q->full);
    if(errno == EAGAIN)return NULL;
    sem_wait(q->read);
    char* e = q->elems[q->queueOut];
    q->queueOut = (q->queueOut + 1) % q->size;
    sem_post(q->read);
    sem_post(q->empty);
    return e;
}

void QDel(struct SQueue* q){
    //sem_wait(sem);
    
    //sem_post(sem);
    sem_close(q->read);
    sem_close(q->empty);
    sem_close(q->full);
    sem_unlink(FILE_NAME_READ);
    sem_unlink(FILE_NAME_EMPTY);
    sem_unlink(FILE_NAME_FULL);
}

int QEmpty(struct SQueue* q){
    sem_wait(q->read);
    if(q->queueIn == q->queueOut){
        sem_post(q->read);
        return 1;
    }
    sem_post(q->read);
    return 0;
}
