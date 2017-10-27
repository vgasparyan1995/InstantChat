#pragma once

#include <memory>

#include <asio.hpp>

#include "ChatRoom.h"

namespace Server {

class ChatSession : public ChatParticipant,
                    public std::enable_shared_from_this<ChatSession>
{
public:
    explicit ChatSession(asio::ip::tcp::socket&& socket, ChatRoom& room);
    void start();
    void deliver(const Generic::ChatMessage& msg);

private:
    void readHeader();
    void readBody();
    void writeOne();

private:
    asio::ip::tcp::socket   m_socket;
    ChatRoom&               m_room;
    Generic::ChatMessage    m_lastReadMessage;
    ChatMessageQueue        m_messagesToWrite;
};

} // namespace Server
