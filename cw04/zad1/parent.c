#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

#include "clock.h"

bool child_working = false;
int child_pid;

void func_stop(){
    if(child_working){
        kill(child_pid, SIGINT);
        child_working = false;
    }
    else{
        if((child_pid = fork())){
            child_working = true;
        }
        else{
            setpgid(0, 0);
            execl("./main", "./main", NULL);
        }
    }
}

void func_term(){
    kill(child_pid, SIGINT);
    exit(0);
}

int main(int argc, char* argv[]){
    struct sigaction act;
    act.sa_handler = func_term;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT, &act, NULL);
    signal(SIGTSTP, func_stop);
    
    func_stop();
    pause();
    return 0;
}
