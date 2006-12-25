#ifdef PLATFORM_WIN32
#ifndef _MAX_PATH
static const int _MAX_PATH = MAX_PATH;
#endif
#endif

#ifdef PLATFORM_POSIX
static const int _MAX_PATH = PATH_MAX;
int      GetTickCount();
#endif

class TimeStop {
	dword starttime;

public:
	int    Elapsed() const           { return GetTickCount() - starttime; }
	String ToString() const;

	TimeStop();
};

void   SetAssertFailedHook(void (*h)(const char *));

void   SetIniFile(const char *name);
String GetIniKey(const char *name);
VectorMap<String, String> LoadIniFile(const char *filename);

String timeFormat(double second);

String Garble(const char *s, const char *e);
String Garble(const String& s);

String Encode64(const String& s);
String Decode64(const String& s);

#ifdef PLATFORM_WINCE
WString ToSystemCharset(const String& src);
String  FromSystemCharset(const WString& src);
#else
String ToSystemCharset(const String& src);
String FromSystemCharset(const String& src);
#endif

#ifdef PLATFORM_WIN32
String GetErrorMessage(dword dwError);
#endif

#ifdef PLATFORM_POSIX
inline int GetLastError() { return errno; }
String GetErrorMessage(int errorno);
#endif

String GetLastErrorMessage();

void   BeepInformation();
void   BeepExclamation();
void   BeepQuestion();

inline
void memsetw(void *t, word value, int count)
{
	word *w = (word *)t;
	word *lim = w + count;
	while(w < lim)
		*w++ = value;
}

inline
void memsetd(void *t, dword value, int count)
{
	dword *w = (dword *)t;
	dword *lim = w + count;
	while(w < lim)
		*w++ = value;
}

inline
void memsetex(void *t, const void *item, int item_size, int count) {
	ASSERT(count >= 0);
	byte *q = (byte *)t;
	while(count--) {
		memcpy(q, item, item_size);
		q += item_size;
	}
}

char *PermanentCopy(const char *s);

int MemICmp(const void *dest, const void *src, int count);

String NormalizeSpaces(const char *s);
String NormalizeSpaces(const char *begin, const char *end);

#ifndef PLATFORM_WIN32
void Sleep(int msec);
#endif

template <class T>
void Zero(T& obj)
{
	::memset(&obj, 0, sizeof(obj));
}

template <class T>
T& Reconstruct(T& object)
{
	object.~T();
	::new(&object) T;
	return object;
}

#define ZeroArray(x)       memset((x), 0, sizeof(x))

#if defined(CPU_UNALIGNED) && defined(CPU_LE)
inline int    Peek16le(const void *ptr)  { return *(const word *)ptr; }
inline int    Peek32le(const void *ptr)  { return *(const dword *)ptr; }
inline int64  Peek64le(const void *ptr)  { return *(const int64 *)ptr; }

inline void   Poke16le(const void *ptr, int val)    { *(word *)ptr = val; }
inline void   Poke32le(const void *ptr, int val)    { *(dword *)ptr = val; }
inline void   Poke64le(const void *ptr, int64 val)  { *(int64 *)ptr = val; }
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
inline void   Poke32be(const void *ptr, int val)    { Poke16le(ptr, HIWORD(val)); Poke16le((byte *)ptr + 2, LOWORD(val)); }
inline void   Poke64be(const void *ptr, int64 val)  { Poke32le(ptr, HIDWORD(val)); Poke32le((byte *)ptr + 4, LODWORD(val)); }

inline void   EndianSwap(word& v)   { byte *x = (byte *)(&v); Swap(x[0], x[1]); }
inline void   EndianSwap(int16& v)  { EndianSwap(*(word *)&v); }
inline void   EndianSwap(dword& v)  { byte *x = (byte *)&v; Swap(x[0], x[3]); Swap(x[1], x[2]); }
inline void   EndianSwap(int& v)    { EndianSwap(*(dword *)&v); }
//inline void   EndianSwap(long& v)   { EndianSwap(*(dword *)&v); }
inline void   EndianSwap(int64& v)  { byte *x = (byte *)&v; Swap(x[0], x[7]); Swap(x[1], x[6]); Swap(x[2], x[5]); Swap(x[3], x[4]); }
inline void   EndianSwap(uint64& v) { EndianSwap(*(int64 *)&v); }

