//
// Created by DoktorovAlexander on 01.11.2025.
//

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <httplib.h>

#include "IClient.hpp"
#include "Message.hpp"

class Client : public IClient {
public:
    explicit Client(const std::string &url);
    httplib::Result Send(const Message &message) override;
private:
    httplib::Client m_HttpClient;
};

#endif //CLIENT_HPP
