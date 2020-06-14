#include <Core/Core.h>

using namespace Upp;

int b;

/*
inline
bool IsAlNum2(int q)
{
	q -= '0';
	int qq = q & 63;
	return ((1 << qq) & I64(0x12345678123456) | (q - qq)) == 0;
}
*/

inline
bool iscid2(int q)
{
	q -= '0';
	return (((I64(0xfffe87fffffe03ff) >> (q & 63)) & 1) | (q & ~63)) == 0;
}

CONSOLE_APP_MAIN
{
	String x = LoadFile("C:/u/upp.src/uppsrc/CodeEditor/CodeEditor.cpp");
	
	uint64 h = 0;
	for(int i = 0; i < 64; i++)
		if(iscid(i + '0'))
			h |= ((uint64)1 << i);
	RDUMPHEX(h);
	
	
	for(int n = 0; n < 10000; n++) {
		{
			RTIMING("isalnum");
			for(int q : x)
				if(isalnum(q))
					b++;
		}
		
		{
			RTIMING("iscid");
			for(int q : x)
				if(iscid(q))
					b++;
		}
		
		{
			RTIMING("isalnum2");
			for(int q : x)
				if(iscid2(q))
					b++;
		}
	}
}
