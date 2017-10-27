#include <iostream>

#include "ClientManager.h"
#include "ConfigManager.h"
#include "Generic/SignalHandler.h"
#include "TUIManager.h"

namespace Client {

void execute()
{
    auto& confMgr = ConfigManager::getInstance();
    confMgr.initialize();
    auto& clientMgr = ClientManager::getInstance();
    if (!clientMgr.connectToServer()) {
        std::cerr << "Could not reach the server." << std::endl;
    }
}

}

int main()
{
    Generic::setSignalHandlers();
    try {
        Client::execute();
    } catch (std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown Exception caught." << std::endl;
    }
    Generic::normalExit();
}
