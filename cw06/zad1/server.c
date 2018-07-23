#include <signal.h>

#include "funs.h"

int sq = 0;

void onExit(){
    RemoveQueue(&sq);
    exit(0);
}

void Reverse(char* p, int size){
    for(int i = 0; i < size/2; ++i){
        char tmp = p[i];
        p[i] = p[size-i-1];
        p[size-i-1] = tmp;
    }
}

int main(int c, char* v[]){
    signal(SIGINT, onExit);
    //Store client queues here
    int pid;
    int Q;
    //int Queues[100];
    //int CurrentNumOfQ = 0;
    sq = CreateQueue("server", 10);
    printf("Created queue, sq = %d\n", sq);
    printf("Awaiting message...\n");
    msg m;
    bool finish = false;
    while(1){
        int from;
        char com_mes[50];
        int a,b;
        char sign;
        FILE* d;
        if(finish && IsEmpty(sq)){
            printf("Queue is empty - shutting down.\n");
            onExit();
        }
        ReadMessage(&sq, &m);
        
        sscanf(m.mtext, "%d %s", &from, com_mes);
        printf("%s from %d\n",com_mes, from);
        switch(m.mtype){
            case 1: //new connection
                sscanf(m.mtext, "%d %d", &pid, &Q);
                printf("New connection created, pid = %d, queueID = %d\n", pid, Q);
                break;
            case 2: //TIME
                d = popen("date", "r");
                fread(m.mtext, sizeof(char), MSGTXTLEN, d);
                SendMessage(&from, &m);
                break;
            case 3: //MIRROR
                Reverse(com_mes, strlen(com_mes));
                strcpy(m.mtext,com_mes);
                SendMessage(&from, &m);
                break;
            case 4: //CALC
                sscanf(com_mes, "%d%c%d", &a, &sign, &b);
                if(sign == '+'){
                    sprintf(m.mtext, "%d", a+b);   
                }else if(sign == '-'){
                    sprintf(m.mtext, "%d", a-b);   
                }else if(sign == '*'){
                    sprintf(m.mtext, "%d", a*b);   
                }else if(sign == '/'){
                    sprintf(m.mtext, "%d", a/b);   
                }
                //printf("%d\n%d\n%s\n", a, b, m.mtext);
                SendMessage(&from, &m);
                break;
            case 5: //END
                finish = true;
                break;
        }
    }
    RemoveQueue(&sq);
}

















