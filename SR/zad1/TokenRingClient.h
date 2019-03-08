//
// Created by Joseph on 08.03.2019.
//

#ifndef ZAD1_TOKENRINGCLIENT_H
#define ZAD1_TOKENRINGCLIENT_H

#include <string>

class TokenRingClient {
public:

    class Builder {
    public:

        Builder() {
            has_token = false;
        }

        Builder& set_id(const std::string* id) {
            this->id = id;
            return *this;
        }

        Builder& set_port(const int port) {
            this->port = port;
            return *this;
        }

        Builder& set_next_port(const int next_port) {
            this->next_port = next_port;
            return *this;
        }

        Builder& set_next_ip(const short* const next_ip) {
            this->next_ip[0] = next_ip[0];
            this->next_ip[1] = next_ip[1];
            this->next_ip[2] = next_ip[2];
            this->next_ip[3] = next_ip[3];
        }

        Builder& set_active_token() {
            has_token = true;
            return *this;
        }

        TokenRingClient build() {
            TokenRingClient client;
            client.id = *this->id;
            client.port = this->port;
            client.next_port = this->next_port;
            client.next_ip[0] = this->next_ip[0];
            client.next_ip[1] = this->next_ip[1];
            client.next_ip[2] = this->next_ip[2];
            client.next_ip[3] = this->next_ip[3];
            client.has_token = this->has_token;
            return client;
        }

    private:
        const std::string* id;
        int port;
        int next_port;
        short next_ip[4];
        bool has_token;
    };

    void run();

    void send_message(std::string& message);
    std::string read_message();

private:
    std::string buffer;

    std::string id;
    int port;
    int next_port;
    short next_ip[4];
    bool has_token;

    static const int sleep_time = 1000;
    static constexpr short multicast_logging_ip[4] = {230, 0, 0, 0};

    static void* run_callback(void*);
};


#endif //ZAD1_TOKENRINGCLIENT_H
