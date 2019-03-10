//
// Created by Joseph on 08.03.2019.
//

#ifndef ZAD1_TOKENRINGCLIENT_H
#define ZAD1_TOKENRINGCLIENT_H

#include <string>
#include <thread>
#include <vector>
#include <arpa/inet.h>

#include "mqueue.h"
#include "Token.h"

class TokenRingClient {
public:

    class Builder {
    public:

        Builder() {
            has_token = false;
            is_single_node = false;
        }

        Builder& dont_join() {
            is_single_node = true;
            return *this;
        }

        Builder& set_id(const char* id) {
            this->id = id;
            return *this;
        }

        Builder& set_port(const unsigned short port) {
            this->port = port;
            return *this;
        }

        Builder& set_next_port(const unsigned short next_port) {
            this->next_port = next_port;
            return *this;
        }

        Builder& set_next_ip(const unsigned short* const next_ip) {
            this->next_ip[0] = next_ip[0];
            this->next_ip[1] = next_ip[1];
            this->next_ip[2] = next_ip[2];
            this->next_ip[3] = next_ip[3];
            return *this;
        }

        Builder& set_active_token() {
            has_token = true;
            return *this;
        }

        TokenRingClient build() {
            TokenRingClient client;
            client.id = this->id;
            client.port = this->port;

            client.get_ip();
            if(!is_single_node) {
                client.next_port = this->next_port;
                client.next_ip[0] = this->next_ip[0];
                client.next_ip[1] = this->next_ip[1];
                client.next_ip[2] = this->next_ip[2];
                client.next_ip[3] = this->next_ip[3];
            } else {
                client.next_port = this->port;
                client.next_ip[0] = client.ip[0];
                client.next_ip[1] = client.ip[1];
                client.next_ip[2] = client.ip[2];
                client.next_ip[3] = client.ip[3];
            }
            client.has_token = this->has_token;
            client.token.currently_used = false;
            client.kill_flag = false;
            QInit(&client.send_queue, 500);
            QInit(&client.read_queue, 500);

            this->has_token = false;
            this->is_single_node = false;
            return client;
        }

    private:
        const char* id;
        unsigned short port;
        unsigned short next_port;
        unsigned short next_ip[4];
        bool has_token;
        bool is_single_node;
    };
    void run();
    void kill();

    void send_message(Message message);
    Message read_message();

    std::string get_ip();

private:

    MQueue send_queue;
    MQueue read_queue;

    bool kill_flag;

    const char* id;
    unsigned short port;
    unsigned short ip[4];
    unsigned short next_port;
    unsigned short next_ip[4];

    bool has_token;
    Token token;

    std::thread* th;

    sockaddr_in server_addr;
    unsigned int addr_length;


    static const int sleep_time = 1000;
    static constexpr short multicast_logging_ip[4] = {230, 0, 0, 0};

    int server_fd;
    int read_socket;
    int write_socket;
    int addition_service_socket;

    static void* init_server(TokenRingClient*);
    static void* init_client(TokenRingClient*);
    static void* run_callback(TokenRingClient*);

    //requires init_server
    static void* init_addition_service(TokenRingClient*);
    static void* join_network(TokenRingClient*);

    void send_msg();
    void read_msg();
    bool is_msg_to_me(Message msg);


};


#endif //ZAD1_TOKENRINGCLIENT_H
