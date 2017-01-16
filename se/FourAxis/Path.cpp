#include "Hot4d.h"

void Path::To(Pt p, bool kerf)
{
	auto& h = Add();
	(Pointf&)h = transform.Transform(p);
	h.kerf = kerf;
}

void Path::Rotate(double x, double y, double angle)
{
	transform = transform * Xform2D::Translation(-x, -y) * Xform2D::Rotation(angle) * Xform2D::Translation(x, y);
}

void Path::Offset(double x, double y)
{
	transform = transform * Xform2D::Translation(x, y);
}

Vector<Pt> FourAxisDlg::GetPath(double k, bool right)
{
	Path path = CurrentShape(right).Get();
/*
	int j = 0;
	for(int i = 1; i < path.pt.GetCount(); i++) {
		Pt d = path.pt[i].pt - path.pt[j].pt;
		if(abs(d.x) > 0.00001 || abs(d.y) > 0.00001)
			path.pt[++j] = path.pt[i];
	}
	path.pt.Trim(j);
*/	
	path.To(Pt(0, 0));
	
	Vector<Pt> h;
	
	int i = 0;
	Pt pt(0, 0);
	while(i < path.GetCount())
		if(k && path[i].kerf) {
			Vector<Pt> kh;
			kh.Add(pt);
			while(i < path.GetCount() && path[i].kerf)
				kh.Add(path[i++]);
			h.Append(KerfCompensation(kh, k / 2));
		}
		else {
			pt = path[i++];
			h.Add(pt);
		}

	for(const auto& p : h)
		if(IsNull(p.x) || IsNull(p.y) || IsNaN(p.x) || IsNaN(p.y)) {
			h.Clear();
			break;
		}

	return h;
}
