#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/times.h>
#include <unistd.h>

#include "library.h"

clock_t start;
clock_t finish;
tms tmsstart;
tms tmsfinish;

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


//argv[1] - 1 - tablica statyczna, 0 - tablica dynamiczna
//argv[2] - rozmiar tablicy
//argv[3..] - kolejne rządane operacje
//alloc [size] [index] - zaalokuj w tablicy size-elementowy blok pod indeksem index
//free [index] - zwalnia blok pod indeksem index
//find [b] [c] - zwraca indeks bloku którego suma elementów jest najbliższa wartosci elementu o indeksie [b][c]
//print [index] - wypisuje index
int main(int argc, char* argv[]) {
    if(argc < 2){
        printf("Niewystarczajaca liczba argumentow!");
        return 1;
    }
    srand(time(NULL));
    startClock();
    if(argv[1][0] == '1'){ //create static table
        stab t;
        t.psize = atoi(argv[2]);
        for(int i = 3; i < argc; i++){
            if(!strcmp(argv[i],"alloc")){
	        int size = atoi(argv[i+1]);
	        int index = atoi(argv[i+2]);
	        printf("Alokuje blok pod indeksem %i o rozmiarze %i...\n",index, size);
	        t.allocateBlock(size, index);
		for(int j = 0; j < size; ++j)
		    t.p[index][j] = rand() % 24 + 67;
		i += 2;
	    }else if(!strcmp(argv[i],"free")){
        	int index = atoi(argv[i+1]);
                printf("Zwalniam pamiec pod indeksem %i...\n", index);
                t.freeBlock(index);
		i++;
	    }else if(!strcmp(argv[i],"find")){
		int b = atoi(argv[i+1]);
		int c = atoi(argv[i+2]);
		printf("Znaleziony indeks dla elementu o indeksie [%i][%i] - %i\n", b, c, t.findBlockClosestTo(b,c));
		i += 2;
	    }else if(!strcmp(argv[i],"print")){
		int index = atoi(argv[i + 1]);
		printf("Drukuje tablice o indeksie %i...\n", index);
		for(int j = 0; j < t.size[index]; j++)
		    printf("%c", t.p[index][j]);
		printf("\n");
		i++;
	    }
        }
    }else if(argv[1][0] == '0'){ //create dynamic table
        dtab t(atoi(argv[2]));
        for(int i = 3; i < argc; i++){
            if(!strcmp(argv[i],"alloc")){
	        int size = atoi(argv[i+1]);
	        int index = atoi(argv[i+2]);
	        printf("Alokuje blok pod indeksem %i o rozmiarze %i...\n",index, size);
	        t.allocateBlock(size, index);
		for(int j = 0; j < size; ++j)
		    t.p[index][j] = rand() % 24 + 67;
		i += 2;
	    }else if(!strcmp(argv[i],"free")){
        	int index = atoi(argv[i+1]);
                printf("Zwalniam pamiec pod indeksem %i...\n", index);
                t.freeBlock(index);
		i++;
	    }else if(!strcmp(argv[i],"find")){
		int b = atoi(argv[i+1]);
		int c = atoi(argv[i+2]);
		printf("Znaleziony indeks dla elementu o indeksie [%i][%i] - %i\n", b, c, t.findBlockClosestTo(b,c));
		i += 2;
	    }else if(!strcmp(argv[i],"print")){
		int index = atoi(argv[i + 1]);
		printf("Drukuje tablice o indeksie %i...\n", index);

		for(int j = 0; j < t.size[index]; j++)
		    printf("%c", t.p[index][j]);
		printf("\n");
		i++;
	    }
	}
    }
    finishClock();
    return 0;
}
