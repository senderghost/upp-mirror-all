#include "CtrlCore.h"

#ifdef PLATFORM_X11

#include <locale.h>

#ifdef _DEBUG
//	#define SYNCHRONIZE
#endif

#define LLOG(x) // LOG(x)

XIM Ctrl::xim;

Atom XAtom(const char *name)
{
	Atom x;
	INTERLOCKED {
		static VectorMap<String, int> atoms;
		int q = atoms.Get(name, Null);
		if(IsNull(q)) {
			q = XInternAtom(Xdisplay, name, XFalse);
			atoms.Add(name, q);
		}
		x = q;
	}
	return x;
}

String XAtomName(Atom atom)
{
	return XGetAtomName(Xdisplay, atom);
}

String GetProperty(Window w, Atom property, Atom rtype)
{
	LOG("GetProperty!");
	String result;
	int format;
	unsigned long nitems, after = 1;
	long offset = 0;
	Atom type = None;
	unsigned char *data;
	long rsize = XMaxRequestSize(Xdisplay);
	while(after > 0 &&
	      XGetWindowProperty(Xdisplay, w, property, offset, rsize, XFalse,
	                         rtype, &type, &format, &nitems, &after, &data) == Success &&
	      type != None) {
		if(data) {
			int len = format == 32 ? sizeof(unsigned long) * nitems : nitems * (format >> 3);
			result.Cat(data, len);
			XFree((char *)data);
			offset += len >> 2;
		}
		else
			break;
	}
	return result;
}

bool WaitForEvent(Window w, int type, XEvent& event){
	for(int i = 0; i < 50; i++) {
		if(XCheckTypedWindowEvent(Xdisplay, w, type, &event))
			return true;
		Sleep(10);
	}
	LOG("WaitForEvent failed");
	return false;
}


String ReadPropertyData(Window w, Atom property, Atom rtype)
{
	static Atom XA_INCR = XAtom("INCR");
	Atom type;
	int format;
	unsigned long nitems, after;
	unsigned char *ptr;
	XEvent event;
	String r;
	if(XGetWindowProperty(Xdisplay, w, property, 0, 0, XFalse, AnyPropertyType,
	                      &type, &format, &nitems, &after, &ptr) == Success && type != None) {
		XFree(ptr);
		if(type == XA_INCR) {
			LOG("Incremental");
			XDeleteProperty(Xdisplay, w, property);
			XFlush(Xdisplay);
			XEvent event;
			for(;;) {
				XFlush(Xdisplay);
				if(!WaitForEvent(w, PropertyNotify, event))
					break;
				DUMP(event.xproperty.state);
				if(event.xproperty.atom == property && event.xproperty.state == PropertyNewValue) {
					LOG("Reading incremental chunk...");
					DUMP(XAtomName(event.xproperty.atom));
					String x = GetProperty(w, property, rtype);
					DUMP(x.GetLength());
					if(!x.GetLength())
						break;
					r.Cat(x);
					XDeleteProperty(Xdisplay, w, property);
				}
			}
		}
		else
			r = GetProperty(w, property, rtype);
	}
	return r;
}

Vector<int> GetPropertyInts(Window w, Atom property, Atom rtype)
{
	Vector<int> result;
	String p = GetProperty(w, property, rtype);
	const long int *ptr = (const long int *)~p;
	const long int *lim = ptr + p.GetLength() / 4;
	result.Reserve(p.GetLength() / 4);
	while(ptr < lim)
		result.Add(*ptr++);
	return result;
}

Index<Atom>& _NET_Supported()
{
	static Index<Atom> q;
	return q;
}

