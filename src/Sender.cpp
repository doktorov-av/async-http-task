//
// Created by DoktorovAlexander on 01.11.2025.
//

#include "Sender.hpp"

Sender::Sender(IClient *client, size_t maxQueueSize) : m_IsRunning(false), m_MaxQueueSize(maxQueueSize),
                                                       m_Client(client) {
    assert(maxQueueSize > 0 && "queue size must be positive");
    assert(client);
}

Sender::~Sender() {
    Stop();
}

void Sender::Start() {
    if (m_IsRunning.exchange(true)) {
        return;
    }

    m_SendThread = std::thread(&Sender::SendLoop, this);
}

void Sender::SendLoop() {
    while (m_IsRunning) {
        MessageData messageData{};
        {
            std::unique_lock lock(m_Mtx);
            m_Cv.wait(lock, [this]() { return !m_IsRunning || !m_MessageQueue.empty(); });

            if (!m_IsRunning) {
                return;
            }

            if (!m_MessageQueue.empty()) {
                messageData = std::move(m_MessageQueue.front());
                m_MessageQueue.pop_front();
            } else {
                continue;
            }
        }

        try {
            auto result = m_Client->Send(messageData.message);
            if (messageData.callback) {
                messageData.callback(std::move(result));
            }
        } catch (std::exception &e) {
            std::cerr << "message couldn't be sent: " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "unknown exception thrown sending message\n";
        }
    }
}

bool Sender::QueueMessage(Message message, Callback callback) {
    if (!IsValid(message)) {
        return false;
    }

    std::unique_lock lock(m_Mtx);
    assert(m_MessageQueue.size() <= m_MaxQueueSize);

    if (m_MaxQueueSize == m_MessageQueue.size()) {
        m_MessageQueue.pop_front();
    }

    m_MessageQueue.emplace_back(MessageData{
        std::move(message),
        std::move(callback)
    });

    lock.unlock();
    m_Cv.notify_one();

    return true;
}

void Sender::Stop() {
    m_IsRunning.store(false);
    m_Cv.notify_one();

    if (m_SendThread.joinable())
        m_SendThread.join();
}
