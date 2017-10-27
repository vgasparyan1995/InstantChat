#pragma once

#include <string>
#include <thread>

#include "ChatClient.h"
#include "Generic/SingletonBase.h"

namespace Client {

class ClientManager : public Generic::SingletonBase
{
SINGLETON_INTERFACE(ClientManager)

public:
    bool connectToServer(const std::string& host, const std::string& port);
    Generic::ChatMessage greetingMessage() const;

private:
    ClientManager() = default;
    ~ClientManager() = default;
};

} // namespace Client
