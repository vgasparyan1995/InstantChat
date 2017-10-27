#pragma once

#include <string>

#include "Generic/SingletonBase.h"

namespace Client {

class ConfigManager : public Generic::SingletonBase
{
SINGLETON_INTERFACE(ConfigManager)

public:
    void initialize();
    std::string getPort() const;
    std::string getFTPPort() const;
    std::string getServerHost() const;
    std::string getUsername() const;

private:
    ConfigManager() = default;
    ~ConfigManager() = default;

private:
    std::string m_username;
    std::string m_port;
    std::string m_ftpPort;
    std::string m_serverHost;
};

} // namespace Client
