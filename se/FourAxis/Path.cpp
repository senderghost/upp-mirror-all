#include "Hot4d.h"

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
			while(i < path.pt.GetCount() && path.pt[i].kerf)
				kh.Add(path.pt[i++].pt);
			if(kh.GetCount() > 2)
				h.Append(KerfCompensation(pt, kh, 0, kh.GetCount(), k / 2));
			else
				h.Append(kh);
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
