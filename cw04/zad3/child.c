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

int l = 0;

void sig1(int v, siginfo_t* info, void* ucont){
    l++;
    printf("Dziecko odebralo sygnal. %i/?\n", l);
    kill(getppid(), info->si_signo);
}

void sig2(int v, siginfo_t* info, void* ucont){
    printf("Dziecko odebralo sygnal zakonczenia.\n");
    exit(0);
}

int main(){
    struct sigaction act;
    act.sa_sigaction = sig1;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act, NULL);
    sigaction(USER_SIG1, &act, NULL);
    
    act.sa_sigaction = sig2;
    sigaction(SIGUSR2, &act, NULL);
    sigaction(USER_SIG2, &act, NULL);
    while(true)pause();
}
