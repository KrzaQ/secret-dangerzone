#ifndef _KQ_RANGE_H_
#define _KQ_RANGE_H_

#include <limits>
#include <stdexcept>
#include <type_traits>

#include <kq/character_pack_utils.h>
#include <kq/def.h>
#include <kq/math.h>
#include <kq/type_traits.h>

namespace kq
{

template<typename T = ullong>
struct RangeImpl
{
	struct RangeIterator
	{
		constexpr RangeIterator(T value, T step, bool up) : value(value), step(step), up(up) {}

		T& operator*() { return value; }
		constexpr T const& operator*() const { return value; }

		constexpr bool operator!=(RangeIterator const& other) const { return up ? *other > value : *other < value; }

		RangeIterator& operator++() { up ? value += step : value -= step; return *this; }

		T value;
		T step;
		bool up;
	};


	constexpr RangeImpl(T min, T max, T step) : min(min), max(max), step(step) {}

	constexpr RangeImpl operator,(T step) const { return RangeImpl(min,max,step); }

	constexpr RangeIterator begin() const { return RangeIterator(min,step,min < max); }
	constexpr RangeIterator end() const { return RangeIterator(max,step,min < max); }

	template<typename U>
	constexpr typename std::enable_if<std::is_integral<T>::value && std::is_floating_point<U>::value,RangeImpl<U>>::type
	operator,(U step) const { return RangeImpl<U>(min,max,step); }

	T min;
	T max;
	T step;
};

constexpr RangeImpl<> range(ullong min, ullong max, ullong step = 1)
{
	return RangeImpl<>(min,max,step);
}

namespace human_readable_range
{

namespace impl
{

template<typename T = ldouble>
struct RangeHelper
{
	typedef kq::signed_type<T> signedT;

	constexpr RangeHelper(T max) : max(max) {}

	constexpr RangeHelper<signedT> operator-() const {
		return max > static_cast<T>(std::numeric_limits<signedT>::max()) ?
					throw std::invalid_argument("max value too high") :
					RangeHelper<signedT>(-static_cast<signedT>(max));
	}

	T max;
};

template<char... c>
struct FloatingRangeHelper : RangeHelper<ldouble>
{
	constexpr FloatingRangeHelper() : RangeHelper(character_pack::get_floating_point_value<c...>()) {}
};

template <typename T, T value>
struct IntegralRangeHelper
{
	typedef kq::signed_type<T> signedT;

	constexpr T get_value() const { return value; }

	constexpr typename std::enable_if<value <= static_cast<T>(std::numeric_limits<signedT>::max()), IntegralRangeHelper<signedT,-static_cast<signedT>(value)>>::type
	operator-() const {
		static_assert(value <= static_cast<T>(std::numeric_limits<signedT>::max()),"maximum range value too big.");
		return IntegralRangeHelper<signedT,-static_cast<signedT>(value)>();
	}
};

template<bool=true, char... c> struct helper_select { typedef IntegralRangeHelper<ullong,character_pack::get_integral_value<c...>::value> type; };
template<char... c> struct helper_select<false,c...> { typedef FloatingRangeHelper<c...> type; };

template<char... c>
using rangehelper = typename helper_select<character_pack::is_integral<c...>::value,c...>::type;

}

template<ullong value>
constexpr RangeImpl<ullong> operator-(ullong min, impl::IntegralRangeHelper<ullong,value> const& max)
{
	return RangeImpl<ullong>(min,max.get_value(),1);
}

template<llong value>
constexpr RangeImpl<llong> operator-(ullong min, impl::IntegralRangeHelper<llong,value> const& max)
{
	return RangeImpl<llong>(min,max.get_value(),1);
}


constexpr RangeImpl<ldouble> operator-(ldouble min, impl::RangeHelper<ldouble> const& max)
{
	return RangeImpl<ldouble>(min,max.max,1);
}


template <char... c>
constexpr impl::rangehelper<c...> operator"" _range()
{
	typedef impl::rangehelper<c...> type;
	return type();
}

}

}

#endif // _KQ_RANGE_H_
