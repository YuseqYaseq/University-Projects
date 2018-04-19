#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <sys/time.h>

#include "clock.h"

#define ARGSIZE 12

int main(int argc, char* argv[]){
    if(argc < 4 || !isNumber(argv[2]) || !isNumber(argv[3])){
        printf("Uzycie programu:\n");
        printf("main arg1 arg2 arg3\n");
        printf("arg1 - sciezka do pliku wsadowego\n");
        printf("arg2 - ograniczenie czasu wykonywania w sekundach\n");
        printf("arg3 - ograniczenie rozmiaru pamieci wirtualnej w megabajtach\n");
        return 0;
    }
    FILE* f = fopen(argv[1], "r");
    if(!f){
        printf("Nie odnaleziono pliku!\n");
        return -1;
    }
    int sign = 100;
    int prev_stime_sec = 0;
    int prev_utime_sec = 0;
    int prev_stime_us = 0;
    int prev_utime_us = 0;
    int prev_mem = 0;
    while(sign != EOF){//arg[0] - filename
        char* arg[ARGSIZE] = {NULL};
        arg[0] = (char*)malloc(sizeof(char) * 256);
        int size;
        if(fscanf(f, "%s", arg[0]) == EOF)break;
        for(size = 1; size < ARGSIZE-1; ++size){
            sign = fgetc(f);
            if(sign == (int)'\n' || sign == EOF)break;
            arg[size] = (char*)malloc(sizeof(char) * 100);
            if(fscanf(f, "%s", arg[size]));
        }
        if(!vfork()){
            struct rlimit lim;
            getrlimit(RLIMIT_CPU, &lim);
            lim.rlim_max = atoi(argv[2]);
            lim.rlim_cur = atoi(argv[2]);
            setrlimit(RLIMIT_CPU, &lim); 
            
            getrlimit(RLIMIT_AS, &lim);
            lim.rlim_max = 1000000*atoi(argv[3]);
            lim.rlim_cur = 1000000*atoi(argv[3]);
            setrlimit(RLIMIT_AS, &lim);
            
            execvp(arg[0], arg);
            return -1;
        }
        int status;
        wait(&status);
        if(WIFEXITED(status)){
            if(WEXITSTATUS(status)){
                printf("\nPolecenie %s zakonczylo sie bledem %i!\n", arg[0], WEXITSTATUS(status));
                exit(-1);
            }
        }
        struct rusage r;
        getrusage(RUSAGE_CHILDREN, &r);
        r.ru_stime.tv_sec  -= prev_stime_sec;
        r.ru_utime.tv_sec  -= prev_utime_sec;
        r.ru_stime.tv_usec -= prev_stime_us;
        r.ru_utime.tv_usec -= prev_utime_us;
        r.ru_maxrss -= prev_mem;
        printf("Czas systemowy: %f\n", ((double)r.ru_stime.tv_sec*1000000.0+(double)r.ru_stime.tv_usec)/1000000.0);
        printf("Czas usera: %f\n", ((double)r.ru_utime.tv_sec*1000000.0+(double)r.ru_utime.tv_usec)/1000000.0);
        printf("Zaalokowana pamiec: %ldkB\n", r.ru_maxrss);
        for(int i = 0; i < size; ++i){
            //printf("%s\n", arg[i]);
            free(arg[i]);
        }
        getrusage(RUSAGE_CHILDREN, &r);
        prev_stime_sec = r.ru_stime.tv_sec;
        prev_utime_sec = r.ru_utime.tv_sec;
        prev_stime_us  = r.ru_stime.tv_usec;
        prev_utime_us  = r.ru_utime.tv_usec;
        prev_mem = r.ru_maxrss;
        
        printf("\n");
    }
    
    
    
    return 0;
}





