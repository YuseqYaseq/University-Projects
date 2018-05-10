#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

#include "lib.h"
#include "queue.h"

int size = 500;
int s = 3;
struct Queue* data;

void onExit(int t){

}

void finished(int x){
    s--;
    printf("Finishing. Need %d more cuts.\n", s);
    if(!s){
        printf("Leaving the barber's.\n");
        exit(0);
    }
}

int main(int c, char* v[]){
    
    signal(SIGUSR1, finished);
    //signal(SIGINT, finished);

    key_t key = CreateKey("newkey.txt", 4);
    int semid = GetSemaphores(key);
    int shmid = GetSharedMem(key);
    data = (struct Queue*)GetMemPointer(shmid);
    //printf("%d\n%d\n%d\n", data->size, data->queueIn, data->queueOut);
    printf("Entering the barber's. My pid is %d.\n", getpid());
    while(1){
        //printf("1\n");
        Add(semid, QUEUE_ID, -1);
        int e = 0;
        if(QEmpty(data)) e = 1;
        int r = QPut(data, getpid());
        //printf("2\n");
        Add(semid, QUEUE_ID, 1);
        if(r == -1){
            printf("Queue full! Leaving the barber's.\n");
            exit(0);
        }else if(IsZero(semid, BARBER_ID)){
            printf("Waking up the barber.\n");
            //printf("3\n");
            Add(semid, BARBER_ID, 2);
        }
        printf("4\n");
        pause();
    }
}


























