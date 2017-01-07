#include "Hot4d.h"

TextPath::TextPath()
{
	CtrlLayout(*this);
	
	offset_x <<= offset_y <<= 0;
}

Path TextPath::Get()
{
	Path r;
	
	/*
		G absolute
		g absolute
		r relative
		R relative
		a angle length
		A angle length
	*/
	
	String h = ~text;
	CParser p(h);
	
	Pointf pt0 = Pointf(0, 0);
	Pointf pt1 = pt0;
	
	int mode = 'G';
	
	while(!p.IsEof()) {
		try {
			while(p.IsChar('G') || p.IsChar('R') || p.IsChar('A'))
				mode = p.GetChar();
			int current_mode = mode;
			while(p.IsChar('g') || p.IsChar('r') || p.IsChar('a'))
				current_mode = ToUpper(p.GetChar());
			Pointf pt;
			pt.x = p.ReadDouble();
			pt.y = p.ReadDouble();
			if(current_mode == 'R')
				pt += pt1;
			r.To(pt);
			pt0 = pt1;
			pt1 = pt;
		}
		catch(CParser::Error) {
			p.SkipTerm();
		}
	}

	return r;
}
