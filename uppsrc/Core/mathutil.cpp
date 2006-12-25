#include "Core.h"

// iscale: computes x * y / z.

NAMESPACE_UPP

#if defined(PLATFORM_WIN32) && defined(COMPILER_MSC) && defined(CPU_X86)
#pragma warning(disable: 4035)
#else
#define __NOASSEMBLY__
#endif

int iscale(int x, int y, int z)
{
#ifdef __NOASSEMBLY__
	return int(x * (double)y / z);
#else
	__asm
	{
		mov		eax, [x]
		imul	[y]
		idiv	[z]
	}
#endif
}

// iscalefloor: computes x * y / z, rounded towards -infty.

int iscalefloor(int x, int y, int z)
{
#ifdef __NOASSEMBLY__
	return (int)ffloor(x * (double)y / z);
#else
	__asm
	{
		mov		eax, [x]
		imul	[y]
		idiv	[z]
		and		edx, edx
		jge		__1
		dec		eax
	__1:
	}
#endif
}

// iscaleceil: computes x * y / z, rounded towards +infty.

int iscaleceil(int x, int y, int z)
{
#ifdef __NOASSEMBLY__
	return fceil(x * (double)y / z);
#else
	__asm
	{
		mov		eax, [x]
		imul	[y]
		idiv	[z]
		and		edx, edx
		jle		__1
		inc		eax
	__1:
	}
#endif
}

#ifdef PLATFORM_WIN32
#pragma warning(default: 4035)
#endif

// idivfloor: returns x / y, truncated towards -infinity.

int idivfloor(int x, int y)
{
	return x / y - (x % y < 0);
}

// idivceil: returns x / y, truncated towards +infinity.

int idivceil(int x, int y)
{
	return x / y + (x % y > 0);
}

// itimesfloor: moves x to nearest lower multiple of y.

int itimesfloor(int x, int y)
{
	return y * idivfloor(x, y);
}

// itimesceil: moves x to nearest higher multiple of y.

int itimesceil(int x, int y)
{
	return y * idivceil(x, y);
}

// fround: converts double to nearest integer. Checks integer limits.

int fround(double value)
{
	return value >= INT_MAX ? INT_MAX : value <= INT_MIN ? INT_MIN
		: (int)floor(value + 0.5);
}

// ffloor: converts double to integer rounding towards -infinity. Checks integer limits.

int ffloor(double value)
{
	return value >= INT_MAX ? INT_MAX : value <= INT_MIN ? INT_MIN
		: (int)floor(value);
}

// fceil: converts double to integer rounding towards +infinity. Checks integer limits.

int fceil(double value)
{
	return value >= INT_MAX ? INT_MAX : value <= INT_MIN ? INT_MIN
		: (int)ceil(value);
}

// fround: converts double to nearest integer. Checks integer limits.

int64 fround64(double value)
{
	return value >= INT64_MAX ? INT64_MAX : value <= INT64_MIN ? INT64_MIN
		: (int64)floor(value + 0.5);
}

// ffloor: converts double to integer rounding towards -infinity. Checks integer limits.

int64 ffloor64(double value)
{
	return value >= INT64_MAX ? INT64_MAX : value <= INT64_MIN ? INT64_MIN
		: (int64)floor(value);
}

// fceil: converts double to integer rounding towards +infinity. Checks integer limits.

int64 fceil64(double value)
{
	return value >= INT64_MAX ? INT64_MAX : value <= INT64_MIN ? INT64_MIN
		: (int64)ceil(value);
}

// asString: converts double numbers to strings.

String AsString(double x, int digits)
{
	if(IsNull(x))
		return Null;

	if(fabs(x) >= 1e15)
		return Format("%g", x);

	char h[64];
	strcpy(h, Format("%.*f", abs(digits), x));
	if(digits <= 0)
		return h;
	char* s = h;
	char* e = s + strlen(s);

	if(digits > 0)
	{
		while(e[-1] == '0')
			e--;
		if(e[-1] == '.')
			e--;
		*e = 0;
		if(!strcmp(s, "-0"))
			s++;
	}
	return s;
}

// modulo: working version of math function `fmod'.

double modulo(double x, double y)
{
	return y ? (x - y * floor(x / y)) : x;
}

int ilog10(double d)
{
	if(IsNull(d) || d == 0)
		return Null;
	return fceil(log10(fabs(d)));
}

double ipow10(int i)
{
	static const double pow_tbl[] =
	{
		1e00,
		1e01, 1e02, 1e03, 1e04, 1e05, 1e06, 1e07, 1e08, 1e09, 1e10,
		1e11, 1e12, 1e13, 1e14, 1e15, 1e16, 1e17, 1e18, 1e19, 1e20,
		1e21, 1e22, 1e23, 1e24, 1e25, 1e26, 1e27, 1e28, 1e29, 1e30,
		1e31, 1e32, 1e33, 1e34, 1e35, 1e36, 1e37, 1e38, 1e39, 1e40,
		1e41, 1e42, 1e43, 1e44, 1e45, 1e46, 1e47, 1e48, 1e49, 1e50,
	};
	if(i >= 0 && i < __countof(pow_tbl))
		return pow_tbl[i];
	else if(i < 0 && i > -__countof(pow_tbl))
		return 1 / pow_tbl[-i];
	return pow(10.0, (double)i);
}

double normalize(double d, int& exp)
{
	if(IsNull(d) || d == 0)
	{
		exp = Null;
		return d;
	}
	bool sign = (d < 0);
	if(sign) d = -d;
	exp = minmax<int>(ilog10(d), -300, +300); // 8-byte double!
	d /= ipow10(exp);
	if(d >= 10) { d /= 10; exp++; }
	if(d < 1)   { d *= 10; exp--; }
	return sign ? -d : d;
}

double roundr(double d, int digits)
{
	int i = ilog10(d);
	if(IsNull(i))
		return d;
	double fac = ipow10(i - digits);
	return floor(d / fac + 0.5) * fac;
}

double floorr(double d, int digits)
{
	int i = ilog10(d);
	if(IsNull(i))
		return d;
	double fac = ipow10(i - digits);
	return floor(d / fac) * fac;
}

double ceilr(double d, int digits)
{
	int i = ilog10(d);
	if(IsNull(i))
		return d;
	double fac = ipow10(i - digits);
	return ceil(d / fac) * fac;
}

END_UPP_NAMESPACE
