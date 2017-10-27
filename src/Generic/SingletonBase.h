#pragma once

#include "SingletonStack.h"

namespace Generic {

struct SingletonBase
{
public:
    SingletonBase() = default;
    virtual ~SingletonBase() = default;
    SingletonBase(const SingletonBase&) = delete;
    SingletonBase(SingletonBase&&) = delete;
    SingletonBase& operator= (const SingletonBase&) = delete;
    SingletonBase& operator= (SingletonBase&&) = delete;
};

} // namespace Generic

#include "TypeUtil.h"

#define SINGLETON_INTERFACE(Class) \
public:\
static Class& getInstance(); \
private: \
static Class* s_instance;

#define SINGLETON_DEFINITION(Class) \
Class* Class::s_instance = nullptr; \
Class& Class::getInstance() \
{ \
    if (s_instance == nullptr) { \
        s_instance = new Class(); \
        Generic::AddToSingletonStack<std::is_base_of<SingletonBase, Class>::value>::exec(s_instance); \
    }\
    return *s_instance; \
}
