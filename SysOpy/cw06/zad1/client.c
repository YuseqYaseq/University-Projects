#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#include "funs.h"

int cq = 0;

void onExit(){
    RemoveQueue(&cq);
    exit(0);
}

int main(int c, char* v[]){
    signal(SIGINT, onExit);
    if(!CheckQueue("server", 10)){
        printf("Server not found!\n");
        return 1;
    }
    int sq = CreateQueue("server", 10);
    cq = CreateQueue("client", getpid());
    printf("Connected, cq = %d\n", cq);
    printf("Sending pid...\n");
    msg m;
    m.mtype = 1;
    //Send PID and queue ID
    sprintf(m.mtext, "%d %d", getpid(), cq);
    SendMessage(&sq, &m);
    while(1){
        char command[7];
        char com_mes[50];
        int a, b;
        char sign;
        printf("Type command: ");
        scanf("%s", command);
        sprintf(m.mtext, "%d", cq);
        if(strstr(command, "TIME")){
            m.mtype = 2;
        }else if(strstr(command, "MIRROR")){
            scanf("%s", com_mes);
            sprintf(m.mtext, "%d %s", cq, com_mes);
            m.mtype = 3;
        }else if(strstr(command, "CALC")){
            scanf("%d%c%d", &a, &sign, &b);
            sprintf(m.mtext, "%d %d%c%d", cq, a, sign, b);
            m.mtype = 4;
        }else if(strstr(command, "ADD")) {
            scanf("%d %d", &a, &b);
            sprintf(m.mtext, "%d %d%c%d", cq, a, '+', b);
            m.mtype = 4;
        }else if(strstr(command, "SUB")) {
            scanf("%d %d", &a, &b);
            sprintf(m.mtext, "%d %d%c%d", cq, a, '-', b);
            m.mtype = 4;
        }else if(strstr(command, "MUL")) {
            scanf("%d %d", &a, &b);
            sprintf(m.mtext, "%d %d%c%d", cq, a, '*', b);
            m.mtype = 4;
        }else if(strstr(command, "DIV")) {
            scanf("%d %d", &a, &b);
            sprintf(m.mtext, "%d %d%c%d", cq, a, '/', b);
            m.mtype = 4; 
        }else if(strstr(command, "END")){
            m.mtype = 5;
            SendMessage(&sq, &m);
            printf("ok\n");
            break;
        }else continue;
        if(!CheckQueue("server", 10)){
            printf("Connection lost. Shutting down.\n");
            onExit();
        }
        SendMessage(&sq, &m);
        ReadMessage(&cq, &m);
        printf("%s\n", m.mtext);
    }
    RemoveQueue(&cq);
}


