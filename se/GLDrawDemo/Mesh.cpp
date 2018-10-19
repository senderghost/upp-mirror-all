#include "Ugl.h"

namespace Upp {

GLVertexData::GLVertexData()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);
}

GLVertexData::~GLVertexData()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
    for(auto h : VBO)
        glDeleteBuffers(1, &h);
}

GLVertexData& GLVertexData::Add(const void *data, int type, int ntuple, int count)
{
    glBindVertexArray(VAO);
    int ii = VBO.GetCount();
	GLuint& vbo = VBO.Add();
	glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    int sz = decode(type, GL_FLOAT, sizeof(float),
	                      GL_BYTE, sizeof(byte),
	                      GL_UNSIGNED_BYTE, sizeof(byte),
	                      GL_SHORT, sizeof(int16),
	                      GL_UNSIGNED_SHORT, sizeof(uint16),
	                      GL_INT, sizeof(int32),
	                      GL_UNSIGNED_INT, sizeof(uint32),
	                      sizeof(double));
	glBufferData(GL_ARRAY_BUFFER, sz * ntuple * count, data, GL_STATIC_DRAW);
	glVertexAttribPointer(ii, ntuple, type, GL_FALSE, ntuple * sz, (void*)0);
    glEnableVertexAttribArray(ii);
	return *this;
}

GLVertexData& GLVertexData::Index(const int *indices, int count)
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * count, indices, GL_STATIC_DRAW);
	elements = count;
	return *this;
}

void GLVertexData::Draw(int mode) const
{
	glBindVertexArray(VAO);
	glDrawElements(mode, elements, GL_UNSIGNED_INT, 0);
}

void GLVertexData::Draw(GLCode& shaders, int mode) const
{
	shaders.Use();
	Draw(mode);
}

GLVertexData& GLVertexData::Add(const Vector<Pointf>& pt)
{
	Buffer<float> f(2 * pt.GetCount());
	float *t = f;
	for(const Pointf& p : pt) {
		*t++ = (float)p.x;
		*t++ = (float)p.y;
	}
	return Add(f, GL_FLOAT, 2, pt.GetCount());
}

};