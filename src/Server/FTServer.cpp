#include <asio.hpp>

#include "FTSession.h"

#include "FTServer.h"

namespace Server {

FTServer::FTServer(asio::io_service& service,
                   const asio::ip::tcp::endpoint& endpoint)
    : m_acceptor(service, endpoint)
    , m_socket(service)
{
    accept();
}

void FTServer::accept()
{
    m_acceptor.async_accept(m_socket,
            [this] (std::error_code ec)
            {
                if (!ec) {
                    std::make_shared<FTSession>(std::move(m_socket), m_room)->start();
                }
                accept();
            });
}

} // namespace Server
