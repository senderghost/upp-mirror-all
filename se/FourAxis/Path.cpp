#include "Hot4d.h"

void Path::To(Pointf p, bool kerf)
{
	auto& h = pt.Add();
	h.pt = transform.Transform(p);
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

Vector<Pointf> FourAxisDlg::GetPath(double k)
{
	Path path = CurrentShape().Get();
/*
	int j = 0;
	for(int i = 1; i < path.pt.GetCount(); i++) {
		Pointf d = path.pt[i].pt - path.pt[j].pt;
		if(abs(d.x) > 0.00001 || abs(d.y) > 0.00001)
			path.pt[++j] = path.pt[i];
	}
	path.pt.Trim(j);
*/	
	path.To(Pointf(0, 0));
	
	Vector<Pointf> h;
	
	int i = 0;
	Pointf pt(0, 0);
	while(i < path.pt.GetCount())
		if(k && path.pt[i].kerf) {
			Vector<Pointf> kh;
			kh.Add(pt);
			while(i < path.pt.GetCount() && path.pt[i].kerf)
				kh.Add(path.pt[i++].pt);
			h.Append(KerfCompensation(kh, k / 2));
		}
		else {
			pt = path.pt[i++].pt;
			h.Add(pt);
		}

	for(const auto& p : h)
		if(IsNull(p.x) || IsNull(p.y) || IsNaN(p.x) || IsNaN(p.y)) {
			h.Clear();
			break;
		}

	return h;
}
