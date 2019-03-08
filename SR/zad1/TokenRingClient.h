//
// Created by Joseph on 08.03.2019.
//

#ifndef ZAD1_TOKENRINGCLIENT_H
#define ZAD1_TOKENRINGCLIENT_H

#include <string>
#include <thread>
#include <vector>
#include "mqueue.h"

class TokenRingClient {
public:

    class Builder {
    public:

        Builder() {
            has_token = false;
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
            client.next_port = this->next_port;
            client.next_ip[0] = this->next_ip[0];
            client.next_ip[1] = this->next_ip[1];
            client.next_ip[2] = this->next_ip[2];
            client.next_ip[3] = this->next_ip[3];
            client.has_token = this->has_token;
            client.has_read = true;
            QInit(&client.send_queue, 500);
            QInit(&client.read_queue, 500);

            this->has_token = false;
            return client;
        }

    private:
        const char* id;
        unsigned short port;
        unsigned short next_port;
        unsigned short next_ip[4];
        bool has_token;
    };
    void run();
    void kill();

    void send_message(std::string message);
    std::string read_message();


private:
    //char send_buffer[1024] = {0};
    //std::vector<std::string> read_buffer;
    char data[1024];

    MQueue send_queue;
    MQueue read_queue;

    bool has_read;


    const char* id;
    unsigned short port;
    unsigned short next_port;
    unsigned short next_ip[4];
    bool has_token;

    std::thread* th;

    static const int sleep_time = 1000;
    static constexpr short multicast_logging_ip[4] = {230, 0, 0, 0};

    int read_socket;
    int write_socket;

    static void* init_server(TokenRingClient*);
    static void* init_client(TokenRingClient*);
    static void* run_callback(TokenRingClient*);


};


#endif //ZAD1_TOKENRINGCLIENT_H