int X11ErrorHandler(XDisplay *, XErrorEvent *error)
{
	static const char *request[] = {
		"",
		"X_CreateWindow",
		"X_ChangeWindowAttributes",
		"X_GetWindowAttributes",
		"X_DestroyWindow",
		"X_DestroySubwindows",
		"X_ChangeSaveSet",
		"X_ReparentWindow",
		"X_MapWindow",
		"X_MapSubwindows",
		"X_UnmapWindow",
		"X_UnmapSubwindows",
		"X_ConfigureWindow",
		"X_CirculateWindow",
		"X_GetGeometry",
		"X_QueryTree",
		"X_InternAtom",
		"X_GetAtomName",
		"X_ChangeProperty",
		"X_DeleteProperty",
		"X_GetProperty",
		"X_ListProperties",
		"X_SetSelectionOwner",
		"X_GetSelectionOwner",
		"X_ConvertSelection",
		"X_SendEvent",
		"X_GrabPointer",
		"X_UngrabPointer",
		"X_GrabButton",
		"X_UngrabButton",
		"X_ChangeActivePointerGrab",
		"X_GrabKeyboard",
		"X_UngrabKeyboard",
		"X_GrabKey",
		"X_UngrabKey",
		"X_AllowEvents",
		"X_GrabServer",
		"X_UngrabServer",
		"X_QueryPointer",
		"X_GetMotionEvents",
		"X_TranslateCoords",
		"X_WarpPointer",
		"X_SetInputFocus",
		"X_GetInputFocus",
		"X_QueryKeymap",
		"X_OpenFont",
		"X_CloseFont",
		"X_QueryFont",
		"X_QueryTextExtents",
		"X_ListFonts",
		"X_ListFontsWithInfo",
		"X_SetFontPath",
		"X_GetFontPath",
		"X_CreatePixmap",
		"X_FreePixmap",
		"X_CreateGC",
		"X_ChangeGC",
		"X_CopyGC",
		"X_SetDashes",
		"X_SetClipRectangles",
		"X_FreeGC",
		"X_ClearArea",
		"X_CopyArea",
		"X_CopyPlane",
		"X_PolyPoint",
		"X_PolyLine",
		"X_PolySegment",
		"X_PolyRectangle",
		"X_PolyArc",
		"X_FillPoly",
		"X_PolyFillRectangle",
		"X_PolyFillArc",
		"X_PutImage",
		"X_GetImage",
		"X_PolyText8",
		"X_PolyText16",
		"X_ImageText8",
		"X_ImageText16",
		"X_CreateColormap",
		"X_FreeColormap",
		"X_CopyColormapAndFree",
		"X_InstallColormap",
		"X_UninstallColormap",
		"X_ListInstalledColormaps",
		"X_AllocColor",
		"X_AllocNamedColor",
		"X_AllocColorCells",
		"X_AllocColorPlanes",
		"X_FreeColors",
		"X_StoreColors",
		"X_StoreNamedColor",
		"X_QueryColors",
		"X_LookupColor",
		"X_CreateCursor",
		"X_CreateGlyphCursor",
		"X_FreeCursor",
		"X_RecolorCursor",
		"X_QueryBestSize",
		"X_QueryExtension",
		"X_ListExtensions",
		"X_ChangeKeyboardMapping",
		"X_GetKeyboardMapping",
		"X_ChangeKeyboardControl",
		"X_GetKeyboardControl",
		"X_Bell",
		"X_ChangePointerControl",
		"X_GetPointerControl",
		"X_SetScreenSaver",
		"X_GetScreenSaver",
		"X_ChangeHosts",
		"X_ListHosts",
		"X_SetAccessControl",
		"X_SetCloseDownMode",
		"X_KillClient",
		"X_RotateProperties",
		"X_ForceScreenSaver",
		"X_SetPointerMapping",
		"X_GetPointerMapping",
		"X_SetModifierMapping",
		"X_GetModifierMapping",
		"X_NoOperation",
	};

	char h[512];
	XGetErrorText(Xdisplay, error->error_code, h, 512);
	String e;
	e << "X Error: " << h;
	if(error->request_code < __countof(request))
		e << ", request: " << request[error->request_code];
	e << ", resource id: " << (int)error->resourceid << " = " << Format("%0X", (int)error->resourceid);
	RLOG(e);
	puts(e);
	BugLog() << e << "\r\n";
	UsrLogT(e);
	return 0;
}

void Ctrl::InitX11(const char *display)
{
	InitX11Draw(display);
	InitTimer();
	byte dummy[5];
	Xbuttons = XGetPointerMapping(Xdisplay, dummy, 5);

	Xeventtime = CurrentTime;
	XSetErrorHandler(X11ErrorHandler);
#ifdef SYNCHRONIZE
	XSynchronize(Xdisplay, 1);
#endif
	Vector<int> nets = GetPropertyInts(Xroot, XAtom("_NET_SUPPORTED"));
	for(int i = 0; i < nets.GetCount(); i++)
		_NET_Supported().Add(nets[i]);

	Ctrl::SetXPStyle();
	Ctrl::SetFlags(Ctrl::EFFECT_SLIDE | Ctrl::DRAGFULLWINDOW | Ctrl::DROPSHADOWS | Ctrl::ALTACCESSKEYS);

	setlocale(LC_ALL, "en_US.utf8");
	if(XSupportsLocale()) {
		XSetLocaleModifiers("");
		xim = XOpenIM(Xdisplay, NULL, NULL, NULL);
	}
	else {
		xim = NULL;
		LOG("IM unsupported!");
	}
}

void Ctrl::ExitX11()
{
//	if(xic)
//		XDestroyIC(xic);
	if(xim)
		XCloseIM(xim);
}

Rect Ctrl::GetDefaultWindowRect()
{
	static int pos = 0;
	pos += 10;
	int cx = Xwidth * 2 / 3;
	int cy = Xheight * 2 / 3;
	if(pos + cx + 50 > Xwidth || pos + cy + 50 > Xheight)
		pos = 0;
	return RectC(pos + 20, pos + 20, cx, cy);
}

Rect Ctrl::GetWorkArea()
{
	return RectC(0, 0, Xwidth, Xheight);
}

int Ctrl::GetKbdDelay()
{
	return 250;
}

int Ctrl::GetKbdSpeed()
{
	return 25;
}
/*
bool Ctrl::IsOpenEffectsMode() {
	return KDESettings()("KDE", "EffectAnimateMenu") == "true";
}
*/
#endif
