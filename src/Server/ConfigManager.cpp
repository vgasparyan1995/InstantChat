#include "Generic/ConsoleManager.h"

#include "ConfigManager.h"

namespace Server {

SINGLETON_DEFINITION(ConfigManager)

void ConfigManager::initialize()
{
    auto& cmgr = Generic::ConsoleManager::getInstance();
    m_port = cmgr.askFor<unsigned short>("Specify the port: ");
    m_ftpPort = cmgr.askFor<unsigned short>("Specify the FTP port: ");
}

uint16_t ConfigManager::getPort() const
{
    return m_port;
}

uint16_t ConfigManager::getFTPPort() const
{
    return m_ftpPort;
}

ConfigManager::ConfigManager()
    : m_port(0)
{
}

ConfigManager::~ConfigManager()
{
}

} // namespace Server
