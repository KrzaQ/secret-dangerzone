#ifndef TYPE_TRAITS_H
#define TYPE_TRAITS_H

#include <type_traits>

namespace kq
{

namespace impl
{

template<typename T, bool = std::is_integral<T>::value> struct make_signed { typedef T type; };
template<typename T> struct make_signed<T, true> { typedef typename std::make_signed<T>::type type; };

}

template<typename T>
using signed_type = typename kq::impl::make_signed<T>::type;

}

#endif // TYPE_TRAITS_H
