#include <unistd.h>
#include <signal.h>

#include "lib.h"
#include "queue.h"

#define BARBER_READY ("barber_ready")
#define ACCESS_SEATS ("access_seats")
#define CUST_READY ("cust_ready")

#define CNAME ("customers")
#define QNAME ("queue")
#define QSIZE (sizeof(struct Queue) + sizeof(int))

sem_t* barberReady;
sem_t* accessWRSeats;
sem_t* custReady;
int* numOfCust;

int* numOfFreeWRSeats;
struct Queue* Data;

void onExit(int t){
    CloseSemaphore(barberReady);
    CloseSemaphore(accessWRSeats);
    CloseSemaphore(custReady);
    RemoveSemaphore(BARBER_READY);
    RemoveSemaphore(ACCESS_SEATS);
    RemoveSemaphore(CUST_READY);
    ReleaseSharedMem(numOfFreeWRSeats, QSIZE, QNAME);
    ReleaseSharedMem(numOfCust, sizeof(int), CNAME);
    exit(0);
}

void Init(int N){
    signal(SIGINT, onExit);
    signal(SIGTERM, onExit);
    
    barberReady = CreateSemaphore(BARBER_READY, 0);
    accessWRSeats = CreateSemaphore(ACCESS_SEATS, 1);
    custReady = CreateSemaphore(CUST_READY, 1);
    
    numOfCust = (int*)CreateSharedMem(CNAME, sizeof(int));
    numOfFreeWRSeats = (int*)CreateSharedMem(QNAME, QSIZE);
    
    *numOfCust = 0;
    *numOfFreeWRSeats = N;
    
    Data = (struct Queue*)(numOfFreeWRSeats+1);
    QInit(Data, N+1);
}

int main(int c, char* v[]){
    if(c < 2){
        printf("Uzycie programu: ./b N\n");
        printf("N - liczba siedzen w kolejce do golibrody.\n");
        return 0;
    }
    
    Init(atoi(v[1]));
    
    while(1){
        for(int i = 0; i < Data->size; ++i){
                printf("         Q[%d] = %d\n", i, Data->elems[i]);
            }
    
        Take(custReady);
        if((*numOfCust) == 0){
            Release(custReady);
            continue;
        }
        (*numOfCust)--;
        Release(custReady);
        
        Take(accessWRSeats);
        
        int cust_pid = QGet(Data);
        (*numOfFreeWRSeats)++;
        
        Release(barberReady);
        Release(accessWRSeats);
        
        //Work here
        //sleep(1);
        printf("Cutting %d.\n", cust_pid);
        
        
        kill(cust_pid, SIGUSR1);
        
    }
    onExit(0);
}

/*
sem_t* SemQ;
sem_t* SemB;
sem_t* SemT;
struct Queue* Data;
size_t N;

void onExit(int t){
    CloseSemaphore(SemQ);
    CloseSemaphore(SemB);
    CloseSemaphore(SemT);
    RemoveSemaphore(BARBER);
    RemoveSemaphore(QUEUE);
    RemoveSemaphore(BARBER_TEST);
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
    SemT = CreateSemaphore(BARBER_TEST, 1);
    
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
            //Take(SemT);
                Take(SemB);
                Take(SemB);
            //Release(SemT);
            printf("Waking up.\n");
        }
        Take(SemQ);
            printf("Q: in = %d, out = %d, size = %d.\n", Data->queueIn, Data->queueOut, Data->size);
            for(int i = 0; i < Data->size; ++i){
                printf("         Q[%d] = %d\n", i, Data->elems[i]);
            }
            int pid = QGet(Data);
        Release(SemQ);
        
        printf("Cutting %d.\n", pid);
        
        //Simulating doing job
        //sleep(1);
        
        printf("Stopping cutting %d.\n", pid);
        kill(pid, SIGUSR1);
    }
    
    onExit(0);
}

*/
















