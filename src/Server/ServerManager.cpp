#include "ChatServer.h"
#include "FTServer.h"

#include "ServerManager.h"

namespace Server {

SINGLETON_DEFINITION(ServerManager)

void ServerManager::setPort(const uint16_t port)
{
    m_port = port;
}

void ServerManager::setFTPPort(const uint16_t port)
{
    m_ftpPort = port;
}

void ServerManager::start()
{
    asio::io_service service;
    asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v4(), m_port);
    ChatServer cServer(service, endpoint);
    asio::ip::tcp::endpoint ftpEndpoint(asio::ip::tcp::v4(), m_ftpPort);
    FTServer fServer(service, ftpEndpoint);
    service.run();
}

ServerManager::ServerManager()
    : m_port(0)
    , m_ftpPort(0)
{
}

} // namespace Server
