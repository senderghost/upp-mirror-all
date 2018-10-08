#include <CtrlLib/CtrlLib.h>
#include <GLDraw/GLDraw.h>
#include <GLCtrl/GLCtrl.h>

using namespace Upp;

void Tesselate(Vector<Vector<Pointf>>& shape, Vector<Pointf>& vertex, Vector<Tuple<int, int, int>>& triangle);



struct OpenGLExample : GLCtrl {
	Point point;
	
	OpenGLExample() {
	}

	virtual void GLPaint() {
		Size sz = GetSize();
		
		GLDraw w;
		
		w.Init(sz);

		w.Flush();
		
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

#if 1
		static GLProgram program;
		static GLMesh mesh;
		ONCELOCK {
			program.Create(R"(
				#version 330 core
			    in vec4 aPos;
				uniform mat4 u_projection;
				uniform vec4 offset;
				uniform vec2 scale;
			    void main()
			    {
					vec4 h;
					h.x = scale.x * aPos.x;
					h.y = scale.y * aPos.y;
					gl_Position = u_projection * (aPos + offset);
			    }

			)", R"(
				#version 330 core
				out vec4 FragColor;
				uniform vec4 ourColor;
				void main()
				{
					FragColor = ourColor;
				}

				)",
				ATTRIB_VERTEX, "aPos"
			);

			Vector<Pointf> p = { Pointf(100, 100), Pointf(200, 100), Pointf(150, 320) };
//			Vector<Pointf> p = { Pointf(-0.3, -0.3), Pointf(0.3, -0.3), Pointf(0, 0.2) };
			Vector<int> i = { 0, 1, 2 };

			Vector<Vector<Pointf>> polygon;
			Vector<Pointf>& c = polygon.Add();
			for(int i = 0; i < 360; i += 20) {
				c.Add(300 * Polar(M_2PI * i / 360.0) + Pointf(350, 350));
				c.Add(200 * Polar(M_2PI * (i + 10) / 360.0) + Pointf(350, 350));
			}
		
			Vector<Pointf> vertex;
			Vector<Tuple<int, int, int>> triangle;
			Tesselate(polygon, vertex, triangle);
			
			Vector<int> ndx;
			for(const auto& t : triangle) {
				ndx.Add(t.a);
				ndx.Add(t.b);
				ndx.Add(t.c);
			}
			
			DDUMP(ndx.GetCount());
			DDUMP(vertex.GetCount());

			mesh.Set(vertex, ndx);

		}

		DDUMP(sz.cx);
		DDUMP(point.x);

		program.Use();
		GLOrtho(0, (float)sz.cx, (float)sz.cy, 0, 0.0f, 1.0f, program.GetUniform("u_projection"));
		glUniform4f(program.GetUniform("offset"), point.x, point.y, 0, 0);
		glUniform2f(program.GetUniform("scale"), point.x / 1000.0, 1);
		glUniform4f(program.GetUniform("ourColor"), 0.0f, (float)point.x / sz.cx, 0.0f, 1.0f);

		glDisable(GL_BLEND);

		mesh.Paint();

#else
		for(int i = 0; i < 200; i++) {
			Rect r(GetSize());
			r.Deflate(point.x + i);
			gl_image.Use();
		
			Size isz = image.GetSize();
			Rect s = isz;
			
			GLint vertex[] = {
			    r.left, r.top,
			    r.left, r.bottom,
			    r.right, r.bottom,
			    r.right, r.top,
			};
		
			static GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
		
			const float *tc;
		
			static float fixed[] = {
				0.0, 0.0,
				0.0, 1.0,
				1.0, 1.0,
				1.0, 0.0,
			};
			tc = fixed;
		
			glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
			glEnableVertexAttribArray(ATTRIB_TEXPOS);
			glVertexAttribPointer(ATTRIB_TEXPOS, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), tc);
			glVertexAttribPointer(ATTRIB_VERTEX, 2, GL_INT, GL_FALSE, 2 * sizeof(GLint), vertex);
			glBindTexture(GL_TEXTURE_2D, GetTextureForImage(TEXTURE_LINEAR|TEXTURE_MIPMAP, image));
		
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
		
			glDisableVertexAttribArray(ATTRIB_TEXPOS);
		}
#endif
	}

	virtual void MouseMove(Point p, dword) {
		point = p;
		Refresh();
	}
};

namespace Upp {
extern int max_texture_memory;
extern int max_texture_count;
};

GUI_APP_MAIN
{
	max_texture_memory = 1024*1024*1024;
//	image = StreamRaster::LoadFileAny("C:/xxx/IMG_20180818_183724382.jpg");
//	image = CtrlImg::HelpCursor1();
//	DDUMP(image.GetSize());
//	Ctrl::GlobalBackPaint();
	TopWindow win;
	OpenGLExample gl;
	gl.SetFrame(InsetFrame());
	win.Add(gl.HSizePos(10, 10).VSizePos(10, 10));
	win.Sizeable().Zoomable();
	win.Open();
	win.Run();
}
