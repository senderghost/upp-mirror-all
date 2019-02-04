#ifndef _GLDrawNew_GLDrawNew_h_
#define _GLDrawNew_GLDrawNew_h_

#include <GLDraw/GLDraw.h>

namespace Upp {

class GLTriangles2 {
	Vector<float>  pos;
	Vector<dword>  info;
	Vector<GLint>  elements;
	int            ii = 0;

public:
	int  Vertex(float x, float y, Color c, double alpha) {
		pos << x << y << (float)alpha;
		info << (((byte)c.GetR() << 16) | ((byte)c.GetG() << 8) | (byte)c.GetB());
		return ii++;
	}
	int  Vertex(Pointf p, Color c, double alpha)          { return Vertex((float)p.x, (float)p.y, c, alpha); }
	int  Vertex(int x, int y, Color c, double alpha)      { return Vertex((float)x, (float)y, c, alpha); }
	
	int  Vertex(float x, float y, int texi, int tex_x, int tex_y, double alpha) {
		pos << x << y << (float)alpha;
		info << (((1 + texi) << 28) | ((16383 & tex_x) << 14) | (16383 & tex_y));
		return ii++;
	}
	int  Vertex(int x, int y, int texi, int tex_x, int tex_y, double alpha) { return Vertex((float)x, (float)y, texi, tex_x, tex_y, alpha); }

	void Triangle(int a, int b, int c)                    { elements << a << b << c; }
	
	void Clear()                                          { elements.Clear(); pos.Clear(); info.Clear(); ii = 0; }

	void Draw(const GLContext2D& dd, const GLTexture *tex, int tex_count);
};

};

#endif
