#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

#include "clock.h"

#define USER_SIG1 (SIGRTMIN)
#define USER_SIG2 (SIGRTMIN+1)

#define PRINT_M1(X) printf("Rodzic  wyslal   sygnal. %i/%i\n", X, L)
#define PRINT_M2() printf("Rodzic  wyslal   sygnal koncowy.\n")
#define PRINT_M3(X) printf("Rodzic  odebral  sygnal. %i/%i\n", X, L)

int L;
int L2 = 0;
int Type;
int pid = 0;

void fsig1_sync(int v, siginfo_t* info, void* ucont){
    L2++;
    PRINT_M3(L2);
    if(L2 == L){
        PRINT_M2();
        kill(pid, SIGUSR2);
        exit(0);
    }else{
        PRINT_M1(L2+1);
        kill(pid, SIGUSR1);
    }
}

void fsig1_asyn(int v, siginfo_t* info, void* ucont){
    L2++;
    PRINT_M3(L2);
}

void fsig2(int v, siginfo_t* info, void* ucont){
    L2++;
    PRINT_M3(L2);
}

void fint(int v){
    if(pid != 0)kill(pid, SIGKILL);
    exit(0);
}


int main(int c, char* v[]){
    if(c<3 || !isNumber(v[1]) || !isNumber(v[2])){
        printf("Uzycie programu:\n");
        printf("parent L Type\n");
        printf("L - parent wysyła L sygnałów do potomka\n");
        printf("Type - Sposób wykonania programu\n");
        return -1;
    }
    
    L = atoi(v[1]);
    Type = atoi(v[2]);
    struct sigaction act;
    
    switch(Type){
    case 1:
        act.sa_sigaction = fsig1_asyn;
        sigemptyset(&act.sa_mask);
        act.sa_flags = SA_SIGINFO;
        sigaction(SIGUSR1, &act, NULL);
        break;
    case 2:
        act.sa_sigaction = fsig1_sync;
        sigemptyset(&act.sa_mask);
        act.sa_flags = SA_SIGINFO;
        sigaction(SIGUSR1, &act, NULL);
        break;
    case 3:
        act.sa_sigaction = fsig2;
        sigemptyset(&act.sa_mask);
        act.sa_flags = SA_SIGINFO;
        sigaction(USER_SIG1, &act, NULL);
        break;
    }
    act.sa_flags = 0;
    act.sa_handler = fint;
    sigaction(SIGINT, &act, NULL);
    //finished setting signals...
    
    if(!(pid = fork())){
        execl("./child", "./child", NULL);
    }
    sleep(1);
    if(Type == 1){
        for(int i = 0; i < L; ++i){
            PRINT_M1(i+1);
            kill(pid, SIGUSR1);
            //sleep(1);
        }
        PRINT_M2();
        kill(pid, SIGUSR2);
    }else if(Type == 2 && L > 0){
        PRINT_M1(1);
        kill(pid, SIGUSR1);
        while(true) pause();
    }else if(Type == 3){
        for(int i = 0; i < L; ++i){
            PRINT_M1(i+1);
            kill(pid, USER_SIG1);
            //sleep(1);
        }
        PRINT_M2();
        kill(pid, USER_SIG2);
    }
}









