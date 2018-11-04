#ifndef _Painter_LinearPath_h_
#define _Painter_LinearPath_h_

struct LinearPathConsumer {
	virtual void Move(const Pointf& p) = 0;
	virtual void Line(const Pointf& p) = 0;
	virtual void End();
};

void ApproximateQuadratic(LinearPathConsumer& t,
                          const Pointf& p1, const Pointf& p2, const Pointf& p3,
                          double tolerance);
void ApproximateCubic(LinearPathConsumer& t,
                      const Pointf& x0, const Pointf& x1, const Pointf& x2, const Pointf& x,
                      double tolerance);

struct LinearPathFilter : LinearPathConsumer {
	virtual void End();

	LinearPathConsumer *target;

	void PutMove(const Pointf& p)               { target->Move(p); }
	void PutLine(const Pointf& p)               { target->Line(p); }
	void PutEnd()                               { target->End(); }
};

class Stroker : public LinearPathFilter {
public:
	virtual void Move(const Pointf& p);
	virtual void Line(const Pointf& p);
	virtual void End();

private:
	double w2;
	double qmiter;
	double fid;
	double tw;

	Pointf p0, v0, o0, a0, b0;
	Pointf p1, v1, o1, a1, b1;
	Pointf p2;
	int    linecap;
	int    linejoin;
	Rectf  preclip;
	int    lines;
	
	void   Finish();
	void   Round(const Pointf& p, const Pointf& v1, const Pointf& v2, double r);
	void   Cap(const Pointf& p0, const Pointf& v0, const Pointf& o0,
	           const Pointf& a0, const Pointf& b0);
	bool   PreClipped(Pointf p2, Pointf p3);

public:	
	void Init(double width, double miterlimit, double tolerance, int linecap, int linejoin, const Rectf& preclip);
};

class Dasher : public LinearPathFilter {
public:
	virtual void Move(const Pointf& p);
	virtual void Line(const Pointf& p);

private:
	const Vector<double> *pattern;
	int            patterni;
	double         sum, rem;
	bool           flag;
	Pointf         p0;

	void    Put(const Pointf& p);

public:
	void Init(const Vector<double>& pattern, double distance);
};

struct Transformer : public LinearPathFilter {
public:
	virtual void Move(const Pointf& p);
	virtual void Line(const Pointf& p);

private:
	const Xform2D& xform;

public:
	Transformer(const Xform2D& xform) : xform(xform) {}
};

inline RGBA Mul8(const RGBA& s, int mul)
{
	RGBA t;
	t.r = (mul * s.r) >> 8;
	t.g = (mul * s.g) >> 8;
	t.b = (mul * s.b) >> 8;
	t.a = (mul * s.a) >> 8;
	return t;
}

inline void AlphaBlend(RGBA& t, const RGBA& c)
{
	int alpha = 256 - (c.a + (c.a >> 7));
	t.r = c.r + (alpha * t.r >> 8);
	t.g = c.g + (alpha * t.g >> 8);
	t.b = c.b + (alpha * t.b >> 8);
	t.a = c.a + ((256 - c.a) * t.a >> 8);
}

inline void AlphaBlendCover8(RGBA& t, const RGBA& c, int cover)
{
	int a = c.a * cover >> 8;
	int alpha = 256 - a - (a >> 7);
	t.r = (c.r * cover >> 8) + (alpha * t.r >> 8);
	t.g = (c.g * cover >> 8) + (alpha * t.g >> 8);
	t.b = (c.b * cover >> 8) + (alpha * t.b >> 8);
	t.a = a + (alpha * t.a >> 8);
}

class Rasterizer : public LinearPathConsumer {
public:
	virtual void Move(const Pointf& p);
	virtual void Line(const Pointf& p);

private:
	struct Cell : Moveable<Cell> {
		int16 x;
		int16 cover;
		int   area;

		bool operator<(const Cell& b) const { return x < b.x; }
    };
	struct CellArray {
		int  count;
		int  alloc;
	};

	Rectf                   cliprect;
	Pointf                  p0;
	Buffer<CellArray *>     cell;

	int                     min_y;
	int                     max_y;
	Size                    sz;
	int                     mx;
	double                  offsety = 0;

	static CellArray       *AllocArray(int n);

	void  Init();
	Cell *AddCells(int y, int n);
	void  RenderHLine(int ey, int x1, int y1, int x2, int y2);
	void  LineClip(double x1, double y1, double x2, double y2);
	int   CvX(double x);
	int   CvY(double y);
	void  CvLine(double x1, double y1, double x2, double y2);
	bool  BeginRender(int y, const Cell *&c, const Cell *&e);
	void  Free();

	static int Q8Y(double y) { return int(y * 256 + 0.5); }
	int Q8X(double x)        { return int(x * mx + 0.5); }

public:
	struct Filler {
		virtual void Start(int x, int len) = 0;
		virtual void Render(int val) = 0;
		virtual void Render(int val, int len) = 0;
		virtual void End();
	};

	void LineRaw(int x1, int y1, int x2, int y2);
	
//	void  SetClip(const Rectf& rect);
	Rectf GetClip() const                     { return cliprect; }

	int  MinY() const                         { return min_y; }
	int  MaxY() const                         { return max_y; }
	void Render(int y, Filler& g, bool evenodd);

	void Reset();

	void Create(int cx, int cy, bool subpixel, double offsety = 0);
	
	double GetOffsetY() const                 { return offsety; }
	
	Rasterizer(int cx, int cy, bool subpixel);
	Rasterizer() { sz = Size(0, 0); }
	~Rasterizer();
};

class LinearInterpolator {
	struct Dda2 {
		int count, lift, rem, mod, p;
		
		void  Set(int a, int b, int len);
		int   Get();
	};

	Xform2D xform;
	Dda2    ddax, dday;

	static int Q8(double x) { return int(256 * x + 0.5); }
	
public:
	void   Set(const Xform2D& m)                    { xform = m; }

	void   Begin(int x, int y, int len);
	Point  Get();
};

void ApproximateChar(LinearPathConsumer& t, Pointf at, int ch, Font fnt, double tolerance = 0.3);

#endif
