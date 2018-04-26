#include <CtrlLib/CtrlLib.h>

namespace Upp {

class DDAColorRasterizer {
	struct Segment : Moveable<Segment> {
		int  l;
		int  h;
		RGBA lc;
		RGBA rc;
		bool flag;
		
		bool operator<(const Segment& b) const { return h < b.h; }
	};
	
	struct Segments;
	
	int           cy;
	int           diry;
	int           dirx;
	One<Segments> pseg;
	Point         p0, p1;
	int           width;
	bool          close;

	int           miny;
	int           maxy;
	bool          flag;
	Vector< Vector< Segment > > segment;

	void AHorz(int x, int y, int cx, RGBA c1, RGBA c2);
	void AVert(int x, int y, int cy, RGBA c1, RGBA c2);
	void DoLine(Point p1, Point p2, bool last);

public:
	virtual void PutHorz(int x, int y, int cx, RGBA c1, RGBA c2) = 0;
	virtual void PutVert(int x, int y, int cy, RGBA c1, RGBA c2) = 0;
	
	int  GetDirx() const                      { return dirx; }
	int  GetDiry() const                      { return diry; }
	
	DDAColorRasterizer& Move(Point p, RGBA c);
	DDAColorRasterizer& Line(Point p, RGBA c);
	DDAColorRasterizer& Close();
	
	DDAColorRasterizer& Polygon();
	DDAColorRasterizer& Fill();
	
	void Cy(int cy_)                          { cy = cy_; }
	
	DDAColorRasterizer();
	virtual ~DDAColorRasterizer();
};

};