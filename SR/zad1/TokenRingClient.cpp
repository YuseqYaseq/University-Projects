//
// Created by Joseph on 08.03.2019.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include "TokenRingClient.h"
#include "Token.h"

void TokenRingClient::run() {
    th = new std::thread(run_callback, this);
}

void TokenRingClient::kill() {

    th->detach();
    delete th;
    th = nullptr;
}

std::string TokenRingClient::read_message() {
    return QTryGet(&read_queue);
}

void TokenRingClient::send_message(std::string message) {
    QPut(&send_queue, message);
}

void* TokenRingClient::run_callback(TokenRingClient* client_info) {

    std::thread server(init_server, client_info);
    std::thread client(init_client, client_info);
    server.join();
    client.join();

    while(true) {
        if (client_info->has_token) {
            sleep(1);
            std::string data = QTryGet(&client_info->send_queue);
            if(!data.empty())
                std::cout << client_info->id << " sends: " << data << std::endl;
            send(client_info->write_socket, data.c_str(), data.length()+1, 0);
            client_info->has_token = false;
        }
        read(client_info->read_socket, &client_info->data, 1024);
        std::string msg(client_info->data);
        if(!msg.empty()) {
            QPut(&client_info->read_queue, msg);
            std::cout << client_info->id << " reads: " << client_info->data << std::endl;
        }
        client_info->has_token = true;
    }
    return nullptr;
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

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
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