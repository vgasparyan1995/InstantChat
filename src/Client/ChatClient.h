#pragma once

#include <queue>

#include <asio.hpp>

#include "Generic/ChatMessage.h"

namespace Client {

using ChatMessageQueue = std::queue<Generic::ChatMessage>;

class ChatClient
{
public:
    explicit ChatClient(asio::io_service& service,
                        asio::ip::tcp::resolver::iterator endpointIter);
    void write(const Generic::ChatMessage& msg);
    void close();

private:
    void connect(asio::ip::tcp::resolver::iterator endpointIter);
    void readHeader();
    void readBody();
    void writeOne();

private:
    asio::io_service&       m_service;
    asio::ip::tcp::socket   m_socket;
    Generic::ChatMessage    m_lastReadMessage;
    ChatMessageQueue        m_messagesToWrite;
};

} // namespace Client
