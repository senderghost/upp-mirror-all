#ifndef _hdIE_ActiveX2_h_
#define _hdIE_ActiveX2_h_

#include <CtrlLib/CtrlLib.h>

#ifdef PLATFORM_WIN32

#ifndef OLERENDER_DRAW	
	#define OLERENDER_DRAW	1
#endif

#define CY void *

#include <windows.h>
#include <Mshtml.h>
#include <winnls.h>

#include "ActiveX_base.h"
#include <Exdisp.h>

// static const CLSID CLSID_MozillaBrowser = {0x1339B54C, 0x3453, 0x11D2, {0x93, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};	//http://www.iol.ie/~locka/mozilla/control.htm

NAMESPACE_UPP

class InternetExplorerBrowser : public DHCtrlActiveX {
public:
	virtual void Created();
	
	InternetExplorerBrowser(bool status = true) : DHCtrlActiveX(CLSID_WebBrowser, "IExplorer", status) {
		set = NOP;
		silent = false;
	};
	~InternetExplorerBrowser();

	void   Browse(const String& url);
	void   ShowHTML(const String& html);
	void   Silent(bool b = true);

	bool   GoForward();
	bool   GoBack();
	String GetLocation();
	String GetTitle();
	bool   GetOffline(bool &offline);
	String GetReadyState();
	bool   GoHome();
	bool   RefreshPage();
	bool   Stop();
	void   Quit();

private:
	enum { NOP, SETHTML, SETURL };
	int    set;
	String data;
	bool   silent;

	void Setup();

	class IIWebBrowser {
	public:
		IIWebBrowser(InternetExplorerBrowser *obj) {
			if (obj->GetStatus())
				web = (IWebBrowser2 *)obj->QueryInterface(IID_IWebBrowser2);
			else
				web = 0;
		}
		~IIWebBrowser() {
			if (web)
				web->Release();
		}
		operator IWebBrowser2 *()    { return web; }
		IWebBrowser2 * operator ->() { return web; }

	private:
		IWebBrowser2 *web;
	};
};

END_UPP_NAMESPACE

#endif

#endif
