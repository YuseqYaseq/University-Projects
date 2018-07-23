#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>

#define USER_SIGNAL SIGRTMIN

int itime;
bool showProcEnding;

void receive(){

    //printf("Dziecko otrzymalo sygnal!\n");
    
    union sigval signal;
    signal.sival_int = itime;
    
    if(sigqueue(getppid(), rand() % (SIGRTMAX-(SIGRTMIN + 1)) + (SIGRTMIN + 1), signal))
        printf("Sigqueue fail. Blad nr %i.\n", errno);
    if(showProcEnding)printf("Proces o PID %i konczy dzialanie. T = %i.\n", getpid(), itime);
    exit(0);
}

int main(int c, char* v[]){
    
    showProcEnding = atoi(v[1]);
    
    signal(USER_SIGNAL, receive);
    srand(time(NULL));
    itime = rand() % 11;
    
    sigset_t sset;
    sigemptyset(&sset);
    sigaddset(&sset, USER_SIGNAL);
    
    sleep(itime);
    
    union sigval signal;
    signal.sival_int = getpid();
    if(sigqueue(getppid(), USER_SIGNAL, signal))
        printf("Sigqueue fail. Blad nr %i.\n", errno);
    pause();
    
    return 0;
}
