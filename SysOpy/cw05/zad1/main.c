#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>
#include <sys/wait.h>

#define ARGSIZE 12

//#define DEBUG

int main(int argc, char* argv[]){
    if(argc < 2){
        printf("Nie podano nazwy pliku!\n");
        return -1;
    }
    FILE* f = fopen(argv[1], "r");
    if(!f){
        printf("Nie odnaleziono pliku!\n");
        return -1;
    }
    int sign = 100;
    bool isPrevPiped = false;
    int fd[2];
    int prev_read_desc;
    while(sign != EOF){//arg[0] - filename
        /******************/
        bool isPiped = false;
        pipe(fd);
        /******************/
        char* arg[ARGSIZE] = {NULL};
        arg[0] = (char*)malloc(sizeof(char) * 256);
        int size;
        if(fscanf(f, "%s", arg[0]) == EOF)break;
        for(size = 1; size < ARGSIZE-1 && !isPiped; ++size){
            sign = fgetc(f);
            if(sign == (int)'\n' || sign == EOF)break;
            arg[size] = (char*)malloc(sizeof(char) * 100);
            fscanf(f, "%s", arg[size]);
            if(arg[size][0] == '|'){
                isPiped = true;
                free(arg[size]);
                arg[size] = NULL;
                size--;
                #ifdef DEBUG
                fprintf(stderr,"mamy pipe i wywolujemy %s\n", arg[0]);
                #endif
                break;
            }
        }
        #ifdef DEBUG
        printf("%s\n", arg[0]);
        #endif
        if(!vfork()){
            if(isPiped) dup2(fd[1], STDOUT_FILENO);
            if(isPrevPiped) dup2(prev_read_desc, STDIN_FILENO);
            #ifdef DEBUG
            fprintf(stderr,"wywoluje %s isPiped:%i isPrevPiped:%i\n", arg[0], isPiped, isPrevPiped);
            #endif
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
        for(int i = 0; i < size; ++i){
            free(arg[i]);
        }
        isPrevPiped = isPiped;
        if(isPrevPiped)prev_read_desc = fd[0];
        close(fd[1]);
        if(!isPiped)printf("\n");
    }
    
    
    
    return 0;
}





