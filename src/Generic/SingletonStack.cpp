#include "SingletonBase.h"

#include "SingletonStack.h"

namespace Generic {

SingletonStack* SingletonStack::s_instance = nullptr;

SingletonStack& SingletonStack::getInstance()
{
    if (s_instance == nullptr) {
        s_instance = new SingletonStack();
    }
    return *s_instance;
}

void SingletonStack::removeInstance()
{
    delete s_instance;
    s_instance = nullptr;
}

SingletonStack::~SingletonStack()
{
    while (!m_stack.empty()) {
        delete m_stack.top();
        m_stack.pop();
    }
}

void SingletonStack::push(const SingletonBase* instance)
{
    m_stack.push(instance);
}

} // namespace Generic
