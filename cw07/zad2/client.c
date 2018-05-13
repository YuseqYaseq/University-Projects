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

int N;
int s;

int cut;

void onExit(int t){
    CloseSemaphore(barberReady);
    CloseSemaphore(accessWRSeats);
    CloseSemaphore(custReady);
    CloseSharedMem(numOfFreeWRSeats, QSIZE);
    CloseSharedMem(numOfCust, sizeof(int));
    exit(0);
}

void finished(int t){
    printf("%d: Hair cut!\n", getpid());
    cut = 1;
}

void Init(){
    signal(SIGUSR1, finished);
    
    barberReady = GetSemaphore(BARBER_READY);
    accessWRSeats = GetSemaphore(ACCESS_SEATS);
    custReady = GetSemaphore(CUST_READY);
    
    numOfFreeWRSeats = (int*)GetSharedMem(QNAME, QSIZE);
    Data = (struct Queue*)(numOfFreeWRSeats+1);
    
    numOfCust = (int*)GetSharedMem(CNAME, sizeof(int));
}

int main(int c, char* v[]){
    if(c < 3){
        printf("Uzycie programu: ./c N S\n");
        printf("N - liczba klientow do stworzenia.\n");
        printf("S - liczba strzyzen dla klienta.\n");
        return 0;
    }
    N = atoi(v[1]);
    s = atoi(v[2]);
    
    Init();
    
    for(int i = 0; i < N; ++i){
        if(fork() == 0){
            cut = 0;
            Take(accessWRSeats);
            printf("%d: %d wolnych miejsc.\n", getpid(), (*numOfFreeWRSeats));
            if((*numOfFreeWRSeats) > 0){
                
                Take(custReady);
                
                (*numOfCust)++;
                (*numOfFreeWRSeats)--;
                QPut(Data, getpid());
                
                printf("   l\n");
                Release(custReady);
                Release(accessWRSeats);
                
                Take(barberReady);
                while(cut == 0);
            }else{
                //no free seats
                Release(accessWRSeats);
                printf("No free seats!\n");
            }
            
            break;
        }
    }
    onExit(0);
}


/*
void goToB(){
    used = 0;
    printf("%d: Take(SemQ = %d)\n", pid, GetValue(SemQ));
    Take(SemQ);
        printf("   %d: Entering CRIT 1\n", pid);
        int r = QPut(Data, pid);
        printf("   %d: Leaving CRIT 1\n", pid);
    Release(SemQ);
    
    printf("%d: Entering queue.\n", pid);
    if(r == -1){
        printf("%d: Queue full! Leaving the barber's.\n", pid);
        onExit(0);
    }else{
        printf("%d: Take(SemT = %d)\n", getpid(), GetValue(SemT));
        Take(SemT);
            printf("   %d: Entering CRIT 2\n", pid);
            printf("%d: Wake up the barber? SemB = %d\n", getpid(), GetValue(SemB));
            if(GetValue(SemB) == 0){
                Release(SemB);
                while(GetValue(SemB) != 0);
                Release(SemB);
                printf("%d: Waking up the barber.\n", pid);
            }
            printf("   %d: Leaving CRIT 2\n", pid);
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
    SemT = /*CreateSemaphore(BARBER_TEST, 0);*//*GetSemaphore(BARBER_TEST);
    
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

*/















