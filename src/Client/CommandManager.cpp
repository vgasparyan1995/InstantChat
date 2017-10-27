#include <cstring>
#include <sstream>
#include <utility>

#include "CommandManager.h"
#include "Generic/FilePackage.h"
#include "Generic/FileUtils.h"
#include "Generic/SignalHandler.h"
#include "TUIManager.h"

namespace Client {

SINGLETON_DEFINITION(CommandManager)

void CommandManager::execute(const std::string& command) const
{
    std::istringstream s(command);
    std::string cmd;
    s >> cmd;
    if (std::memcmp(cmd.data(), "exit", 4) == 0) {
        Generic::normalExit();
    } else if (std::memcmp(cmd.data(), "send", 4) == 0) {
        try {
            std::string filename;
            s >> filename;
            auto fileRawData = Generic::FileUtils::readFile(filename);
            if (fileRawData.empty()) {
                return;
            }
            Generic::FilePackage file;
            file.setFilename(Generic::FileUtils::removeDir(filename).c_str());
            file.setFile(std::move(fileRawData));
            file.encode();
            TUIManager::getInstance().sendFile(file);
        } catch (...) {
            TUIManager::getInstance().print("Unable to send file.\n");
        }
    } else {
        const std::string help = "\'" + cmd + "\' is not a command. Try \'exit\' or \'send <filename>\'.\n";
        TUIManager::getInstance().print(help.c_str());
    }
}

} // namespace Client
