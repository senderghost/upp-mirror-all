#include "jetstory.h"

#define IMAGECLASS MapImg
#define IMAGEFILE <JetStory/map.iml>
#include <Draw/iml_source.h>

#define IMAGECLASS JetStoryImg
#define IMAGEFILE <JetStory/jetstory.iml>
#include <Draw/iml_source.h>

using namespace Upp;


struct JetStory : TopWindow {
	Point pos;

	virtual void Paint(Draw& w);
	
	virtual void MouseMove(Point p, dword keyflags) {
		pos = p;
		pos.x *= 2;
		Refresh();
	}

	virtual void RightDown(Point p, dword keyflags) {
		Break();
	}

	JetStory() {
		FullScreen();
	}
};

Pointf ship = Pointf(100, 100);

void JetStory::Paint(Draw& w)
{
	Size sz = GetSize();

	w.DrawRect(GetSize(), Black());
	
	for(int x = 0; x < MAPX; x++)
		for(int y = 0; y < MAPY; y++) {
			Point p = BLOCKSIZE * Size(x, y) - (Point)ship;
			if(p.x + BLOCKSIZE >= 0 && p.y + BLOCKSIZE >= 0 && p.x < sz.cx && p.y < sz.cy)
				w.DrawImage(x * BLOCKSIZE - pos.x, y * BLOCKSIZE - pos.y, BlocksImg::Get(jetstory[y][x]));
		}
	
	Image m = JetStoryImg::ship();
	Size isz = m.GetSize();
	
	w.DrawImage(sz.cx / 2 - isz.cx / 2, sz.cy / 2 - isz.cy / 2, m);
}


GUI_APP_MAIN
{
//	ImportMap();
	
	JetStory().Run();
}
