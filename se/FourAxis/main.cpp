#include <CtrlLib/CtrlLib.h>
#include <Painter/Painter.h>

using namespace Upp;

#define LAYOUTFILE <FourAxis/dlg.lay>
#include <CtrlCore/lay.h>

struct Target {
	virtual void To(Pointf p) = 0;
	
	void To(double x, double y) { To(Pointf(x, y)); }
};

struct GCode : Target {
	FileOut& out;
	Pointf   pos;
	int      speed;
	
	void Put(const String& s) { out.PutLine(s); LOG(s); }
	
	void To(Pointf p);
	
	GCode(FileOut& out, int speed) : out(out), pos(0, 0), speed(speed) {};
};

String GFormat(double x)
{
#ifdef _DEBUG
	return Format("%.4f", x);
#else
	return AsString(x);
#endif
}

void GCode::To(Pointf p)
{
	Pointf d = p - pos;
	String x = GFormat(d.x);
	String y = GFormat(d.y);
	Put(String() << "G1X" << x << "Y" << y << "Z" << x << "A" << y << "F" << speed);
	pos = p;
}

struct FourAxisDlg : WithFourAxisLayout<TopWindow> {
	typedef FourAxisDlg CLASSNAME;
	
	void Circle(Target& path);

	void Sync();
	void Save();
	void Render(Target& r) { Circle(r); }

	FourAxisDlg();
};

/*
void FourAxisDlg::Circle(Target& path)
{
	Pointf start(~leadin, ~central);

	path.To(0, start.y);
	path.To(start.x, start.y);
	
	double rx = (double)~diameter_x / 2;
	double ry = (double)~diameter_y / 2;
	Pointf center = start + Sizef(rx, 0);

	int n = ~steps;
	int nn = n - int((double)~leadoutp * steps / 100);
	for(int i = 0; i <= nn; i++) {
		double angle = 2 * M_PI * i / n;
		Pointf c = Pointf(rx * -cos(angle) + center.x, ry * sin(angle) + center.y);
		path.To(c);
	}
	path.To(0, start.y);
	path.To(0, 0);
}
*/

void FourAxisDlg::Circle(Target& path)
{

	int n4 = (int)~steps / 4;

	Sizef rect(~rect_x, ~rect_y);
	Sizef left(~left_x, ~left_y);
	Sizef right(~right_x, ~right_y);

	Pointf center((double)~leadin + left.cx / 2 + rect.cx / 2, ~central);

	path.To(0, center.y);
	
	for(int i = 0; i < 4; i++) {
		int ts = findarg(i, 0, 1) >= 0 ? 1 : -1;
		int rs = findarg(i, 0, 3) >= 0 ? -1 : 1;
	
		double rx = (findarg(i, 0, 3) >= 0 ? left.cx : right.cx) / 2;
		double ry = (findarg(i, 0, 3) >= 0 ? left.cy : right.cy) / 2;

		Pointf c;
		c.x = center.x + rs * rect.cx / 2;
		c.y = center.y + ts * rect.cy / 2;
		
		for(int a = 0; a <= n4; a++) {
			double angle = M_PI * a / n4 / 2 + i * M_PI / 2;
			path.To(rx * -cos(angle) + c.x, ry * sin(angle) + c.y);
		}
	}
	path.To(center.x - left.cx / 2 - rect.cx / 2, center.y + rect.cy / 2);
	path.To(0, 0);
}

void FourAxisDlg::Save()
{
	if(!Accept())
		return;

#ifdef _DEBUG
	FileOut out("c:/xxx/circle.nc");
#else
	SelectFileOut out("*.nc");
#endif
	if(!out)
		return;
	
	GCode gcode(out, ~speed);
	gcode.Put("G21");
	gcode.Put("G17");
	gcode.Put("G91");
	Circle(gcode);
}

