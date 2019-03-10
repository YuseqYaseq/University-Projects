#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sstream>
#include <signal.h>

#include "TokenRingClient.h"

const char* message[4] = {"message1", "message2", "message3", "message4"};


const unsigned short client1_address[4] = {10, 0, 2, 15};

int main(int argc, const char* argv[]) {

    if(argc < 4) {
        std::cout << "Usage: main a b [c d] e" << std::endl;
        std::cout << "a - client port" << std::endl;
        std::cout << "b - client name" << std::endl;
        std::cout << "c - port where you want to connect to" << std::endl;
        std::cout << "d - ip address where you want to connect to" << std::endl;
        std::cout << "e - 1: print full diagnostic info 0: dont" << std::endl;
        std::cout << "Don't use c and d if you want to connect Client to itself" << std::endl;
        return 0;
    }
    signal(SIGPIPE, SIG_IGN);
    TokenRingClient::Builder builder;
    TokenRingClient client;
    Message msg;
    std::stringstream parser;
    const char* client_id = argv[2];
    unsigned short client_port;
    char tmp;
    unsigned short destination_port;
    unsigned short destination_ip[4];

    client_port = atoi(argv[1]);

    if(argc < 6) {
        builder.set_active_token()
                .dont_join();
        if(atoi(argv[3]))
            builder.set_print_diagnostic();
    } else {
        destination_port = atoi(argv[3]);
        parser << argv[4];
        parser >> destination_ip[0] >> tmp >> destination_ip[1] >> tmp
                >> destination_ip[2] >> tmp >> destination_ip[3];
        builder.set_next_port(destination_port);
        builder.set_next_ip(destination_ip);
        if(atoi(argv[5]))
            builder.set_print_diagnostic();
    }

    client = builder.set_id(client_id)
            .set_port(client_port)
            .build();
    std::string command;
    client.run();
    while(true) {
        std::cin >> command;
        if (command == "q" || command == "exit" || command == "quit") break;
        std::cin >> msg.content >> msg.port_to >> msg.ip_to[0] >> msg.ip_to[1]
            >> msg.ip_to[2] >> msg.ip_to[3];
        client.send_message(msg);
    }

    while(true) {
        msg = client.read_message();
        std::cout << "Message from " << msg.ip_from[0] << "." << msg.ip_from[1]
            << "." << msg.ip_from[2] << "." << msg.ip_from[3] << ":" << msg.port_from
            << "\t" << msg.content << std::endl;
    }
}