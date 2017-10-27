#include <stringstream>

#include "CommandManager.h"
#include "Generic/FilePackage.h"
#include "Generic/SignalHandler.h"

namespace Client {

SINGLETON_DEFINITION(CommandManager)

void CommandManager::execute(const std::string& command) const
{
    std::istringstream s;
    std::string cmd;
    s >> cmd;
    if (cmd == "exit") {
        Generic::normalExit();
    } else if (cmd == "send") {
        std::string filename;
        s >> filename;
        auto fileRawData = Generic::FileUtils::readFile(filename);
        if (fileRawData.empty()) {
            return;
        }
        FilePackage file;
        file.setFilename(Generic::FileUtils::removeDir(filename));
        file.setFile(fileRawData);
        encode();
        TUIManager::getInstance().sendFile(file);
    }
}

} // namespace Client
