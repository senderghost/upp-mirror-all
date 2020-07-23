#include <Core/Core.h>

#include "SIMD_NEON.h"


String AsString(const i32x4& x)
{
	int *f = (int *)&x;
	return Format("%d %d %d %d", f[3], f[2], f[1], f[0]);
}
/*
String AsString(const i8x16& x)
{
	int8 *f = (int8 *)&x;
	return Format("%d %d %d %d . %d %d %d %d . %d %d %d %d . %d %d %d %d",
	              f[15], f[14], f[13], f[12], f[11], f[10], f[9], f[8],
	              f[7], f[6], f[5], f[4], f[3], f[2], f[1], f[0]);
}
*/

String AsString(const f32x4& x)
{
	float *f = (float *)&x;
	return Format("%g %g %g %g", f[3], f[2], f[1], f[0]);
}

String AsString(const i16x8& x)
{
	int16 *f = (int16 *)&x;
	return Format("%d %d %d %d  %d %d %d %d", f[7], f[6], f[5], f[4], f[3], f[2], f[1], f[0]);
}


CONSOLE_APP_MAIN
{
	StdLogSetup(LOG_FILE|LOG_COUT);

	{
		float r[4] = { 0 };
		DUMP(f32x4(r));
	
		f32x4 x;
		float y[] = { 1, 2, 3, 4 };
		x.Load(y);
		DUMP(x);
		x.Store32(r);
		DUMP(f32x4(r));
		x.Store64(r);
		DUMP(f32x4(r));
		x.Store(r);
		DUMP(f32x4(r));
		
		float yy[] = { 11, 12 };
		x.Load32(yy);
		DUMP(x);
		x.Load64(yy);
		DUMP(x);
		
		DUMP(f32x4((int)1));
		DUMP(f32x4((float)2));
		DUMP(f32x4((double)3));
		
		DUMP(f32x4(11, 22, 33, 44));
		
		DUMP(f32all(3.14159));
		
		f32x4 a(1, 2, 3, 4);
		f32x4 b(2, 2, 2, 2);

		DUMP(a);
		DUMP(b);
		DUMP(a + b);
		DUMP(a - b);
		DUMP(a * b);
		DUMP(a / b);
		DUMP(min(a, b));
		DUMP(max(a, b));
		
		DUMP(Broadcast0(a));
		DUMP(Broadcast1(a));
		DUMP(Broadcast2(a));
		DUMP(Broadcast3(a));

		DUMP((a == a));
		DUMP((a != a));
		DUMP((a == b));
		DUMP((a != b));

		DUMP((a < b));
		DUMP((b < a));

		DUMP((a > b));
		DUMP((b > a));
		
		DUMP(AllTrue(a == a));
		DUMP(AllTrue(a != a));
		DUMP(AllTrue(a == b));
		DUMP(AllTrue(a != b));
		
		b = f32all(5);

		DUMP(AllTrue(a < b));
		DUMP(AllTrue(b < a));

		DUMP(AllTrue(a > b));
		DUMP(AllTrue(b > a));
		
		LOG("==================================");
	}
	
	{
		int16 y[] = { 1, 2, 3, 4,  5, 6, 7, 8 };
		
		i16x8 x;
		x.Load32(y);
		DUMP(x);
		x.Load64(y);
		DUMP(x);
		x.Load(y);
		DUMP(x);
		
		int16 r[8] = { 0 };
		x.Store32(r);
		DUMP(i16x8(r));
		x.Store64(r);
		DUMP(i16x8(r));
		x.Store(r);
		DUMP(i16x8(r));
		
		DUMP(i16x8(13));
		DUMP(i16all(13));
		
		i16x8 a(1, 2, 3, 4, 5, 6, 7, 8);
		i16x8 b(2, 2, 2, 2, 2, 2, 2, 2);
		
		DUMP(a);
		DUMP(b);
		
		DUMP(a + b);
		DUMP(a - b);
		DUMP(a * b);
		
		DUMP(a & b);
		DUMP(a | b);
		DUMP(a ^ b);
		DUMP(~a);
		
		DUMP(a << 1);
		DUMP(a >> 1);

		DUMP((a == a));
		DUMP((a == b));

		DUMP((a < b));
		DUMP((b < a));

		DUMP((a > b));
		DUMP((b > a));
		
		DUMP(AllTrue(a == a));
		DUMP(AllTrue(a == b));
		
		b = i16all(10);

		DUMP(AllTrue(a < b));
		DUMP(AllTrue(b < a));

		DUMP(AllTrue(a > b));
		DUMP(AllTrue(b > a));
	}

	{
		LOG("==========================================================");
		int y[] = { 1, 2, 3, 4 };
		
		i32x4 x;
		x.Load32(y);
		DUMP(x);
		x.Load64(y);
		DUMP(x);
		x.Load(y);
		DUMP(x);
		
		int16 r[8] = { 0 };
		x.Store32(r);
		DUMP(i32x4(r));
		x.Store64(r);
		DUMP(i32x4(r));
		x.Store(r);
		DUMP(i32x4(r));
		
		DUMP(i32x4(13));
		DUMP(i32all(13));

		i32x4 a(1, 2, 3, 4);
		i32x4 b(2, 2, 2, 2);
		
		DUMP(a);
		DUMP(b);
		
		DUMP(a + b);
		DUMP(a - b);
		
		DUMP(a & b);
		DUMP(a | b);
		DUMP(a ^ b);
		DUMP(~a);
		
		DUMP(a << 1);
		DUMP(a >> 1);

		DUMP((a == a));
		DUMP((a == b));

		DUMP((a < b));
		DUMP((b < a));

		DUMP((a > b));
		DUMP((b > a));
		
		DUMP(AllTrue(a == a));
		DUMP(AllTrue(a == b));
		
		b = i32all(10);

		DUMP(AllTrue(a < b));
		DUMP(AllTrue(b < a));

		DUMP(AllTrue(a > b));
		DUMP(AllTrue(b > a));
	}
}
