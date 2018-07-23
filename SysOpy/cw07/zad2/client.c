#include <unistd.h>
#include <signal.h>

#include "lib.h"
#include "queue.h"

#define QUEUE ("sem1")
#define BARBER ("sem2")
#define BARBER_TEST ("sem3")

sem_t* SemQ;
sem_t* SemB;
sem_t* SemT;
struct Queue* Data;
size_t N;

int over;
int used;
int pid;
int s;

void onExit(int t){
    CloseSemaphore(SemQ);
    CloseSemaphore(SemB);
    CloseSemaphore(SemT);
    CloseSharedMem(Data, sizeof(struct Queue));
    exit(0);
}


void goToB(){
    used = 0;
    Take(SemQ);
        int r = QPut(Data, pid);
    Release(SemQ);
    
    printf("%d: Entering queue.\n", pid);
    if(r == -1){
        printf("%d: Queue full! Leaving the barber's.\n", pid);
        onExit(0);
    }else{
        Take(SemT);
            printf("%d: Wake up the barber? SemB = %d\n", getpid(), GetValue(SemB));
            if(GetValue(SemB) == 0){
                Release(SemB);
                while(GetValue(SemB) != 0);
                Release(SemB);
                printf("%d: Waking up the barber.\n", pid);
            }
        Release(SemT);
    }
    while(used == 0);
    if(!over)goToB();
    onExit(0);
}

void finished(int x){
    s--;
    printf("%d: Finishing. Need %d more cuts.\n", pid, s);
    used = 1;
    if(!s){
        printf("%d: Leaving the barber's.\n", pid);
        over = 1;
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
    SemT = /*CreateSemaphore(BARBER_TEST, 0);*/GetSemaphore(BARBER_TEST);
    
    Data = (struct Queue*)GetSharedMem(QUEUE, sizeof(struct Queue));
    int N = atoi(v[1]);
    s = atoi(v[2]);
    
    for(int i = 0; i < N; ++i){
        if(fork() == 0){
            pid = getpid();
            printf("%d: Entering the barber's.\n", pid);
            goToB();
            exit(0);
        }
    }
    
    onExit(0);
}















