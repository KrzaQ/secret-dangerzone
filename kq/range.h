#ifndef _KQ_RANGE_H_
#define _KQ_RANGE_H_

#include <type_traits>

#include <kq/def.h>
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

template<typename T = ullong>
struct RangeHelper
{
	typedef kq::signed_type<T> signedT;

	constexpr RangeHelper(T max) : max(max) {}

	constexpr RangeHelper<signedT> operator-() const { return RangeHelper<signedT>(-static_cast<signedT>(max)); }

	T max;
};

constexpr RangeImpl<ullong> operator-(ullong min, RangeHelper<ullong> const& max)
{
	return RangeImpl<ullong>(min,max.max,1);
}

constexpr RangeImpl<llong> operator-(ullong min, RangeHelper<llong> const& max)
{
	return RangeImpl<llong>(min,max.max,1);
}

constexpr RangeImpl<ldouble> operator-(ldouble min, RangeHelper<ldouble> const& max)
{
	return RangeImpl<ldouble>(min,max.max,1);
}

constexpr RangeHelper<> operator"" _range(ullong max)
{
	return RangeHelper<>(max);
}

constexpr RangeHelper<ldouble> operator"" _range(ldouble max)
{
	return RangeHelper<ldouble>(max);
}

}

}

#endif // _KQ_RANGE_H_
