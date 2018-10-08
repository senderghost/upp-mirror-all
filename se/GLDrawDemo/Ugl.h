#ifndef _GLDrawDemo_Ugl_h_
#define _GLDrawDemo_Ugl_h_

#include <GLDraw/GLDraw.h>

namespace Upp {

struct GLCode : GLProgram {
	GLCode(const char *vertex_shader, const char *pixel_shader);
};

class GLMesh {
	GLuint  VAO, EBO;
	int      elements;
    
	Vector<GLuint> VBO;

public:
	void Add(const void *data, int size, int count, int gltype);
	
	void Add(const float *vertices, int count);
	void Set(const float *vertices, int vcount, const int *indices, int icount);
	void Set(const Vector<Pointf>& vertices, const Vector<int>& indices);
    void Paint();

	GLMesh();
	~GLMesh();
};

};

#endif