inline word   SwapEndian(word v)    { EndianSwap(v); return v; }
inline int16  SwapEndian(int16 v)   { EndianSwap(v); return v; }
inline dword  SwapEndian(dword v)   { EndianSwap(v); return v; }
inline int    SwapEndian(int v)     { EndianSwap(v); return v; }
//inline long   SwapEndian(long v)    { EndianSwap(v); return v; }
inline int64  SwapEndian(int64 v)   { EndianSwap(v); return v; }
inline uint64 SwapEndian(uint64 v)  { EndianSwap(v); return v; }

void EndianSwap(word *v, int count);
void EndianSwap(int16 *v, int count);
void EndianSwap(dword *v, int count);
void EndianSwap(int *v, int count);
//void EndianSwap(long *v, int count);
void EndianSwap(int64 *v, int count);
void EndianSwap(uint64 *v, int count);

// Math utils

inline double  sqr          (double a)                      { return a * a; }
inline double  argsinh      (double s)                      { return log(s + sqrt(s * s + 1)); }
inline double  argcosh      (double c)                      { ASSERT(c >= 1); return log(c + sqrt(c * c - 1)); }
inline double  argtanh      (double t)                      { ASSERT(fabs(t) < 1); return log((1 + t) / (1 - t)) / 2; }

int            iscale(int x, int y, int z);
int            iscalefloor(int x, int y, int z);
int            iscaleceil(int x, int y, int z);
int            idivfloor(int x, int y);
int            idivceil(int x, int y);
int            itimesfloor(int x, int y);
int            itimesceil(int x, int y);

int            fround(double x);
int            ffloor(double x);
int            fceil(double x);

int64          fround64(double x);
int64          ffloor64(double x);
int64          fceil64(double x);

String         AsString(double x, int nDigits);
double         modulo(double x, double y);

int            ilog10       (double d);
double         ipow10       (int i);
double         normalize    (double d, int& exponent);

double         roundr       (double d, int digits);
double         floorr       (double d, int digits);
double         ceilr        (double d, int digits);

//BW - use max<double>
//inline double fmax(double x, double y)            { return x >= y ? x : y; }
//BW - use min<double>
//inline double fmin(double x, double y)            { return x <= y ? x : y; }
//BW - use minmax<double>
//inline double fbind(double l, double x, double h) { return x >= h ? h : x <= l ? l : x; }
//BW - use sgn<double>
//inline int    fsgn(double x)                      { return x > 0 ? +1 : x < 0 ? -1 : 0; }

// Constants rounded for 21 decimals.

#ifndef M_E

#define M_E         2.71828182845904523536
#define M_LOG2E     1.44269504088896340736
#define M_LOG10E    0.434294481903251827651
#define M_LN2       0.693147180559945309417
#define M_LN10      2.30258509299404568402
#define M_PI        3.14159265358979323846
#define M_PI_2      1.57079632679489661923
#define M_PI_4      0.785398163397448309616
#define M_1_PI      0.318309886183790671538
#define M_2_PI      0.636619772367581343076
#define M_1_SQRTPI  0.564189583547756286948
#define M_2_SQRTPI  1.12837916709551257390
#define M_SQRT2     1.41421356237309504880
#define M_SQRT_2    0.707106781186547524401

#endif

#define M_2PI       (2 * M_PI)

// ------

//# System dependent !
class BitAndPtr {
	uintptr_t bap;

public:
	void  SetBit(bool b)  { bap = (~1 & bap) | (uintptr_t)b; }
	void  SetPtr(void *p) { bap = (1 & bap) | (uintptr_t)p; }

