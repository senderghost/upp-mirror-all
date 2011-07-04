#include "LinuxFbLocal.h"

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

NAMESPACE_UPP

#define LLOG(x)       LOG(x)

	int fbfd = 0;
	struct fb_var_screeninfo vinfo;
	struct fb_fix_screeninfo finfo;
	long int screensize = 0;
	char *fbp = 0;
	bool fbEndSession = false;

//FIXME get input events
bool GetShift()       { return false; }//!!(GetKeyState(VK_SHIFT) & 0x8000); }
bool GetCtrl()        { return false; }//!!(GetKeyState(VK_CONTROL) & 0x8000); }
bool GetAlt()         { return false; }//!!(GetKeyState(VK_MENU) & 0x8000); }
bool GetCapsLock()    { return false; }//!!(GetKeyState(VK_CAPITAL) & 1); }
bool GetMouseLeft()   { return false; }//!!(GetKeyState(VK_LBUTTON) & 0x8000); }
bool GetMouseRight()  { return false; }//!!(GetKeyState(VK_RBUTTON) & 0x8000); }
bool GetMouseMiddle() { return false; }//!!(GetKeyState(VK_MBUTTON) & 0x8000); }


bool FBEndSession()
{
	return fbEndSession;
}

bool FBIsWaitingEvent()
{
	//MSG msg;
	return false; //PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE);
}

bool FBProcessEvent(bool *quit)
{
/*
	MSG msg;
	if(PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
		if(msg.message == WM_QUIT && quit)
			*quit = true;
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
		return true;
	}
*/
	static int i = 10;
	if(--i > 0) return true; //fake message processing
	return false;
}

void FBSleep(int ms)
{
//	MsgWaitForMultipleObjects(0, NULL, FALSE, ms, QS_ALLINPUT);
}

void FBUpdate(const Rect& inv)
{
//	if(fbHWND)
//		::InvalidateRect(fbHWND, inv, false);
	const ImageBuffer& framebuffer = Ctrl::GetFrameBuffer();
	memcpy(fbp, (const char*)~framebuffer, framebuffer.GetLength() * sizeof(RGBA));
}

void FBInit(const String& fbdevice)
{
	Ctrl::InitFB();

	// Open the file for reading and writing
	fbfd = open(fbdevice, O_RDWR);
	if (!fbfd) {
		printf("Error: cannot open framebuffer device.\n");
		exit(1);
	}
	RLOG("The framebuffer device was opened successfully.\n");

	// Get fixed screen information
	if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo)) {
		printf("Error reading fixed information.\n");
		exit(2);
	}

	// Get variable screen information
	if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo)) {
		printf("Error reading variable information.\n");
		exit(3);
	}

	RLOG(vinfo.xres << "x" << vinfo.yres << " @ " << vinfo.bits_per_pixel);

	// Figure out the size of the screen in bytes
	screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

	// Map the device to memory
	fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED,
					fbfd, 0);
	if ((intptr_t)fbp == -1) {
		printf("Error: failed to map framebuffer device to memory.\n");
		exit(4);
	}
	RLOG("The framebuffer device was mapped to memory successfully.\n");
	
	Ctrl::SetFramebufferSize(Size(vinfo.xres, vinfo.yres));
}

void FBDeInit();
{
	munmap(fbp, screensize);
	close(fbfd);
}

END_UPP_NAMESPACE
