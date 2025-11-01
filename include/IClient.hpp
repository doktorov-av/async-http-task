//
// Created by DoktorovAlexander on 01.11.2025.
//

#ifndef ISENDER_HPP
#define ISENDER_HPP

#include "httplib.h"
#include "Message.hpp"

struct IClient {
    virtual ~IClient() = default;
    virtual httplib::Result Send(const Message &message) = 0;
};

#endif //ISENDER_HPP
