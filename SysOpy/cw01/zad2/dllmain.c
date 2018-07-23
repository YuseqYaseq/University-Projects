#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/times.h>
#include <unistd.h>
#include <dlfcn.h>

#include "dll_library.h"

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
//find [b] [c] - zwraca indeks bloku którego suma elementów jest najblizsza wartości elementu o indeksie [b][c]
//print [index] - wypisuje index
int main(int argc, char* argv[]) {
    if(argc < 2){
        printf("Niewystarczajaca liczba argumentow!");
        return 1;
    }
    srand(time(NULL));
    void* handle = dlopen("/home/joseph/sysopy/Projekty/Zad1/main/libdll.so", RTLD_LAZY | RTLD_LOCAL);
    if(!handle){
        printf("Nie udalo sie otworzyc biblioteki!");
	printf("%s",dlerror());
        return -1;
    }
    void (*allocateBlock)(int, int);
    void (*freeBlock)(int);
    int  (*findBlockClosestTo)(int, int);
    startClock();
    if(argv[1][0] == '1'){ //create static table
        allocateBlock =		(void (*) (int, int) )dlsym(handle, "s_allocateBlock");
	if(dlerror() != NULL){
	    printf("%s",dlerror());
	    printf("Blad ladowania funkcji!");
	    return -1;
	}
	freeBlock =		(void (*) (int     ) )dlsym(handle, "s_freeBlock");
	if(dlerror() != NULL){
	    printf("%s",dlerror());
	    printf("Blad ladowania funkcji!");
	    return -1;
	}
	findBlockClosestTo =	(int  (*) (int, int) )dlsym(handle, "s_findBlockClosestTo");
	if(dlerror() != NULL){
	    printf("%s",dlerror());
	    printf("Blad ladowania funkcji!");
	    return -1;
	}
        ssize = atoi(argv[2]);
        for(int i = 3; i < argc; i++){
            if(!strcmp(argv[i],"alloc")){
	        int size = atoi(argv[i+1]);
	        int index = atoi(argv[i+2]);
	        printf("Alokuje blok pod indeksem %i o rozmiarze %i...\n",index, size);
	        allocateBlock(size, index);
		//for(int j = 0; j < size; ++j)
		    //sta[index][j] = rand() % 24 + 67;
		i += 2;
	    }else if(!strcmp(argv[i],"free")){
        	int index = atoi(argv[i+1]);
                printf("Zwalniam pamiec pod indeksem %i...\n", index);
                freeBlock(index);
		i++;
	    }else if(!strcmp(argv[i],"find")){
		int b = atoi(argv[i+1]);
		int c = atoi(argv[i+2]);
		printf("Znaleziony indeks dla elementu o indeksie [%i][%i] - %i\n", b, c, findBlockClosestTo(b,c));
		i += 2;
	    }else if(!strcmp(argv[i],"print")){
		int index = atoi(argv[i + 1]);
		printf("Drukuje tablice o indeksie %i...\n", index);
		for(int j = 0; j < sta_e[index]; j++)
		    printf("%c", sta[index][j]);
		printf("\n");
		i++;
	    }
        }
    }else if(argv[1][0] == '0'){ //create dynamic table
	allocateBlock =		(void (*) (int, int) )dlsym(handle, "d_allocateBlock");
	if(dlerror() != NULL){
	    printf("%s",dlerror());
	    printf("Blad ladowania funkcji!");
	    return -1;
	}
	freeBlock =		(void (*) (int     ) )dlsym(handle, "d_freeBlock");
	if(dlerror() != NULL){
	    printf("%s",dlerror());
	    printf("Blad ladowania funkcji!");
	    return -1;
	}
	findBlockClosestTo =	(int  (*) (int, int) )dlsym(handle, "d_findBlockClosestTo");
	if(dlerror() != NULL){
	    printf("%s",dlerror());
	    printf("Blad ladowania funkcji!");
	    return -1;
	}
        dsize = atoi(argv[2]);
	dyn = (char**) calloc(dsize, sizeof(char*));
	dyn_e = (int*) calloc(dsize, sizeof(int));
        for(int i = 3; i < argc; i++){
            if(!strcmp(argv[i],"alloc")){
	        int size = atoi(argv[i+1]);
	        int index = atoi(argv[i+2]);
	        printf("Alokuje blok pod indeksem %i o rozmiarze %i...\n",index, size);
	        allocateBlock(size, index);
		for(int j = 0; j < size; ++j)
		    dyn[index][j] = rand() % 24 + 67;
		i += 2;
	    }else if(!strcmp(argv[i],"free")){
        	int index = atoi(argv[i+1]);
                printf("Zwalniam pamiec pod indeksem %i...\n", index);
                freeBlock(index);
		i++;
	    }else if(!strcmp(argv[i],"find")){
		int b = atoi(argv[i+1]);
		int c = atoi(argv[i+2]);
		printf("Znaleziony indeks dla elementu o indeksie [%i][%i] - %i\n", b, c, findBlockClosestTo(b,c));
		i += 2;
	    }else if(!strcmp(argv[i],"print")){
		int index = atoi(argv[i + 1]);
		printf("Drukuje tablice o indeksie %i...\n", index);

		for(int j = 0; j < dyn_e[index]; j++)
		    printf("%c", dyn[index][j]);
		printf("\n");
		i++;
	    }
	}
	free(dyn);
	free(dyn_e);
	
    }
    finishClock();
    dlclose(handle);
    return 0;
}
