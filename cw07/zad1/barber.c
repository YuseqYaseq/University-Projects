#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#include "queue.h"

//sem1:
//  0 - barber is working
//  <0 - barber is sleeping
//sem2: 
//  0 - client can join the queue
// <0 - client will be able to join the queue soon 

key_t k;
int semid;
int shmid;
struct Queue* data;
int numOfSems = 2;
//Number of seats
int N = 5;

void onExit(int t){
    ReleaseSemaphores(semid);
    QDel(data);
    
    shmctl(shmid, IPC_RMID, NULL);
    
    exit(0);
}

int main(int c, char* v[]){
    if(c < 2){
        printf("Uzycie programu: ./b N\n");
        printf("N - liczba siedzen w kolejce do golibrody.\n");
        return 0;
    }
    signal(SIGINT, onExit);
    signal(SIGTERM, onExit);
    
    //printf("%ld\n%ld\n%ld\n", sizeof(struct Queue), sizeof(int), sizeof(int*));
    N = atoi(v[1]);
    k = CreateKey("newkey.txt", 4);
    semid = CreateSemaphores(k, numOfSems);
    shmid = CreateSharedMem(k, sizeof(struct Queue));
    data = (struct Queue*)GetMemPointer(shmid);
    QInit(data, N);
    Add(semid, QUEUE_ID, 1);
    Add(semid, BARBER_ID, 1);
    while(1){
        Add(semid, QUEUE_ID, -1);
        int v = QEmpty(data);
        Add(semid, QUEUE_ID, 1);
        if(v == 1){
            printf("Falling asleep.\n");
            Add(semid, BARBER_ID, -1);
            Add(semid, BARBER_ID, -1);
            printf("Waking up.\n");
        }
        Add(semid, QUEUE_ID, -1);
        printf("Q: in = %d, out = %d, size = %d.\n", data->queueIn, data->queueOut, data->size);
        int pid = QGet(data);
        Add(semid, QUEUE_ID, 1);
        printf("Cutting %d.\n", pid);
        
        //Simulating doing job
        //sleep(3);
        
        printf("Stopping cutting %d.\n", pid);
        kill(pid, SIGUSR1);
    }
    
    
    onExit(0);
}













