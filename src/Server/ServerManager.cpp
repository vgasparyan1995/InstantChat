#include "ChatServer.h"

#include "ServerManager.h"

namespace Server {

SINGLETON_DEFINITION(ServerManager)

void ServerManager::setPort(const uint16_t port)
{
    m_port = port;
}

void ServerManager::start()
{
    asio::io_service service;
    asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v4(), m_port);
    ChatServer server(service, endpoint);
    service.run();
}

ServerManager::ServerManager()
    : m_port(0)
{
}

} // namespace Server
