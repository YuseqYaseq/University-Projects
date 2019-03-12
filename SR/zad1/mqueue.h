#ifndef _M_QUEUE_H_
#define _M_QUEUE_H_

#include <pthread.h>
#include "Message.h"

struct MQueue{
    Message elems[500];
    int size;
    int queueIn;
    int queueOut;
    
    pthread_mutex_t mutex;
    pthread_cond_t empty;
    pthread_cond_t full;
};

void QInit(struct MQueue* q, int size);
int QPut(struct MQueue* q, Message& e);
Message QGet(struct MQueue* q);
//Try to take QGet version. Leaves if Queue is empty.
Message QTryGet(struct MQueue* q);
void QDel(struct MQueue* q);
int QEmpty(struct MQueue* q);

#endif
