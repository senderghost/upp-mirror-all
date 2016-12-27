#include "Hot4d.h"

struct HGlyphPainter : NilPainter, LinearPathConsumer {
	Vector<float>       glyph;
	double              tolerance;
	Pointf              pos, move;
	
	virtual void LineOp(const Pointf& p, bool);
	virtual void MoveOp(const Pointf& p, bool);
	virtual void QuadraticOp(const Pointf& p1, const Pointf& p, bool);
	virtual void CubicOp(const Pointf& p1, const Pointf& p2, const Pointf& p, bool);
	virtual void CloseOp();

	virtual void Line(const Pointf& p);
	virtual void Move(const Pointf& p);
};

void HGlyphPainter::Move(const Pointf& p)
{
	glyph.Add((float)1e31);
	Line(p);
	move = pos;
}

void HGlyphPainter::Line(const Pointf& p)
{
	glyph.Add((float)p.x);
	glyph.Add((float)p.y);
	pos = p;
}

void HGlyphPainter::MoveOp(const Pointf& p, bool)
{
	Move(p);
}

void HGlyphPainter::LineOp(const Pointf& p, bool)
{
	Line(p);
}

void HGlyphPainter::QuadraticOp(const Pointf& p1, const Pointf& p, bool)
{
	ApproximateQuadratic(*this, pos, p1, p, tolerance);
	pos = p;
}

void HGlyphPainter::CubicOp(const Pointf& p1, const Pointf& p2, const Pointf& p, bool)
{
	ApproximateCubic(*this, pos, p1, p2, p, tolerance);
	pos = p;
}

void HGlyphPainter::CloseOp()
{
	if(move != pos && !IsNull(move))
		Line(move);
}

struct GlyphKey {
	Font   fnt;
	int    chr;
	double tolerance;
	
	bool operator==(const GlyphKey& b) const {
		return fnt == b.fnt && chr == b.chr && tolerance == b.tolerance;
	}
	unsigned GetHashValue() const {
		return CombineHash(fnt, chr, tolerance);
	}
};

struct sHMakeGlyph : LRUCache<Value, GlyphKey>::Maker {
	GlyphKey gk;

	GlyphKey Key() const     { return gk; }
	int      Make(Value& v) const {
		HGlyphPainter gp;
		gp.move = gp.pos = Null;
		gp.tolerance = gk.tolerance;
		PaintCharacter(gp, Pointf(0, 0), gk.chr, gk.fnt);
		int sz = gp.glyph.GetCount() * 4;
		v = RawPickToValue(pick(gp.glyph));
		return sz;
	}
};

void DoApproximateChar(Vector<Pointf>& path, Pointf pos, int ch, Font fnt, double tolerance)
{
	PAINTER_TIMING("ApproximateChar");
	Value v;
	INTERLOCKED {
		PAINTER_TIMING("ApproximateChar::Fetch");
		static LRUCache<Value, GlyphKey> cache;
		cache.Shrink(500000);
		sHMakeGlyph h;
		h.gk.fnt = fnt.Height(100 * fnt.GetHeight());
		h.gk.chr = ch;
		h.gk.tolerance = tolerance;
		v = cache.Get(h);
	}
	const Vector<float>& g = ValueTo< Vector<float> >(v);
	int i = 0;
	while(i < g.GetCount()) {
		Pointf p;
		p.x = g[i++];
		if(p.x > 1e30) {
			p.x = g[i++];
			p.y = -g[i++];
			path.Add(p / 100.0 + pos);
		}
		else {
			PAINTER_TIMING("ApproximateChar::Line");
			p.y = -g[i++];
			path.Add(p / 100.0 + pos);
		}
	}
}

Vector<Pointf> Text::Get()
{
	Vector<Pointf> r;
	Font fnt = Font(~font, (int)~height).Bold(~bold).Italic(~italic);
	String h = ~text;
	Pointf pos = Pointf(~leadin, ~line);
	r.Add(Pointf(0, pos.y));
	r.Add(Pointf(pos.x, pos.y));
	for(int i = 0; i < h.GetCount(); i++) {
		Vector<Pointf> ch;
		Pointf npos = pos;
		npos.x += fnt[h[i]] + (int)~spacing;
		r.Add(npos);
		DoApproximateChar(ch, pos, h[i], fnt, 0.05);
		if(ch.GetCount() > 2) {
			int ei = FindBest(ch, [=](Pointf p1, Pointf p2) { return SquaredDistance(p1, pos) < SquaredDistance(p2, pos); });
			r.AppendRange(SubRange(ch, ei, ch.GetCount() - ei));
			r.AppendRange(SubRange(ch, 0, ei + 1));
		}
		pos = npos;
	}
	r.Add(pos);
	r.Add(Pointf(0, pos.y));
	r.Add(Pointf(0, 0));
	return r;
}

void Text::Load(const ValueMap& json)
{
	SetValues(*this, json);
}

ValueMap Text::Save()
{
	return GetValues(*this);
}

Text::Text()
{
	CtrlLayout(*this);
	font.Add(Font::SANSSERIF, "SansSerif");
	font.Add(Font::SERIF, "Serif");
	font.Add(Font::MONOSPACE, "Monospace");
	
	font <<= Font::SERIF;
	height <<= 20;
	line <<= 8;
	leadin <<= 10;
	spacing <<= 0;
}
