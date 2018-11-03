#ifndef _Painter_PainterPath_h_
#define _Painter_PainterPath_h_

class PainterFrontend : public Painter {
public:
	virtual void   MoveOp(const Pointf& p, bool rel);
	virtual void   LineOp(const Pointf& p, bool rel);
	virtual void   QuadraticOp(const Pointf& p1, const Pointf& p, bool rel);
	virtual void   QuadraticOp(const Pointf& p, bool rel);
	virtual void   CubicOp(const Pointf& p1, const Pointf& p2, const Pointf& p, bool rel);
	virtual void   CubicOp(const Pointf& p2, const Pointf& p, bool rel);
	virtual void   ArcOp(const Pointf& c, const Pointf& r, double angle, double sweep, bool rel);
	virtual void   SvgArcOp(const Pointf& r, double xangle, bool large, bool sweep,
	                        const Pointf& p, bool rel);
	virtual void   CloseOp();
	virtual void   DivOp();

	virtual void   CharacterOp(const Pointf& p, int ch, Font fnt);

	virtual void   ColorStopOp(double pos, const RGBA& color);
	virtual void   ClearStopsOp();
	
	virtual void   OpacityOp(double o);
	virtual void   LineCapOp(int linecap);
	virtual void   LineJoinOp(int linejoin);
	virtual void   MiterLimitOp(double l);
	virtual void   EvenOddOp(bool evenodd);
	virtual void   DashOp(const Vector<double>& dash, double start);
	virtual void   InvertOp(bool invert);

	virtual void   TransformOp(const Xform2D& m);

	virtual void   BeginOp();
	virtual void   EndOp();

protected:
	enum {
		MOVE, LINE, QUADRATIC, CUBIC, CHAR, DIV
	};
	struct PathElement {
		int    type;
	};
	struct LinearData : PathElement {
		Pointf p;
	};
	struct QuadraticData : LinearData {
		Pointf p1;
	};
	struct CubicData : QuadraticData {
		Pointf p2;
	};
	struct CharData : LinearData {
		int  ch;
		int  _filler;
		Font fnt;
	};
	struct PathLine : Moveable<PathLine> {
		Pointf p;
		double len;
	};
	struct Attr : Moveable<Attr> {
		Xform2D                         mtx;
		bool                            evenodd;
		byte                            join;
		byte                            cap;
		double                          miter_limit;
		WithDeepCopy< Vector<double> >  dash;
		WithDeepCopy< Vector<double> >  stop;
		WithDeepCopy< Vector<RGBA> >    stop_color;
		double                          dash_start;
		double                          opacity;
		bool                            invert;

//		int                             cliplevel;
		bool                            hasclip;
		bool                            mask;
		bool                            onpath;
	};
	
	Attr             attr;
	Array<Attr>      attrstack;
	StringBuffer     path;
	Pointf           path_min, path_max;
	bool             ischar;
	Attr             pathattr;

	Pointf           current, ccontrol, qcontrol, move;
	bool             dopreclip;

	PathElement&           PathAddRaw(int type, int size); // TODO: -> inline
	template <class T> int ElementSize()                   { union Aligner { double a; T b; }; return sizeof(Aligner); }
	template <class T> T&  PathAdd(int type)               { return (T&)PathAddRaw(type, ElementSize<T>()); }
	template <class T> T&  ReadElement(const char *& data) { auto h = (T *)data; data += ElementSize<T>(); return *h; }

	Pointf           PathPoint(const Pointf& p, bool rel);
	Pointf           EndPoint(const Pointf& p, bool rel);
	void             DoMove0();
	void             ClearPath();
	void             ColorStop0(Attr& a, double pos, const RGBA& color);

public:
	PainterFrontend();
};

#endif
