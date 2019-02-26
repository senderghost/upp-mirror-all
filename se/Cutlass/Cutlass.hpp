#include "Cutlass.h"

namespace Upp {

inline
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

template <class Out>
void Cutlass::Do(const Out& out)
{
	if(line.GetCount() == 0)
		return;

	Sort(line, [](const Line& a, const Line& b) { return a.p1.y < b.p1.y; });

	Vector<double> y;
	for(const auto& ln : line) // first add sorted ones to speedup sorting
		y.Add(ln.p1.y);
	for(const auto& ln : line)
		y.Add(ln.p2.y);
	
	Sort(y);

	band.Reserve(y.GetCount());
	for(int i = 0; i < y.GetCount(); i++)
		if(i == 0 || y[i] != y[i - 1]) // create bands, but unique y only
			band.Add().y = y[i];

	int ii = 0; // progress so far from the top
	for(const auto& ln : line) {
		while(ln.p1.y > band[ii].y) // find a band at p1.y, start of current line
			ii++;

		Pointf h = ln.p2 - ln.p1;
		double d = h.x / h.y;

		double x1 = ln.p1.x;
		for(int i = ii; i + 1 < band.GetCount(); i++) { // cut the line, add to appropriate bands
			BandLine& bl = band[i].line.Add(); // we need to add line segment to this band
			bl.dir = ln.dir;
			bl.x1 = x1;

			double y2 = band[i + 1].y; // start of next band is end of the current
			if(y2 >= ln.p2.y) { // this is the last band for ln
				bl.x2 = ln.p2.x;
				break;
			}
			else
				bl.x2 = x1 = d * (y2 - ln.p1.y) + ln.p1.x; // cut the line
		}
	}
	
	for(int j = 0; j + 1 < band.GetCount(); j++) {
		Band& b = band[j];
		double y1 = b.y;
		double y2 = band[j + 1].y;
		if(b.line.GetCount() > 1) {
			Sort(b.line, [](const BandLine& a, const BandLine& b) { return a.x1 < b.x1; });
			// TODO: Line crossing detection
			// TODO: Winding rules
			for(int i = 0; i + 1 < b.line.GetCount(); i += 2)
				out(y1, b.line[i].x1, b.line[i + 1].x1, y2, b.line[i].x2, b.line[i + 1].x2);
		}
	}
}

};