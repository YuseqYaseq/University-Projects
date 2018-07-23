#include <sys/times.h>
#include <string.h>
#include <stdbool.h>



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
    printf("Czas rzeczywisty: %f\nCzas usera: %f\nCzas systemowy: %f\n",
		(finish - start) / (double)ticks,
		(tmsfinish.tms_utime - tmsstart.tms_utime) / (double)ticks,
		(tmsfinish.tms_stime - tmsstart.tms_stime) / (double)ticks);
}


bool isNumber(char* string){
    int n;
    int value;
    char c;
    n = sscanf(string, "%d%c", &value, &c);
    if(n != 1) return false;
    return true;
}
