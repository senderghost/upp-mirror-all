#if defined(CPU_UNALIGNED) && defined(CPU_LE)
NOUBSAN inline int    Peek16le(const void *ptr)  { return *(const word *)ptr; }
NOUBSAN inline int    Peek32le(const void *ptr)  { return *(const dword *)ptr; }
NOUBSAN inline int64  Peek64le(const void *ptr)  { return *(const int64 *)ptr; }

NOUBSAN inline void   Poke16le(const void *ptr, int val)    { *(word *)ptr = val; }
NOUBSAN inline void   Poke32le(const void *ptr, int val)    { *(dword *)ptr = val; }
NOUBSAN inline void   Poke64le(const void *ptr, int64 val)  { *(int64 *)ptr = val; }
#else
inline int    Peek16le(const void *ptr)  { return MAKEWORD(((byte *)ptr)[0], ((byte *)ptr)[1]); }
inline int    Peek32le(const void *ptr)  { return MAKELONG(Peek16le(ptr), Peek16le((byte *)ptr + 2)); }
inline int64  Peek64le(const void *ptr)  { return MAKEQWORD(Peek32le(ptr), Peek32le((byte *)ptr + 4)); }

inline void   Poke16le(const void *ptr, int val)    { ((byte *)ptr)[0] = LOBYTE(val); ((byte *)ptr)[1] = HIBYTE(val); }
inline void   Poke32le(const void *ptr, int val)    { Poke16le(ptr, LOWORD(val)); Poke16le((byte *)ptr + 2, HIWORD(val)); }
inline void   Poke64le(const void *ptr, int64 val)  { Poke32le(ptr, LODWORD(val)); Poke32le((byte *)ptr + 4, HIDWORD(val)); }
#endif

inline int    Peek16be(const void *ptr)  { return MAKEWORD(((byte *)ptr)[1], ((byte *)ptr)[0]); }
inline int    Peek32be(const void *ptr)  { return MAKELONG(Peek16be((byte *)ptr + 2), Peek16be(ptr)); }
inline int64  Peek64be(const void *ptr)  { return MAKEQWORD(Peek32be((byte *)ptr + 4), Peek32be(ptr)); }

inline void   Poke16be(const void *ptr, int val)    { ((byte *)ptr)[1] = LOBYTE(val); ((byte *)ptr)[0] = HIBYTE(val); }
inline void   Poke32be(const void *ptr, int val)    { Poke16be(ptr, HIWORD(val)); Poke16be((byte *)ptr + 2, LOWORD(val)); }
inline void   Poke64be(const void *ptr, int64 val)  { Poke32be(ptr, HIDWORD(val)); Poke32be((byte *)ptr + 4, LODWORD(val)); }

#ifdef CPU_LITTLE_ENDIAN

#define MAKE2B(b0, b1)                  MAKEWORD(b0, b1);
#define MAKE4B(b0, b1, b2, b3)          MAKELONG(MAKEWORD(b0, b1), MAKEWORD(b2, b3))

inline int    Peek16(const void *ptr)  { return Peek16le(ptr); }
inline int    Peek32(const void *ptr)  { return Peek32le(ptr); }
inline int64  Peek64(const void *ptr)  { return Peek64le(ptr); }

inline void   Poke16(const void *ptr, int val)    { Poke16le(ptr, val); }
inline void   Poke32(const void *ptr, int val)    { Poke32le(ptr, val); }
inline void   Poke64(const void *ptr, int64 val)  { Poke64le(ptr, val); }

#else

#define MAKE2B(b0, b1)                  MAKEWORD(b1, b0);
#define MAKE4B(b0, b1, b2, b3)          MAKELONG(MAKEWORD(b2, b3), MAKEWORD(b0, b1))

inline int    Peek16(const void *ptr)  { return Peek16be(ptr); }
inline int    Peek32(const void *ptr)  { return Peek32be(ptr); }
inline int64  Peek64(const void *ptr)  { return Peek64be(ptr); }

inline void   Poke16(const void *ptr, int val)    { Poke16be(ptr, val); }
inline void   Poke32(const void *ptr, int val)    { Poke32be(ptr, val); }
inline void   Poke64(const void *ptr, int64 val)  { Poke64be(ptr, val); }

