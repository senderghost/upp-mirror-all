#include "Ugl.h"

GLMesh::GLMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);
}

GLMesh::~GLMesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
    for(auto h : VBO)
        glDeleteBuffers(1, &h);
}

void GLMesh::Add(const void *data, int type, int ntuple, int count)
{
    glBindVertexArray(VAO);
	GLuint& vbo = VBO.Add();
	glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    int sz = decode(gltype, GL_FLOAT, sizeof(float),
                            GL_BYTE, sizeof(byte),
                            GL_UNSIGNED_BYTE, sizeof(byte),
                            GL_SHORT, sizeof(int16),
                            GL_UNSIGNED_SHORT, sizeof(uint16),
                            GL_INT, sizeof(int32),
                            GL_UNSIGNED_INT, sizeof(uint32),
                            GL_DOUBLE);
    glBufferData(GL_ARRAY_BUFFER, sz * ntuple * count);
    glVertexAttribPointer(vbo.GetCount() - 1, ntuple, type, GL_FALSE, ntuple * sz, (void*)0);
}

void GLMesh::Index(const int *indices, int count)
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * icount, indices, GL_STATIC_DRAW);
}

void GLMesh::Use()
{
	glBindVertexArray(VAO);
}
