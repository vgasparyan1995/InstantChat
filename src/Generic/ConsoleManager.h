#pragma once

#include <mutex>
#include <string>

#include "SingletonBase.h"

namespace Generic {

class ConsoleManager : public SingletonBase
{
SINGLETON_INTERFACE(ConsoleManager)

public:
    template <typename ResultT, typename OutputT>
    ResultT askFor(OutputT&& output);

    template <typename OutputT>
    void write(OutputT&& output);

    template <typename OutputT>
    void writeLine(OutputT&& output);

    std::string readLine();

private:
    ConsoleManager() = default;
    ~ConsoleManager() = default;

private:
    std::recursive_mutex m_mutex;
};

} // namespace Generic

#include "ConsoleManager.hpp"
