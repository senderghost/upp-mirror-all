#ifndef _FourAxis_Hot4d_h_
#define _FourAxis_Hot4d_h_

#include <CtrlLib/CtrlLib.h>
#include <Painter/Painter.h>

using namespace Upp;

#define LAYOUTFILE <FourAxis/dlg.lay>
#include <CtrlCore/lay.h>

VectorMap<String, Ctrl *> GetCtrlMap(Ctrl& parent);
void SetValues(Ctrl& parent, const ValueMap& json);
ValueMap GetValues(Ctrl& parent);

Vector<Pointf> KerfCompensation(Pointf start, const Vector<Pointf>& in, int from, int count, double kerf);

struct Line : Moveable<Line> {
	Pointf pt;
	bool   kerf = false;
};

struct Path {
	Vector<Line> pt;
	
	void To(Pointf p)             { pt.Add().pt = p; }
	void To(double x, double y)   { To(Pointf(x, y)); }
	void Kerf(Pointf p)           { auto& h = pt.Add(); h.pt = p; h.kerf = true; }
	void Kerf(double x, double y) { Kerf(Pointf(x, y)); }
};

struct Shape : ParentCtrl {
	virtual Path     Get() = 0;
	virtual void     Load(const ValueMap& json);
	virtual ValueMap Save();
	virtual String   GetId() const = 0;
	virtual String   GetName() const = 0;
};

struct Rod : WithRodLayout<Shape> {
	virtual Path     Get();
	virtual String   GetId() const   { return "rod"; }
	virtual String   GetName() const { return "Rod"; }

	typedef Rod CLASSNAME;

	Rod();
};

struct Text : WithTextLayout<Shape> {
	typedef Text CLASSNAME;

	virtual Path    Get();
	virtual String  GetId() const   { return "text"; }
	virtual String  GetName() const { return "Text"; }

	Text();
};

struct Angle : WithAngleLayout<Shape> {
	typedef Angle CLASSNAME;

	virtual Path    Get();
	virtual String  GetId() const   { return "angle"; }
	virtual String  GetName() const { return "Angle cut"; }

	Angle();
};

struct FourAxisDlg : WithFourAxisLayout<TopWindow> {
	typedef FourAxisDlg CLASSNAME;
	
	String filepath;
	
	Rod  rod;
	Text text;
	Angle angle;

	VectorMap<String, Shape *> shape;

	Shape& CurrentShape();
	
	void   Type();
	void   Sync();
	void   Save();
	void   Load(const char *path);
	void   Load();
	
	Vector<Pointf> GetPath();
	
	String MakeSave();

	void   AddShape(Shape& s);

	FourAxisDlg();
};

#endif
