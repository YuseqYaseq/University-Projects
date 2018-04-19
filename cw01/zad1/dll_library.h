#ifndef PROJEKTY_LIBRARY_H
#define PROJEKTY_LIBRARY_H

#define n 1000

char* sta[n] = {0};
int sta_e[n] = {0};//rozmiar bloków
int ssize;//rozmiar tablicy

char** dyn = 0;
int* dyn_e = 0;//rozmiar bloków
int dsize;//rozmiar tablicy

/****** STATIC ******/

//size - how many elements to allocate
//index - index in p where block is going to be put
void s_allocateBlock(int size, int index);

void s_freeBlock(int index);

//Find block with sum closest to element p[b][c]
//returns index of the block
int s_findBlockClosestTo(int b, int c);


/****** DYNAMIC ******/

//size - how many elements to allocate
//index - index in p where block is going to be put
void d_allocateBlock(int size, int index);

void d_freeBlock(int index);

//Find block with sum closest to element p[b][c]
//returns index of the block
int d_findBlockClosestTo(int b, int c);

#endif
