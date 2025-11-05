//
// Created by DoktorovAlexander on 01.11.2025.
//

#ifndef SENDER_HPP
#define SENDER_HPP

#include <mutex>
#include <string>
#include <thread>
#include <atomic>
#include <deque>

#include "IClient.hpp"
#include "Message.hpp"

using Callback = std::function<void(httplib::Result)>;

struct MessageData {
    Message message;
    Callback callback;
};

class Sender {
public:
    explicit Sender(IClient* client, size_t maxQueueSize);
    ~Sender();

    void Start();
    void Stop();

    bool QueueMessage(Message message, Callback callback);
private:
    void SendLoop();

    std::thread m_SendThread;
    std::mutex m_Mtx;
    std::deque<MessageData> m_MessageQueue;
    std::atomic<bool> m_IsRunning;
    const size_t m_MaxQueueSize = 0;
    IClient* m_Client = nullptr;
    std::condition_variable m_Cv;
};

#endif //SENDER_HPP
