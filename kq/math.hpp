#ifndef MATH_H
#define MATH_H

#include <kq/def.h>

namespace kq
{

namespace template_math
{

template <ullong base, ullong exp>
struct Power
{
	constexpr static ullong value = base * Power<base,exp-1>::value;
};

template <ullong base>
struct Power<base,0>
{
	constexpr static ullong value = 1;
};

}

namespace constexpr_math
{

}

}

#endif // MATH_H
