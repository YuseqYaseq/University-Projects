#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

mqd_t q;

#define SERVER_NAME "/server"

void onExit(){
    mq_close(q);
    mq_unlink(SERVER_NAME);
    exit(0);
}

#include "funs.h"


//mqd_t qs[10];


void Reverse(char* p, int size){
    for(int i = 0; i < size/2; ++i){
        char tmp = p[i];
        p[i] = p[size-i-1];
        p[size-i-1] = tmp;
    }
}

int main(int c, char* v[]){
    signal(SIGINT, onExit);
    
    q = CreateQueue(SERVER_NAME);
    
    printf("Created queue, q = %d\n", q);
    printf("Awaiting message...\n");
    
    int pid, qid;
    char qname[20];
    char message[50];
    int n1, n2;
    char sign;
    FILE* d;
    bool finish = false;
    while(1){
        if(finish){
            struct mq_attr isEmpty;
            mq_getattr(q, &isEmpty);
            if(isEmpty.mq_curmsgs == 0){
                printf("Queue is empty. Shutting down.\n");
                onExit();
            }
        }
        char a[SIZE] = {0};
        ReceiveMessage(q, a);
        printf("%s\n", a+1);
        switch(a[0]){
            case 1: //New connection
                sscanf(a+1, "%d %d", &pid, &qid);
                printf("New connection created, pid = %d\n", pid);
                break;
            case 2: //TIME
                sscanf(a+1, "%s", qname);
                d = popen("date", "r");
                fread(a, sizeof(char), SIZE, d);
                qid = OpenQueue(qname);
                SendMessage(qid, a);
                mq_close(qid);
                break;
            case 3: //MIRROR
                sscanf(a+1, "%s %s", qname, message);
                Reverse(message, strlen(message));
                strcpy(a, message);
                qid = OpenQueue(qname);
                SendMessage(qid, a);
                mq_close(qid);
                break;
            case 4: //CALC
                sscanf(a+1, "%s %d%c%d", qname, &n1, &sign, &n2);
                memset(a, 0, SIZE);
                if(sign == '+') sprintf(a, "%d", n1+n2);
                else if(sign == '-') sprintf(a, "%d", n1-n2);
                else if(sign == '*') sprintf(a, "%d", n1*n2);
                else if(sign == '/') sprintf(a, "%d", n1/n2);
                qid = OpenQueue(qname);
                SendMessage(qid, a);
                mq_close(qid);
                break;
            case 5: //END
                finish = true;
                break;
        }
        
    }
    
    onExit();
    return 0;
}
