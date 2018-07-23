#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

char name[100];
mqd_t client_q;
mqd_t server_q;
void onExit(){
    mq_close(client_q);
    mq_close(server_q);
    mq_unlink(name);
    exit(0);
}

#include "funs.h"

int main(int c, char* v[]){
    signal(SIGINT, onExit);
    
    char name[20];
    sprintf(name, "%s%d", CLIENT_NAME, getpid());
    client_q = CreateQueue(name);
    server_q = OpenQueue(SERVER_NAME);
    
    char a[SIZE];
    a[0] = 1;
    sprintf(a+1, "%d %d", getpid(), client_q);
    printf("%d %d\n", getpid(), client_q);
    
    SendMessage(server_q, a);
    
    while(1){
        char command[7];
        printf("Type command: ");
        scanf("%s", command);
        if(strstr(command, "TIME")){
            a[0] = 2;
            sprintf(a+1, "%s", name);
        }else if(strcmp(command, "MIRROR") == 0){
            a[0] = 3;
            sprintf(a+1, "%s", name);
            a[1+strlen(name)] = ' ';
            scanf("%s", a+2+strlen(name));
        }else if(strcmp(command, "CALC") == 0){
            a[0] = 4;
            sprintf(a+1, "%s", name);
            a[1+strlen(name)] = ' ';
            scanf("%s", a+2+strlen(name));
        }else if(strcmp(command, "ADD") == 0){
            a[0] = 4;
            int n1, n2;
            scanf("%d %d", &n1, &n2);
            sprintf(a+1, "%s %d+%d", name, n1, n2);
        }else if(strcmp(command, "SUB") == 0){
            a[0] = 4;
            int n1, n2;
            scanf("%d %d", &n1, &n2);
            sprintf(a+1, "%s %d-%d", name, n1, n2);
        }else if(strcmp(command, "MUL") == 0){
            a[0] = 4;
            int n1, n2;
            scanf("%d %d", &n1, &n2);
            sprintf(a+1, "%s %d*%d", name, n1, n2);
        }else if(strcmp(command, "DIV") == 0){
            a[0] = 4;
            int n1, n2;
            scanf("%d %d", &n1, &n2);
            sprintf(a+1, "%s %d/%d", name, n1, n2);
        }else if(strcmp(command, "END") == 0){
            a[0] = 5;
            printf("ok\n");
            SendMessage(server_q, a);
            onExit();
        }else continue;
        //struct mq_attr isEmpty;
        //if(mq_getattr(server_q, &isEmpty) == -1)
        //if(isEmpty.mq_curmsgs == 0){
        //    printf("$$$ %ld %ld %ld\n", isEmpty.mq_flags, isEmpty.mq_maxmsg, isEmpty.mq_msgsize);
        //    onExit();
        //}
        SendMessage(server_q, a);
        ReceiveMessage(client_q, a);
        printf("%s\n", a);
    }
    
    onExit();
    return 0;
}



