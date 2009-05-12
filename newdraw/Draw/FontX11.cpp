#include "Draw.h"

NAMESPACE_UPP

#ifdef PLATFORM_X11

#define LLOG(x)     //  LOG(x)
#define LTIMING(x)  //  TIMING(x)

struct XFTFontFaceInfo {
	String      name;
	bool        fixed:1;
	bool        scaleable:1;
	bool        compose:1;

	XFTFontFaceInfo()
	{
		fixed = scaleable = false;
	}
};

ArrayMap<String, XFTFontFaceInfo>& XFTFontFace()
{
	static ArrayMap<String, XFTFontFaceInfo> x;
	return x;
}

FontInfo::Data::Data()
{
	refcount = 1;
	for(int i = 0; i < 64; i++)
		base[i] = NULL;
	xftfont = NULL;
}

FontInfo::Data::~Data()
{
	DrawLock __;
	if(xftfont0 && xftfont0 != xftfont)
		XftFontClose(Xdisplay, xftfont0);
	if(xftfont)
		XftFontClose(Xdisplay, xftfont);
	for(int i = 0; i < 64; i++)
		if(base[i]) delete[] base[i];
}

void FontInfo::Data::GetMetrics(CharMetrics *t, int from, int count)
{
	DrawLock __;
	LTIMING("GetMetrics");
	LLOG("GetMetrics " << font << " " << from << ", " << count);
	if(xftfont) {
		for(int i = 0; i < count; i++) {
			LTIMING("XftTextExtents16");
			wchar h = from + i;
			XGlyphInfo info;
			XftTextExtents16(Xdisplay, xftfont0, &h, 1, &info);
			t[i].width = info.xOff;
			t[i].lspc = -info.x;
			t[i].rspc = info.xOff - info.width + info.x;
		}
	}
}

const char *basic_fonts[] = {
	"sans-serif",
	"serif",
	"sans-serif",
	"monospace",
	"serif",
	"sans-serif",
	"monospace",
};

static int sCheckComposed(const char *face)
{
	XftFont *xftfont = XftFontOpen(Xdisplay, Xscreenno,
	                               XFT_FAMILY, XftTypeString, (char *)face,
	                               XFT_PIXEL_SIZE, XftTypeInteger, 20,
	                               (void *)0);
	if(xftfont == NULL )
		return -1;
	int n = 0;
	for(int c = 0; c < 128; c++)
		if(!XftCharExists(Xdisplay, xftfont, c + 256))
			n++;
	XftFontClose(Xdisplay, xftfont);
	return n > 10;
}

bool FontInfo::Data::HasChar(int ch) const
{
	return XftCharExists(Xdisplay, xftfont, ch);
}

void FontInfo::InitPlatformFonts()
{
	for(int i = 0; i < __countof(basic_fonts); i++) {
		XFTFontFaceInfo& f = XFTFontFace().Add(basic_fonts[i]);
		f.name = basic_fonts[i];
		f.scaleable = true;
		f.fixed = i == 3 || i == 6;
		f.compose = sCheckComposed(basic_fonts[i]);
	}
	FcFontSet *fs = XftListFonts(Xdisplay, Xscreenno, (void *)0, XFT_FAMILY, XFT_SPACING,
	                             XFT_SCALABLE, (void *)0);
	for(int i = 0; i < fs->nfont; i++) {
		FcChar8 *family = NULL;
		if(FcPatternGetString(fs->fonts[i], FC_FAMILY, 0, &family) == 0 && family) {
			int comp = sCheckComposed((char *)family);
			if(comp >= 0) {
				XFTFontFaceInfo& f = XFTFontFace().GetAdd((char *)family);
				int spacing;
				if(FcPatternGetInteger(fs->fonts[i], FC_SPACING, 0, &spacing) == 0 && spacing == XFT_MONO)
					f.fixed = true;
				FcBool scaleable;
				if(FcPatternGetBool(fs->fonts[i], FC_SCALABLE, 0, &scaleable) == 0 && scaleable)
					f.scaleable = true;
				f.compose = comp;
			}
		}
	}
	FcFontSetDestroy(fs);
}

int    Font::GetFaceCount()
{
	ONCELOCK {
		FontInfo::InitFonts();
	}
	return XFTFontFace().GetCount();
}

String Font::GetFaceName(int index)
{
	ONCELOCK {
		FontInfo::InitFonts();
	}
	return index >= 0 && index < XFTFontFace().GetCount() ? XFTFontFace().GetKey(index)
	                                                      : Null;
}

dword Font::GetFaceInfo(int index) {
	ONCELOCK {
		FontInfo::InitFonts();
	}
	dword w = 0;
	if(index >= 0 && index < XFTFontFace().GetCount()) {
		XFTFontFaceInfo& fi = XFTFontFace()[index];
		if(fi.fixed)
			w |= FIXEDPITCH;
		if(fi.scaleable)
			w |= SCALEABLE;
		if(fi.compose)
			w |= COMPOSED;
	}
	return w;
}

int    gtk_antialias = -1;
int    gtk_hinting = -1;
String gtk_hintstyle;
String gtk_rgba;

