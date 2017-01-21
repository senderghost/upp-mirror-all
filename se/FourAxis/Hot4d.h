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

struct Pt : Moveable<Pt, Pointf> {
	int    kerf = 0;
	int    segment = 0;
	
	Pt Attr(const Pt& b)     { Pt p = *this; p.kerf = b.kerf; p.segment = b.segment; return p; }
	
	Pt(double x_, double y_) { x = x_, y = y_; }
	Pt(const Pointf& a)      { x = a.x; y = a.y; }
	Pt(const Point& a)       { x = a.x; y = a.y; }
	Pt(Sizef& a)             { x = a.cx; y = a.cy; }
	Pt(const Nuller& n)      { x = y = Null; }
	Pt() {}
};

VectorMap<String, Ctrl *> GetCtrlMap(Ctrl& parent);
void SetValues(Ctrl& parent, const ValueMap& json);
ValueMap GetValues(Ctrl& parent);

Pt MakePoint(Ctrl& a, Ctrl& b);

double LineIntersectionT(Pt a1, Pt a2, Pt b1, Pt b2);
Pt LineIntersection(Pt a1, Pt a2, Pt b1, Pt b2);
int    LineCircleIntersections(Pt c, double radius, Pt p1, Pt p2, double& t1, double& t2, double def = Null);
double PathLength(const Vector<Pt>& path, int from, int count);
double PathLength(const Vector<Pt>& path);
Pt AtPath(const Vector<Pt>& path, double at, Pt *dir1 = 0, int from = 0);

void Mix(const Vector<Pt>& left, int li, int lcount,
         const Vector<Pt>& right, int ri, int rcount,
         Vector<Pt>& left_out, Vector<Pt>& right_out);

void MixAll(const Vector<Pt>& left, const Vector<Pt>& right,
            Vector<Pt>& left_out, Vector<Pt>& right_out);

void CncPath(Vector<Pt>& left, Vector<Pt>& right, double width, double tower_distance, double left_distance);

Vector<Pt> KerfCompensation(const Vector<Pt>& in0, double kerf);

struct Path : Vector<Pt> {
	Xform2D     transform;
	int         segment = 0; // used to split path for tapering
	
	void To(Pt p, bool kerf = false);
	void To(double x, double y, bool kerf = false)   { To(Pt(x, y), kerf); }
	void Kerf(Pt p)                                  { To(p, true); }
	void Kerf(double x, double y)                    { To(x, y, true); }
	void NewSegment()                                { segment++; }
	
	void Rotate(double x, double y, double angle);
	void Offset(double x, double y);
	void Identity()                                  { transform = Xform2D::Identity(); }
};

enum {
	TAPERED = 1
};

struct Shape : ParentCtrl {
	virtual Path     Get() = 0;
	virtual void     Load(const ValueMap& json);
	virtual ValueMap Save();
	virtual String   GetId() const = 0;
	virtual String   GetName() const = 0;
	virtual void     AddPoint(Pt& p) {}
	virtual dword    GetInfo() const { return 0; }
	virtual bool     IsTapered() const { return GetInfo() & TAPERED; }
	
	void SyncView();
};

struct Rod : WithRodLayout<Shape> {
	virtual Path     Get();
	virtual String   GetId() const   { return "rod"; }
	virtual String   GetName() const { return "Rod"; }
	virtual dword    GetInfo() const { return TAPERED; }

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
	
	void Render(Path& path, double width, Pt p0, double te, bool smooth);
	
	Vector<Pt> Get();
	
	AirfoilCtrl();
};

struct Wing : WithWingLayout<Shape> {
	typedef Wing CLASSNAME;
	
	AirfoilCtrl airfoil;

	virtual Path    Get();
	virtual String  GetId() const   { return "wing"; }
	virtual String  GetName() const { return "Wing panel"; }
	virtual dword   GetInfo() const { return TAPERED; }

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
	virtual void    AddPoint(Pt& p);

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
	
	Rod      rod[2];
	Text     text[1];
	Angle    angle[1];
	Wing     wing[2];
	Motor    motor[1];
	TextPath textpath[1];
	
	View     view;
	Button   home;
	Point    org = Point(0, 0);
	bool     drag = false;
	Point    click;
	Point    click_org;
	
	LRUList lrufile;

	VectorMap<String, Tuple<Shape *, Shape *>> shape;

	Shape& CurrentShape(bool right = false);
	
	virtual void Layout();
	virtual bool Key(dword key, int count);

	void ViewDown(Point p);
	void ViewUp(Point p);
	void ViewMove(Point p);
	void ViewWheel(Point p, int zdelta);
	void ViewDrag(Point p);
	
	void   Zoom(int dir, Point p);
	void   Home()                       { org = Pt(0, 0); Sync(); }
	void   Type();
	void   Sync();
	void   PaintArrows(Painter& p, const Vector<Pt>& path, double scale);
	void   ViewPars(Font& fnt, int& w, Point& origin) const;
	Point  ViewOrigin() const;
	Pt GetViewPos(Point p);
	
	bool   IsTapered()                  { return CurrentShape().IsTapered() && tapered; }
	
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
	
	Vector<Pt> GetPath(double k, bool right);
	void       MakePaths(Vector<Pt> *path, Vector<Pt> *cnc);
	
	String MakeSave();

	void   AddShape(Shape *l, Shape *r = NULL);
	
	void   Serialize(Stream& s);

	FourAxisDlg();
};

#endif
