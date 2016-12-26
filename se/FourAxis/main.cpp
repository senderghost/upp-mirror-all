#include "Hot4d.h"

struct GCode {
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
	
	for(auto p :  CurrentShape().Get())
		gcode.To(p);
	
	gcode.To(Pointf(0, 0));
}

void FourAxisDlg::Sync()
{
	auto path = CurrentShape().Get();
	Rectf r = Rect(0, 0, 0, 0);
	for(auto p : path)
		r.Union(p);
	
	Size isz = preview.GetSize();
	
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
	
	ImagePainter p(isz);

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
		
		for(auto pt : path)
			p.Line(pt);

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
	
	DUMP(AsJSON(CurrentShape().Get()));
}

Shape& FourAxisDlg::CurrentShape()
{
	if(~type == 1)
		return text;
	return rod;
}

void FourAxisDlg::Type()
{
	rod.Show(~type == 0);
	text.Show(~type == 1);
	Sync();
}

FourAxisDlg::FourAxisDlg()
{
	CtrlLayout(*this, "4 axis CNC G-code generator");
	
	WhenClose = [=] { Break(); };
	
	save_as << [=] { Save(); };
	
	speed <<= 140;
	
	for(auto i : { 1, 2, 3, 5, 10, 20, 30, 50, 100 })
		scale.Add(i, AsString(i) + " pixels / mm");
	scale <<= 5;
	scale << [=] { Sync(); };
	
	shape.Add(rod.SizePos());
	shape.Add(text.SizePos());
	
	type.Add(0, "Rod");
	type.Add(1, "Text");
	type << [=] { Type(); };
	type <<= 0;

	arrows.Add(0, "None");
	for(int i = 0; i < 100; i += 4)
		arrows.Add(i, AsString(i));
	arrows <<= 16;
	arrows << [=] { Sync(); };

	for(int i = 0; i < 3; i++)
		for(Ctrl *q = decode(i, 0, (TopWindow *)&rod, 1, (TopWindow *)&text, (TopWindow *)this)->GetFirstChild(); q; q = q->GetNext())
			*q << [=] { Sync(); };
			
	preview.SetFrame(ViewFrame());
	
	Type();
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
