#define _GNU_SOURCE

#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdbool.h>

#include "clock.h"

int year;
int month;
int day;
char sign;
char* progName;
char* path;
int mode;

int fn(const char* path, const struct stat* buf, int typeflag, struct FTW* ftwbuf){
    if(typeflag)return 0;
    char* pos;
    char* lastpos;
    pos = strchr(path, '/');
    while(pos != NULL){
        lastpos = pos;
        pos = strchr(pos+1, '/');
    }
    char* name = malloc(strlen(path) - (lastpos - path) + 1);
    strncpy(name, lastpos+1, strlen(path) - (lastpos - path) + 1);

    
    int fsize = buf->st_size;
    time_t mdate = buf->st_mtime;
    char access[10] = "---------";
    char* apath = (char*)malloc((PATH_MAX+1)*sizeof(char));
    realpath(path, apath);
    
    if(buf->st_mode & S_IRUSR) access[0] = 'r';/*owner*/
    if(buf->st_mode & S_IWUSR) access[1] = 'w';/*owner*/
    if(buf->st_mode & S_IXUSR) access[2] = 'x';/*owner*/
    if(buf->st_mode & S_IRGRP) access[3] = 'r';/*group*/
    if(buf->st_mode & S_IWGRP) access[4] = 'w';/*group*/
    if(buf->st_mode & S_IXGRP) access[5] = 'x';/*group*/
    if(buf->st_mode & S_IROTH) access[6] = 'r';/*other*/
    if(buf->st_mode & S_IWOTH) access[7] = 'w';/*other*/
    if(buf->st_mode & S_IXOTH) access[8] = 'x';/*other*/
    
    struct tm t = *localtime(&mdate);
    
    bool visible = false;            
    if(sign == '='){
        if(year == t.tm_year + 1900 && month == t.tm_mon + 1 && day == t.tm_mday) visible = true;
    }else if(sign == '>'){
        if(year < t.tm_year + 1900) visible = true;
        else if(year == t.tm_year){
            if(month < t.tm_mon + 1) visible = true;
            else if(month == t.tm_mon + 1){
                if(day < t.tm_mday) visible = true;
            }
        }
    }else{
        if(year > t.tm_year + 1900) visible = true;
        else if(year == t.tm_year + 1900){
            if(month > t.tm_mon + 1) visible = true;
            else if(month == t.tm_mon + 1){
                if(day > t.tm_mday)visible = true;
            }
        }
    }
    if(visible == true){
        printf("%s", access);
        printf("%*s%s", 3, "", name);
        printf("%*s%i", (int)(30-strlen(name)), "", fsize);
        printf("%*s%d-",12-digits(fsize), "", t.tm_year+1900);
        if(digits(t.tm_mon+1) < 2)printf("0");
        printf("%d-", t.tm_mon+1);
        if(digits(t.tm_mday) < 2)printf("0");
        printf("%d ", t.tm_mday);
        if(digits(t.tm_hour) < 2)printf("0");
        printf("%d:", t.tm_hour);
        if(digits(t.tm_min) < 2)printf("0");
        printf("%d:", t.tm_min);
        if(digits(t.tm_sec) < 2)printf("0");
        printf("%d  ", t.tm_sec);
        printf("%s\n", apath);
    }
    free(apath);
    return 0;
}

void read2(char* path){
    nftw(path, fn, 1000, FTW_PHYS);
}

