#ifndef PROJEKTY_LIBRARY_H
#define PROJEKTY_LIBRARY_H

#define n 1000

//stały rozmiar tablicy n
struct stab
{
    char* p[n];
    int size[n];
    int psize;

    //size - how many elements to allocate
    //index - index in p where block is going to be put
    void allocateBlock(int size, int index);

    void freeBlock(int index);

    //Find block with sum closest to element p[b][c]
    //returns index of the block
    int findBlockClosestTo(int b, int c);

    stab();
};

//zmienny rozmiar tablicy podawany w konstruktorze
struct dtab
{
    char** p;
    int* size;
    int psize;

    //size - how many elements to allocate
    //index - index in p where block is going to be put
    void allocateBlock(int size, int index);

    void freeBlock(int index);

    //Find block with sum closest to element p[b][c]
    //returns index of the block
    int findBlockClosestTo(int b, int c);

    dtab(int psize);
    ~dtab();
};

#endif