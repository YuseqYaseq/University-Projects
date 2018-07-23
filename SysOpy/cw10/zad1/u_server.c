#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/un.h>

#define SOCK_PATH "/home/joseph/CODE/SysOpy/cw10/zad1/socket"
#define LISTEN_BACKLOG 50

struct test{
    int var1;
    int var2;
    char buf[20];
};

int main(int c, char* v[]){

    //int fd = socket(AF_INET, SOCK_STREAM, 0);
    int sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sfd == -1){
        fprintf(stderr, "Failed to open socket. errno = %d.\n", errno);
        exit(-1);
    }
    struct sockaddr_un my_addr, peer_addr;
    int cfd;
    socklen_t peer_addr_size;
    
    memset(&my_addr, 0, sizeof(struct sockaddr_un));
    my_addr.sun_family = AF_UNIX;
    strncpy(my_addr.sun_path, SOCK_PATH, sizeof(my_addr.sun_path) - 1);
    
    if(bind(sfd, (const struct sockaddr*) &my_addr, sizeof(struct sockaddr_un)) == -1){
        fprintf(stderr, "Failed to bind socket to a name. errno = %d.\n", errno);
        exit(-1);
    }
    if(listen(sfd, LISTEN_BACKLOG) == -1){
        fprintf(stderr, "Failed to make the socket listen. errno = %d.\n", errno);
        exit(-1);
    }
    
    peer_addr_size = sizeof(struct sockaddr_un);
    cfd = accept(sfd, (struct sockaddr*) &peer_addr, &peer_addr_size);
    if(cfd == -1){
        fprintf(stderr, "Failed to accept the socket. errno = %d.\n", errno);
        exit(-1);
    }
    
    struct test t;
    t.var1 = 5;
    t.var2 = 100;
    strcpy(t.buf,"co sie dzieje");
    send(cfd, &t, sizeof(t), 0);
    
    if(unlink(SOCK_PATH) == -1){
        fprintf(stderr, "Failed to unlink socket path. errno = %d.\n", errno);
        exit(-1);
    }
    
    return 0;
}
