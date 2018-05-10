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
int pid;
struct Queue* data;

void onExit(int t){
    
}

void finished(int x){
    s--;
    printf("%d: Finishing. Need %d more cuts.\n", pid, s);
    if(!s){
        printf("%d: Leaving the barber's.\n", pid);
        exit(0);
    }
}

int main(int c, char* v[]){
    if(c < 3){
        printf("Uzycie programu: ./c N S\n");
        printf("N - liczba klientow do stworzenia.\n");
        printf("S - liczba strzyzen dla klienta.\n");
    }
    signal(SIGUSR1, finished);
    //signal(SIGINT, kill);
    
    key_t key = CreateKey("newkey.txt", 4);
    int semid = GetSemaphores(key);
    int shmid = GetSharedMem(key);
    data = (struct Queue*)GetMemPointer(shmid);
    int N = atoi(v[1]);
    s = atoi(v[2]);
    for(int i = 0; i < N; ++i){
        if(fork() == 0){
            pid = getpid();
            printf("%d: Entering the barber's.\n", pid);
            while(1){
                
                Add(semid, QUEUE_ID, -1);
                //int e = 0;
                int r = QPut(data, getpid());
                Add(semid, QUEUE_ID, 1);
                printf("%d: Entering queue.\n", pid);
                if(r == -1){
                    printf("%d: Queue full! Leaving the barber's.\n", pid);
                    exit(0);
                }else if(IsZero(semid, BARBER_ID)){
                    printf("%d: Waking up the barber.\n", pid);
                    //printf("3\n");
                    Add(semid, BARBER_ID, 2);
                }
                //printf("4\n");
                pause();
            }
            break;
        }
    }
    //pause();
}


























