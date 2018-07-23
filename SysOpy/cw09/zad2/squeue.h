#ifndef _S_QUEUE_H_
#define _S_QUEUE_H_

#include <semaphore.h>

struct SQueue{
    char* elems[500];
    int size;
    int queueIn;
    int queueOut;
    
    sem_t* read;
    sem_t* empty;
    sem_t* full;
};

void QInit(struct SQueue* q, int size);
int QPut(struct SQueue* q, char* e);
char* QGet(struct SQueue* q);
//Timed QGet version. Returns after time specifed in timer.
char* QTimedGet(struct SQueue* q, const struct timespec* timer);
//Try to take QGet version. Leaves if Queue is empty.
char* QTryGet(struct SQueue* q);
void QDel(struct SQueue* q);
int QEmpty(struct SQueue* q);

#endif
