#include <unistd.h>
#include <signal.h>

#include "lib.h"
#include "queue.h"

#define BARBER ("semaphore1")
#define QUEUE ("semaphore2")
#define BARBER_TEST ("semaphore3")

sem_t* SemQ;
sem_t* SemB;
sem_t* SemT;
struct Queue* Data;
int s;
int pid;

void onExit(int t){
    CloseSemaphore(SemQ);
    CloseSemaphore(SemB);
    ReleaseSharedMem(Data, sizeof(struct Queue), QUEUE);
    exit(0);
}

void finished(int x){
    s--;
    printf("%d: Finishing. Need %d more cuts.\n", pid, s);
    if(!s){
        printf("%d: Leaving the barber's.\n", pid);
        onExit(0);
    }
}


int main(int c, char* v[]){
    if(c < 3){
        printf("Uzycie programu: ./c N S\n");
        printf("N - liczba klientow do stworzenia.\n");
        printf("S - liczba strzyzen dla klienta.\n");
        return 0;
    }
    signal(SIGUSR1, finished);
    
    SemQ = GetSemaphore(QUEUE);
    SemB = GetSemaphore(BARBER);
    SemT = CreateSemaphore(BARBER_TEST, 1);
    
    Data = (struct Queue*)GetSharedMem(QUEUE, sizeof(struct Queue));
    int N = atoi(v[1]);
    s = atoi(v[2]);
    
    for(int i = 0; i < N; ++i){
        if(fork() == 0){
            pid = getpid();
            printf("%d: Entering the barber's.\n", pid);
            while(1){
                Take(SemQ);
                    int r = QPut(Data, pid);
                Release(SemQ);
                
                printf("%d: Entering queue.\n", pid);
                if(r == -1){
                    printf("%d: Queue full! Leaving the barber's.\n", pid);
                    onExit(0);
                }else{
                    Take(SemT);
                        if(GetValue(SemB) == 0){
                        Release(SemB);
                        Release(SemB);
                        printf("%d: Waking up the barber.\n", pid);
                        }
                    Release(SemT);
                }
                pause();
            }
            break;
        }
    }
    
    onExit(0);
}


















