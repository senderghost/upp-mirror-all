#include <Core/Core.h>

using namespace Upp;

template <int N>
struct BigInt {
	dword data[N];
	
	dword& operator[](int i)       { return data[i]; }
	dword  operator[](int i) const { return data[i]; }
	
	template <int N2>
	BigInt<N2>
};

template <int N>
BigInt<N> operator+(const BigInt<N>& a, const BigInt<N>& b)
{
	dword carry = 0;
	BigInt<N> r;
	for(int i = 0; i < N; i++) {
		uint64 v = a[i] + b[i] + carry;
		r[i] = (dword)v;
		carry = (dword)(v >> 32);
	}
	return r;
}

template <int N>
BigInt<N> operator-(const BigInt<N>& a)
{
	dword carry = 0;
	BigInt<N> r;
	for(int i = 0; i < N; i++) {
		uint64 v = ~a[i] + 0xffffffff + carry;
		r[i] = (dword)v;
		carry = (dword)(v >> 32);
	}
	return r;
}

template <int N>
BigInt<N> operator-(const BigInt<N>& a, const BigInt<N>& b)
{
	return a + (-b);
}

CONSOLE_APP_MAIN
{
	BigInt<20> a, b;
	a = a - b;
}
