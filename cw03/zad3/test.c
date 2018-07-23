#include <stdlib.h>
#include <stdio.h>

int main(){
    while(1){
        int* mem = (int*)malloc(1000);
        mem[2] = 49;
        mem[5] = 0;
    }
    return 0;
}
