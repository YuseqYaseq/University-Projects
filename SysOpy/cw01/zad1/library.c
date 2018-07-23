#include "library.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void stab::allocateBlock(int size, int index) {
    p[index] = (char*)calloc(size, sizeof(char));
    this->size[index] = size;
}

void stab::freeBlock(int index) {
    free(p[index]);
    size[index] = 0;
}

int stab::findBlockClosestTo(int b, int c) {
    int minDiff = INT_MAX;
    int ind = INT_MAX;
    for(int i = 0; i < n; ++i)
    {
        if(size[i] == 0) continue;
        int curSum = 0;
        for(int j = 0; j < size[i]; ++j)
        {
            curSum += (int)p[i][j];
        }
        curSum = abs(curSum - p[b][c]);
        if(curSum < minDiff)
        {
            minDiff = curSum;
            ind = i;
        }
    }
    return ind;
}

stab::stab() {
    memset(size, 0, n*sizeof(int));
}


void dtab::allocateBlock(int size, int index) {
    p[index] = (char*)calloc(size, sizeof(char));
    this->size[index] = size;
}

void dtab::freeBlock(int index) {
    free(p[index]);
    size[index] = 0;
}

int dtab::findBlockClosestTo(int b, int c) {
    int minDiff = INT_MAX;
    int ind = INT_MAX;
    for(int i = 0; i < psize; ++i)
    {
        if(size[i] == 0) continue;
        int curSum = 0;
        for(int j = 0; j < size[i]; ++j)
        {
            curSum += (int)p[i][j];
        }
        curSum = abs(curSum - p[b][c]);
        if(curSum < minDiff)
        {
            minDiff = curSum;
            ind = i;
        }
    }
    return ind;
}

dtab::dtab(int psize) {
    p = (char**)calloc(psize, sizeof(char*));
    size = (int*)calloc(psize, sizeof(int));
    memset(size, 0, psize*sizeof(int));
    this->psize = psize;
}

dtab::~dtab() {
    free(p);
    free(size);
}
