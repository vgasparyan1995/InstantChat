#include <chrono>

#include "ConfigManager.h"
#include "TUIManager.h"

#include "ClientManager.h"

namespace Client {

SINGLETON_DEFINITION(ClientManager)

bool ClientManager::connectToServer(const std::string& host, const std::string& port)
{
    try {
        asio::io_service service;
        asio::ip::tcp::resolver resolver(service);
        auto endpointIter = resolver.resolve({ host.c_str(), port.c_str() }); 
        ChatClient cClient(service, endpointIter);
        std::thread t([&service] () { service.run(); });
        std::this_thread::sleep_for(std::chrono::seconds(1));
        auto messageWriter = [&cClient] (const Generic::ChatMessage& msg)
            {
                cClient.write(msg);
            };
        auto& tuiMgr = TUIManager::getInstance();
        tuiMgr.setMessageWriter(messageWriter);
        tuiMgr.start();
        cClient.close();
        t.join();
    } catch (...) {
        return false;
    }
    return true;
}


Generic::ChatMessage ClientManager::greetingMessage() const
{
    Generic::ChatMessage result;
    result.setSender(ConfigManager::getInstance().getUsername());
    result.setText("Joined!");
    result.encode();
    return result;
}

} // namespace Client
