#include "Hot4d.h"

void AirfoilCtrl::DoAction()
{
	SelectFileIn in("*.dat");
	if(!in)
		return;
	
	String name = TrimBoth(in.GetLine());
	
	ValueArray va;
	
	while(!in.IsEof()) {
		String ln = in.GetLine();
		CParser p(ln);
		Pointf pt = Null;
		try {
			pt.x = p.ReadDouble();
			pt.y = p.ReadDouble();
		}
		catch(CParser::Error) {
			pt = Null;
		}
		if(!IsNull(pt)) {
			Value h;
			h("x") = pt.x;
			h("y") = pt.y;
			va.Add(h);
		}
	}
	
	Value h;
	h("name") = name;
	h("data") = va;
	SetData(h);
	
	Action();
}

struct CvAirfoil : Convert {
	virtual Value Format(const Value& v) const;
};

Value CvAirfoil::Format(const Value& v) const
{
	return v["name"];
}

AirfoilCtrl::AirfoilCtrl()
{
	SetConvert(Single<CvAirfoil>());
}

Vector<Pointf> SmoothAirfoil(const Vector<Pointf>& foil)
{
	DDUMPC(foil);
	if(foil.GetCount() < 4)
		return clone(foil);

	struct Cons : LinearPathConsumer {
		Vector<Pointf> r;
		
		virtual void Line(const Pointf& p) { r.Add(p); }
		virtual void Move(const Pointf& p) {}
		virtual void End() {}
	} r;

	r.r.Add(foil[0]);
	r.r.Add(foil[1]);
	int i;
	for(i = 1; i < foil.GetCount() - 2; i++) {
		Pointf p2 = LineIntersection(foil[i - 1], foil[i], foil[i + 1], foil[i + 2]);
		if(!IsNull(p2)) {
		#if 1
			r.r.Add(p2);
			r.r.Add(foil[i + 1]);
		#else
			ApproximateQuadratic(r, foil[i], Mid(Mid(foil[i], foil[i + 1]), p2), foil[i + 1], 0.0001);
		#endif
		}
		else
			r.r.Add(foil[i + 1]);
	}
	r.r.Add(foil[i++]);
	r.r.Add(foil[i++]);
	DDUMPC(r.r);
	return pick(r.r);
}

void AirfoilCtrl::Render(Path& path, double width, Pointf p0, double te, bool smooth)
{
	Value p = GetData()["data"];

	Vector<Pointf> foil;

	try {
		for(int i = 0; i < p.GetCount(); i++)
			foil.Add(Pointf(p[i]["x"], p[i]["y"]));
		
		if(smooth)
			foil = SmoothAirfoil(foil);
	}
	catch(ValueTypeError) {
		return;
	}

	for(int i = 0; i < foil.GetCount(); i++) {
		Pointf pt = foil[i];
		pt.x = 1 - pt.x;
		Pointf a = width * pt;
		if(te && a.x < width / 4 && i < p.GetCount() / 2) // adjust te thickness in entry phase
			a.y = max(a.y, te);
		path.Kerf(a + p0);
	}
}
