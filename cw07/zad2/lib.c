#include <sys/mman.h>
#include <unistd.h>

#include "lib.h"

sem_t* CreateSemaphore(const char* name, unsigned int initVal){
    sem_t* s = sem_open(name, O_CREAT | O_RDWR, 0666, initVal);
    if(s == SEM_FAILED){
        fprintf(stderr, "Failed to create a semaphore!\n");
        perror(strerror(errno));
        onExit(0);
    }
    return s;
}

sem_t* GetSemaphore(const char* name){
    sem_t* s = sem_open(name, O_RDWR);
    if(s == SEM_FAILED){
        fprintf(stderr, "Failed to get a semaphore!\n");
        perror(strerror(errno));
        onExit(0);
    }
    return s;
}

void Take(sem_t* s){
    if(sem_wait(s) == -1){
        fprintf(stderr, "Failed to take the semaphore!\n");
        perror(strerror(errno));
        onExit(0);
    }
}

void Release(sem_t* s){
    if(sem_post(s) == -1){
        fprintf(stderr, "Failed to release the semaphore!\n");
        perror(strerror(errno));
        onExit(0);
    }
}

void CloseSemaphore(sem_t* s){
    sem_close(s);
}

void* CreateSharedMem(const char* name, off_t size){
    int fd;
    void* ret;
    if((fd = shm_open(name, O_CREAT | O_RDWR, 0666)) == -1){
        fprintf(stderr, "Failed to create shared memory!\n");
        perror(strerror(errno));
        onExit(0);
    }
    if(ftruncate(fd, size) == -1){
        fprintf(stderr, "Failed to truncate shared memory!\n");
        perror(strerror(errno));
        onExit(0);
    }
    if((ret = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED){
        fprintf(stderr, "Failed to map memory to the process!\n");
        perror(strerror(errno));
        onExit(0);
    }
    return ret;
}

void* GetSharedMem(const char* name, off_t size){
    int fd;
    void* ret;
    if((fd = shm_open(name, O_RDWR, 0666)) == -1){
        fprintf(stderr, "Failed to get shared memory!\n");
        perror(strerror(errno));
        onExit(0);
    }
    if((ret = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED){
        fprintf(stderr, "Failed to map memory to the process!\n");
        perror(strerror(errno));
        onExit(0);
    }
    return ret;
}

void ReleaseSharedMem(void* addr, size_t len, const char* name){
    munmap(addr, len);
    shm_unlink(name);
}

int GetValue(sem_t* sem){
    int ret;
    if(sem_getvalue(sem, &ret) == -1){
        fprintf(stderr, "Failed to get value of the semaphore!\n");
        perror(strerror(errno));
        onExit(0);
    }
    return ret;
}




































