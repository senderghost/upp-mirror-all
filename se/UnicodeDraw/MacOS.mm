#include <CtrlCore/CocoMM.h>

#ifdef PLATFORM_COCOA

#define LLOG(x)
#define LTIMING(x)

namespace Upp {
CTFontRef CT_Font(Font fnt, bool& synth);
};

using namespace Upp;

int GlyphIndex(Font fnt, int ch)
{
	bool synth;
	CTFontRef ctfont = CT_Font(fnt, synth);
	if(ctfont) {
	    CGGlyph glyph_index[2];
		WString h = ToUtf16(ch);
	    UniChar uh[2];
	    uh[0] = h[0];
	    if(h.GetCount() > 1)
		    uh[1] = h[1];
		CTFontGetGlyphsForCharacters(ctfont, uh, glyph_index, h.GetCount());
		return glyph_index[0];
	}
	return -1; // perhaps 0
}

bool HasCodepoint(Font fnt, int ch)
{
	static Vector<int> tofu;
	int& q = tofu.At(fnt.GetFace(), Null);
	if(IsNull(q))
		q = GlyphIndex(fnt, 1); // this is 99.99% to produce tofu
	return ch == ' ' || GlyphIndex(fnt, ch) != q;
}

int GetAdvanceWidth(Font fnt, int ch)
{
	bool bold_synth;
	CTFontRef ctfont = CT_Font(fnt, bold_synth);
	int width = -1; // rather tofu width?-
	if(ctfont) {
		LTIMING("GetGlyphInfoSys 2");
	    CGGlyph glyph_index = GlyphIndex(fnt, ch);
		if(glyph_index) {
		    CGSize advance;
			CTFontGetAdvancesForGlyphs(ctfont, kCTFontOrientationHorizontal, &glyph_index, &advance, 1);
			width = ceil(advance.width);
			if(bold_synth)
				width++;
//				CTFontGetBoundingRectsForGlyphs(ctfont, kCTFontOrientationHorizontal,
//				                                &glyph_index, bounds, 1);
		}
	}
	return width;
}

struct sCGPathTarget {
	double x, y;
	FontGlyphConsumer *sw;
};

static void convertCGPathToQPainterPath(void *info, const CGPathElement *e)
{
	auto t = (sCGPathTarget *)info;
	switch(e->type) {
	case kCGPathElementMoveToPoint:
		t->sw->Move(Pointf(e->points[0].x + t->x, e->points[0].y + t->y));
		break;
	case kCGPathElementAddLineToPoint:
		t->sw->Line(Pointf(e->points[0].x + t->x, e->points[0].y + t->y));
		break;
	case kCGPathElementAddQuadCurveToPoint:
		t->sw->Quadratic(Pointf(e->points[0].x + t->x, e->points[0].y + t->y),
	                     Pointf(e->points[1].x + t->x, e->points[1].y + t->y));
		break;
	case kCGPathElementAddCurveToPoint:
		t->sw->Cubic(Pointf(e->points[0].x + t->x, e->points[0].y + t->y),
	                 Pointf(e->points[1].x + t->x, e->points[1].y + t->y),
	                 Pointf(e->points[2].x + t->x, e->points[2].y + t->y));
		break;
	case kCGPathElementCloseSubpath:
		t->sw->Close();
		break;
	}
}

void RenderCodepoint(FontGlyphConsumer& sw, double x, double y, int chr, Font font)
{
	CGAffineTransform cgMatrix = CGAffineTransformIdentity;
	cgMatrix = CGAffineTransformScale(cgMatrix, 1, -1);
	bool synth;
	CTFontRef ctfont = CT_Font(font, synth);
    CGGlyph glyph_index = GlyphIndex(font, chr);
    CFRef<CGPathRef> cgpath = CTFontCreatePathForGlyph(ctfont, glyph_index, &cgMatrix);
    sCGPathTarget t;
    t.x = x;
    t.y = y + font.GetAscent();
    t.sw = &sw;
    CGPathApply(cgpath, &t, convertCGPathToQPainterPath);
}

void DrawCodepoint(Draw& w, int x, int y, int ch, Font font)
{
	SystemDraw *sw = dynamic_cast<SystemDraw *>(&w);
	if(!sw) return;
	
	void *handle = sw->GetCGHandle();

	bool synth;
	CFRef<CGFontRef> cgFont = CTFontCopyGraphicsFont(CT_Font(font, synth), NULL);
	
	CGContextSetFont(cgHandle, cgFont);

	Point off = sw->GetOffset();
	CGAffineTransform tm = CGAffineTransformMakeTranslation(x + off.x, y + off.y);
	tm = CGAffineTransformScale(tm, 1, -1);
	double angle = 0;
	tm = CGAffineTransformRotate(tm, M_2PI * angle / 3600);
	x = 0;
	y = -font.GetAscent();
	if(font.IsItalic() && synth) {
		x += font.GetDescent();
		tm = CGAffineTransformConcat(CGAffineTransformMake(1, 0, 0.2, 1, 0, 0), tm);
	}
	CGContextSetTextMatrix(cgHandle, tm);

	CGGlyph g[1];
	CGPoint p[1];

	p[0].y = y;
	p[0].x = x;
	g[0] = GlyphIndex(font, ch);
	
	DDUMP(g[0]);

	Color c = Black();
    CGContextSetRGBFillColor(cgHandle, c.GetR() / 255.0, c.GetG() / 255.0, c.GetB() / 255.0, 1.0);

	CGContextSetFontSize(cgHandle, font.GetHeight());
    CGContextShowGlyphsAtPositions(cgHandle, g, p, 1);
}

#endif