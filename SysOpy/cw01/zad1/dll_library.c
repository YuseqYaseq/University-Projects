#include "dll_library.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void s_allocateBlock(int size, int index) {
    sta[index] = (char*)calloc(size, sizeof(char));
    sta_e[index] = size;
}

void s_freeBlock(int index) {
    free(sta[index]);
    sta_e[index] = 0;
}

int s_findBlockClosestTo(int b, int c) {
    int minDiff = INT_MAX;
    int ind = INT_MAX;
    for(int i = 0; i < ssize; ++i)
    {
        if(sta_e[i] == 0) continue;
        int curSum = 0;
        for(int j = 0; j < sta_e[i]; ++j)
        {
            curSum += (int)sta[i][j];
        }
        curSum = abs(curSum - sta[b][c]);
        if(curSum < minDiff)
        {
            minDiff = curSum;
            ind = i;
        }
    }
    return ind;
}

void d_allocateBlock(int size, int index) {
    dyn[index] = (char*)calloc(size, sizeof(char));
    dyn_e[index] = size;
}

void d_freeBlock(int index) {
    free(dyn[index]);
    dyn_e[index] = 0;
}

int d_findBlockClosestTo(int b, int c) {
    int minDiff = INT_MAX;
    int ind = INT_MAX;
    for(int i = 0; i < dsize; ++i)
    {
        if(dyn_e[i] == 0) continue;
        int curSum = 0;
        for(int j = 0; j < dyn_e[i]; ++j)
        {
            curSum += (int)dyn[i][j];
        }
        curSum = abs(curSum - dyn[b][c]);
        if(curSum < minDiff)
        {
            minDiff = curSum;
            ind = i;
        }
    }
    return ind;
}
