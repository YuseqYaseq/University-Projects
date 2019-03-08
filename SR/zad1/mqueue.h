#ifndef _M_QUEUE_H_
#define _M_QUEUE_H_

#include <pthread.h>
#include <string>

struct MQueue{
    std::string elems[500];
    int size;
    int queueIn;
    int queueOut;
    
    pthread_mutex_t mutex;
    pthread_cond_t empty;
    pthread_cond_t full;
};

void QInit(struct MQueue* q, int size);
int QPut(struct MQueue* q, std::string& e);
std::string QGet(struct MQueue* q);
//Try to take QGet version. Leaves if Queue is empty.
std::string QTryGet(struct MQueue* q);
void QDel(struct MQueue* q);
int QEmpty(struct MQueue* q);

#endif
