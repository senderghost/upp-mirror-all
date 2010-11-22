#include <CtrlLib/CtrlLib.h>

using namespace Upp;

#include <SDL/SDLCtrl.h>

#define LAYOUTFILE <SDLCtrl_demo/demobasic.lay>
#include <CtrlCore/lay.h>

struct SDLCtrl_Basic : public WithBasic<TopWindow> {
typedef SDLCtrl_Basic CLASSNAME;	
	virtual void Layout() {
		if (!sdlctrl.IsReady())
			return;
		
		ImageDraw iwLogo(500, 100);
		iwLogo.DrawEllipse(20, 20, 100, 40, LtGreen());
		iwLogo.DrawText(50, 28, "U++", Arial(20).Bold(), Black()); 
		Image imLogo = iwLogo;
		
		Rect r = sdlctrl.GetView();
		
		if	(usingBlit) {
			SDLSurface surf(r.GetWidth(), r.GetHeight(), sdlctrl.GetBpp());
			
			surf.Lock();
			for (int radius = r.GetWidth(); radius > 0; radius -= 5)
		 		surf.DrawCircle(r.GetWidth()/2, r.GetHeight()/2, radius, 2, White());
			surf.DrawRect(0, 0, r.GetWidth(), r.GetHeight(), 3, LtRed());	
			surf.DrawLine(0, 0, r.GetWidth()-1, r.GetHeight()-1, 1, LtGreen());
			surf.DrawImage(imLogo, 0, 0, Black());
			surf.Unlock();
			
			sdlctrl.Blit(surf);
		} else {
			sdlctrl.Lock();
			for (int radius = r.GetWidth(); radius > 0; radius -= 5)
		 		sdlctrl.DrawCircle(r.GetWidth()/2, r.GetHeight()/2, radius, 2, White());
			sdlctrl.DrawRect(0, 0, r.GetWidth(), r.GetHeight(), 3, LtRed());	
			sdlctrl.DrawLine(0, 0, r.GetWidth()-1, r.GetHeight()-1, 1, LtGreen());
			sdlctrl.DrawImage(imLogo, 0, 0, Black());
			sdlctrl.Unlock();
		}
	};
	SDLCtrl_Basic() {
		CtrlLayout(*this, "Basic demo");
		Zoomable().Sizeable();	
		
		usingBlit = false;
	}
};

void Run_Basic() {
	SDLCtrl_Basic().Run();
}
