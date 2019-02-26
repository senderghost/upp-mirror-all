#ifndef _Cutlas_Cutlas_h_
#define _Cutlas_Cutlas_h_

namespace Upp {

struct Cutlass {
	struct Line : Moveable<Line> {
		Pointf p1, p2;
		int    dir;
	};
	struct BandLine {
		double x1, double x2;
		int    dir;
	};
	struct Band {
		double y;
		Vector<BandLine> line;
	};
	
	Vector<Line>   line;
	Vector<Band>   band;
	
	void AddLine(Pointf p1, Pointf p2);
	void Do();
};

void Cutlass::AddLine(Pointf p1, Pointf p2)
{
	if(p1.y == p2.y)
		return;

	Line& ln = line.Add();
	if(p1.y < p2.y) {
		ln.p1 = p1;
		ln.p2 = p2;
		ln.dir = 1;
	}
	else {
		ln.p1 = p2;
		ln.p2 = p1;
		ln.dir = -1;
	}
}

void Cutlass::Do()
{
	Sort(line, [](const Line& a, const Line& b) { return a.p1.y < b.p1.y; });
	
	Vector<double> y;
	for(const auto& ln : line) // first add sorted ones to speedup sorting
		y.Add(a.p1.y);
	for(const auto& ln : line)
		y.Add(a.p2.y);
	
	Sort(y);
	
	band.Reserve(y.GetCount());
	for(int i = 0; i < y.GetCount(); y++)
		if(i == 0 || y[i] != y[i - 1]) // create bands, but unique y only
			band.Add().y = y[i];
	
	int ii = 0; // progress so far
	for(const auto& ln : line) {
		while(ln.p1.y > band[ii].y) // find a band at p1.y, start of current line
			ii++;

		Pointf h = ln.p2 - ln.p1;
		double d = h.x / h.y;

		double x1 = p1.x;
		for(int i = ii; i + 1 < band.GetCount(); i++) { // cut the line, add to appropriate bands
			BandLine& bl = band[ii].line.Add(); // we need to add line segment to this band
			bl.dir = ln.dir;

			double y2 = band[i + 1].y; // start of next band is end of current
			if(y2 <= p2.y) { // this is the last band for ln
				bl.x1 = x1;
				bl.x2 = ln.p2.x;
				break;
			}
			else {
				bl.x1 = x1;
				bl.x2 = x1 = d * (y2 - ln.p1.y) + p1.x; // cut the line
			}
		}
	}
}

#endif
