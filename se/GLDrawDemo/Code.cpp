#include "Ugl.h"

namespace Upp {

GLCode::GLCode(const char *vertex_shader, const char *pixel_shader)
{
	Create(vertex_shader, pixel_shader);
	Vector<Tuple2<int, const char *>> ins;
	CParser p(vertex_shader);
	int ii = 0;
	while(!p.IsEof() && !p.Char('{'))
		if(p.Id("attribute") || p.Id("in")) {
			String id;
			while(!p.IsEof() && p.Char(';'))
				if(p.IsId())
					id = p.ReadId();
				else
					p.SkipTerm();
			if(id.GetCount())
				glBindAttribLocation(program, ii++, id);
		}
		else
			p.SkipTerm();
}

};
