#include <Core/Core.h>

using namespace Upp;

template <typename... Args>
struct CoStack {
	Vector<Tuple<Args...>> stack;
	SpinLock               lock;
	CoWork                 cw;

	int Push(const Args&... args) {
		SpinLock::Lock __(lock);
		stack.Add(Tuple<Args...>(args...));
		return stack.GetCount();
	}
	void Fork(const Args&... args, const Function<void ()>& fn) {
		if(cw.GetScheduledCount() < min(CoWork::GetPoolSize(), Push(args...)))
			cw & fn;
	}
	bool Pop(Args&... args) {
		SpinLock::Lock __(lock);
		if(stack.GetCount() == 0)
			return false;
		Tie(args...) = stack.Pop();
		return true;
	}
};

template <class I, class Less>
void CoSort2__(CoStack<I, I>& cs, const Less& less)
{
	const int PARALLEL_THRESHOLD = 60;
	
	Event<> job = [&] { CoSort2__(cs, less); };
	
	I l, h;
	while(cs.Pop(l, h))
		for(;;) {
			int count = int(h - l);
			if(count < 2)
				break;
			if(count < 8) {                         // Final optimized SelectSort
				FinalSort__(l, h, less);
				break;
			}
			int pass = 4;
			for(;;) {
				I middle = l + (count >> 1);        // get the middle element
				OrderIter2__(l, middle, less);      // sort l, middle, h-1 to find median of 3
				OrderIter2__(middle, h - 1, less);
				OrderIter2__(l, middle, less);      // median is now in middle
				IterSwap(l + 1, middle);            // move median pivot to l + 1
				I ii = l + 1;
				for(I i = l + 2; i != h - 1; ++i)   // do partitioning; already l <= pivot <= h - 1
					if(less(*i, *(l + 1)))
						IterSwap(++ii, i);
				IterSwap(ii, l + 1);                // put pivot back in between partitions
				I iih = ii;
				while(iih + 1 != h && !less(*ii, *(iih + 1))) // Find middle range of elements equal to pivot
					++iih;
				if(pass > 5 || min(ii - l, h - iih) > (max(ii - l, h - iih) >> pass)) { // partition sizes ok or we have done max attempts
					if(ii - l < h - iih - 1) {       // schedule or recurse on smaller partition, tail on larger
						if(ii - l < PARALLEL_THRESHOLD) // too small to run in parallel?
							Sort__(l, ii, less); // resolve in this thread
						else
							cs.Fork(l, ii, job); // schedule for parallel execution
						l = iih + 1;
					}
					else {
						if(h - iih - 1 < PARALLEL_THRESHOLD) // too small to run in parallel?
							Sort__(iih + 1, h, less); // resolve in this thread
						else
							cs.Fork(iih + 1, h, job); // schedule for parallel execution
						h = ii;
					}
					break;
				}
				IterSwap(l, l + (int)Random(count));     // try some other random elements for median pivot
				IterSwap(middle, l + (int)Random(count));
				IterSwap(h - 1, l + (int)Random(count));
				pass++;
			}
		}
}

template <class I, class Less>
void CoSort2__(I l, I h, const Less& less)
{
	CoStack<I, I> cs;
	cs.Push(l, h);
	CoSort2__(cs, less);
}

template <class Range, class Less>
void CoSort2(Range& c, const Less& less)
{
	CoSort2__(c.begin(), c.end(), less);
}

template <class Range, class Less>
void CoSort2(Range&& c, const Less& less)
{
	CoSort2(c, less);
}

template <class Range>
void CoSort2(Range& c)
{
	CoSort2__(c.begin(), c.end(), std::less<ValueTypeOf<Range>>());
}

template <class Range>
void CoSort2(Range&& c)
{
	CoSort2(c);
}

#include <Core/Core.h>

using namespace Upp;

#ifdef _DEBUG
#define N 10000
#else
#define N 100000
#endif

CONSOLE_APP_MAIN
{
	StdLogSetup(LOG_FILE|LOG_COUT);
	
	for(int ii = 0; ii < 100; ii++) {

		Vector<String> h;
		for(int i = 0; i < N; i++)
			h.Add(AsString(Random()));
	
		auto h0 = clone(h);
		{
			RTIMING("Sort");
			TimeStop tm;
			Sort(h0);
		}
	
		{
			RTIMING("CoSort2");
			auto h1 = clone(h);
			TimeStop tm;
			CoSort2(h1);
			ASSERT(h1 == h0);
		}
	
		{
			RTIMING("CoSort");
			auto h1 = clone(h);
			TimeStop tm;
			CoSort(h1);
			ASSERT(h1 == h0);
		}

	}
	
	Thread::ShutdownThreads();
	RLOG("Exit");
}
