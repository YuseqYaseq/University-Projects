#ifndef _LIB_H_
#define _LIB_H_

#include <errno.h>
#include <string.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>    

extern void onExit(int);

sem_t* CreateSemaphore(const char* name, unsigned int initVal);
sem_t* GetSemaphore(const char* name);
void Take(sem_t* sem);
void Release(sem_t* sem);
void CloseSemaphore(sem_t* sem);
void* CreateSharedMem(const char* name, off_t len);
void* GetSharedMem(const char* name, off_t len);
void ReleaseSharedMem(void* addr, size_t len, const char* name);
int GetValue(sem_t* sem);


/*key_t CreateKey(char* name, int num);
int CreateSemaphores(key_t k, int numOfSems);
void ReleaseSemaphores(int semid);
int GetSemaphores(key_t key);
int CreateSharedMem(key_t k, int size);
int GetSharedMem(key_t key);
int* GetMemPointer(int shmid);
void Add(int semid, int n, int val);
int IsZero(int semid, int n);
void WaitTillZero(int semid, int n);*/

#endif
