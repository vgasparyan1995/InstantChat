#include "Generic/ConsoleManager.h"

#include "ConfigManager.h"

namespace Server {

SINGLETON_DEFINITION(ConfigManager)

void ConfigManager::initialize()
{
    auto& cmgr = Generic::ConsoleManager::getInstance();
    m_port = cmgr.askFor<unsigned short>("Specify the port: ");
}

uint16_t ConfigManager::getPort() const
{
    return m_port;
}

ConfigManager::ConfigManager()
    : m_port(0)
{
}

ConfigManager::~ConfigManager()
{
}

} // namespace Server
