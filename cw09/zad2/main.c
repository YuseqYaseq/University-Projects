#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

#include "squeue.h"

//Size of buffers created by producers/consumed by consumers
#define BUFF_SIZE (5)

//Semaphore queue for produced items
struct SQueue q;
int size = 100;

pthread_t* producers = 0;
pthread_t* consumers = 0;

int prod_num = 15;
int cons_num = 15;

char* file_name = "file.txt";
FILE* file;
char* lock_name = "lock2";
sem_t* file_lock;

//producers finished producing
char* finished_name = "finished";
sem_t* finished;

char* consumers_name = "consumers";
sem_t* consumers_locked;

void onExit(int z){
    sem_close(file_lock);
    sem_unlink(lock_name);
    sem_close(finished);
    sem_unlink(finished_name);
    sem_close(consumers_locked);
    sem_unlink(consumers_name);
    QDel(&q);
    exit(0);
}

void* produce(void* args){
    while(1){
        char* buffer = (char*)malloc(BUFF_SIZE*sizeof(char));
        int res;
        
        //Read the data
        sem_wait(file_lock);
        res = fread(buffer, sizeof(char), BUFF_SIZE, file);
        sem_post(file_lock);
        
        //If the entire file has been read
        if(res == 0){
            sem_post(finished);
            free(buffer);
            return NULL;
        }
        QPut(&q, buffer);
    }
}

void* consume(void* args){
    while(1){
        sem_wait(consumers_locked);
        char* buf = QGet(&q);
        sem_post(consumers_locked);
        printf("%s\n", buf);
        free(buf);
    }
}

void* consume_special(void* args){
    sem_wait(finished);
    while(1){
        
        char* buf = QTryGet(&q);
        if(buf == NULL){
            while(1){
                int val;
                sem_getvalue(consumers_locked, &val);
                if(val == 0)break;
            }
            onExit(0);
        }
        printf("%s\n", buf);
        free(buf);
    }
}

int main(int c, char* v[]){
    
    signal(SIGINT, onExit); 
    QInit(&q, size);
    
    file = fopen(file_name, "r");
    if(file == NULL){
        fprintf(stderr, "Failed to open file! Errno = %d.\n", errno);
        exit(0);
    }
    
    file_lock = sem_open(lock_name, O_RDWR | O_CREAT, 0666, 1);
    if(file_lock == SEM_FAILED){
        fprintf(stderr, "Failed to create a semaphore! Errno = %d.\n", errno);
        exit(0);
    }
    finished = sem_open(finished_name, O_RDWR | O_CREAT, 0666, 0);
    if(finished == SEM_FAILED){
        fprintf(stderr, "Failed to create a semaphore! Errno = %d.\n", errno);
        exit(0);
    }
    consumers_locked = sem_open(consumers_name, O_RDWR | O_CREAT, 0666, cons_num);
    
    producers = (pthread_t*)malloc(prod_num*sizeof(pthread_t));
    consumers = (pthread_t*)malloc((cons_num+1)*sizeof(pthread_t));
    
    for(int i = 0; i < prod_num; ++i){
        pthread_create(&producers[i], NULL, &produce, NULL);
    }
    pthread_create(&consumers[0], NULL, &consume_special, NULL);
    for(int i = 1; i < cons_num+1; ++i){
        pthread_create(&consumers[i], NULL, &consume, NULL);
    }
    
    for(int i = 0; i < prod_num; ++i){
        pthread_join(producers[i], NULL);
    }
    for(int i = 0; i < cons_num; ++i){
        pthread_join(consumers[i], NULL);
    }
    
    onExit(5);
}






