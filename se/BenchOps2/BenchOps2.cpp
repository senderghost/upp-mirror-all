#include <Core/Core.h>

using namespace Upp;

Vector<Tuple2<String, double>> data;

const int N = 10000000;

struct Bench {
	String name;
	double count;
	int    time0;
	
	Bench(const char *nm, double n = 1) {
		Cout() << data.GetCount() + 1 << ": " << nm << "\n";
		name = nm;
		time0 = (double)usecs();
		count = n;
	}
	
	~Bench() {
		int t = usecs() - time0;
		data.Add(MakeTuple(name, t / count));
	}
};

const int AN = 256;

volatile int    integer[16];
volatile thread_local int  tls[16];
volatile int64  i64[16];
volatile double fp64[16];
volatile float  fp32[16];
volatile Atomic atomic[16];

struct Data64 {
	int64 data[8];
};

Data64 data1[16], data2[16];

CONSOLE_APP_MAIN
{
	int n = Random();
	if(!n)
		n = 1;
	int64 n64 = n;
	double dn = Randomf() + 0.01;
	float fn = (float)dn;
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
		Bench _("TLS", 100);
		for(int i = 0; i < 100 * N; i++) {
			tls[0] += n;
			tls[1] += n;
			tls[2] += n;
			tls[3] += n;
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
		Bench _("FP64 Add", 100);
		for(int i = 0; i < 100 * N; i++) {
			fp64[0] += dn;
			fp64[1] += dn;
			fp64[2] += dn;
			fp64[3] += dn;
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
		Bench _("sin 64", 10);
		for(int i = 0; i < 10 * N; i++) {
			fp64[0] = sin(fp64[0]);
			fp64[1] = sin(fp64[1]);
			fp64[2] = sin(fp64[2]);
			fp64[3] = sin(fp64[3]);
		}
	}
	{
		Bench _("sin 32", 10);
		for(int i = 0; i < 10 * N; i++) {
			fp32[0] = sin(fp32[0]);
			fp32[1] = sin(fp32[1]);
			fp32[2] = sin(fp32[2]);
			fp32[3] = sin(fp32[3]);
		}
	}
	{
		Bench _("Copy 64bytes", 100);
		for(int i = 0; i < 100 * N; i++) {
			data1[0] = data2[0];
			data1[1] = data2[1];
			data1[2] = data2[2];
			data1[3] = data2[3];
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
			void *ptr1 = malloc(64);
			void *ptr2 = malloc(64);
			void *ptr3 = malloc(64);
			void *ptr4 = malloc(64);
			free(ptr1);
			free(ptr2);
			free(ptr3);
			free(ptr4);
		}
	}
	{
		Bench _("delete new byte[32]", 10);
		for(int i = 0; i < 10 * N; i++) {
			delete new byte[32];
			delete new byte[32];
			delete new byte[32];
			delete new byte[32];
		}
	}
	{
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

	RDUMP(data);
	
	double n0 = data[0].b;
	for(int i = 0; i < data.GetCount(); i++) {
		data[i].b /= n0;
		RLOG(data[i].a << ": " << data[i].b);
	}
	
	RDUMP(data);
}
