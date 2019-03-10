//
// Created by joseph on 08.03.19.
//

#ifndef ZAD1_TOKEN_H
#define ZAD1_TOKEN_H

#include "Message.h"

struct Token {
    Message msg;
    bool currently_used;

    //0 - standard token
    //1 - I want to be your server
    //2 - I want to be your client
    int new_client_flag;
};

#endif //ZAD1_TOKEN_H
