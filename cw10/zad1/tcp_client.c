#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#define PORT_NUM 8080

struct test{
    int var1;
    int var2;
    char buf[20];
};

int main(int c, char* v[]){
    int cfd = socket(AF_INET, SOCK_STREAM, 0);
    if(cfd == -1){
        fprintf(stderr, "Failed to open socket. errno = %d.\n", errno);
        exit(-1);
    }
    struct sockaddr_in my_addr;
    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    //my_addr.sin_addr.s_addr = inet_addr("192.168.0.11");
    my_addr.sin_addr.s_addr = inet_addr("83.4.155.197");
    my_addr.sin_port = PORT_NUM;
    
    if(connect(cfd, (struct sockaddr*)&my_addr, sizeof(my_addr)) == -1){
        fprintf(stderr, "Failed to connect to server. errno = %d.\n", errno);
        exit(-1);
    }
    
    struct test t;
    read(cfd, &t, sizeof(t));
    printf("test.var1 = %d\ntest.var2 = %d\ntest.buf = %s\n", t.var1, t.var2, t.buf);
    
    close(cfd);
}
