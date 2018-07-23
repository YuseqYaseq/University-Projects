#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int c, char* v[]){
    if(c < 2){
        printf("Uzycie programu:\n");
        printf("./master s\n");
        printf("s - sciezka do potoku nazwanego ktory zostanie utworzony.\n");
    }
    //char tab[100] = {0};
    mkfifo(v[1], S_IWGRP | S_IWOTH);
    //sleep(5);
    FILE* fd = fopen(v[1], "r");
    int c2;
    while ((c2 = getc(fd)) != EOF)
        putchar(c2);
    fclose(fd);
}
