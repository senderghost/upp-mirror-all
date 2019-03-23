#include <Core/Core.h>

using namespace Upp;

struct Data {
	std::atomic<int> refcount = 1;

	void   Retain()  { ++refcount; }
	void   Release() { if(--refcount == 0) delete this; }
};

static Mutex BigLock;
static thread_local int BigLockLevel = 0;

void EnterBigMutex(int levels = 1)
{
	if(n > 0) {
		if(BigLockLevel == 0)
			BigLock.Enter();
		BigLockLevel += n;
	}
}

void LeaveBigMutex()
{
	if(--BigLockLevel == 0)
		BigLock.Leave();
}

int LeaveBigMutexAll()
{
	int q = BigLockLevel;
	if(q) {
		BigLock.Leave();
		BigLockLevel = 0;
	}
	return q;
}

CONSOLE_APP_MAIN
{
	std::atomic<int> x = 10;
	x++;
	RDUMP((int)x);
}
