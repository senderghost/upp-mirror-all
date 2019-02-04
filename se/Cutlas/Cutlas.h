#ifndef _Cutlas_Cutlas_h_
#define _Cutlas_Cutlas_h_



namespace Upp {

struct Cutlas {
	struct Ln {
		double x1, x2;
		double dir;
		int    winding;
	};
	SortedVectorMap<double, Vector<Ln> > band;
	
	void Line(Pointf p1, Pointf p2);
};

void Cutlas::Line(Pointf p1, Pointf p2)
{
	if(p1.y == p2.y)
		return;

	int dir = 1;
	if(p1.y > p2.y) {
		dir = -1;
		Swap(p1, p2);
	}
	
	Pointf h = p2 - p1;
	double ratio = h.x / h.y;

	int  = band.FindLowerBound(p1.y);
	int y = band.GetKey(ii);

	if(p1.y > y || p2.y < y) {
		Ln& l = band.Add(p1.y);
		l.x1 = p1.x;
		l.x2 = p2.x;
		l.ratio = ratio;
		l.winding = winding;
		return;
	}

	
	
}

};

#endif
