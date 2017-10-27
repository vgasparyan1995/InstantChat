#pragma once

#include "Generic/SingletonBase.h"

namespace Server {

class ConfigManager : public Generic::SingletonBase
{
SINGLETON_INTERFACE(ConfigManager)

public:
    void initialize();
    uint16_t getPort() const;
    uint16_t getFTPPort() const;

private:
    ConfigManager();
    ~ConfigManager();

private:
    uint16_t m_port;
    uint16_t m_ftpPort;
};

} // namespace Server
