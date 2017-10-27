#include <iostream>

#include "ConfigManager.h"
#include "Generic/SignalHandler.h"
#include "ServerManager.h"

namespace Server {

void execute()
{
    auto& confMgr = ConfigManager::getInstance();
    confMgr.initialize();
    auto& server = ServerManager::getInstance();
    server.setPort(confMgr.getPort());
    server.setFTPPort(confMgr.getFTPPort());
    server.start();
}

}

int main()
{
    Generic::setSignalHandlers();
    try {
        Server::execute();
    } catch (std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "Unknown Exception caught." << std::endl;
    }
    Generic::normalExit();
}
