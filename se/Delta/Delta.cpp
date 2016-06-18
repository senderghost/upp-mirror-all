#include <Core/Core.h>

using namespace Upp;

dword hash_rand[256];

#if 0
inline
void Hash(dword& hash, byte value)
{
	hash = _rotl(hash ^ hash_rand[value], 1);
}

inline
void Hash(dword& hash, byte value_out, byte value_in)
{
	hash = _rotl(hash ^ hash_rand[value_out] ^ hash_rand[value_in], 1);
}
#endif

#if 1
inline
void Hash(dword& hash, byte value)
{
	hash = _rotl(hash ^ value, 1);
}

inline
void Hash(dword& hash, byte value_out, byte value_in)
{
	hash = _rotl(hash ^ value_out ^ value_in, 1);
}
#endif

#if 0
inline
void Hash(dword& hash, byte value)
{
	hash = _rotl(hash ^ (2654435761U * value), 1);
}

inline
void Hash(dword& hash, byte value_out, byte value_in)
{
	hash = _rotl(hash ^ (2654435761U * value_out) ^ (2654435761U * value_in), 1);
}
#endif

#if 0
inline dword MaskHash(dword mask, dword h)
{
	return mask & (h - SwapEndian32((dword)h));
}
#endif

#if 1
inline dword MaskHash(dword mask, dword h)
{
	return mask & h;
}
#endif

const char *GetMatch(const char *src, const char *srcmax, const char *ref)
{
	const char *s = src;
	while(s < srcmax && *s == *ref) {
		s++;
		ref++;
	}
	return s;
}

const char *GetMatchBack(const char *src, const char *srcmin, const char *ref)
{
	const char *s = src;
	while(s > srcmin && *(s - 1) == *(ref - 1)) {
		s--;
		ref--;
	}
	return s;
}

CONSOLE_APP_MAIN
{
	String ref = LoadFile("C:/u/upp.src/uppsrc/Core/Algo.h");
	String src = LoadFile("C:/xxx/Algo.h");

	ONCELOCK {
		for(int i = 0; i < 128; i++)
			hash_rand[i] = Random();
	}
	
	dword hash = 0, hash1 = 0;
	
	dword map[65536];
	
	memset(map, 0xff, sizeof(map));
	
	const int hashmask = 127;

	int rp = 0;
	while(rp + 128 <= ref.GetCount()) {
		dword hash = 0;
		int pos = rp;
		for(int i = 0; i < 128; i++)
			Hash(hash, ref[rp++]);
		map[MaskHash(hashmask, hash)] = pos;
		LOG("************ " << MaskHash(hashmask, hash));
//		LOG(ref.Mid(pos, 128));
	}
	
	LOG("================");
	
	int total = 0, count = 0;
	hash = 0;
	for(int i = 0; i < 128; i++)
		Hash(hash, src[i]);
	const char *literalpos = ~src;
	const char *pos = ~src;
	
	int attempthash = 0;
	int failedhash = 0;
	int totalhash = 0;
	
	while(pos + 128 < src.End()) {
	//	DDUMP(hash);
		int refpos = map[MaskHash(hashmask, hash)];
		attempthash++;
		if(refpos != 0xffffffff) {
			DLOG("##### HASH " << hash << " " << MaskHash(hashmask, hash));
			DDUMP(refpos);
			DDUMP(String(pos, 128) == String(~ref + refpos, 128));
			failedhash += String(pos, 128) != String(~ref + refpos, 128);
			totalhash++;
			LOGHEXDUMP(pos, 128);
			LOGHEXDUMP(~ref + refpos, 128);
	
			const char *begin = GetMatchBack(pos, pos - min(pos - literalpos, refpos), ~ref + refpos);
			const char *end = GetMatch(pos, pos + min(src.end() - pos, ref.GetCount() - refpos), ~ref + refpos);
			
			int matchlen = (int)(end - begin);
			
			DDUMP(matchlen);
	
			if(matchlen >= 3 * sizeof(dword)) { // really just needs to be bigger than delta record
				int litlen = begin - literalpos;
				ASSERT(litlen >= 0);
				LOG("==== LITERAL " << literalpos - ~src << ", " << litlen);
				if(litlen > 0)
					LOG(String(literalpos, litlen));
				int rbegin = refpos - (pos - begin);
				LOG("---- Found at " << rbegin << ", " << matchlen);
				LOG(ref.Mid(rbegin, matchlen));
				total += matchlen;
				count++;
				while(pos < end && pos + 128 < src.End()) {
					Hash(hash, pos[0], pos[128]);
					pos++;
				}
				literalpos = end;
				continue;
			}
		}
		Hash(hash, pos[0], pos[128]);
		pos++;
	}

	int litlen = src.End() - literalpos;
	LOG("==== LITERAL " << literalpos - ~src << ", " << litlen);
	if(litlen > 0)
		LOG(String(literalpos, litlen));
	
	DDUMP(src.GetCount());
	DDUMP(ref.GetCount());
	DDUMP(total);
	DDUMP(count);
	DDUMP(attempthash);
	DDUMP(failedhash);
	DDUMP(totalhash);
	DDUMP(ref.GetCount());
	DDUMP(hashmask);
}
