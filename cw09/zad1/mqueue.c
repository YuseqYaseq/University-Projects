#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>

#include "mqueue.h"

void QInit(struct MQueue* q, int size){
    q->size = size;
    q->queueIn = q->queueOut = 0;
    
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_NORMAL);
    pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
    
    int err;
    if((err = pthread_mutex_init(&(q->mutex), &attr))){
        fprintf(stderr, "Failed to initialize mutex!. Err = %d.\n", err);
        exit(-1);
    }
    
    pthread_condattr_t cattr;
    pthread_condattr_init(&cattr);
    pthread_condattr_setpshared(&cattr, PTHREAD_PROCESS_SHARED);
    pthread_cond_init(&(q->empty), &cattr);
    pthread_cond_init(&(q->full), &cattr);
    
}

int QPut(struct MQueue* q, char* e){
    //sem_wait(q->empty);
    //sem_wait(q->read);
    /*if(q->queueIn == ((q->queueOut -1 + q->size) % q->size)){
        sem_post(q->read);
        sem_post(q->full);
        return -1; //Queue full
    }*/
    
    pthread_mutex_lock(&(q->mutex));
    while(q->queueIn == ((q->queueOut -1 + q->size) % q->size)){
        pthread_cond_wait(&(q->full), &(q->mutex));
    }
    
    q->elems[q->queueIn] = e;
    q->queueIn = (q->queueIn + 1) % q->size;
    
    pthread_cond_signal(&(q->empty));
    pthread_mutex_unlock(&(q->mutex));
    
    //sem_post(q->read);
    //sem_post(q->full);
    return 0;
}

char* QGet(struct MQueue* q){
    //sem_wait(q->full);
    //sem_wait(q->read);
    
    pthread_mutex_lock(&(q->mutex));
    while(q->queueIn == q->queueOut){
        pthread_cond_wait(&(q->empty), &(q->mutex));
    }
    
    char* e = q->elems[q->queueOut];
    q->queueOut = (q->queueOut + 1) % q->size;
    
    pthread_cond_signal(&(q->full));
    pthread_mutex_unlock(&(q->mutex));
    
    //sem_post(q->read);
    //sem_post(q->empty);
    return e;
}

/*char* QTimedGet(struct SQueue* q, const struct timespec* timer){
    sem_timedwait(q->full, timer);
    sem_wait(q->read);
    char* e = q->elems[q->queueOut];
    q->queueOut = (q->queueOut + 1) % q->size;
    sem_post(q->read);
    sem_post(q->empty);
    return e;
}*/

char* QTryGet(struct MQueue* q){
    //sem_trywait(q->full);
    //if(errno == EAGAIN)return NULL;
    //sem_wait(q->read);
    
    pthread_mutex_lock(&(q->mutex));
    if(q->queueIn == q->queueOut){
        pthread_mutex_unlock(&(q->mutex));
        return NULL;
    }
    
    char* e = q->elems[q->queueOut];
    q->queueOut = (q->queueOut + 1) % q->size;
    
    
    //sem_post(q->read);
    //sem_post(q->empty);
    
    pthread_mutex_unlock(&(q->mutex));
    return e;
}

void QDel(struct MQueue* q){
    //sem_wait(sem);
    
    //sem_post(sem);
    /*sem_close(q->read);
    sem_close(q->empty);
    sem_close(q->full);
    sem_unlink(FILE_NAME_READ);
    sem_unlink(FILE_NAME_EMPTY);
    sem_unlink(FILE_NAME_FULL);*/
    
    pthread_mutex_destroy(&(q->mutex));
}

int QEmpty(struct MQueue* q){
    //sem_wait(q->read);
    pthread_mutex_lock(&(q->mutex));
    if(q->queueIn == q->queueOut){
        //sem_post(q->read);
        pthread_mutex_unlock(&(q->mutex));
        return 1;
    }
    //sem_post(q->read);
    pthread_mutex_unlock(&(q->mutex));
    return 0;
}




