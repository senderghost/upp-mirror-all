#include <Core/Core.h>
#include <Painter/Painter.h>

using namespace Upp;

const int N = 10000000;

#include <chrono>

/*
int64 usecs()
	return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now());
}
*/

#define LLOG(x)  // LOG(x)
#define LDUMP(x) // DUMP(x)

Atomic x;
char h[4000 * 8];

int WordDistance(const String& p, const String& w)
{
	RTIMING("WordDistance");
	LLOG("===== " << p << " " << w);

	if(abs(p.GetLength() - w.GetLength()) > 4)
		return INT_MAX;

	VectorMap<int, int> chars;
	for(int i = 0; i < p.GetCount(); i++)
		chars.GetAdd(p[i], 0)++;
	
	int score = 0;
	String pp;
	VectorMap<int, int> found;
	for(int i = 0; i < w.GetCount(); i++) {
		int q = chars.Find(w[i]);
		if(q >= 0 && chars[q]) {
			chars[q]--;
			score++;
			LLOG("Letter " << w[i]);
			found.GetAdd(w[i], 0)++;
		}
	}

	LDUMP(found);
	for(int i = 0; i < p.GetCount(); i++) {
		int q = found.Find(p[i]);
		if(q >= 0 && found[q] > 0) {
			found[q]--;
			pp.Cat(p[i]);
		}
	}

	LDUMP(score);
	LDUMP(pp);
	VectorMap<int, int> pairs;
	for(int i = 1; i < pp.GetCount(); i++)
		pairs.GetAdd(MAKEWORD(pp[i - 1], pp[i]), 0)++;
	
	for(int i = 1; i < w.GetCount(); i++) {
		int q = pairs.Find(MAKEWORD(w[i - 1], w[i]));
		if(q >= 0 && pairs[q]) {
			pairs[q]--;
			score++;
			LLOG("Pair " << (char)w[i-1] << (char)w[i]);
		}
	}
	
	LDUMP(score);
	LDUMP(abs(p.GetLength() - w.GetLength()));
	score -= abs(p.GetLength() - w.GetLength());

	LDUMP(score);
	return -score;
}

struct WordDistanceTester {
	byte pchars[256];
	byte wchars[256];
	byte pairs[256 * 256];
	int  used_pairs[256]; // store used positions in pairs to be able to clear them at exit
	int  used_pairs_count; // count of pairs
	
	int Get(const String& w, const String& p);
	
	WordDistanceTester();
};

WordDistanceTester::WordDistanceTester()
{
	Zero(pchars);
	Zero(wchars);
	Zero(pairs);
	Zero(used_pairs);
	used_pairs_count = 0;
}

int WordDistanceTester::Get(const String& p, const String& w)
{
	if(abs(p.GetLength() - w.GetLength()) > 4 || w.GetCount() > 200 || p.GetCount() > 200)
		return INT_MAX;
	
	LLOG(w << " " << p);
	
	VectorMap<int, int> chars;
	for(int i = 0; i < p.GetCount(); i++)
		pchars[(byte)p[i]]++;
	
	int score = 0;
	String pp;
	VectorMap<int, int> found;
	for(int i = 0; i < w.GetCount(); i++) {
		int c = (byte)w[i];
		if(pchars[c]) {
			pchars[c]--;
			wchars[c]++;
			score++;
			LLOG("Letter " << (char)w[i]);
		}
	}
	
	LDUMP(score);

	int first = 0;
	used_pairs_count = 0;
	for(int i = 0; i < p.GetCount(); i++) {
		int c = p[i];
		if(wchars[c]) {
			wchars[c]--;
			if(first) {
				LLOG("Pair " << (char)first << (char)c);
				int pairi = MAKEWORD(first, c);
				pairs[pairi]++;
				used_pairs[used_pairs_count++] = pairi;
			}
			first = c;
		}
	}

	for(int i = 1; i < w.GetCount(); i++) {
		int pairi = MAKEWORD(w[i - 1], w[i]);
		if(pairs[pairi]) {
			pairs[pairi]--;
			score++;
		}
	}
	
	score -= abs(p.GetLength() - w.GetLength());

	Zero(pchars);
	Zero(wchars);
	for(int i = 0; i < used_pairs_count; i++)
		pairs[used_pairs[i]] = 0;
	
	return -score;
}

