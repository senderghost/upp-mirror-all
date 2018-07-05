#ifndef _NSView_cocoutil_h_
#define _NSView_cocoutil_h_

#import <AppKit/AppKit.h>
#include <Draw/Draw.h>
#include <CocoDraw/CocoDraw.h>

using namespace Upp;

template <class T>
struct CFRef {
	T ptr;
	T operator~()   { return ptr; }
	operator T()    { return ptr; }
	T  operator->() { return ptr; }
	CFRef(T p)      { ptr = p; }
	~CFRef()        { CFRelease(ptr); }
};

struct AutoreleasePool {
	NSAutoreleasePool *pool;

	AutoreleasePool() {
		pool = [[NSAutoreleasePool alloc] init];
	}
	~AutoreleasePool() {
	    [pool release];
	}
};

WString ToWString(CFStringRef s);
String ToString(CFStringRef s);

#endif
