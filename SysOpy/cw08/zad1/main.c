#include <errno.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "clock.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

pthread_t* threads = 0;
int** args = 0;

FILE* result;

short max_val;
short** pic = 0;
double** filter = 0;
short** res = 0;

int w,h,c,n;

void onExit(){
    if(pic){
        for(int i = 0; i < h; ++i){
            free(pic[i]);
        }
        free(pic);
    }
    if(res){
        for(int i = 0; i < h; ++i){
            free(res[i]);
        }
        free(res);
    }
    if(filter){
        for(int i = 0; i < c; ++i){
            free(filter[i]);
        }
        free(filter);
    }
    if(threads){
        free(threads);
    }
    if(args){
        for(int i = 0; i < n; ++i){
            free(args[i]);
        }
        free(args);
    }
}

int readFilter(const char* path){
    FILE* filt = fopen(path, "r");
    if(filt == NULL){
        fprintf(stderr, "Failed to read filter %s!\n", path);
        return -1;
    }
    fscanf(filt, "%d", &c);
    filter = (double**)malloc(c*sizeof(double*));
    for(int i = 0; i < c; ++i){
        filter[i] = (double*)malloc(c*sizeof(double));
        for(int j = 0; j < c; ++j){
            fscanf(filt, "%lf", &filter[i][j]);
        }
    }
    fclose(filt);
    return 0;
}

int readPGM(const char* path){
    FILE* picture = fopen(path, "r");
    if(picture == NULL){
        fprintf(stderr, "Failed to read PGM %s!\n", path);
        return -1;
    }
    //ignore 1st element
    char x[20];
    fscanf(picture, "%s %d %d %hd", x, &w, &h, &max_val);
    pic = (short**)malloc(h*sizeof(short*));
    for(int i = 0; i < h; ++i){
        pic[i] = (short*)malloc(w*sizeof(short));
        for(int j = 0; j < w; ++j){
            fscanf(picture, "%hd", &pic[i][j]);
        }
    }
    fclose(picture);
    return 0;
}

void* transform(void* arg){
    int thread_num = *((int*)arg);
    int c_x;
    int c_y;
    for(int i = thread_num*(h/n); i < (thread_num+1)*(h/n); ++i){
        for(int j = 0; j < w; ++j){
            double s = 0;
            for(int ci = 0; ci < c; ++ci){
                for(int cj = 0; cj < c; ++cj){
                    c_y = MAX(1, i - ceil(c/2.0) + ci);
                    c_y--;
                    if(c_y > h - 1)c_y = h - 1;
                    
                    c_x = MAX(1, j - ceil(c/2.0) + cj);
                    c_x--;
                    if(c_x > w - 1)c_x = w - 1;
                    
                    s += pic[c_y][c_x] * filter[ci][cj];
                }
            }
            if(s > max_val) s = max_val;
            res[i][j] = s;
        }
    }
    return NULL;
}

int main(int c, char* v[]){
    if(c < 5){
        printf("Uzycie programu: ./main n pic fil res\n");
        printf("n - liczba watkow\n");
        printf("pic - plik z wejsciowym obrazem\n");
        printf("fil - plik z definicja filtru\n");
        printf("res - plik wynikowy\n");
    }
    n = atoi(v[1]);
    readFilter(v[3]);
    readPGM(v[2]);
    
    res = (short**)malloc(h*sizeof(short*));
    for(int i = 0; i < h; ++i){
        res[i] = (short*)malloc(w*sizeof(short));
    }
    
    ////////////////////////////
    startClock();
    
    threads = (pthread_t*)malloc(n*sizeof(pthread_t));
    args = (int**)malloc(n*sizeof(int*));
    for(int i = 0; i < n; ++i){
        args[i] = (int*)malloc(sizeof(int));
        *(args[i]) = i;
        pthread_create(&threads[i], NULL, &transform, (void*)args[i]);
    }
    for(int i = 0; i < n; ++i){
        pthread_join(threads[i], NULL);
    }
    
    finishClock();
    ///////////////////////////
    
    result = fopen(v[4], "w");
    if(result){
        fprintf(result, "P2\n%d %d\n%hd\n", w, h, max_val);
        for(int i = 0; i < h; ++i){
            for(int j = 0; j < w; ++j){
                fprintf(result, "%hd ", res[i][j]);
            }
            fprintf(result, "\n");
        }
    }
    
    onExit();
    return 0;
}

























