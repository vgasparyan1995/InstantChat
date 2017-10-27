#pragma once

#include <type_traits>

namespace Generic {

template <bool HasSingletonBase>
struct AddToSingletonStack
{
    static void exec(...) { }
};

template <>
struct AddToSingletonStack<true>
{
    static void exec(Generic::SingletonBase* instance)
    {
        Generic::SingletonStack::getInstance().push(instance);
    }
};


} // namespace Generic
