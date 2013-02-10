#ifndef TYPE_TRAITS_H
#define TYPE_TRAITS_H

#include <type_traits>

#include <kq/def.h>

namespace kq
{

namespace impl
{

template<typename T, bool = std::is_integral<T>::value> struct make_signed { typedef T type; };
template<typename T> struct make_signed<T, true> { typedef typename std::make_signed<T>::type type; };

template<typename T, bool = std::is_integral<T>::value> struct make_biggest { typedef typename std::conditional<std::is_signed<T>::value,llong,ullong>::type type; };
template<typename T> struct make_biggest<T, true> { typedef typename std::make_signed<T>::type type; };

}

template<typename T>
using signed_type = typename kq::impl::make_signed<T>::type;

template<typename T>
using biggest_type = typename kq::impl::make_biggest<T>::type;

template<typename first, typename... Ts>
struct first_type { typedef first type; };

}

#endif // TYPE_TRAITS_H