#endif

#if defined(CPU_X86) && defined(COMPILER_MSC)
#ifdef COMPILER_GCC
#ifdef CPU_64
inline word   SwapEndian16(word v)    { __asm__("xchgb %b0,%h0" : "=Q" (v) :  "0" (v)); return v; }
inline int16  SwapEndian16(int16 v)   { __asm__("xchgb %b0,%h0" : "=Q" (v) :  "0" (v)); return v; }
#else
inline word   SwapEndian16(word v)    { __asm__("xchgb %b0,%h0" : "=q" (v) :  "0" (v)); return v; }
inline int16  SwapEndian16(int16 v)   { __asm__("xchgb %b0,%h0" : "=q" (v) :  "0" (v)); return v; }
#endif
inline dword  SwapEndian32(dword v)   { __asm__("bswap %0" : "=r" (v) : "0" (v)); return v; }
inline int    SwapEndian32(int v)     { __asm__("bswap %0" : "=r" (v) : "0" (v)); return v; }
#endif

#ifdef COMPILER_MSC
#pragma intrinsic (_byteswap_ushort, _byteswap_ulong, _byteswap_uint64, strlen)

inline word   SwapEndian16(word v)    { return _byteswap_ushort(v); }
inline int16  SwapEndian16(int16 v)   { return _byteswap_ushort(v); }
inline dword  SwapEndian32(dword v)   { return _byteswap_ulong(v); }
inline int    SwapEndian32(int v)     { return _byteswap_ulong(v); }
#endif

inline void   EndianSwap(word& v)     { v = SwapEndian16(v); }
inline void   EndianSwap(int16& v)    { v = SwapEndian16(v); }
inline void   EndianSwap(dword& v)    { v = SwapEndian32(v); }
inline void   EndianSwap(int& v)      { v = SwapEndian32(v); }

#else

#ifdef COMPILER_GCC

inline dword  SwapEndian32(dword v)   { return __builtin_bswap32(v); }
inline int    SwapEndian32(int v)     { return __builtin_bswap32(v); }

inline word   SwapEndian16(word v)    { return SwapEndian32(v) >> 16; } // GCC bug workaround
inline int16  SwapEndian16(int16 v)   { return SwapEndian32(v) >> 16; }

inline void   EndianSwap(word& v)     { v = SwapEndian16(v); }
inline void   EndianSwap(int16& v)    { v = SwapEndian16(v); }
inline void   EndianSwap(dword& v)    { v = SwapEndian32(v); }
inline void   EndianSwap(int& v)      { v = SwapEndian32(v); }

#else

inline void   EndianSwap(word& v)     { byte *x = (byte *)(&v); Swap(x[0], x[1]); }
inline void   EndianSwap(int16& v)    { EndianSwap(*(word *)&v); }
inline void   EndianSwap(dword& v)    { byte *x = (byte *)&v; Swap(x[0], x[3]); Swap(x[1], x[2]); }
inline void   EndianSwap(int& v)      { EndianSwap(*(dword *)&v); }
inline word   SwapEndian16(word v)    { EndianSwap(v); return v; }
inline int16  SwapEndian16(int16 v)   { EndianSwap(v); return v; }
inline dword  SwapEndian32(dword v)   { EndianSwap(v); return v; }
inline int    SwapEndian32(int v)     { EndianSwap(v); return v; }

#endif

#endif

#if defined(CPU_AMD64) && (defined(COMPILER_GCC) || defined(COMPILER_MSC))
#ifdef COMPILER_GCC
inline uint64  SwapEndian64(uint64 v) { __asm__("bswap %0" : "=r" (v) : "0" (v)); return v; }
inline int64   SwapEndian64(int64 v)  { __asm__("bswap %0" : "=r" (v) : "0" (v)); return v; }
#endif
#ifdef COMPILER_MSC
inline uint64  SwapEndian64(uint64 v) { return _byteswap_uint64(v); }
inline int64   SwapEndian64(int64 v)  { return _byteswap_uint64(v); }
#endif

inline void   EndianSwap(int64& v)    { v = SwapEndian64(v); }
inline void   EndianSwap(uint64& v)   { v = SwapEndian64(v); }

