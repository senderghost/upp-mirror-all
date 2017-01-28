#include "Hot4d.h"

void Path::To(Pt p, bool kerf)
{
	auto& h = Add();
	(Pointf&)h = transform.Transform(p);
	h.kerf = kerf;
	h.segment = segment;
	DLOG(p << ", segment " << segment << ", kerf " << kerf);
}

void Path::Rotate(double x, double y, double angle)
{
	transform = transform * Xform2D::Translation(-x, -y) * Xform2D::Rotation(angle) * Xform2D::Translation(x, y);
}

void Path::Offset(double x, double y)
{
	transform = transform * Xform2D::Translation(x, y);
}

Vector<Pt> FourAxisDlg::GetShapePath(bool right, double inverted)
{
	Path path = CurrentShape(right).Get(inverted);
	double cut = Nvl((double)~cut_foam);
	if(cut)
		path.To(Pt(0, cut));
	path.To(Pt(0, 0));
	return pick(path);
}

double FourAxisDlg::GetKerf(bool right)
{
	return Nvl(double(right ? ~right_kerf : ~kerf), Nvl((double)~kerf));
}

Vector<Pt> GetKerfPath(const Vector<Pt>& path, double k)
{
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

	if(!IsOk(h))
		h.Clear();

	return h;
}

void FourAxisDlg::MakePaths(Vector<Pt> *shape, Vector<Pt> *path, Vector<Pt> *cnc, double inverted)
{
	for(int r = 0; r < 1 + IsTapered(); r++) {
		shape[r] = GetShapePath(r, inverted);
		if(!IsOk(shape[r]))
			shape[r].Clear();
		path[r] = GetKerfPath(shape[r], GetKerf(r));
	}

	if(IsTapered()) {
		cnc[0].Add(Pointf(0, 0));
		cnc[1].Add(Pointf(0, 0));
		MixAll(path[0], path[1], cnc[0], cnc[1]);
		if(cnc[0].GetCount() == cnc[1].GetCount()) {
			CncPath(cnc[0], cnc[1], Nvl((double)~panel_width),
			        Nvl((double)~tower_distance), Nvl((double)~left_gap));
			if(!IsOk(cnc[0]))
				cnc[0].Clear();
			if(!IsOk(cnc[1]))
				cnc[1].Clear();
		}
		else {
			cnc[0].Clear();
			cnc[1].Clear();
		}
	}
	else {
		cnc[0] = clone(path[0]);
		cnc[1] = clone(path[0]);
	}
}
