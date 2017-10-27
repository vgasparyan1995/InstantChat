#include "ConsoleManager.h"

namespace Generic {

SINGLETON_DEFINITION(ConsoleManager)

std::string ConsoleManager::readLine()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    std::string result;
    std::getline(std::cin, result);
    return result;
}

} // namespace Generic
