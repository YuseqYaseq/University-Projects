//
// Created by joseph on 08.03.19.
//

#ifndef ZAD1_MESSAGE_H
#define ZAD1_MESSAGE_H

#include <string>

struct Message {
    char content[1024];
    unsigned short port_to;
    unsigned short ip_to[4];
    unsigned short port_from;
    unsigned short ip_from[4];
};

#endif //ZAD1_MESSAGE_H
