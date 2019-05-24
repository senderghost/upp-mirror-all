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
	float fn = (float)dn;
	{
		Bench _("TLS Add", 100);
		tls_var++;
		for(int i = 0; i < 100 * N; i++) {
			tls[0] += n;
			tls[1] += n;
			tls[2] += n;
			tls[3] += n;
		}
	}
	{
		Bench _("Add", 100);
		for(int i = 0; i < 100 * N; i++) {
			integer[0] += n;
			integer[1] += n;
			integer[2] += n;
			integer[3] += n;
		}
	}

	{
		Bench _("Copy 64 bytes", 100);
		for(int i = 0; i < 100 * N; i++) {
			data1[0] = data2[one_val];
			data1[1] = data2[one_val + 1];
			data1[2] = data2[one_val + 2];
			data1[3] = data2[one_val - 1];
		}
	}

	{
		Bench _("memcpy 64 bytes", 10);
		for(int i = 0; i < 10 * N; i++) {
			memcpy(&data1[0], &data2[one_val], val64);
			memcpy(&data1[1], &data2[one_val], val64);
			memcpy(&data1[2], &data2[one_val], val64);
			memcpy(&data1[3], &data2[one_val], val64);
		}
	}

#if 1
	if(0) {
		for(int pass = 0; pass < 2; pass++) {
			LOG("==================");
			Buffer<byte> b(4000, 1);
			for(int i = 0; i < 4000; i++) {
				b[i] = pass ? Random(256) : (i < 2000 ? 0 : 255);
//				LOG((int)b[i]);
			}
			
			Bench __(pass ? "Branch prediction miss" : "Branch prediction hit", 100);

#ifndef _DEBUG
			for(int i = 0; i < 100 * N / 4000; i++)
#endif
			{
				result = 0;
				for(int i = 0; i < 4000; i += 4) {
					if(b[i] > 128)
						result++;
					if(b[i + 1] > 128)
						result++;
					if(b[i + 2] > 128)
						result++;
					if(b[i + 3] > 128)
						result++;
				}
				DUMP(result);
			}
		}
	}
	if(0) {
		for(int pass = 0; pass < 2; pass++) {
			LOG("==================");
			Buffer<byte> b(4000, 1);
			for(int i = 0; i < 4000; i++) {
				b[i] = pass ? Random(256) : (i < 2000 ? 0 : 255);
//				LOG((int)b[i]);
			}
			
			Bench __(pass ? "Branch prediction sin miss" : "Branch prediction sin hit", 100);

#ifndef _DEBUG
			for(int i = 0; i < 100 * N / 4000; i++)
#endif
			{
				result = 0;
				for(int i = 0; i < 4000; i += 4) {
					fresult += b[i] > 128 ? cos(i) : sin(i);
					fresult += b[i + 1] > 128 ? cos(i + 1) : sin(i + 1);
					fresult += b[i + 2] > 128 ? cos(i + 2) : sin(i + 2);
					fresult += b[i + 3] > 128 ? cos(i + 3) : sin(i + 3);
				}
				DUMP(result);
			}
		}
	}
	{
		Bench _("Mul", 100);
		for(int i = 0; i < 100 * N; i++) {
			integer[0] *= n;
			integer[1] *= n;
			integer[2] *= n;
			integer[3] *= n;
		}
	}
	{
		Bench _("Div32", 100);
		for(int i = 0; i < 100 * N; i++) {
			integer[0] /= n;
			integer[1] /= n;
			integer[2] /= n;
			integer[3] /= n;
		}
	}
	{
		Bench _("Div64", 100);
		for(int i = 0; i < 100 * N; i++) {
			i64[0] /= n64;
			i64[1] /= n64;
			i64[2] /= n64;
			i64[3] /= n64;
		}
	}
	{
		Bench _("FP64 Mul", 100);
		for(int i = 0; i < 100 * N; i++) {
			fp64[0] *= dn;
			fp64[1] *= dn;
			fp64[2] *= dn;
			fp64[3] *= dn;
		}
	}

	{
		Bench _("FP64 Add", 100);
		for(int i = 0; i < 100 * N; i++) {
			fp64[0] += dn;
			fp64[1] += dn;
			fp64[2] += dn;
			fp64[3] += dn;
		}
	}
	{
		Bench _("FP64 Div", 100);
		for(int i = 0; i < 100 * N; i++) {
			fp64[0] /= dn;
			fp64[1] /= dn;
			fp64[2] /= dn;
			fp64[3] /= dn;
		}
	}
	{
		Bench _("FP32 Add", 100);
		for(int i = 0; i < 100 * N; i++) {
			fp32[0] += fn;
			fp32[1] += fn;
			fp32[2] += fn;
			fp32[3] += fn;
		}
	}
	{
		Bench _("FP32 Mul", 100);
		for(int i = 0; i < 100 * N; i++) {
			fp32[0] *= fn;
			fp32[1] *= fn;
			fp32[2] *= fn;
			fp32[3] *= fn;
		}
	}
	{
		Bench _("FP32 Div", 100);
		for(int i = 0; i < 100 * N; i++) {
			fp32[0] /= fn;
			fp32[1] /= fn;
			fp32[2] /= fn;
			fp32[3] /= fn;
		}
	}
	{
		Bench _("FP64 sin", 10);
		for(int i = 0; i < 10 * N; i++) {
			fp64[0] = sin(fp64[0]);
			fp64[1] = sin(fp64[1]);
			fp64[2] = sin(fp64[2]);
			fp64[3] = sin(fp64[3]);
		}
	}
	{
		Bench _("FP32 sin", 10);
		for(int i = 0; i < 10 * N; i++) {
			fp32[0] = sin(fp32[0]);
			fp32[1] = sin(fp32[1]);
			fp32[2] = sin(fp32[2]);
			fp32[3] = sin(fp32[3]);
		}
	}
	{
		Bench _("Copy 64 bytes", 100);
		for(int i = 0; i < 100 * N; i++) {
			data1[0] = data2[one_val];
			data1[1] = data2[one_val + 1];
			data1[2] = data2[one_val + 2];
			data1[3] = data2[one_val - 1];
		}
	}
	{
		Bench _("AtomicInc", 10);
		for(int i = 0; i < 10 * N; i++) {
			AtomicInc(atomic[0]);
			AtomicInc(atomic[1]);
			AtomicInc(atomic[2]);
			AtomicInc(atomic[3]);
		}
	}
	{
		Bench _("free(malloc(32))", 2);
		for(int i = 0; i < 2 * N; i++) {
			void *ptr1 = malloc(32);
			void *ptr2 = malloc(32);
			void *ptr3 = malloc(32);
			void *ptr4 = malloc(32);
			free(ptr1);
			free(ptr2);
			free(ptr3);
			free(ptr4);
		}
	}
	{
		Bench _("free(malloc(70000))", 0.01);
		for(int i = 0; i < N / 100; i++) {
			free(malloc(70000));
			free(malloc(70000));
			free(malloc(70000));
			free(malloc(70000));
		}
	}
	{
		Bench _("free(malloc(1000000))", 0.01);
		for(int i = 0; i < N / 100; i++) {
			free(malloc(10000000));
			free(malloc(10000000));
			free(malloc(10000000));
			free(malloc(10000000));
		}
	}
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
		Bench _("delete new byte[70000] (U++)", 0.1);
		for(int i = 0; i < N / 10; i++) {
			delete new byte[70000];
			delete new byte[70000];
			delete new byte[70000];
			delete new byte[70000];
		}
	}
	{
		Bench _("delete new byte[1000000] (U++)", 0.1);
		for(int i = 0; i < N / 10; i++) {
			delete new byte[1000000];
			delete new byte[1000000];
			delete new byte[1000000];
			delete new byte[1000000];
		}
	}
	if(0) {
		Bench _("Spinlock", 10);
		SpinLock m;
		for(int i = 0; i < 10 * N; i++) {
			m.Enter(); m.Leave();
			m.Enter(); m.Leave();
			m.Enter(); m.Leave();
			m.Enter(); m.Leave();
		}
	}
	{
		Bench _("Mutex lock/unlock", 10);
		Mutex m;
		for(int i = 0; i < 10 * N; i++) {
			m.Enter(); m.Leave();
			m.Enter(); m.Leave();
			m.Enter(); m.Leave();
			m.Enter(); m.Leave();
		}
	}
	{
		std::atomic<bool> exit = false;
		Thread::Start([&] {
			while(!exit) {
				integer[0] += n;
				integer[1] += n;
				integer[2] += n;
				integer[3] += n;
			}
		});
		
		Bench _("Add 2 threads", 100);
		for(int i = 0; i < 100 * N; i++) {
			integer[0] += n;
			integer[1] += n;
			integer[2] += n;
			integer[3] += n;
		}
		
		exit = true;
	}
	{
		std::atomic<bool> exit = false;
		Thread::Start([&] {
			while(!exit) {
				AtomicInc(atomic[0]);
				AtomicInc(atomic[1]);
				AtomicInc(atomic[2]);
				AtomicInc(atomic[3]);
			}
		});

		Bench _("AtomicInc 2 threads", 10);
		for(int i = 0; i < 10 * N; i++) {
			AtomicInc(atomic[0]);
			AtomicInc(atomic[1]);
			AtomicInc(atomic[2]);
			AtomicInc(atomic[3]);
		}
	}
#endif

	RDUMP(data);
	
	double n0 = data[0].b;
	RLOG(n0 / N / 4 * 1e3 << " ns");
	RLOG("{{1:1:1:1 Operation:: /Add:: eq ops:: time");
	for(int i = 0; i < data.GetCount(); i++)
		RLOG(":: " << DeQtf(data[i].a) << Format(":: %.1f:: %.0f:: %.1f ns", data[i].b / n0, data[i].b / n0 * 3, data[i].b / N / 4 * 1e3));
	RLOG("}}");
}
