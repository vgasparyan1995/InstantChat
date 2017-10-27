#include "Generic/ConsoleManager.h"

#include "ConfigManager.h"

namespace Client {

SINGLETON_DEFINITION(ConfigManager)

void ConfigManager::initialize()
{
    auto& cmgr = Generic::ConsoleManager::getInstance();
    m_username   = cmgr.askFor<std::string>("Your username: ");
    m_serverHost = cmgr.askFor<std::string>("Specify the server host: ");
    m_port       = cmgr.askFor<std::string>("Specify the port: ");
    m_ftpPort    = cmgr.askFor<std::string>("Specify the FTP port: ");
}

std::string ConfigManager::getPort() const
{
    return m_port;
}

std::string ConfigManager::getFTPPort() const
{
    return m_ftpPort;
}

std::string ConfigManager::getServerHost() const
{
    return m_serverHost;
}

std::string ConfigManager::getUsername() const
{
    return m_username;
}

} // namespace Client
