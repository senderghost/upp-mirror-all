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

Pointf MakePoint(Ctrl& a, Ctrl& b);
Pointf LineIntersection(Pointf a1, Pointf a2, Pointf b1, Pointf b2);

struct Line : Moveable<Line> {
	Pointf pt;
	bool   kerf = false;
};

struct Path {
	Xform2D      transform;
	Vector<Line> pt;
	
	void To(Pointf p, bool kerf = false);
	void To(double x, double y, bool kerf = false)   { To(Pointf(x, y), kerf); }
	void Kerf(Pointf p)                              { To(p, true); }
	void Kerf(double x, double y)                    { To(x, y, true); }
	
	void Rotate(double x, double y, double angle);
	void Identity()                                  { transform = Xform2D::Identity(); }
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

struct AirfoilCtrl : public DataPusher {
	virtual void DoAction();
	
	void Render(Path& path, double width, Pointf p0, double te, bool smooth);
	
	AirfoilCtrl();
};

struct Wing : WithWingLayout<Shape> {
	typedef Wing CLASSNAME;
	
	AirfoilCtrl airfoil;

	virtual Path    Get();
	virtual String  GetId() const   { return "wing"; }
	virtual String  GetName() const { return "Wing panel"; }

	Wing();
};

struct Motor : WithMotorLayout<Shape> {
	typedef Motor CLASSNAME;

	virtual Path    Get();
	virtual String  GetId() const   { return "motor_mount"; }
	virtual String  GetName() const { return "Motor mount"; }

	Motor();
};

struct TextPath : WithTextPath<Shape> {
	typedef TextPath CLASSNAME;

	virtual Path    Get();
	virtual String  GetId() const   { return "free_text"; }
	virtual String  GetName() const { return "Free text path"; }

	TextPath();
};

#ifdef _DEBUG
void TestKerf();
#endif

struct FourAxisDlg : WithFourAxisLayout<TopWindow> {
	typedef FourAxisDlg CLASSNAME;
	
	String filepath;
	
	Rod      rod;
	Text     text;
	Angle    angle;
	Wing     wing;
	Motor    motor;
	TextPath textpath;
	
	LRUList lrufile;

	VectorMap<String, Shape *> shape;

	Shape& CurrentShape();
	
	virtual void Layout();
	
	void   Type();
	void   Sync();
	void   PaintArrows(Painter& p, double scale);
	void   SetBar();
	
	void   Save(const char *path);
	bool   Load(const char *path);
	bool   OpenS(const String& fp);
	void   OpenFile(const String& p);
	void   Open();
	void   SaveAs();
	void   Save();
	void   Exit();
	
	Vector<Pointf> GetPath(double k);
	
	String MakeSave();

	void   AddShape(Shape& s);
	
	void   Serialize(Stream& s);

	FourAxisDlg();
};

#endif