#else

#ifdef COMPILER_GCC

inline uint64  SwapEndian64(uint64 v) { return __builtin_bswap64(v); }
inline int64   SwapEndian64(int64 v)  { return __builtin_bswap64(v); }

inline void    EndianSwap(int64& v)   { v = SwapEndian64(v); }
inline void    EndianSwap(uint64& v)  { v = SwapEndian64(v); }

#else
inline void   EndianSwap(int64& v)    { byte *x = (byte *)&v; Swap(x[0], x[7]); Swap(x[1], x[6]); Swap(x[2], x[5]); Swap(x[3], x[4]); }
inline void   EndianSwap(uint64& v)   { EndianSwap(*(int64 *)&v); }
inline int64  SwapEndian64(int64 v)   { EndianSwap(v); return v; }
inline uint64 SwapEndian64(uint64 v)  { EndianSwap(v); return v; }
#endif
#endif

inline word   SwapEndian16(int w)     { return SwapEndian16((word)w); }
inline word   SwapEndian16(dword w)   { return SwapEndian16((word)w); }

void EndianSwap(word *v, size_t count);
void EndianSwap(int16 *v, size_t count);
void EndianSwap(dword *v, size_t count);
void EndianSwap(int *v, size_t count);
void EndianSwap(int64 *v, size_t count);
void EndianSwap(uint64 *v, size_t count);

#if defined(CPU_UNALIGNED) && defined(CPU_LE)
force_inline
int fast_memcmp(const char *a, const char *b, size_t len)
{
#ifdef CPU_64
	while(len >= 8) {
		uint64 a64 = *(uint64 *)a;
		uint64 b64 = *(uint64 *)b;
		if(a64 != b64)
			return SwapEndian64(a64) < SwapEndian64(b64) ? -1 : 1;
		a += 8;
		b += 8;
		len -= 8;
	}
	if(len & 4) {
		uint32 a32 = *(uint32 *)a;
		uint32 b32 = *(uint32 *)b;
		if(a32 != b32)
			return SwapEndian32(a32) < SwapEndian32(b32) ? -1 : 1;
		a += 4;
		b += 4;
	}
#else
	while(len >= 4) {
		uint32 a32 = *(uint32 *)a;
		uint32 b32 = *(uint32 *)b;
		if(a32 != b32)
			return SwapEndian32(a32) < SwapEndian32(b32) ? -1 : 1;
		a += 4;
		b += 4;
		len -= 4;
	}
#endif
	if(len & 2) {
		uint16 a16 = *(uint16 *)a;
		uint16 b16 = *(uint16 *)b;
		if(a16 != b16)
			return SwapEndian16(a16) < SwapEndian16(b16) ? -1 : 1;
		a += 2;
		b += 2;
	}
	if((len & 1) != 0 && *a != *b)
		return (byte)*a < (byte)*b ? -1 : 1;
	return 0;
}
#else
inline
int fast_memcmp(const char *a, const char *b, size_t len)
{
	return memcmp(a, b, len);
}
#endif

inline dword FoldHash(dword h)
{
	return SwapEndian32(0xa3613c16 * h);
}

force_inline
int SignificantBits(dword x)
{ // basically log2(x) + 1 except that for 0 this is 0, number of significant bits of x
#ifdef COMPILER_MSC
	DWORD index;
	return _BitScanReverse(&index, x) ? index + 1 : 0;
#else
	return x ? 32 - __builtin_clz(x) : 0;
#endif
}

force_inline
int SignificantBits64(uint64 x)
{ // basically log2(x) + 1 except that for 0 this is 0, number of significant bits of x
#ifdef COMPILER_MSC
#ifdef CPU_64
	DWORD index;
	return _BitScanReverse64(&index, x) ? index + 1 : 0;
#else
	if(x & 0xffffffff00000000)
		return SignificantBits(HIDWORD(x)) + 32;
	else
		return SignificantBits((DWORD)x);
#endif
#else
	return x ? 64 - __builtin_clzll(x) : 0;
#endif
}

inline bool FitsInInt64(double x)
{
	return x >= -9223372036854775808.0 && x < 9223372036854775808.0;
}
