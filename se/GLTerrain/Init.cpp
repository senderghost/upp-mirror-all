#include "GLCamera.h"

void GLTerrain::SetTerrain(float unit, Size dim, const Vector<Vector<float>>& elevation, const Image& image)
{
	Vector<float> vert;
	Vector<float> tex;
	Vector<int> index;
	int ii = 0;
	Size sz = image.GetSize();
	float tcx = 1.0f / sz.cx;
	float tcy = 1.0f / sz.cy;
	for(int i = 0; i < dim.cx - 1; i++)
		for(int j = 0; j < dim.cy - 1; j++) {
			float v0 = elevation[i][j];
			float v1 = elevation[i + 1][j];
			float v2 = elevation[i][j + 1];
			float v3 = elevation[i + 1][j + 1];
			
			float x = i * unit;
			float y = j * unit;
			float x1 = (i + 1) * unit;
			float y1 = (j + 1) * unit;
			
			vert << x << v0 << y
			     << x1 << v1 << y
			     << x << v2 << y1
			     << x1 << v3 << y1;

			float tx = i * tcx;
			float ty = j * tcy;
			float tx1 = (i + 1) * tcx;
			float ty1 = (j + 1) * tcy;

			tex << tx << ty
			    << tx1 << ty
			    << tx << ty1
			    << tx1 << ty1;
			     
			index << ii + 0 << ii + 1 << ii + 2
			      << ii + 2 << ii + 1 << ii + 3;
			
			ii += 4;
		}
	
	texture.Set(image);

	verts.Add(vert, 3);
	verts.Add(tex, 2);
	verts.Index(index);
}

void GLTerrain::Test()
{
    // ------------------------------------------------------------------
    static float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

	Vector<float> vert;
	Vector<float> tex;
	Vector<int> index;
	
	int ii = 0;
	for(int i = 0; i < __countof(vertices); i += 5) {
		float *v = vertices + i;
		vert << v[0] << v[1] << v[2];
		tex << v[3] << v[4];
		index.Add(ii++);
	}

	verts.Add(vert, 3);
	verts.Add(tex, 2);
	verts.Index(index);
}