	bool  GetBit() const  { return bap & 1; }
	void *GetPtr() const  { return (void *) (bap & ~1); }

	void  Set0(void *ptr) { bap = (uintptr_t)ptr; }
	void  Set1(void *ptr) { bap = (uintptr_t)ptr | 1; }

	BitAndPtr()           { bap = 0; }
};

class Exc : public String {
public:
	Exc(); // throw according to GetLastError()
	Exc(const String& desc) : String(desc) {}

//	void Show() const;
};

class AbortExc : public Exc {
public:
	AbortExc();
};

// --------------

/*
template <class T>
va_list va_ptr(const T& obj)
{
	va_list temp;
	va_start(temp, obj);
	return temp;
}
*/

// ---------------

struct TextTest {
	virtual const char *Accept(const char *s) const = 0;
};

class CharFilterTextTest : public TextTest {
	int (*filter)(int);

public:
	virtual const char *Accept(const char *s) const;
	CharFilterTextTest(int (*filter)(int));
	~CharFilterTextTest();
};

Vector<String> Split(const char *s, const TextTest& delim, bool ignoreempty = true);
Vector<String> Split(const char *s, int (*filter)(int), bool ignoreempty = true);
Vector<String> Split(const char *s, int chr, bool ignoreempty = true);
String Join(const Vector<String>& im, const String& delim);

class StringC {
	BitAndPtr bap;

	bool     IsString() const                  { return bap.GetBit(); }
	void     Free();

public:
	void     SetString(const String& s);
	void     SetCharPtr(const char *s);

	bool     IsEmpty() const;

	operator const char *() const;
	operator String() const;

	~StringC();
};

// ------------------- Linux style text settings -------------

class TextSettings {
	VectorMap< String, VectorMap< String, String > > settings;

public:
	String Get(const char *group, const char *key) const;
	String Get(const char *key) const                            { return Get("", key); }

	String operator()(const char *group, const char *key) const  { return Get(group, key); }
	String operator()(const char *key) const                     { return Get(key); }

	void Clear()                                                 { settings.Clear(); }
	void Load(const char *filename);
};

// ------------------- Advanced streaming --------------------

bool Load(Callback1<Stream&> serialize, Stream& stream);
bool Store(Callback1<Stream&> serialize, Stream& stream);
bool LoadFromFile(Callback1<Stream&> serialize, const char *file = NULL);
bool StoreToFile(Callback1<Stream&> serialize, const char *file = NULL);

template <class T>
bool Load(T& x, Stream& s) {
	return Load(callback(&x, &T::Serialize), s);
}

template <class T>
bool Store(T& x, Stream& s) {
	return Store(callback(&x, &T::Serialize), s);
}

template <class T>
bool LoadFromFile(T& x, const char *name = NULL) {
	return LoadFromFile(callback(&x, &T::Serialize), name);
}

template <class T>
bool StoreToFile(T& x, const char *name = NULL) {
	return StoreToFile(callback(&x, &T::Serialize), name);
}

template <class T>
String StoreAsString(T& x) {
	StringStream ss;
	Store(x, ss);
	return ss;
}

template <class T>
bool LoadFromString(T& x, const String& s) {
	StringStream ss(s);
	return Load(x, ss);
}

void             RegisterGlobalConfig(const char *name);
void             RegisterGlobalConfig(const char *name, Callback WhenFlush);

String           GetGlobalConfigData(const char *name);
void             SetGlobalConfigData(const char *name, const String& data);

template <class T>
bool LoadFromGlobal(T& x, const char *name)
{
	StringStream ss(GetGlobalConfigData(name));
	return ss.IsEof() || Load(x, ss);
}

template <class T>
void StoreToGlobal(T& x, const char *name)
{
	StringStream ss;
	Store(x, ss);
	SetGlobalConfigData(name, ss);
}

void SerializeGlobalConfigs(Stream& s);

#ifdef PLATFORM_WINCE
inline void abort() { TerminateProcess(NULL, -1); }
#endif
