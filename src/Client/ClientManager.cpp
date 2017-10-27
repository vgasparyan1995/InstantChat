#include <chrono>

#include "ConfigManager.h"
#include "TUIManager.h"

#include "ClientManager.h"

namespace Client {

SINGLETON_DEFINITION(ClientManager)

bool ClientManager::connectToServer()
{
    auto configMgr = ConfigManager::getInstance();
    const auto host = configMgr.getHost();
    const auto port = configMgr.getPort();
    const auto ftpPort = configMgr.getFTPPort();
    try {
        asio::io_service service;
        asio::ip::tcp::resolver resolver(service);
        auto endpointIter = resolver.resolve({ host.c_str(), port.c_str() }); 
        ChatClient cClient(service, endpointIter);
        auto ftpEndpointIter = resolver.resolve({ host.c_str(), ftpPort.c_str() }); 
        FTPClient ftpClient(service, ftpEndpointIter);
        std::thread t([&service] () { service.run(); });
        std::this_thread::sleep_for(std::chrono::seconds(1));
        auto messageWriter = [&cClient] (const Generic::ChatMessage& msg)
            {
                cClient.write(msg);
            };
        auto fileSender = [&ftpClient] (const Generic::FilePackage& file)
            {
                ftpClient.send(file);
            };
        auto& tuiMgr = TUIManager::getInstance();
        tuiMgr.setMessageWriter(messageWriter);
        tuiMgr.setFileSender(fileSender);
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
