#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#include "squeue.h"

//Size of buffers created by producers/consumed by consumers
#define BUFF_SIZE (5)

//Semaphore queue for produced items
struct SQueue q;
//N
int size;

pthread_t* producers = 0;
pthread_t* consumers = 0;

//P
int prod_num;
//K
int cons_num;
//L
int L;
//information mode
//0 - basic
//1 - full
int inf_mode;
//nk
int NK;
//search mode '<' - take smaller than '>' - take bigger than '=' take equal
char search_mode;

//file name
char* file_name;
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
        if(inf_mode)printf("Producer: read line %s.\n", buffer);
        QPut(&q, buffer);
    }
}

void* consume(void* args){
    while(1){
        sem_wait(consumers_locked);
        char* buf = QGet(&q);
        sem_post(consumers_locked);
        int size = strlen(buf);
        int write = 0;
        switch(search_mode){
        case '<':
            if(L < size) write = 1;
            break;
        case '>':
            if(L > size) write = 1;
            break;
        case '=':
            if(L == size) write = 1;
            break;
        };
        if(inf_mode){
            if(write)printf("Consumer: read line %s.\n", buf);
            else printf("Consumer: line \"%s\" didn't match search mode!\n", buf);
        }else if(write)printf("%s", buf);
        free(buf);
    }
}

void* consume_special(void* args){
    sem_wait(finished);
    while(1){
        char* buf = QTryGet(&q);
        if(buf == NULL){
        //if(QEmpty(&q)){
            while(1){
                //if(inf_mode)printf("Producers read the entire file. Waiting for consumers.\n");
                int val;
                sem_getvalue(consumers_locked, &val);
                if(val == 0)break;
            }
            if(inf_mode)printf("Consumers consumed the entire file.\n");
            onExit(0);
        }else{
            int size = strlen(buf);
            int write = 0;
            switch(search_mode){
            case '<':
                if(L < size) write = 1;
                break;
            case '>':
                if(L > size) write = 1;
                break;
            case '=':
                if(L == size) write = 1;
                break;
            };
            if(inf_mode){
                if(write)printf("Consumer_s: read line %s.\n", buf);
                else printf("Consumer_s: line \"%s\" didn't match search mode!\n", buf);
            }else if(write)printf("%s", buf);
            free(buf);
            //QPut(&q, buf);
        }
    }
}

int main(int c, char* v[]){
    
    //Clear used semaphores in case of an interruption and leftover semaphores 
    sem_close(file_lock);
    sem_unlink(lock_name);
    sem_close(finished);
    sem_unlink(finished_name);
    sem_close(consumers_locked);
    sem_unlink(consumers_name);
    QDel(&q);

    if(c < 9){
        printf("Uzycie programu: ./main P K N F L S I NK\n");
        printf("P - liczba producentow\n");
        printf("K - liczba konsumentow\n");
        printf("N - rozmiar kolejki danych\n");
        printf("F - nazwa pliku do pobrania dla producentow\n");
        printf("L - rozmiar danych dla konsumentow\n");
        printf("S - tryb wyszukiwania ('<' - mniejsze od, '>' - wieksze od, '=' - rowne)\n");
        printf("I - tryb wypisywania informacji (0 - tryb uproszczony, 1 - tryb opisowy)\n");
        printf("NK - czas dzialania procesu\n");
    }
    prod_num = atoi(v[1]);
    cons_num = atoi(v[2]);
    size = atoi(v[3]);
    file_name = v[4];
    L = atoi(v[5]);
    search_mode = v[6][0];
    inf_mode = atoi(v[7]);
    NK = atoi(v[8]);
    
    if(NK){
        signal(SIGALRM, onExit);
    }
    
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
    
    for(int i = 1; i < cons_num+1; ++i){
        pthread_create(&consumers[i], NULL, &consume, NULL);
    }
    pthread_create(&consumers[0], NULL, &consume_special, NULL);
    
    if(NK)alarm(NK);
    
    for(int i = 0; i < prod_num; ++i){
        pthread_join(producers[i], NULL);
    }
    for(int i = 0; i < cons_num+1; ++i){
        pthread_join(consumers[i], NULL);
    }
    
    onExit(5);
}






