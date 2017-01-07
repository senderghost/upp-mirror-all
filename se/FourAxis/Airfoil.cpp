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

void AirfoilCtrl::Render(Path& path, double width, Pointf p0)
{
	Value p = GetData()["data"];
	DUMP(p);
	try {
		for(int i = 0; i < p.GetCount(); i++) {
			Pointf pt(p[i]["x"], p[i]["y"]);
			pt.x = 1 - pt.x;
			path.Kerf(width * pt + p0);
		}
	}
	catch(ValueTypeError) {}
}
