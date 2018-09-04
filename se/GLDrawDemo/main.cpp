#include <CtrlLib/CtrlLib.h>
#include <GLDraw/GLDraw.h>
#include <GLCtrl/GLCtrl.h>

using namespace Upp;

Image image;

struct OpenGLExample : GLCtrl {
	Point point;

	virtual void GLPaint() {
		Size sz = GetSize();
/*
		GLint total_mem_kb = 0;
		glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &total_mem_kb);
		DDUMP(total_mem_kb);
*/
//		DDUMP((char *)glGetString(GL_VENDOR));
		
		GLDraw w;
		
		w.Init(sz);
/*
		w.DrawRect(0, 0, sz.cx, sz.cy, SWhite);
		w.DrawRect(10, 10, 30, 30, SRed);
		w.DrawLine(45, 45, 80, 120, 4, Blue);
		w.DrawLine(80, 90, 400, 0, PEN_DASHDOT);
		w.DrawImage(200, 10, CtrlImg::reporticon());
		const char *text = "This text is centered";
		Size tsz = GetTextSize(text, Arial(25).Bold());
		w.DrawText((sz.cx - tsz.cx) / 2, (sz.cy - tsz.cy) / 2, text, Arial(27).Bold(), SBlue);
		w.Clipoff(200, 50, 95, 100);
		w.DrawText(0, 80, "CLIPPED", Roman(25));
		w.End();
		
		return;
		// w.DrawImage(0, 0, Rescale(image, sz)); return;
*/
		w.Flush();

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
	image = StreamRaster::LoadFileAny("C:/xxx/IMG_20180818_183724382.jpg");
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
