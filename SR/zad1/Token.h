//
// Created by joseph on 08.03.19.
//

#ifndef ZAD1_TOKEN_H
#define ZAD1_TOKEN_H

struct Token {
    unsigned short ip_from[4];
    unsigned short port_from;
    unsigned short ip_to[4];
    unsigned short port_to[4];
    bool currently_used;
    char msg[1024];
};

#endif //ZAD1_TOKEN_H
