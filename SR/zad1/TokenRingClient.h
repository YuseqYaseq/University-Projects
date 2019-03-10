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
            print_full_diagnostic = false;
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

        Builder& set_print_diagnostic() {
            print_full_diagnostic = true;
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
            client.token.queue_max = 0;
            client.token.queue_curr = 0;
            client.token.new_client_flag = 0;
            client.kill_flag = false;
            client.queue_pos = 0;
            client.print_full_diagnostic = print_full_diagnostic;
            QInit(&client.send_queue, 500);
            QInit(&client.read_queue, 500);

            this->has_token = false;
            this->is_single_node = false;
            this->print_full_diagnostic = false;
            return client;
        }

    private:
        const char* id;
        unsigned short port;
        unsigned short next_port;
        unsigned short next_ip[4];
        bool has_token;
        bool is_single_node;
        bool print_full_diagnostic;
    };
    void run();
    void kill();

    void send_message(Message message);
    Message read_message();

private:

    MQueue send_queue;
    MQueue read_queue;

    bool kill_flag;
    unsigned long queue_pos;

    const char* id;
    unsigned short port;
    unsigned short ip[4];
    unsigned short next_port;
    unsigned short next_ip[4];

    bool has_token;
    Token token;

    bool print_full_diagnostic;

    std::thread* th;

    sockaddr_in server_addr;
    unsigned int addr_length;

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

    std::string get_ip();
};


#endif //ZAD1_TOKENRINGCLIENT_H
