#pragma once

#include <string>
#include <thread>

#include "Generic/ChatMessage.h"
#include "Generic/SingletonBase.h"

namespace Client {

class ClientManager : public Generic::SingletonBase
{
SINGLETON_INTERFACE(ClientManager)

public:
    bool connectToServer();
    Generic::ChatMessage greetingMessage() const;

private:
    ClientManager() = default;
    ~ClientManager() = default;
};

} // namespace Client
