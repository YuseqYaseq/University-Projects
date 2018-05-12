#include <unistd.h>
#include <signal.h>

#include "lib.h"
#include "queue.h"

#define BARBER ("semaphore1")
#define QUEUE ("semaphore2")
#define BARBER_TEST ("semaphore3")

sem_t* SemQ;
sem_t* SemB;
struct Queue* Data;
size_t N;

void onExit(int t){
    CloseSemaphore(SemQ);
    CloseSemaphore(SemB);
    ReleaseSharedMem(Data, sizeof(struct Queue), QUEUE);
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
    
    SemQ = CreateSemaphore(QUEUE, 1);
    SemB = CreateSemaphore(BARBER, 1);
    
    N = atoi(v[1]);
    Data = (struct Queue*)CreateSharedMem(QUEUE, sizeof(struct Queue));
    QInit(Data, N);
    
    while(1){
        Take(SemQ);
            int v = QEmpty(Data);
        Release(SemQ);
        if(v == 1){
            //printf("%d\n", 
            printf("Falling asleep.\n");
            Take(SemT);
                Take(SemB);
                Take(SemB);
            Release(SemT);
            printf("Waking up.\n");
        }
        Take(SemQ);
            printf("Q: in = %d, out = %d, size = %d.\n", Data->queueIn, Data->queueOut, Data->size);
            int pid = QGet(Data);
        Release(SemQ);
        
        printf("Cutting %d.\n", pid);
        
        //Simulating doing job
        //sleep(2);
        
        printf("Stopping cutting %d.\n", pid);
        kill(pid, SIGUSR1);
    }
    
    onExit(0);
}


















