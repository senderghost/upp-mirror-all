#include "Ugl.h"

namespace Upp {

void GLBind(const Image& img, dword style)
{
	glBindTexture(GL_TEXTURE_2D, GetTextureForImage(img, style));
}

void GLDrawImage(Size sz, const Rect& rect, const Image img, double alpha)
{
	static GLCode program(R"(
		#version 330 core
		uniform vec2 offset;
		uniform vec2 scale;
	    in      vec2 aPos;
		out vec2 tPos;
	    void main()
	    {
			gl_Position = vec4(scale * aPos + offset, 0, 1);
			tPos = aPos;
	    }
	)", R"(
		#version 330 core
		in vec2 tPos;
		uniform float alpha;
		uniform sampler2D s_texture;
		void main()
		{
		   gl_FragColor = alpha * texture2D(s_texture, tPos);
		}
	)");
	static GLMesh mesh;
	ONCELOCK {
		static const float box[] = {
			0, 0, // 0
			0, 1, // 1
			1, 0, // 2
			1, 1, // 3
		};
		static const int ndx[] = {
			0, 1, 2, 1, 2, 3
		};
		mesh.Add(box, 2, 4).Index(ndx, 6);
	}
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	
	Size isz = rect.GetSize();
	Point point = rect.TopLeft();

	GLBind(img);
	mesh.Draw(
		program("offset", 2.0 * point.x / sz.cx - 1, -2.0 * point.y / sz.cy + 1)
		       ("scale", 2.0 * isz.cx / sz.cx, -2.0 * isz.cy / sz.cy)
		       ("alpha", alpha)
	);
}

};


