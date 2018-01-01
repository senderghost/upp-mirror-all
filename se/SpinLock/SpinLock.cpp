#include <Core/Core.h>

using namespace Upp;

struct SLock {
#ifdef COMPILER_MSC
	volatile LONG locked;

	bool TryEnter() { return InterlockedCompareExchange(&locked, 1, 0) == 0; }
	void Leave()    { _ReadWriteBarrier(); locked = 0; }
#else
	volatile int locked;
	
	bool TryEnter() { return  __sync_bool_compare_and_swap (&locked, 0, 1); }
	void Leave()    { __sync_lock_release(&locked); }
#endif

	void Enter()    { while(!TryEnter()) Wait(); }
	
	void Wait();
	
	class Lock;

	SLock()         { locked = 0; }
};

void SLock::Wait()
{
	volatile int n = 0;
	while(locked) {
	#ifdef CPU_X86
		_mm_pause();
	#endif
		if(n++ > 500)
			Sleep(0);
	}
}

CONSOLE_APP_MAIN
{
	SLock spin;
	Mutex mutex;

	Vector<String> h;
	for(int i = 0; i < 10000000; i++)
		h.Add(AsString(i));

	{
		int data = 0;
		{
			RTIMING("NoLocks");
			for(int pass = 0; pass < 3; pass++)
				for(int i = 0; i < h.GetCount(); i++) {
					data += atoi(h[i]);
				}
		}
		RDUMP(data);
	}
	
	{
		int   data = 0;

		auto f = [&] {
			for(int i = 0; i < h.GetCount(); i++) {
				spin.Enter();
				data += atoi(h[i]);
				spin.Leave();
			}
		};
		
		{
			RTIMING("Spin work");
			Thread t1, t2, t3;
			t1.Run(f);
			t2.Run(f);
			t3.Run(f);
			t1.Wait();
			t2.Wait();
			t3.Wait();
		}
		RDUMP(data);
	}

	{
		int   data = 0;

		auto f = [&] {
			for(int i = 0;  i < h.GetCount(); i++) {
				mutex.Enter();
				data += atoi(h[i]);
				mutex.Leave();
			}
		};
		
		{
			RTIMING("Mutex work");
			Thread t1, t2, t3;
			t1.Run(f);
			t2.Run(f);
			t3.Run(f);
			t1.Wait();
			t2.Wait();
			t3.Wait();
		}
		RDUMP(data);
	}
	
	for(int i = 0; i < 10000000; i++)
		{
			RTIMING("Spin");
			spin.Enter();
			spin.Leave();
		}
	for(int i = 0; i < 10000000; i++)
		{
			RTIMING("Mutex")
			mutex.Enter();
			mutex.Leave();
		}
}
