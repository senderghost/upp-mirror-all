#ifndef _GLDrawDemo_Ugl_h_
#define _GLDrawDemo_Ugl_h_

#include <GLDraw/GLDraw.h>

namespace Upp {

struct GLCode : GLProgram {
	GLCode(const char *vertex_shader, const char *pixel_shader);
	
	GLCode& Uniform(const char *id, double a);
	GLCode& Uniform(const char *id, double a, double b);
	GLCode& Uniform(const char *id, double a, double b, double c);
	GLCode& Uniform(const char *id, double a, double b, double c, double d);

	GLCode& operator()(const char *id, double a)                               { return Uniform(id, a); }
	GLCode& operator()(const char *id, double a, double b)                     { return Uniform(id, a, b); }
	GLCode& operator()(const char *id, double a, double b, double c)           { return Uniform(id, a, b, c); }
	GLCode& operator()(const char *id, double a, double b, double c, double d) { return Uniform(id, a, b, c, d); }

	int operator[](const char *id)    { return GetUniform(id); }
};

/*
class GLTexture {
	int textureid = 0;
	
public:
	void Clear() { if(textureid) 
	void Set(const Image& img, dword flags);
	
	operator GLuint() const     { return textureid; }
	GLuint operator~() const    { return textureid; }
	void     Bind() const       { 

	GLTexture();
	GLTexture(const Image& img) { Set(img); }
	~GLTexture()                { Clear(); }
}
*/

void GLBind(const Image& img, dword style = TEXTURE_LINEAR|TEXTURE_MIPMAP);

void GLDrawImage(Size sz, const Rect& rect, const Image img, double alpha);

class GLMesh {
	GLuint  VAO, EBO;
	int      elements;
    
	Vector<GLuint> VBO;

public:
	GLMesh& Add(const void *data, int type, int ntuple, int count);
	GLMesh& Add(const float *data, int ntuple, int count)                      { return Add(data, GL_FLOAT, ntuple, count); }
	GLMesh& Add(const Vector<Pointf>& pt);
	GLMesh& Index(const int *indices, int count);
	GLMesh& Index(const Vector<int>& indices)                                  { return Index(indices, indices.GetCount()); }
	
	void Draw(int mode = GL_TRIANGLES);

	void Draw(GLCode& shaders, int mode = GL_TRIANGLES);

	GLMesh();
	~GLMesh();
};

};

#endif
