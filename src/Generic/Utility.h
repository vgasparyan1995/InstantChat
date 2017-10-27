#pragma once

#include <functional>

namespace Generic {

struct LocalTask
{
    LocalTask(std::function<void ()> preTask,
              std::function<void ()> postTask)
        : m_postTask(postTask)
    {
        preTask();
    }

    ~LocalTask()
    {
        m_postTask();
    }

private:
    std::function<void ()> m_postTask;
};

} // namespace Generic
