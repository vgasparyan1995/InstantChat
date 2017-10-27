#pragma once

#include <stack>

namespace Generic {

struct SingletonBase;

class SingletonStack
{
public:
    static SingletonStack& getInstance();
    static void removeInstance();

private:
    static SingletonStack* s_instance;

private:
    SingletonStack() = default;
    ~SingletonStack();
    SingletonStack(const SingletonStack&) = delete;
    SingletonStack(SingletonStack&&) = delete;
    SingletonStack operator= (const SingletonStack&) = delete;
    SingletonStack operator= (SingletonStack&&) = delete;

public:
    void push(const SingletonBase* instance);

private:
    std::stack<const SingletonBase*> m_stack;
};

} // namespace Generic
