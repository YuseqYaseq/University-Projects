#include <iostream>
#include <unistd.h>

#include "TokenRingClient.h"

const char* id1 = "jeden";
const char* id2 = "dwa";
const unsigned short port1 = 10007;
const unsigned short port2 = 10008;

const unsigned short localhost[4] = {127, 0, 0, 1};

int main(int argc, const char* argv[]) {

    TokenRingClient::Builder builder;

    TokenRingClient client1 = builder.set_active_token()
            .set_id(id1)
            .set_next_ip(localhost)
            .set_port(port1)
            .set_next_port(port2)
            .build();

    TokenRingClient client2 = builder
            .set_id(id2)
            .set_next_ip(localhost)
            .set_port(port2)
            .set_next_port(port1)
            .build();

    client1.run();
    client2.run();

    const char* msg1 = "dupa1";
    const char* msg2 = "dupa2";
    client1.send_message(msg1);
    client1.send_message(msg2);

    sleep(10);

    std::cout << client2.read_message() << std::endl;
    std::cout << client2.read_message() << std::endl;

    client1.kill();
    client2.kill();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}