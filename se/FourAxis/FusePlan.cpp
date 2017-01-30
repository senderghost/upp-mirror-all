#include "Hot4d.h"

Path FusePlan::Get()
{
	Path r;
	
	Pt start = MakePoint(x, y);
	
	Sizef dim = MakePoint(cx, cy);
	
	Vector<Pt> foil = airfoil.Get();
	double ay = 0;
	double x = DBL_MAX;
	for(int i = 0; i < foil.GetCount(); i++) {
		if(foil[i].x > x) { // Get the top half of airfoil only
			foil.Trim(i);
			break;
		}
		ay = max(ay, foil[i].y);
		x = foil[i].x;
	}

	if(ay)
		ay = dim.cy / ay;
	
	double head = Nvl((double)~head_y);
	double tail = Nvl((double)~tail_y);
	
	double w = dim.cx;
	
	for(Pt& a : foil) {
		a.x = 1 - a.x;
		a.y *= ay;
	}

	if(tail > 0) {
		double tailx = 0;
		for(int i = 0; i < foil.GetCount(); i++) {
			Pt& a = foil[i];
			if(i > 0 && a.y > tail) {
				Pt& prev = foil[i - 1];
				prev = LineIntersection(prev, a, Pt(0, tail), Pt(1, tail));
				tailx = prev.x;
				foil.Remove(0, i - 1);
				break;
			}
		}
		for(Pt& a : foil)
			a.x -= tailx;
	}
	if(head > 0)
		for(int i = foil.GetCount() - 1; i > 0; i--) {
			Pt& a = foil[i];
			Pt& prev = foil[i - 1];
			if(prev.y > head) {
				a = LineIntersection(prev, a, Pt(0, head), Pt(1, head));
				foil.Trim(i + 1);
				break;
			}
		}

	
	double ax = foil.GetCount() ? dim.cx / foil.Top().x : 0;
	DDUMP(ax);

	for(Pt& a : foil) {
		a.x *= ax;
		DDUMP(a.x);
	}

	r.To(0, start.y);
	r.Kerf(start);
	r.Offset(start.x, start.y);
	bool top = true;
	for(int i = 0; i < foil.GetCount(); i++) {
		Pt p = foil[i];
		r.Kerf(p);
	}

	x = dim.cx;
	for(int i = 0; i < sector.GetCount(); i++) {
		double len = Nvl((double)~sector[i].length);
		double width = Nvl((double)~sector[i].width);
		if(len > 0) {
			r.Kerf(x, width);
			x -= len;
			r.Kerf(x, width);
		}
	}
	
	r.Kerf(x, 0);

	r.Identity();
	
	r.Kerf(0, start.y);

	return r;
}

void FusePlan::MakeSector(int ii)
{
	while(ii >= list.GetCount())
		list.Add();
	Sector& s = sector.At(ii);
	s.length ^= s.width ^= [=] { WhenAction(); };
	list.SetCtrl(ii, 0, s.length);
	list.SetCtrl(ii, 1, s.width);
}

void FusePlan::Load(const ValueMap& json)
{
	Shape::Load(json);
	sector.Clear();
	list.Clear();
	ValueArray va = json["sectors"];
	for(int i = 0; i < va.GetCount(); i++) {
		MakeSector(i);
		sector[i].length <<= va[i]["length"];
		sector[i].width <<= va[i]["width"];
	}
}

ValueMap FusePlan::Save()
{
	ValueMap m = Shape::Save();
	ValueArray va;
	for(const Sector& s : sector)
		va.Add(ValueMap()("length", ~s.length)("width", ~s.width));
	m.Add("sectors", va);
	return m;
}

FusePlan::FusePlan()
{
	CtrlLayout(*this);
	
	y <<= 5;
	x <<= 10;
	
	list.AddColumn("Length");
	list.AddColumn("Width");
	list.SetLineCy(EditDouble::GetStdHeight() + 2);
	list.EvenRowColor();
	list.Moving();
	
	add << [=] {
		int ii = list.GetCount();
		MakeSector(ii);
		WhenAction();
	};
	insert << [=] {
		int ii = list.GetCursor();
		if(ii < 0)
			return;
		list.Insert(ii);
		sector.Insert(ii);
		MakeSector(ii);
		WhenAction();
	};
	remove << [=] {
		int q = list.GetCursor();
		if(q < 0)
			return;
		list.Remove(q);
		if(q < sector.GetCount())
			sector.Remove(q);
		WhenAction();
	};
}
