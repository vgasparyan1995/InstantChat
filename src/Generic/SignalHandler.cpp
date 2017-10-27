#include <csignal>
#include <cstdlib>
#include <iostream>

#include "SingletonStack.h"

#include "SignalHandler.h"

namespace Generic {

void normalExit()
{
    SingletonStack::removeInstance();
    std::exit(0);
}

void handler(int signal)
{
    if (signal == SIGTERM || signal == SIGABRT) {
        std::signal(SIGTERM, SIG_IGN);
        std::signal(SIGABRT, SIG_IGN);
    }
    std::cerr << signal << " signal was handled." << std::endl;
    normalExit();
}

void setSignalHandlers()
{
    std::signal(SIGABRT, handler);
    std::signal(SIGFPE , handler);
    std::signal(SIGILL , handler);
    std::signal(SIGINT , handler);
    std::signal(SIGSEGV, handler);
    std::signal(SIGTERM, handler);
}

} // namespace Generic
