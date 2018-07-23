#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/times.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>




clock_t start;
clock_t finish;
struct tms tmsstart;
struct tms tmsfinish;

void startClock() {
    start = times(&tmsstart);
}

void finishClock() {
    long ticks = sysconf(_SC_CLK_TCK);
    finish = times(&tmsfinish);
    printf("Czas rzeczywisty: %f\n",
		(finish - start) / (double)ticks);
}


bool isNumber(char* string){
    int n;
    int value;
    char c;
    n = sscanf(string, "%d%c", &value, &c);
    if(n != 1) return false;
    return true;
}

//brzydkie a szybkie
int digits(int n){
    if(n < 10)          return 1;
    if(n < 100)         return 2;
    if(n < 1000)        return 3;
    if(n < 10000)       return 4;
    if(n < 100000)      return 5;
    if(n < 1000000)     return 6;
    if(n < 10000000)    return 7;
    if(n < 100000000)   return 8;
    if(n < 1000000000)  return 9;
    return 10;
}
