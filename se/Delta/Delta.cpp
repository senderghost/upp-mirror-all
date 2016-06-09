#include <Core/Core.h>

using namespace Upp;

inline
void Hash(dword& hash, dword value)
{
	hash = _rotl(hash ^ value, 1);
}

void DeltaCompress(const byte *ref, int reflen, const byte *s, int len)
{
	
}

CONSOLE_APP_MAIN
{
	String ref = LoadFile("C:/u/upp.src/uppsrc/Core/Algo.h");
	String src = LoadFile("C:/xxx/Algo.h");
	
	dword hash = 0, hash1 = 0;
	
	dword map[65536];
	
	memset(map, 0, sizeof(map));
	
	const int hashmask = 0xfff;

	int rp = 0;
	while(rp + 128 <= ref.GetCount()) {
		dword hash = 0;
		int pos = rp;
		for(int i = 0; i < 128; i++)
			Hash(hash, ref[rp++]);
		map[hash & hashmask] = pos;
//		LOG("************ " << (hash & hashmask));
//		LOG(ref.Mid(pos, 128));
	}
	
	LOG("================");
	
	int total = 0, count = 0;
	hash = 0;
	for(int i = 0; i < 128; i++)
		Hash(hash, src[i]);
	int literalpos = 0;
	int pos = 0;
	while(pos + 128 < src.GetCount()) {
		int refpos = map[hash & hashmask];

		int begin = pos;
		int rbegin = refpos;

		while(begin > literalpos && rbegin > 0 && src[begin - 1] == ref[rbegin - 1]) {
			begin--;
			rbegin--;
		}

		int end = pos;
		int rend = refpos;
		
		while(end < src.GetCount() && rend < ref.GetCount() && src[end] == ref[rend]) {
			end++;
			rend++;
		}
		
		int matchlen = end - begin;

		if(matchlen >= 32) { // really just needs to be bigger than delta record
			int litlen = begin - literalpos;
			ASSERT(litlen >= 0);
			LOG("==== LITERAL " << literalpos << ", " << litlen);
			if(litlen > 0)
				LOG(src.Mid(literalpos, litlen));
			LOG("---- Found at " << rbegin << ", " << matchlen);
			LOG(ref.Mid(rbegin, matchlen));
			total += matchlen;
			count++;
			int l = end - pos;
			while(--l && pos + 128 < src.GetCount()) {
				Hash(hash, src[pos] ^ src[pos + 128]);
				pos++;
			}
			literalpos = end;
		}
		else {
			Hash(hash, src[pos] ^ src[pos + 128]);
			pos++;
		}
	}

	int litlen = src.GetCount() - literalpos;
	LOG("==== LITERAL " << literalpos << ", " << litlen);
	if(litlen > 0)
		LOG(src.Mid(literalpos, litlen));
	
	DDUMP(src.GetCount());
	DDUMP(ref.GetCount());
	DDUMP(total);
	DDUMP(count);
}

/*
	int pos;
	for(pos = 0; pos < 32; pos++) {
		Hash(hash, ref[pos]);
		Hash(hash1, ref[pos]);
	}

	for(; pos < ref.GetLength(); pos++) {
		if((pos & 31) == 0) {
			LOG(hash << ' ' << hash1);
			hash1 = 0;
		}
		Hash(hash, ref[pos - 32] ^ ref[pos]);
		Hash(hash1, ref[pos]);
	}

		if(p < src.GetCount() - 200 && rp < ref.GetCount() && rpos && 0) {
			DDUMP(hash & hashmask);
			LOG("============ SRC");
			LOG(src.Mid(p, 200));
			LOG("------------ REF");
			LOG(ref.Mid(rp, 200));
			LOG("---");
		}
		
*/
