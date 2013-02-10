#ifndef CHARACTER_PACK_UTILS_H
#define CHARACTER_PACK_UTILS_H

#include <type_traits>

#include <kq/def.h>
#include <kq/math.h>

namespace kq
{

namespace character_pack
{

template <char value>
struct digit{};

template<> struct digit<'0'> { constexpr static uint value = 0; };
template<> struct digit<'1'> { constexpr static uint value = 1; };
template<> struct digit<'2'> { constexpr static uint value = 2; };
template<> struct digit<'3'> { constexpr static uint value = 3; };
template<> struct digit<'4'> { constexpr static uint value = 4; };
template<> struct digit<'5'> { constexpr static uint value = 5; };
template<> struct digit<'6'> { constexpr static uint value = 6; };
template<> struct digit<'7'> { constexpr static uint value = 7; };
template<> struct digit<'8'> { constexpr static uint value = 8; };
template<> struct digit<'9'> { constexpr static uint value = 9; };
template<> struct digit<'a'> { constexpr static uint value = 10; };
template<> struct digit<'b'> { constexpr static uint value = 11; };
template<> struct digit<'c'> { constexpr static uint value = 12; };
template<> struct digit<'d'> { constexpr static uint value = 13; };
template<> struct digit<'e'> { constexpr static uint value = 14; };
template<> struct digit<'f'> { constexpr static uint value = 15; };
template<> struct digit<'A'> { constexpr static uint value = 10; };
template<> struct digit<'B'> { constexpr static uint value = 11; };
template<> struct digit<'C'> { constexpr static uint value = 12; };
template<> struct digit<'D'> { constexpr static uint value = 13; };
template<> struct digit<'E'> { constexpr static uint value = 14; };
template<> struct digit<'F'> { constexpr static uint value = 15; };


template<char c, char... Cs>
struct is_integral
{
	constexpr static bool value = c != '.' && is_integral<Cs...>::value;
};

template<char c>
struct is_integral<c>
{
	constexpr static bool value = c != '.';
};

template <char c, char... Cs>
struct has_x
{
	constexpr static bool value = c == 'x' ? true : has_x<Cs...>::value;
};

template <char c>
struct has_x<c>
{
	constexpr static bool value = c == 'x' ? true : false;
};

template <char c, char... Cs>
struct get_decimal_value
{
	constexpr static ullong value = digit<c>::value * kq::template_math::Power<10,sizeof...(Cs)>::value + get_decimal_value<Cs...>::value;
};

template <char c>
struct get_decimal_value<c>
{
	constexpr static ullong value = digit<c>::value;
};

template <char c, char... Cs>
struct get_hexadecimal_value
{
	constexpr static ullong value = digit<c>::value * kq::template_math::Power<16,sizeof...(Cs)>::value + get_hexadecimal_value<Cs...>::value;
};

template <char... Cs>
struct get_hexadecimal_value<'0','x',Cs...>
{
	constexpr static ullong value = get_hexadecimal_value<Cs...>::value;
};

template <char c>
struct get_hexadecimal_value<c>
{
	constexpr static ullong value = digit<c>::value;
};

template<bool=true, char... c> struct get_integral_type { typedef get_hexadecimal_value<c...> type; };
template<char... c> struct get_integral_type<false,c...> { typedef get_decimal_value<c...> type; };

template <char... c>
struct get_integral_value
{
	typedef std::integral_constant<bool,has_x<c...>::value> is_hex;

	constexpr static ullong value = get_integral_type<is_hex::value, c...>::type::value;
};


template<unsigned index, bool, char... Cs>
struct get_dot_index_helper
{
	constexpr static unsigned value = index;
};

template <unsigned index, char c, char... Cs>
struct get_dot_index;

template<unsigned index, char... Cs>
struct get_dot_index_helper<index,false, Cs...>
{
	constexpr static unsigned value = get_dot_index<index+1,Cs...>::value;
};


template <unsigned index, char c, char... Cs>
struct get_dot_index
{
	constexpr static unsigned value = get_dot_index_helper<index,c == '.',Cs...>::value;
};

template <unsigned index, char c>
struct get_dot_index<index,c>
{
	constexpr static typename std::enable_if<c=='.',unsigned>::type value = index;
};

template<int dot, char first, char... c>
struct get_integral_part
{
	constexpr static ullong value = dot != 0 ? (first-'0')*kq::template_math::Power<10,sizeof...(c)-(dot>0?1:0)>::value + get_integral_part<dot-1,c...>::value : get_integral_part<dot-1,c...>::value;
};

template<int dot, char first>
struct get_integral_part<dot,first>
{
	constexpr static ullong value = dot != 0 ? first-'0' : 0;
};

template <char... Cs>
constexpr ldouble get_floating_point_value()
{
	typedef std::integral_constant<unsigned,get_dot_index<0,Cs...>::value> dot_at;
	typedef std::integral_constant<ullong,get_integral_part<static_cast<int>(dot_at::value),Cs...>::value> integral_part;

	return static_cast<ldouble>(integral_part::value)/static_cast<ldouble>(kq::template_math::Power<10,sizeof...(Cs)-dot_at::value-1>::value);
}

}
}

#endif // CHARACTER_PACK_UTILS_H
