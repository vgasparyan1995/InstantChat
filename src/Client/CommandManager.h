#pragma once

#include <string>

#include "Generic/SingletonBase.h"

namespace Client {

class CommandManager : public Generic::SingletonBase
{
SINGLETON_INTERFACE(CommandManager)

public:
    void execute(const std::string& command) const;

private:
    CommandManager() = default;
    ~CommandManager() = default;
};

} // namespace Client
