//
// Created by DoktorovAlexander on 01.11.2025.
//

#include "Client.hpp"

inline constexpr auto g_Endpoint ="/api/photos";

Client::Client(const std::string &url) : m_HttpClient(url) {
}

httplib::Result Client::Send(const Message &message) {
    if (!IsValid(message)) {
        throw std::invalid_argument("message is not valid");
    }

    const auto content = std::string(reinterpret_cast<const char *>(message.image.data()), message.image.size());
    const auto items = httplib::UploadFormDataItems{
        httplib::UploadFormData{
            .name = "image",
            .content = content,
            .filename = "image.png",
            .content_type = "image/png"
        },
        httplib::UploadFormData{
            .name = "payload_json",
            .content = json(message.payload).dump(),
            .filename = {},
            .content_type = "application/json",
        },
    };

    return m_HttpClient.Post(g_Endpoint, items);
}