int LevenshteinDistance(const String& s, const String& t) {
	RTIMING("Distance");
	int lens = s.GetLength();
	int lent = t.GetLength();
	
    Buffer<int> v0(lent + 1);
    Buffer<int> v1(lent + 1);

    for (int i = 0; i <= lent; ++i)
        v0[i] = i;

    for (int i = 0; i < lens; ++i) {
        v1[0] = i + 1;

        for (int j = 0; j < lent; ++j) {
            int deletionCost = v0[j + 1] + 1;
            int insertionCost = v1[j] + 1;
            int substitutionCost;
            if (s[i] == t[j])
                substitutionCost = v0[j];
            else
                substitutionCost = v0[j] + 1;

            v1[j + 1] = min(deletionCost, insertionCost, substitutionCost);
        }
        Swap(v0, v1);
	}
    return v0[lent];
}

Vector<String> FindCloseWords(int lang, const String& w, int n)
{
	RLOG("=============================");
	RDUMP(w);
	RTIMING("FindCloseWords");
	Vector<String> r;
	Vector<int>    min_distance;
	if(n < 1)
		return r;
	String aw = ToUpper(ToAscii(w));
	One<WordDistanceTester> tester;
	tester.Create();
	AllSpellerWords(lang, [&] (String h) -> bool {
		if(abs(h.GetLength() - w.GetLength()) < 4) {
			int d = tester->Get(Utf8ToUpperAscii(h), aw);
			if(min_distance.GetCount() == 0) {
				min_distance.Add(d);
				r.Add(h);
			}
			else
			if(d <= min_distance.Top()) {
				int ii = min_distance.GetCount() - 1;
				while(ii > 0 && d < min_distance[ii - 1])
					ii--;
				min_distance.Insert(ii, d);
				r.Insert(ii, h);
				if(r.GetCount() > n) {
					r.Trim(n);
					min_distance.Trim(n);
				}
			}
		}
		return false;
	});
	RDUMP(r);
	RDUMP(min_distance);
	return r;
}

CONSOLE_APP_MAIN
{
/*	DDUMP(ToUpperAscii(0x111));
	DDUMP(ToLowerAscii(0x111));
	DDUMP(ToUpper(ToAscii(0x111)));

	DUMPHEX(ToAscii("Český đŞא"));
	DUMPHEX(Utf8ToAscii("Český đŞא"));
	DUMPHEX(Utf8ToUpperAscii("Český đŞא"));
	DUMPHEX(Utf8ToLowerAscii("Český đŞא"));
	return;
	int n = 0;
	AllSpellerWords(LNG_('C','S','C','Z'), [&](const String& h) { RTIMING("ToAscii"); ToAscii(h); n++; return false; });
	AllSpellerWords(LNG_('C','S','C','Z'), [&](const String& h) { RTIMING("ToUpper ToAscii"); ToUpper(ToAscii(h)); n++; return false; });
	AllSpellerWords(LNG_('C','S','C','Z'), [&](const String& h) { RTIMING("ToAsciiFast"); Utf8ToAscii(h); n++; return false; });
	AllSpellerWords(LNG_('C','S','C','Z'), [&](const String& h) { RTIMING("ToUpperAsciiFast"); Utf8ToUpperAscii(h); n++; return false; });
	RDUMP(n);
	return;*/
	WordDistanceTester t;
	DUMP(t.Get("peek", "pek"));
	DUMP(t.Get("keep", "pek"));

//	FindCloseWords(LNG_ENGLISH, "pek", 20);
	FindCloseWords(LNG_ENGLISH, "tomrw", 20);
//	FindCloseWords(LNG_ENGLISH, "ht", 20);
	FindCloseWords(LNG_('C','S','C','Z'), "csky", 20);
//	FindCloseWords(LNG_('C','S','C','Z'), "csky", 20);
}

#if 0
	String h;
	for(int i = 0; i < 2048; i++) {
		h << Format("0x%02x,", (int)ToLower(ToAscii(i)));
		if((i & 511) == 511)
			h << "\n";
	}
	LOG(h);

	return;


	String h;
	for(int i = 0; i < 2048; i++) {
		h << Format("0x%02x,", (int)ToLower(ToAscii(i)));
		if(i % 512 == 0)
			h << "\n";
	}
	DUMP(h);
	
	return;
#endif