void FourAxisDlg::Sync()
{
	struct Extents : Target {
		Rectf r = Rect(0, 0, 0, 0);

		virtual void To(Pointf p) {
			r.Union(p);
		}
	} e;

	Render(e);
	
	Size isz = preview.GetSize();
	
	struct PaintPath : Target, ImagePainter {
		Pointf pp;

		virtual void To(Pointf p) {
			Line(p);
		}

		PaintPath(Size isz) : ImagePainter(isz) { pp = Pointf(0, 0); }
	} p(isz);
	
	int scale = ~this->scale;
	
	bool ok = true;
	for(auto q = GetFirstChild(); q; q = q->GetNext())
		if(q->GetData().IsError())
			ok = false;

	Font fnt = Arial(Zy(12));
	int  w = Zx(4);
	int b = fnt.GetLineHeight() + w;
	Point origin(b, isz.cy - b);
	
	Size psz = isz - Size(b, b);

	p.Translate(0.5, 0.5);
	p.Clear(White());
	p.Move(origin).Line(isz.cx, origin.y).Stroke(1, Gray());
	p.Move(origin).Line(origin.x, 0).Stroke(1, Gray());

	for(int i = 0; i < max(psz.cy / scale, psz.cx / scale); i += 5) {
		int si = i * scale;
		bool ten = i % 10 == 0;
		int w1 = Zx(ten ? 4 : 2);
		Color c = ten ? LtGray() : WhiteGray();
		p.Move(origin.x + si, origin.y + w1).Line(origin.x + si, 0).Stroke(1, c);
		p.Move(origin.x - w, origin.y - si).Line(isz.cx, origin.y - si).Stroke(1, c);
		if(i % 10 == 0 && (scale > 1 || i % 20 == 0)) {
			String s = AsString(i / 10);
			Size tsz = GetTextSize(s, fnt);
			p.Text(origin.x + si - tsz.cx / 2, origin.y + w, s, fnt).Fill(Gray());
			p.Text(origin.x - tsz.cx - w1 - Zx(2), origin.y - si - tsz.cy / 2, s, fnt).Fill(Gray());
		}
	}

	if(ok) {
		p.Translate(origin);
		p.Scale(scale, -scale);
		p.Move(0, 0);
		Render(p);
		p.Stroke(1.0 / scale, Red());

		int a = ~arrows;
		if(a)
			for(double i = 0; i < a; i++) {
				p.BeginOnPath(i / (a - 1));
				p.Move(0, -6.0 / scale).Line(6.0 / scale, 0).Line(0, 6.0 / scale).Close().Stroke(1.0 / scale, LtRed());
				p.End();
			}
	}

	preview.SetImage(p);
}

FourAxisDlg::FourAxisDlg()
{
	CtrlLayout(*this, "4 axis CNC G-code generator");
	
	WhenClose = [=] { Break(); };
	
	save << [=] { Save(); };
	
	central <<= 15;
	leadin <<= 10;
	leadoutp <<= 0;
	left_x <<= 30;
	left_y <<= 20;
	right_x <<= 30;
	right_y <<= 20;
	rect_x <<= 5;
	rect_y <<= 5;
	steps <<= 1000;
	speed <<= 140;
	
	for(auto i : { 1, 2, 3, 5, 10, 20, 30, 50, 100 })
		scale.Add(i, AsString(i) + " pixels / mm");
	scale <<= 5;
	scale << [=] { Sync(); };

	arrows.Add(0, "None");
	for(int i = 0; i < 100; i += 4)
		arrows.Add(i, AsString(i));
	arrows <<= 16;
	arrows << [=] { Sync(); };
	
	for(Ctrl *q = GetFirstChild(); q; q = q->GetNext())
		if(dynamic_cast<EditField *>(q))
			*q << [=] { Sync(); };
			
	preview.SetFrame(ViewFrame());
	
	Sync();
}

GUI_APP_MAIN
{
	FourAxisDlg dlg;
#ifdef _DEBUG0
	dlg.Save();
#else
	dlg.Run();
#endif
}
