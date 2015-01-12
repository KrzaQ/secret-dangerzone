#ifndef KQDEF_H
#define KQDEF_H

#include <cstdint>

typedef std::uint64_t			QWORD;
typedef std::uint32_t			DWORD;
typedef std::uint16_t			WORD;
typedef std::uint8_t			BYTE;

typedef long double				ldouble;

typedef unsigned long long		ullong;
typedef unsigned long			ulong;
typedef unsigned int			uint;
typedef unsigned short			ushort;
typedef unsigned char			uchar;

// char, signed char and unsigned char are all different types
typedef signed char				schar;

typedef long long				llong;

typedef std::uint64_t			u64;
typedef std::uint32_t			u32;
typedef std::uint16_t			u16;
typedef std::uint8_t			u8;

typedef std::int64_t			i64;
typedef std::int32_t			i32;
typedef std::int16_t			i16;
typedef std::int8_t				i8;


namespace kq
{
template <int size, bool is_signed = false>
struct sized_int
{
};

template<> struct sized_int<8,false>
{
	typedef u8 type;
};

template<> struct sized_int<16,false>
{
	typedef u16 type;
};

template<> struct sized_int<32,false>
{
	typedef u32 type;
};

template<> struct sized_int<64,false>
{
	typedef u64 type;
};

template<> struct sized_int<8,true>
{
	typedef i8 type;
};

template<> struct sized_int<16,true>
{
	typedef i16 type;
};

template<> struct sized_int<32,true>
{
	typedef i32 type;
};

template<> struct sized_int<64,true>
{
	typedef i64 type;
};

}

#endif // KQDEF_H
