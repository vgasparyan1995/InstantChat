#include <asio.hpp>

#include "ChatServer.h"
#include "ChatSession.h"

namespace Server {

ChatServer::ChatServer(asio::io_service& service,
                       const asio::ip::tcp::endpoint& endpoint)
    : m_acceptor(service, endpoint)
    , m_socket(service)
{
    accept();
}

void ChatServer::accept()
{
    m_acceptor.async_accept(m_socket,
            [this] (std::error_code ec)
            {
                if (!ec) {
                    std::make_shared<ChatSession>(std::move(m_socket), m_room)->start();
                }
                accept();
            });
}

} // namespace Server
