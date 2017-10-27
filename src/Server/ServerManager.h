#pragma once

#include <cstdint>

#include "Generic/SingletonBase.h"

namespace Server {

class ServerManager : public Generic::SingletonBase
{
SINGLETON_INTERFACE(ServerManager)

public:
    void setPort(const uint16_t port);
    void start();

private:
    ServerManager();
    ~ServerManager() = default;

private:
    uint16_t m_port;
};

} // namespace Server
