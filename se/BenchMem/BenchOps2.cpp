#include <Core/Core.h>
#include <RichText/RichText.h>

using namespace Upp;

Vector<Tuple2<String, double>> data;

#ifdef _DEBUG
const int N = 1;
#else
const int N = 10000000;
#endif

struct Bench {
	String name;
	double count;
	double time0;
	
	Bench(const char *nm, double n = 1) {
		Cout() << data.GetCount() + 1 << ": " << nm << "\n";
		RLOG("===== " << nm);
		name = nm;
		time0 = (double)usecs();
		count = n;
	}
	
	~Bench() {
		double t = usecs() - time0;
		RLOG(t << " us");
		data.Add(MakeTuple(name, t / count));
	}
};

const int AN = 256;

volatile thread_local int  tls_var;
volatile int    integer[16];
volatile thread_local int  tls[16];
volatile int64  i64[16];
volatile double fp64[16];
volatile float  fp32[16];
volatile Atomic atomic[16];

int result;
double fresult;

int one_val = 1;

volatile int val64 = 64;

struct Data64 {
	byte data[64];
};

Data64 data1[16], data2[16];

/*
BFEBB083  mov rax,[gs:0x58] 

BFEBB07D  mov ecx,[rel 0xffffffffc00afb48] 
BFEBB08C  mov rsi,[rax+rcx*8] 

BFEBB095  mov eax,[rcx+rsi] 
BFEBB098  inc eax 
BFEBB09A  mov [rcx+rsi],eax 
*/

/*
A4EB9A60  mov eax,[var] 
A4EB9A66  add eax,ebx 
A4EB9A68  mov [var],eax 
*/

CONSOLE_APP_MAIN
{
	int n = Random();
	if(!n)
		n = 1;
	int64 n64 = n;
	double dn = Randomf() + 0.01;
	{
		Bench _("delete new byte[32] (U++)", 10);
		for(int i = 0; i < 10 * N; i++) {
			delete new byte[32];
			delete new byte[32];
			delete new byte[32];
			delete new byte[32];
		}
	}
	{
		Bench _("delete new byte[1000] (U++)", 4);
		for(int i = 0; i < 4 * N; i++) {
			delete new byte[1000];
			delete new byte[1000];
			delete new byte[1000];
			delete new byte[1000];
		}
	}
	{
		Bench _("delete new byte[30000] (U++)", 0.1);
		for(int i = 0; i < N / 10; i++) {
			delete new byte[30000];
			delete new byte[30000];
			delete new byte[30000];
			delete new byte[30000];
		}
	}

	RDUMP(data);
	
	double n0 = data[0].b;
	RLOG(n0 / N / 4 * 1e3 << " ns");
	RLOG("{{1:1:1:1 Operation:: /Add:: eq ops:: time");
	for(int i = 0; i < data.GetCount(); i++)
		RLOG(":: " << DeQtf(data[i].a) << Format(":: %.1f:: %.0f:: %.1f ns", data[i].b / n0, data[i].b / n0 * 3, data[i].b / N / 4 * 1e3));
	RLOG("}}");
}
