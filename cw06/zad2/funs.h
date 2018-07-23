#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <mqueue.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#define SIZE (100)
#define SERVER_NAME "/server"
#define CLIENT_NAME "/client"

mqd_t CreateQueue(char* name){
    struct mq_attr atr;
    atr.mq_flags = 0;
    atr.mq_maxmsg = 10;
    atr.mq_msgsize = SIZE;
    atr.mq_curmsgs = 0;
    mqd_t q = mq_open(name, O_EXCL | O_CREAT | O_RDONLY, 0666, &atr);
    if(q == -1){
        printf("Failed to create queue. Errno = %d.\n", errno);
        onExit();
    }
    return q;
}

mqd_t OpenQueue(char* name){
    mqd_t q = mq_open(name, O_RDWR);
    if(q == -1){
        printf("Failed to open queue. Errno = %d.\n", errno);
        onExit();
    }
    return q;
}

void ReceiveMessage(mqd_t q, char* buf){
    int s = mq_receive(q, buf, (SIZE+1), NULL);
    if(s == -1){
        printf("Failed to receive message. Errno = %d.\n", errno);
        onExit();
    }
}

void SendMessage(mqd_t q, char* buf){
    if(mq_send(q, buf, SIZE, 1) == -1){
        printf("Failed to send message. Errno = %d.\n", errno);
        onExit();
    }
}





