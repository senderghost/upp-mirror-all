#ifndef _Cutlas_Cutlas_h_
#define _Cutlas_Cutlas_h_

#include <Core/Core.h>

namespace Upp {

struct Cutlass {
	struct Line : Moveable<Line> {
		Pointf p1, p2;
		int    dir;
	};
	struct BandLine : Moveable<BandLine> {
		double x1, x2;
		int    dir;
	};
	struct Band : Moveable<Band> {
		double y;
		Vector<BandLine> line;
	};
	
	Vector<Line>   line;
	Vector<Band>   band;
	
	void Clear()                             { line.Clear(); band.Clear(); }
	void AddLine(Pointf p1, Pointf p2);
	
	template <class Out>
	void Do(const Out& out);
};

};

#include "Cutlass.hpp"

#endif
