#include "Hot4d.h"

Path FusePlan::Get()
{
	Path r;
	
	Pt start = MakePoint(x, y);
	
	Sizef dim = MakePoint(cx, cy);
	
	Vector<Pt> foil = GetHalfFoil(airfoil.Get());
	
	double ay = GetMaxY(foil);

	if(ay)
		ay = dim.cy / ay;
	
	Mul(foil, 1, ay);

	CutHalfFoil(foil, Nvl((double)~head_y), Nvl((double)~tail_y));
	
	Mul(foil, foil.GetCount() ? dim.cx / foil.Top().x : 0, 1);

	r.To(0, start.y);
	r.Kerf(start);
	r.Offset(start.x, start.y);

	for(int i = 0; i < foil.GetCount(); i++)
		r.Kerf(foil[i]);

	double x = dim.cx;
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
