#ifndef UTILS_HPP
#define UTILS_HPP

#include <random>
#include <type_traits>

namespace kq{


namespace detail{
template<typename T, bool = std::is_integral<T>::value>
struct uniform_distribution{
	using type = std::uniform_int_distribution<T>;
};

template<typename T>
struct uniform_distribution<T, false>{
	using type = std::uniform_real_distribution<T>;
};

}

template<typename T>
typename std::remove_reference<T>::type const&
as_const(T&& t){
	return t;
}

}


#endif // UTILS_HPP
