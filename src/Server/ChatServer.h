#pragma once

#include <asio.hpp>

#include "ChatRoom.h"

namespace Server {

class ChatServer
{
public:
    explicit ChatServer(asio::io_service& service,
                        const asio::ip::tcp::endpoint& endpoint);
private:
    void accept();

private:
    asio::ip::tcp::acceptor m_acceptor;
    asio::ip::tcp::socket   m_socket;
    ChatRoom                m_room;
};

} // namespace Server
