#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <mqueue.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#define MSGTXTLEN (128)

typedef struct msg_buf {
    long mtype;
    char mtext[MSGTXTLEN];
} msg;

void RemoveQueue(int* queue){
    if(*queue == 0)return;
    if(msgctl(*queue, IPC_RMID, NULL) < 0){
        perror(strerror(errno));
        fprintf(stderr, "failed to remove the queue!\n");
        return;
    }
    *queue = 0;
}

bool CheckQueue(char* name, int num){
    int ret;
    if( (ret = msgget(ftok(name, num), IPC_EXCL |IPC_CREAT | 0666)) < 0){
        if(errno == EEXIST)return true;
        return false;
    }
    RemoveQueue(&ret);
    return false;
}

bool IsEmpty(int queue){
    struct msqid_ds buf;
    msgctl(queue, IPC_STAT, &buf);
    return !buf.msg_qnum;
}

int CreateQueue(char* name, int num){
    int ret;
    if( (ret = msgget(ftok(name, num), IPC_CREAT | 0666)) < 0){
        perror(strerror(errno));
        fprintf(stderr, "failed to create message queue!\n");
        return 0;
    }
    return ret;
}

void SendMessage(int* queue, msg* m){
    if(msgsnd(*queue, m, sizeof(m->mtext), 0) < 0){
        perror(strerror(errno));
        fprintf(stderr, "failed to send the message!\n");
        RemoveQueue(queue);
    }
}

void ReadMessage(int* queue, msg* m){
    if(msgrcv(*queue, m, sizeof(m->mtext), 0, 0) < 0){
        perror(strerror(errno));
        fprintf(stderr, "failed to receive the message!\n");
        RemoveQueue(queue);
    }
}
