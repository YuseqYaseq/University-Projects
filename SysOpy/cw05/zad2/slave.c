#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#include "clock.h"

#define BUFF_SIZE 40

int main(int c, char* v[]){
    srand(time(NULL));
    if(c < 3 || !isNumber(v[2])){
        printf("Uzycie programu:\n");
        printf("./slave s N\n");
        printf("s - sciezka do potoku nazwanego do ktorego beda zapisywane dane.\n");
        printf("N - ile razy dane beda zapisane.\n");
    }
    printf("PID: %i\n", getpid());
    int N = atoi(v[2]);
    FILE* fd = fopen(v[1], "a");
    for(int i = 0; i < N; ++i){
        char d[BUFF_SIZE] = {0};
        FILE* date = popen("date", "r");
        fgets(d, BUFF_SIZE, date);
        pclose(date);
        fprintf(fd, "%sPID: %i\n", d, getpid());
        sleep(rand() % 4 + 2);
    }
    fclose(fd);
}
