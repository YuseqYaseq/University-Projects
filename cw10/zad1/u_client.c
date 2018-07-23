#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>

#define SOCK_PATH "/home/joseph/CODE/SysOpy/cw10/zad1/socket"

struct test{
    int var1;
    int var2;
    char buf[20];
};

int main(int c, char* v[]){
    int cfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(cfd == -1){
        fprintf(stderr, "Failed to open socket. errno = %d.\n", errno);
        exit(-1);
    }
    struct sockaddr_un my_addr, peer_addr;
    int sfd;
    memset(&my_addr, 0, sizeof(struct sockaddr_un));
    strncpy(my_addr.sun_path, SOCK_PATH, sizeof(my_addr.sun_path) - 1);
    my_addr.sun_family = AF_UNIX;
    
    if(connect(cfd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr_un)) == -1){
        fprintf(stderr, "Failed to connect to server. errno = %d.\n", errno);
        exit(-1);
    }
    
    struct test t;
    read(cfd, &t, sizeof(t));
    printf("test.var1 = %d\ntest.var2 = %d\ntest.buf = %s\n", t.var1, t.var2, t.buf);
}
