#include "CocoDraw.h"

#define LLOG(x)
#define LTIMING(x)

namespace Upp {

CTFontRef CT_Font(Font fnt)
{ // TODO: Caching (?)
	CFRef<CFStringRef> s = CFStringCreateWithCString(NULL, ~fnt.GetFaceName(), kCFStringEncodingUTF8);
    CFRef<CTFontRef> ctfont0 = CTFontCreateWithName(s, fnt.GetHeight(), NULL);
	if(fnt.IsItalic() || fnt.IsBold()) {
	    CTFontSymbolicTraits symbolicTraits = 0;
	    if(fnt.IsBold())
		    symbolicTraits |= kCTFontBoldTrait;
	    if(fnt.IsItalic())
			symbolicTraits |= kCTFontItalicTrait;
		CGAffineTransform transform = CGAffineTransformIdentity;
		return CTFontCreateCopyWithSymbolicTraits(ctfont0, 32, &transform, symbolicTraits, symbolicTraits);
	}
	return ctfont0.Detach();
}

CommonFontInfo GetFontInfoSys(Font font)
{
	CommonFontInfo fi;
	String path;
	CFRef<CTFontRef> ctfont = CT_Font(font);
	if(ctfont) {
	#if 0
		DDUMP(font);
	    DDUMP(CTFontGetAscent(ctfont));
	    DDUMP(CTFontGetDescent(ctfont));
	    DDUMP(CTFontGetLeading(ctfont));
	    DDUMP(CTFontGetXHeight(ctfont));
	    DDUMP(CTFontGetUnderlinePosition(ctfont));
	#endif
		fi.ascent = ceil(CTFontGetAscent(ctfont));
		fi.descent = ceil(CTFontGetDescent(ctfont));
		fi.height = fi.ascent + fi.descent;
		fi.lineheight = fi.height; // TODO!
		fi.external = 0;
		fi.internal = 0;
		fi.overhang = 0;
		fi.maxwidth = 99999; // TODO?
		fi.avewidth = fi.maxwidth;
		fi.default_char = '?';
		fi.fixedpitch = false; _DBG_ // TODO!
		fi.ttf = true;
		_DBG_ // TODO: PATH for data
//		if(path.GetCount() < 250)
//			strcpy(fi.path, ~path);
//		else
			*fi.path = 0;
	}
	return fi;
}

GlyphInfo  GetGlyphInfoSys(Font font, int chr)
{
	LTIMING("GetGlyphInfoSys");
	GlyphInfo gi;
	gi.lspc = gi.rspc = 0;
	gi.width = 0x8000;

	CFRef<CTFontRef> ctfont = CT_Font(font);
	if(ctfont) {
		LTIMING("GetGlyphInfoSys 2");
	    CGGlyph glyph_index;
	    UniChar h = chr;
		CTFontGetGlyphsForCharacters(ctfont, &h, &glyph_index, 1);
		if(glyph_index) {
		    CGSize advance;
			CTFontGetAdvancesForGlyphs(ctfont, kCTFontOrientationHorizontal, &glyph_index, &advance, 1);
			gi.width = ceil(advance.width);
			gi.lspc = gi.rspc = 0; _DBG_ // TODO! (using bounding box?)
		}
	}
	return gi;
}

Vector<FaceInfo> GetAllFacesSys()
{
	Index<String> facename;
	facename.Add("Arial"); // TODO: This should be default GUI font
	facename.Add("Times New Roman");
	facename.Add("Arial");
	facename.Add("Courier New");

	AutoreleasePool __;

    CFRef<CTFontCollectionRef> collection = CTFontCollectionCreateFromAvailableFonts(0);
    if(collection) {
	    CFRef<CFArrayRef> fonts = CTFontCollectionCreateMatchingFontDescriptors(collection);
	    if(fonts) {
			int count = CFArrayGetCount(fonts);
		    for(int i = 0; i < count; ++i) {
				CTFontDescriptorRef font = (CTFontDescriptorRef)CFArrayGetValueAtIndex(fonts, i);
				CFRef<CFStringRef> family_name = (CFStringRef)CTFontDescriptorCopyAttribute(font, kCTFontFamilyNameAttribute);
				facename.FindAdd(ToString(family_name));
		    }
		}
    }
    
	Vector<FaceInfo> r;
	for(String s : facename) {
        FaceInfo& fi = r.Add();
		fi.name = s;
		fi.info = 0;
    }
    
    return r;
}

String GetFontDataSys(Font font)
{// TODO! CFUrl?
	_DBG_
	return Null;
}

void RenderCharacterSys(FontGlyphConsumer& sw, double x, double y, int ch, Font fnt)
{
	// TODO!
	_DBG_
}

};