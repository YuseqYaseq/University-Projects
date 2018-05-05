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

int size = 20;
int s = 1;
struct Queue* data;

void finished(int x){
    s--;
    printf("Finishing. s = %d.\n", s);
    exit(0);
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
    if(!IsZero(semid, BARBER_ID)){
        printf("Waking up the barber.\n");
        QPut(data, getpid());
        Add(semid, BARBER_ID, 1);
        printf("uh\n");
        pause();
        

    }else if(QPut(data, getpid()) == 0){
        pause();
    }else{
        printf("Queue full! Leaving the barber.\n");
        exit(0);
    }
}


























