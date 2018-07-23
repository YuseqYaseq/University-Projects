#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#define LISTEN_BACKLOG 50

#define PORT_NUM 8080

struct test{
    int var1;
    int var2;
    char buf[20];
};

int main(int c, char* v[]){
    //int fd = socket(AF_INET, SOCK_STREAM, 0);
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sfd == -1){
        fprintf(stderr, "Failed to open socket. errno = %d.\n", errno);
        exit(-1);
    }
    struct sockaddr_in my_addr, peer_addr;
    int cfd;
    socklen_t peer_addr_size;
    
    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = INADDR_ANY;
    my_addr.sin_port = htons( PORT_NUM );
    
    
    
    if(bind(sfd, (const struct sockaddr*) &my_addr, sizeof(my_addr)) == -1){
        fprintf(stderr, "Failed to bind socket to a name. errno = %d.\n", errno);
        exit(-1);
    }
    if(listen(sfd, LISTEN_BACKLOG) == -1){
        fprintf(stderr, "Failed to make the socket listen. errno = %d.\n", errno);
        exit(-1);
    }
    
    peer_addr_size = sizeof(peer_addr);
    cfd = accept(sfd, (struct sockaddr*) &peer_addr, &peer_addr_size);
    if(cfd == -1){
        fprintf(stderr, "Failed to accept the socket. errno = %d.\n", errno);
        exit(-1);
    }
    
    struct test t;
    read(cfd, &t, sizeof(t));
    printf("test.var1 = %d\ntest.var2 = %d\ntest.buf = %s\n", t.var1, t.var2, t.buf);
    
    if(shutdown(sfd, SHUT_RDWR) == -1){
        fprintf(stderr, "Failed to unlink socket path. errno = %d.\n", errno);
        exit(-1);
    }
    if(close(sfd) == -1){
        fprintf(stderr, "Failed to close socket. errno = %d.\n", errno);
        exit(-1);
    }
    
    return 0;
}
