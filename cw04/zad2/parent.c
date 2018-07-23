#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

#include "clock.h"

#define USER_SIGNAL SIGRTMIN

bool showCreation = false;
bool showRequest = false;
bool showAllowance = false;
bool showReceivedSig = false;
bool showProcEnding = false;

int* pids; //pids of all created children
int N; //these many children will be created
int K; //these many children will need to gather before permission is sent

int* CurP; //pids of these children which requested permission
int CurK = 0; //how many children are waiting for the permission
int HowManyFinished = 0; //how many children finished working

//SIGUSR1 - sygnał pozwolenia o działanie
//(SIGMIN;SIGMAX) - przedział sygnałów zakończenia działania
void fsig1(int v, siginfo_t* info, void* ucont){
    CurK++;
    if(showRequest)printf("Otrzymalem prosbe od procesu o PID %i.\n", info->si_pid);
    if(CurK < K){
        CurP[CurK-1] = info->si_pid;
    }else if(CurK > K){
        if(showAllowance)printf("Wysylam pozwolenie na dzialanie do procesu o PID %i.\n", info->si_pid);
        kill(info->si_pid, USER_SIGNAL);
    }else{
        //printf("Rozdzielam pozwolenia...\n");
        CurP[CurK-1] = info->si_pid;
        for(int i = 0; i < K; ++i){
            if(showAllowance)printf("Wysylam pozwolenie na dzialanie do procesu o PID %i.\n", CurP[i]);
            kill(CurP[i], USER_SIGNAL);
        }
    }
}

void fsig2(int v, siginfo_t* info, void* ucont){
    HowManyFinished++;
    if(showReceivedSig)printf("Sygnal %i od PID %i! T = %is!\n", info->si_signo, info->si_pid, info->si_value.sival_int);
    if(HowManyFinished == N){
        printf("Wszystkie dzieci zakonczyly dzialanie!\n");
        exit(0);
    }
}

void fint(int v){
    for(int i = 0; i < N; ++i){
        kill(pids[i], SIGKILL);
    }
    exit(0);
}


int main(int c, char* v[]){
    if(c<3 || !isNumber(v[1]) || !isNumber(v[2])){
        printf("Uzycie programu:\n");
        printf("parent N K T\n");
        printf("N - parent tworzy N potomków\n");
        printf("K - parent czeka na sygnał od K potomków\n");
        printf("T - dowolny ciag znakow zawierajacy litery od a do e. Ustala formatowanie tekstu.\n");
        return -1;
    }
    if(c>3){
        if(strchr(v[3], 'a'))showCreation = true;
        if(strchr(v[3], 'b'))showRequest = true;
        if(strchr(v[3], 'c'))showAllowance = true;
        if(strchr(v[3], 'd'))showReceivedSig = true;
        if(strchr(v[3], 'e'))showProcEnding = true;
    }
    N = atoi(v[1]);
    K = atoi(v[2]);
    struct sigaction act;
    act.sa_sigaction = fsig1;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;
    sigaction(USER_SIGNAL, &act, NULL);
    
    act.sa_sigaction = fsig2;
    for(int i = SIGRTMIN+1; i <= SIGRTMAX; ++i){
        sigaction(i, &act, NULL);
    }
    act.sa_flags = 0;
    act.sa_handler = fint;
    sigaction(SIGINT, &act, NULL);
    //finished setting signals...
    
    pids = (int*)malloc(N*sizeof(int));
    CurP = (int*)malloc(K*sizeof(int));
    
    for(int i = 0; i < N; ++i){
        if((pids[i] = fork())){
            if(showCreation)printf("Tworze proces potomny o PID %i.\n", pids[i]);
            sleep(1);
        }else{
            if(showProcEnding)
                execl("./child", "./child", "1", NULL);
            else
                execl("./child", "./child", "0", NULL);
        }
    }
    while(true)pause();
    free(pids);
    free(CurP);
}