void read1(char* path){
    DIR* dir = opendir(path);
    if(dir == NULL){
        printf("Nie odnaleziono takiego katalogu!\n");
        return;
    }
    struct dirent* pDirent;
    for(pDirent = readdir(dir); pDirent != NULL; pDirent = readdir(dir)){
        if(!strcmp(pDirent->d_name, ".") || !strcmp(pDirent->d_name, ".."))continue;

        char* fpath = malloc((strlen(path)+strlen(pDirent->d_name)+2)*sizeof(char));
        strcpy(fpath, path);
        strcat(fpath, "/");
        strcat(fpath, pDirent->d_name);
        
        struct stat buf;
        if(lstat(fpath, &buf) != 0){
            printf("Blad odczytu struktury!");
            return;
        }
        if(S_ISDIR(buf.st_mode)){
            if(!vfork()){
                read1(fpath);
                exit(0);
            }
        }else if(S_ISREG(buf.st_mode)){
            
            int fsize = buf.st_size;
            time_t mdate = buf.st_mtime;
            char access[10] = "---------";
            char* apath = (char*)malloc((PATH_MAX+1)*sizeof(char));
            realpath(path, apath);
            
            if(buf.st_mode & S_IRUSR) access[0] = 'r';/*owner*/
            if(buf.st_mode & S_IWUSR) access[1] = 'w';/*owner*/
            if(buf.st_mode & S_IXUSR) access[2] = 'x';/*owner*/
            if(buf.st_mode & S_IRGRP) access[3] = 'r';/*group*/
            if(buf.st_mode & S_IWGRP) access[4] = 'w';/*group*/
            if(buf.st_mode & S_IXGRP) access[5] = 'x';/*group*/
            if(buf.st_mode & S_IROTH) access[6] = 'r';/*other*/
            if(buf.st_mode & S_IWOTH) access[7] = 'w';/*other*/
            if(buf.st_mode & S_IXOTH) access[8] = 'x';/*other*/
            
            struct tm t = *localtime(&mdate);
            
            bool visible = false;            
            if(sign == '='){
                if(year == t.tm_year + 1900 && month == t.tm_mon + 1 && day == t.tm_mday) visible = true;
            }else if(sign == '>'){
                if(year < t.tm_year + 1900) visible = true;
                else if(year == t.tm_year){
                    if(month < t.tm_mon + 1) visible = true;
                    else if(month == t.tm_mon + 1){
                        if(day < t.tm_mday) visible = true;
                    }
                }
            }else{
                if(year > t.tm_year + 1900) visible = true;
                else if(year == t.tm_year + 1900){
                    if(month > t.tm_mon + 1) visible = true;
                    else if(month == t.tm_mon + 1){
                        if(day > t.tm_mday)visible = true;
                    }
                }
            }
            if(visible == true){
                printf("%s", access);
                printf("%*s%s", 3, "", pDirent->d_name);
                printf("%*s%i", (int)(30-strlen(pDirent->d_name)), "", fsize);
                printf("%*s%d-",12-digits(fsize), "", t.tm_year+1900);
                if(digits(t.tm_mon+1) < 2)printf("0");
                printf("%d-", t.tm_mon+1);
                if(digits(t.tm_mday) < 2)printf("0");
                printf("%d ", t.tm_mday);
                if(digits(t.tm_hour) < 2)printf("0");
                printf("%d:", t.tm_hour);
                if(digits(t.tm_min) < 2)printf("0");
                printf("%d:", t.tm_min);
                if(digits(t.tm_sec) < 2)printf("0");
                printf("%d  ", t.tm_sec);
                printf("%s/%s\n", apath, pDirent->d_name);
                
            }
            free(apath);
        }
        free(fpath);
    }
    if(errno > 0){
        printf("Nie udalo sie odczytac katalogu %s! Blad %i.\n", path, errno);
        return;
    }
}

void show(){
    printf("Dostep%*sNazwa%*sRozmiar%*sData modyfikacji%*sSciezka bezwgledna\n", 6, "", 25, "", 5, "", 5, "");
    if(mode) read1(path);
    else read2(path);
}

//argv[1] - sciezka dostepu
//argv[2] - znak operacji (<, >, =)
//argv[3] - rok wybieranej daty
//argv[4] - miesiac wybieranej daty
//argv[5] - dzien wybieranej daty
//argv[6] - tryb otwarcia (0 - uzywamy nftw, dowolna inna liczba - uzywamy opendir/readdir/stat)
//argv[7] - istnieje jeżeli wywołujemy dziecko
int main(int argc, char* argv[]){
    if(argc < 7){
        printf("Za malo argumentow!\n");
        return -1;
    }
    if(!isNumber(argv[3]) || !isNumber(argv[4]) || !isNumber(argv[5]) || !isNumber(argv[6]) || (argv[2][0] != '<' && argv[2][0] != '>' && argv[2][0] != '=')){
        printf("Niepoprawne argumenty!\n");
        return -1;
    }
    sign = argv[2][0];
    year = atoi(argv[3]);
    month = atoi(argv[4]);
    day = atoi(argv[5]);
    mode = atoi(argv[6]);
    path = argv[1];
    show();
    return 0;
}
