//
// Created by Joseph on 08.03.2019.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <ifaddrs.h>
#include <sstream>
#include "TokenRingClient.h"
#include "Token.h"

void TokenRingClient::run() {
    th = new std::thread(run_callback, this);
}

void TokenRingClient::kill() {
    th->detach();
    delete th;
    th = nullptr;
    QDel(&send_queue);
    QDel(&read_queue);
}

Message TokenRingClient::read_message() {
    return QTryGet(&read_queue);
}

void TokenRingClient::send_message(Message msg) {
    QPut(&send_queue, msg);
}

void* TokenRingClient::run_callback(TokenRingClient* client_info) {

    client_info->get_ip();
    std::thread server(init_server, client_info);
    std::thread client(init_client, client_info);
    server.join();
    client.join();

    while(true) {
        sleep(1);
        client_info->send_msg();
        client_info->read_msg();
    }
    return nullptr;
}

void TokenRingClient::send_msg() {
    if (has_token) {
        if(!token.currently_used) {
            token.msg = QTryGet(&send_queue);
            if (strlen(token.msg.content) > 0) {
                token.currently_used = true;
                std::cout << id << " sends: " << token.msg.content << std::endl;
            }
        }
        send(write_socket, &token, sizeof(token), 0);
        has_token = false;
    }
}

void TokenRingClient::read_msg() {
    read(read_socket, &token, sizeof(token));
    if(token.currently_used) {
        if(is_msg_to_me(token.msg)) {
            QPut(&read_queue, token.msg);
            std::cout << id << " reads: " << token.msg.content << std::endl;
            token.currently_used = false;
        }

    }
    has_token = true;
}

bool TokenRingClient::is_msg_to_me(Message msg) {
    if(msg.port_to != port)
        return false;
    if(msg.ip_to[0] == ip[0] && msg.ip_to[1] == ip[1]
       && msg.ip_to[2] == ip[2] && msg.ip_to[3] == ip[3])
        return true;
    if(msg.ip_to[0] == 127 && msg.ip_to[1] == 0
       && msg.ip_to[2] == 0 && msg.ip_to[3] == 1)
        return true;
    return false;
}

void* TokenRingClient::init_server(TokenRingClient* client_info) {
    int server_fd;
    int opt = 1;
    sockaddr_in server_addr;
    int addr_length = sizeof(server_addr);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        //std::cerr << "socket failed" << std::endl;
        perror("socket failed p");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
        std::cerr << "setsockopt failed" << std::endl;
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons( client_info->port );

    if (bind(server_fd, (struct sockaddr *)&server_addr,
             sizeof(server_addr))<0)
    {
        std::cerr << "bind failed" << std::endl;
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        std::cerr << "listen failed" << std::endl;
        perror("listen");
        exit(EXIT_FAILURE);
    }


    if ((client_info->read_socket = accept(server_fd, (struct sockaddr *)&server_addr,
                             (socklen_t*)&addr_length))<0)
    {
        std::cerr << "accept failed" << std::endl;
        perror("accept");
        exit(EXIT_FAILURE);
    }
    return nullptr;
}

void* TokenRingClient::init_client(TokenRingClient* client_info) {
    sockaddr_in serv_addr;

    if ((client_info->write_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cerr << "client socket failed" << std::endl;
        printf("\n Socket creation error \n");
        //return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(client_info->next_port);

    std::stringstream text_ip;
    text_ip << client_info->ip[0] << "." << client_info->ip[1]
        << "." << client_info->ip[2] << "." << client_info->ip[3];
    if(inet_pton(AF_INET, text_ip.str().c_str(), &serv_addr.sin_addr)<=0)
    {
        std::cerr << "\nInvalid address/ Address not supported \n" << std::endl;
        printf("\nInvalid address/ Address not supported \n");
        //return -1;
    }

    int res;
    do
    {
        res = connect(client_info->write_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
        if(res < 0) {
            std::cout << client_info->id <<
                ": connection failed. Retrying in 1 second" << std::endl;
            sleep(1);
        }
    } while(res < 0);
    return nullptr;
}

std::string TokenRingClient::get_ip() {
    struct ifaddrs * ifAddrStruct=NULL;
    struct ifaddrs * ifa=NULL;
    void * tmpAddrPtr=NULL;

    getifaddrs(&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr) {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET) { // check it is IP4
            // is a valid IP4 Address
            tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            if(strcmp(ifa->ifa_name, "lo") == 0) continue;
            std::string ret(addressBuffer);
            if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);
            ip[0] = atoi(strtok(addressBuffer, "."));
            ip[1] = atoi(strtok(nullptr, "."));
            ip[2] = atoi(strtok(nullptr, "."));
            ip[3] = atoi(strtok(nullptr, "."));
            return ret;
        }
    }
}