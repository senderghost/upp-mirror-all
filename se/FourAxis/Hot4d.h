#ifndef _FourAxis_Hot4d_h_
#define _FourAxis_Hot4d_h_

#include <CtrlLib/CtrlLib.h>
#include <Painter/Painter.h>

using namespace Upp;

#define LAYOUTFILE <FourAxis/dlg.lay>
#include <CtrlCore/lay.h>

#define IMAGECLASS HotImg
#define IMAGEFILE <FourAxis/HotImg.iml>
#include <Draw/iml_header.h>

VectorMap<String, Ctrl *> GetCtrlMap(Ctrl& parent);
void SetValues(Ctrl& parent, const ValueMap& json);
ValueMap GetValues(Ctrl& parent);

Pointf MakePoint(Ctrl& a, Ctrl& b);

double LineIntersectionT(Pointf a1, Pointf a2, Pointf b1, Pointf b2);
Pointf LineIntersection(Pointf a1, Pointf a2, Pointf b1, Pointf b2);
int    LineCircleIntersections(Pointf c, double radius, Pointf p1, Pointf p2, double& t1, double& t2, double def = Null);
double PathLength(const Vector<Pointf>& path, int from, int count);
double PathLength(const Vector<Pointf>& path);
Pointf AtPath(const Vector<Pointf>& path, double at, Pointf *dir1 = 0, int from = NULL);

Vector<Pointf> KerfCompensation(const Vector<Pointf>& in0, double kerf);

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
	void Offset(double x, double y);
	void Identity()                                  { transform = Xform2D::Identity(); }
};

struct Shape : ParentCtrl {
	virtual Path     Get() = 0;
	virtual void     Load(const ValueMap& json);
	virtual ValueMap Save();
	virtual String   GetId() const = 0;
	virtual String   GetName() const = 0;
	virtual void     AddPoint(Pointf& p) {}
	
	void SyncView();
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
	
	Vector<Pointf> Get();
	
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
	virtual void    AddPoint(Pointf& p);

	TextPath();
};

#ifdef _DEBUG
void TestKerf();
#endif

struct FourAxisDlg;

struct View : Ctrl {
	FourAxisDlg *fa = NULL;
	Image img;
	
	virtual void Paint(Draw& w);
	virtual void LeftDown(Point p, dword);
	virtual void LeftUp(Point p, dword);
	virtual void MouseMove(Point p, dword);
	virtual void MouseWheel(Point p, int zdelta, dword keyflags);
	virtual void LeftDrag(Point p, dword keyflags);
	virtual void LeftHold(Point p, dword keyflags);
	
	View();
};

struct FourAxisDlg : WithFourAxisLayout<TopWindow> {
	typedef FourAxisDlg CLASSNAME;
	
	String filepath;
	
	Rod      rod;
	Text     text;
	Angle    angle;
	Wing     wing;
	Motor    motor;
	TextPath textpath;
	
	View     view;
	Button   home;
	Point    org = Point(0, 0);
	bool     drag = false;
	Point    click;
	Point    click_org;

	
	LRUList lrufile;

	VectorMap<String, Shape *> shape;

	Shape& CurrentShape();
	
	virtual void Layout();
	virtual bool Key(dword key, int count);

	void ViewDown(Point p);
	void ViewUp(Point p);
	void ViewMove(Point p);
	void ViewWheel(Point p, int zdelta);
	void ViewDrag(Point p);
	
	void   Zoom(int dir, Point p);
	void   Home()                       { org = Pointf(0, 0); Sync(); }
	void   Type();
	void   Sync();
	void   PaintArrows(Painter& p, const Vector<Pointf>& path, double scale);
	void   ViewPars(Font& fnt, int& w, Point& origin) const;
	Point  ViewOrigin() const;
	Pointf GetViewPos(Point p);
	
	void   SetBar();
	bool   Save(const char *path);
	bool   Load(const char *path);
	bool   OpenS(const String& fp);
	void   OpenFile(const String& p);
	void   Open();
	bool   SaveAs();
	void   NewInstance(const String& path);
	bool   Save();
	void   Exit();
	
	Vector<Pointf> GetPath(double k);
	
	String MakeSave();

	void   AddShape(Shape& s);
	
	void   Serialize(Stream& s);

	FourAxisDlg();
};

#endif
