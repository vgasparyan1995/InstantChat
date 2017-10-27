#pragma once

#include <iostream>
#include <utility>

#include "Utility.h"

namespace Generic {

template <typename ResultT, typename OutputT>
ResultT ConsoleManager::askFor(OutputT&& output)
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    write(std::forward<OutputT>(output));
    ResultT result;
    std::cin >> result;
    return result;
}

template <typename OutputT>
void ConsoleManager::write(OutputT&& output)
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    std::cout << output;
}

template <typename OutputT>
void ConsoleManager::writeLine(OutputT&& output)
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    std::cout << output << std::endl;
}

} // namespace Generic
