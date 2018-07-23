#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define ARGSIZE 12

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
    while(sign != EOF){//arg[0] - filename
        char* arg[ARGSIZE] = {NULL};
        arg[0] = (char*)malloc(sizeof(char) * 256);
        int size;
        if(fscanf(f, "%s", arg[0]) == EOF)break;
        for(size = 1; size < ARGSIZE-1; ++size){
            sign = fgetc(f);
            if(sign == (int)'\n' || sign == EOF)break;
            arg[size] = (char*)malloc(sizeof(char) * 100);
            fscanf(f, "%s", arg[size]);
        }
        if(!vfork()){
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
            //printf("%s\n", arg[i]);
            free(arg[i]);
        }
        
        printf("\n");
    }
    
    
    
    return 0;
}





