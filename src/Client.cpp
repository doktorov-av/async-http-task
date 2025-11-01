//
// Created by DoktorovAlexander on 01.11.2025.
//

#include "Client.hpp"

Client::Client(const std::string &url) : m_HttpClient(url) {
}

httplib::Result Client::Send(const Message &message) {
    using std::string_literals::operator ""s;

    if (!IsValid(message)) {
        throw std::invalid_argument("message is not valid");
    }

    const auto content = std::string(reinterpret_cast<const char *>(message.image.data()), message.image.size());
    const auto items = httplib::UploadFormDataItems{
        httplib::UploadFormData{
            .name = "image"s,
            .content = content,
            .filename = "image.png"s,
            .content_type = "image/png"s
        },
        httplib::UploadFormData{
            .name = "payload_json"s,
            .content = json(message.payload).dump(),
            .filename = {},
            .content_type = "application/json"s,
        },
    };

    return m_HttpClient.Post("/api/photos"s, items);
}
