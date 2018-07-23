#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

#include "clock.h"

void generate(int file, int records, int size){
    char* buf = (char*)malloc(size*sizeof(char));
    for(int n = 0; n < records; n++){
        for(int i = 0; i < size; ++i){
            buf[i] = rand() % 26 + 65;
        }
        write(file, buf, size);
    }
    free(buf);
}

void sys_sort(int file, int records, int size){
    char* cbuf = (char*)malloc(size*sizeof(char));
    char* current = (char*)malloc(size*sizeof(char));        
    
    for(int i = 0; i < records; i++)
    {
        lseek(file, size*i, SEEK_SET);
        read(file, cbuf, size);
        int smallest = i;
        for(int j = i+1; j < records; j++){
            read(file, current, 1);
            lseek(file, size - 1, SEEK_CUR);
            if((unsigned char)cbuf[0] > (unsigned char)current[0]){
                smallest = j;
                cbuf[0] = current[0];
            }
        }
        lseek(file, size*i, SEEK_SET);
        read(file, cbuf, size);
        lseek(file, size*smallest, SEEK_SET);
        read(file, current, size);
        
        lseek(file, size*i, SEEK_SET);
        write(file, current, size);
        lseek(file, size*smallest, SEEK_SET);
        write(file, cbuf, size);
    }
    free(cbuf);
    free(current);
}

void sys_copy(int file1, int file2, int records, int size){
    char* blok = (char*)malloc(size*sizeof(char));
    int liczyt;
    for(int i = 0; i < records; ++i){
        liczyt = read(file1,blok,size);
        write(file2,blok,liczyt);
    }
    free(blok);
}

void lib_sort(FILE* file, int records, int size){
    char* cbuf = (char*)malloc(size*sizeof(char));
    char* current = (char*)malloc(size*sizeof(char));        
    
    for(int i = 0; i < records; i++)
    {
        fseek(file, size*i, 0);
        fread(cbuf, sizeof(char), size, file);
        int smallest = i;
        for(int j = i+1; j < records; j++){
            fread(current, sizeof(char), 1, file);
            fseek(file, size - 1, 1);
            if((unsigned char)cbuf[0] > (unsigned char)current[0]){
                smallest = j;
                cbuf[0] = current[0];
            }
        }
        fseek(file, size*i, 0);
        fread(cbuf, sizeof(char), size, file);
        fseek(file, size*smallest, 0);
        fread(current, sizeof(char), size, file);
        
        fseek(file, size*i, 0);
        fwrite(current, sizeof(char), size, file);
        fseek(file, size*smallest, 0);
        fwrite(cbuf, sizeof(char), size, file);
    }
    free(cbuf);
    free(current);
}

void lib_copy(FILE* file1, FILE* file2, int records, int size){
    char* blok = (char*)malloc(size*sizeof(char));
    int liczyt;
    for(int i = 0; i < records; ++i){
        liczyt = fread(blok,sizeof(char),size,file1);
        fwrite(blok,sizeof(char),liczyt, file2);
    }
    free(blok);
}

//argv[1] - name of the function
//generate:
//argv[2] - name of the file
//argv[3] - number of records
//argv[4] - size
//sort:
//argv[2] - name of the file
//argv[3] - number of records
//argv[4] - size
//argv[5] - (sys|lib)
//copy:
//argv[2] - name of the file1
//argv[3] - name of the file2
//argv[4] - number of records
//argv[5] - size
//argv[6] - (sys|lib)
int main(int argc, char* argv[]){
    srand(time(NULL));
    int we,wy;
    FILE* cwe, *cwy;
    startClock();
    if(argc < 5){
        printf("Za mala liczba argumentow!");
        return -1;
    }
    if(!strcmp(argv[1],"generate")){
        if(argc < 5){
            printf("Za mala liczba argumentow!");
            return -1;
        }
        if(!isNumber(argv[3]) || !isNumber(argv[4])){
            printf("Niepoprawne argumenty!");
            return -1;
        }
        wy = open(argv[2],O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);
        if(wy < 0){
            printf("Nie udalo sie otworzyc pliku!");
            return -1;
        }
        generate(wy, atoi(argv[3]), atoi(argv[4]));
        close(wy);
    }else if(!strcmp(argv[1],"sort")){
        if(argc < 6){
            printf("Za mala liczba argumentow!");
            return -1;
        }
        if(!isNumber(argv[3]) || !isNumber(argv[4])){
            printf("Niepoprawne argumenty!");
            return -1;
        }
        if(!strcmp(argv[5], "sys")){
            we = open(argv[2], O_RDWR);
            if(we < 0){
                printf("Nie udalo sie otworzyc pliku!");
                return -1;
            }
            sys_sort(we, atoi(argv[3]), atoi(argv[4]));
            close(we);
        }else if(!strcmp(argv[5], "lib")){
            cwe = fopen(argv[2], "r+");
            if(!cwe){
                printf("Nie udalo sie otworzyc pliku!");
                return -1;
            }
            lib_sort(cwe, atoi(argv[3]), atoi(argv[4]));
            fclose(cwe);
        }else{
            printf("Niepoprawne argumenty!");
            return -1;
        }
    }else if(!strcmp(argv[1],"copy")){
        if(argc < 7){
            printf("Za mala liczba argumentow!");
            return -1;
        }
        if(!isNumber(argv[4]) || !isNumber(argv[5])){
            printf("Niepoprawne argumenty!");
            return -1;
        }
        if(!strcmp(argv[6], "sys")){
            we = open(argv[2], O_RDONLY);
            if(we < 0){
                printf("Nie udalo sie otworzyc pliku!");
                return -1;
            }
            wy = open(argv[3],O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);
            if(wy < 0){
                printf("Nie udalo sie otworzyc pliku!");
                return -1;
            }
            sys_copy(we, wy, atoi(argv[4]), atoi(argv[5]));
            close(we);
            close(wy);
        }else if(!strcmp(argv[6], "lib")){
            cwe = fopen(argv[2], "r");
            if(!cwe){
                printf("Nie udalo sie otworzyc pliku!");
                return -1;
            }
            cwy = fopen(argv[3], "w");
            lib_copy(cwe, cwy, atoi(argv[4]), atoi(argv[5]));
            fclose(cwe);
            fclose(cwy);
        }else{
            printf("Niepoprawne argumenty!");
            return -1;
        }
    }else{
        printf("Nieznana funckja! %s", argv[1]);
        return -1;
    }
    finishClock();
    return 0;
}
