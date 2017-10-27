#pragma once

#include <stdint.h>
#include <type_traits>
#include <utility>

namespace Generic {

template <typename T>
struct has_begin
{
    using yes = uint8_t;
    using no = uint16_t;

    template <typename C>
    static yes test(decltype( std::declval<C>().begin() )* );
    template <typename C>
    static no test(...);

    static const bool value = (sizeof(test<T>(nullptr)) == sizeof(yes));
};

template <typename T>
struct has_size
{
    using yes = uint8_t;
    using no = uint16_t;

    template <typename C>
    static yes test(decltype( std::declval<C>().size() )* );
    template <typename C>
    static no test(...);

    static const bool value = (sizeof(test<T>(nullptr)) == sizeof(yes));
};

template <typename T>
struct is_stl_container
{
    static const bool value = has_begin<T>::value && has_size<T>::value;
};

} // namespace Generic

