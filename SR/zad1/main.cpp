#include <iostream>
#include <unistd.h>

#include "TokenRingClient.h"

const char* id1 = "jeden";
const char* id2 = "dwa";
const char* id3 = "trzy";
const unsigned short port1 = 10007;
const unsigned short port2 = 10008;
const unsigned short port3 = 10009;

const unsigned short localhost[4] = {127, 0, 0, 1};

int main(int argc, const char* argv[]) {

    TokenRingClient::Builder builder;

    TokenRingClient client1 = builder.set_active_token()
            .dont_join()
            .set_id(id1)
            //.set_next_ip(localhost)
            .set_port(port1)
            //.set_next_port(port2)
            .build();


    TokenRingClient client2 = builder
            .set_id(id2)
            .set_next_ip(localhost)
            .set_port(port2)
            .set_next_port(port1)
            .build();

    TokenRingClient client3 = builder
            .set_id(id3)
            .set_next_ip(localhost)
            .set_port(port3)
            .set_next_port(port1)
            .build();

    client1.run();

    Message msg1;
    Message msg2;
    msg1.content[0] = 'd';
    msg1.content[1] = 'u';
    msg1.content[2] = 'p';
    msg1.content[3] = 'a';
    msg1.content[4] = '1';
    msg2.content[0] = 'd';
    msg2.content[1] = 'u';
    msg2.content[2] = 'p';
    msg2.content[3] = 'a';
    msg2.content[4] = '2';
    msg1.ip_to[0] = msg2.ip_to[0] = 10;
    msg1.ip_to[1] = msg2.ip_to[1] = 0;
    msg1.ip_to[2] = msg2.ip_to[2] = 2;
    msg1.ip_to[3] = msg2.ip_to[3] = 15;
    msg1.port_to = port1; msg2.port_to = port1;
    for(int i = 0; i < 10; ++i)
    client1.send_message(msg1);
    client2.send_message(msg2);

    sleep(2);
    client2.run();
    sleep(2);
    client3.run();
    sleep(1000);

    std::cout << client2.read_message().content << std::endl;
    std::cout << client2.read_message().content << std::endl;

    client1.kill();
    client2.kill();
    return 0;
}