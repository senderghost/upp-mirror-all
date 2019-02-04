#include "GLDrawNew.h"

namespace Upp {

void GLTriangles2::Draw(const GLContext2D& dd, const GLTexture *tex, int tex_count)
{
	ASSERT(tex_count <= 8);

	if(elements.GetCount() == 0)
		return;

	static GLCode program(R"(
	#version 130
	    in vec3 p;
	    in uint f;
		uniform vec2 offset;
		uniform vec2 scale;
		out vec4 v_color;
		out vec2 texpos;
		out uint texi;
	    void main()
	    {
			gl_Position = vec4(scale * p.xy + offset, 0, 1);
			vec3 c = vec3(255u & (f >> 16), 255u & (f >> 8), 255u & f);
			v_color = vec4(1/255.0 * c.rgb, p.z);
			texpos = vec2(16383u & (f >> 14), 16383u & f);
			texi = 15u & (f >> 28);
	    }
	)", R"(
		in vec4 v_color;
		in vec2 texpos;
		flat in uint texi;
		uniform sampler2D tex1;
		uniform sampler2D tex2;
		uniform sampler2D tex3;
		uniform sampler2D tex4;
		uniform sampler2D tex5;
		uniform sampler2D tex6;
		uniform sampler2D tex7;
		uniform sampler2D tex8;
		void main()
		{
			if(texi) {
				vec4 v;

				if(texi < 5)
					if(texi < 3)
						if(texi == 1)
							v = texture2D(tex1, texpos / vec2(textureSize(tex1, 0)));
						else
							v = texture2D(tex2, texpos / vec2(textureSize(tex2, 0)));
					else
						if(texi == 3)
							v = texture2D(tex3, texpos / vec2(textureSize(tex3, 0)));
						else
							v = texture2D(tex4, texpos / vec2(textureSize(tex4, 0)));
				else
					if(texi < 7)
						if(texi == 5)
							v = texture2D(tex5, texpos / vec2(textureSize(tex5, 0)));
						else
							v = texture2D(tex6, texpos / vec2(textureSize(tex6, 0)));
					else
						if(texi == 7)
							v = texture2D(tex7, texpos / vec2(textureSize(tex7, 0)));
						else
							v = texture2D(tex8, texpos / vec2(textureSize(tex8, 0)));

				gl_FragColor = v_color.a * clamp(v, vec4(0, 0, 0, 0), v.aaaa); // clamp fixes non-premultiplied textures
			}
			else
				gl_FragColor = v_color;
		}
	)");

	static int ioffset = program["offset"];
	static int iscale = program["scale"];

	GLVertexData va;
	va.Add(pos, 3);
	va.Add(info, 1);
	va.Index(elements);
	
	glEnable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDisable(GL_DEPTH_TEST);
	
	program(ioffset, dd.off)
	       (iscale, dd.vs)
	;

	for(int i = 0; i < tex_count; i++)
		tex[i].Bind(i);

	va.Draw(program);
}

};