XftFont *FontInfo::CreateXftFont(Font font, int angle)
{
	LTIMING("CreateXftFont");
	XftFont *xftfont;
	double sina, cosa;
	int hg = abs(font.GetHeight());
	if(hg == 0) hg = 10;
	int i = font.GetFace();
	if(i < 0 || i >= XFTFontFace().GetCount())
		i = 0;
	const char *face = i < 7 ? basic_fonts[i] : ~XFTFontFace().GetKey(i);
	FcPattern *p = FcPatternCreate();
	FcPatternAddString(p, FC_FAMILY, (FcChar8*)face);
	FcPatternAddInteger(p, FC_SLANT, font.IsItalic() ? 110 : 0);
	FcPatternAddInteger(p, FC_PIXEL_SIZE, hg);
	FcPatternAddInteger(p, FC_WEIGHT, font.IsBold() ? 200 : 100);
	FcPatternAddBool(p, FC_MINSPACE, 1);
	if(angle) {
		FcMatrix mx;
		Draw::SinCos(angle, sina, cosa);
		mx.xx = cosa;
		mx.xy = -sina;
		mx.yx = sina;
		mx.yy = cosa;
		FcPatternAddMatrix(p, FC_MATRIX, &mx);
	}
	FcResult result;
	FcPattern *m = XftFontMatch(Xdisplay, Xscreenno, p, &result);
	if(font.IsNonAntiAliased() || gtk_antialias >= 0) {
		FcPatternDel(m, FC_ANTIALIAS);
		FcPatternAddBool(m, FC_ANTIALIAS,
		                 font.IsNonAntiAliased() ? FcFalse : gtk_antialias ? FcTrue : FcFalse);
	}
	if(gtk_hinting >= 0) {
		FcPatternDel(m, FC_HINTING);
		FcPatternAddBool(m, FC_HINTING, gtk_hinting);
	}
	const char *hs[] = { "hintnone", "hintslight", "hintmedium", "hintfull" };
	for(int i = 0; i < 4; i++)
		if(gtk_hintstyle == hs[i]) {
			FcPatternDel(m, FC_HINT_STYLE);
			FcPatternAddInteger(m, FC_HINT_STYLE, i);
		}
	const char *rgba[] = { "_", "rgb", "bgr", "vrgb", "vbgr" };
	for(int i = 0; i < __countof(rgba); i++)
		if(gtk_rgba == rgba[i]) {
			FcPatternDel(m, FC_RGBA);
			FcPatternAddInteger(m, FC_RGBA, i);
		}
	xftfont = XftFontOpenPattern(Xdisplay, m);
	FcPatternDestroy(p);
	return xftfont;
}

FontInfo FontInfo::AcquireFontInfo(Font font, int angle)
{
	DrawLock __;
	LTIMING("Acquire");
	if(IsNull(font))
		font = StdFont();
	if(font.GetFace() == 0)
		font.Face(AStdFont.GetFace());
	if(font.GetHeight() == 0)
		font.Height(AStdFont.GetHeight());
	FontInfo::Data *f, *fh;
	f = fh = GetFontHash((font.GetHashValue() ^ angle) % (int)FONTHASH);
	LLOG("Acquire " << font << " device: " << device);
	for(;;) {
		f = f->GetNext(HASH);
		if(f == fh) break;
		if(f->font == font && f->angle == angle)
		{
			LLOG("Reusing " << f->font);
			if(f->InList(LRU)) {
				f->Unlink(LRU);
				FontCached--;
				LLOG("Removing from cache " << f->font << " cached:" << FontCached);
			}
			f->refcount++;
			return f;
		}
	}
	LLOG("New " << font);
	LTIMING("Acquire New");
	f = fh->InsertNext(HASH);
	f->font = font;
	f->angle = angle;
	int hg = abs(font.GetHeight());
	if(hg == 0) hg = 10;
	f->xftfont0 = f->xftfont = CreateXftFont(font, angle);
	if(angle)
		f->xftfont0 = CreateXftFont(font, 0);
	f->filename = NULL;
	f->ascent = (int16)f->xftfont0->ascent;
	f->descent = (int16)f->xftfont0->descent;
	f->height = f->ascent + f->descent;
	f->lineheight = (int16)f->xftfont0->height;
	f->external = 0;
	f->internal = 0;
	f->overhang = 0;
	f->maxwidth = (int16)f->xftfont0->max_advance_width;
	f->avewidth = f->maxwidth;
	f->default_char = '?';
	f->fixedpitch = font.GetFaceInfo() & Font::FIXEDPITCH;
	f->underline_thickness = max(hg / 20, 1);
	f->underline_position = max(hg / 15, int(f->descent > 0));
	if(angle) {
		Draw::SinCos(angle, f->sina, f->cosa);
		f->offset.cx = fround(f->ascent * f->sina);
		f->offset.cy = fround(f->ascent * f->cosa);
	}
	FontInfo fi = FontInfo(f);
	fi.GetPage(0);
	return fi;
}

String FontInfo::GetFileName() const
{
	if(IsNull(ptr->filename)) {
		char *fn = NULL;
		XftPatternGetString(ptr->xftfont->pattern, XFT_FILE, 0, &fn);
		if(fn)
			ptr->filename = fn;
	}
	return ptr->filename;
}

#endif

END_UPP_NAMESPACE
