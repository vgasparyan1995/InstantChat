#pragma once

#include "Generic/SingletonBase.h"

namespace Server {

class ConfigManager : public Generic::SingletonBase
{
SINGLETON_INTERFACE(ConfigManager)

public:
    void initialize();
    uint16_t getPort() const;

private:
    ConfigManager();
    ~ConfigManager();

private:
    uint16_t m_port;
};

} // namespace Server
