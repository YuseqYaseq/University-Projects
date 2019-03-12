//
// Created by Joseph on 08.03.2019.
//

#include <sys/socket.h>
#include <netinet/in.h>
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
    kill_flag = true;
    th->detach();
    delete th;
    th = nullptr;
    QDel(&send_queue);
    QDel(&read_queue);
}

Message TokenRingClient::read_message() {
    return QGet(&read_queue);
}

void TokenRingClient::send_message(Message msg) {
    msg.port_from = port;
    msg.ip_from[0] = ip[0];
    msg.ip_from[1] = ip[1];
    msg.ip_from[2] = ip[2];
    msg.ip_from[3] = ip[3];
    QPut(&send_queue, msg);
}

void* TokenRingClient::run_callback(TokenRingClient* client_info) {

    if(!client_info->has_token) {
        join_network(client_info);
    }

    std::thread server(init_server, client_info);
    std::thread client(init_client, client_info);
    server.join();
    client.join();

    std::thread addition_service(init_addition_service, client_info);

    while(!client_info->kill_flag) {
        sleep(1);
        client_info->send_msg();
        client_info->read_msg();
    }
    return nullptr;
}

void* TokenRingClient::join_network(TokenRingClient* client_info) {
    init_client(client_info);
    Token token;
    token.new_client_flag = 1;
    token.currently_used = false;
    token.msg.port_from = client_info->port;
    token.msg.ip_from[0] = client_info->ip[0];
    token.msg.ip_from[1] = client_info->ip[1];
    token.msg.ip_from[2] = client_info->ip[2];
    token.msg.ip_from[3] = client_info->ip[3];
    if(send(client_info->write_socket, &token, sizeof(token), 0) < 0) {
        std::cerr << "Failed to send token 1." << std::endl;
    }
    if(read(client_info->write_socket, &token, sizeof(token)) == 0) {
        std::cerr << "Failed to read join msg." << std::endl;
    }

    token.new_client_flag = 2;
    client_info->next_port = token.msg.port_to;
    client_info->next_ip[0] = token.msg.ip_to[0];
    client_info->next_ip[1] = token.msg.ip_to[1];
    client_info->next_ip[2] = token.msg.ip_to[2];
    client_info->next_ip[3] = token.msg.ip_to[3];

    close(client_info->write_socket);
    init_client(client_info);
    if(send(client_info->write_socket, &token, sizeof(token), 0) < 0) {
        std::cerr << "Failed to send token 2." << std::endl;
    }
    return nullptr;
}

void TokenRingClient::send_msg() {
    if (has_token) {
        if (!QEmpty(&send_queue)) {
            if(!token.currently_used && queue_pos == token.queue_curr) {
                token.currently_used = true;
                token.queue_curr++;
                token.msg = QGet(&send_queue);
                token.new_client_flag = 0;
                queue_pos = 0;
            } else if(queue_pos == 0){
                queue_pos = token.queue_max;
                token.queue_max++;
            }
        }
        while(send(write_socket, &token, sizeof(token), 0) < 0) {
            std::cerr << "Failed to send msg. Retrying in 1 second" << std::endl;
            sleep(1);
        }
        has_token = false;
    }
}

void TokenRingClient::read_msg() {
    if(print_full_diagnostic)
        std::cout << "Token received." << std::endl;
    if(read(read_socket, &token, sizeof(token)) == 0) {
        std::cerr << "Failed to read msg." << std::endl;
    }
    if(token.new_client_flag == 0) {
        if (token.currently_used) {
            if (is_msg_to_me(token.msg)) {
                QPut(&read_queue, token.msg);
                std::cout << id << " reads: " << token.msg.content << std::endl;
                token.currently_used = false;

            } else {
                std::cout << id << ": not my message." << std::endl;
            }
        }
        has_token = true;
    } else {
        std::cerr << "Bad token received." << std::endl;
    }
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
    int opt = 1;
    client_info->addr_length = sizeof(client_info->server_addr);


    if ((client_info->server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        std::cerr << "socket failed" << std::endl;
        perror("socket failed p");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(client_info->server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
        std::cerr << "setsockopt failed" << std::endl;
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    client_info->server_addr.sin_family = AF_INET;
    client_info->server_addr.sin_addr.s_addr = INADDR_ANY;
    client_info->server_addr.sin_port = htons( client_info->port );

    if (bind(client_info->server_fd, (struct sockaddr *)&client_info->server_addr, client_info->addr_length)<0)
    {
        std::cerr << "bind failed" << std::endl;
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(client_info->server_fd, 3) < 0)
    {
        std::cerr << "listen failed" << std::endl;
        perror("listen");
        exit(EXIT_FAILURE);
    }


    if ((client_info->read_socket = accept(client_info->server_fd, nullptr, nullptr))<0)
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
                ": connection failed. \n" << "Retrying in 1 second" << std::endl;
            perror(strerror(errno));
            sleep(1);
        }
    } while(res < 0);
    return nullptr;
}

void* TokenRingClient::init_addition_service(TokenRingClient* client_info) {
    while(true) {
        if ((client_info->addition_service_socket = accept(client_info->server_fd, nullptr, nullptr)) < 0) {
            std::cerr << "accept failed" << std::endl;
            perror("accept");
            exit(EXIT_FAILURE);
        }
        Token response;
        read(client_info->addition_service_socket, &response, sizeof(response));
        if (response.new_client_flag == 1) {
            close(client_info->write_socket);

            response.msg.port_to = client_info->next_port;
            response.msg.ip_to[0] = client_info->next_ip[0];
            response.msg.ip_to[1] = client_info->next_ip[1];
            response.msg.ip_to[2] = client_info->next_ip[2];
            response.msg.ip_to[3] = client_info->next_ip[3];

            client_info->next_port = response.msg.port_from;
            client_info->next_ip[0] = response.msg.ip_from[0];
            client_info->next_ip[1] = response.msg.ip_from[1];
            client_info->next_ip[2] = response.msg.ip_from[2];
            client_info->next_ip[3] = response.msg.ip_from[3];

            if (send(client_info->addition_service_socket, &response, sizeof(response), 0) < 0) {
                std::cerr << "Failed to respond to token 1" << std::endl;
            }

            init_client(client_info);

        } else if (response.new_client_flag == 2) {
            close(client_info->read_socket);
            if ((client_info->read_socket = accept(client_info->server_fd, nullptr, nullptr)) < 0) {
                std::cerr << "accept failed" << std::endl;
                perror("accept");
                exit(EXIT_FAILURE);
            }
        }
    }
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