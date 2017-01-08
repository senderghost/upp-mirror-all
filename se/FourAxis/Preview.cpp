#include "Hot4d.h"

void FourAxisDlg::Sync()
{
	Title(filepath);

	Size isz = preview.GetSize();
	
	if(isz.cx > 0 && isz.cy > 0) {
		int scale = ~this->scale;
		
		bool ok = true;
		for(auto q = GetFirstChild(); q; q = q->GetNext())
			if(q->GetData().IsError())
				ok = false;
	
		Font fnt = Arial(Zy(12));
		int  w = Zx(4);
		int b = fnt.GetLineHeight() + w;
		Point origin(b, isz.cy - b);
		
		Size psz = isz - Size(b, b);
		
		ImagePainter p(isz);
	
		p.Translate(0.5, 0.5);
		p.Clear(White());
	
		int ny = INT_MIN;
		int nx = INT_MIN;
		for(int i = 0; i < max(psz.cy / scale, psz.cx / scale); i += 5) {
			int si = i * scale;
			bool ten = i % 10 == 0;
			int w1 = Zx(ten ? 4 : 2);
			Color c = ten ? LtGray() : WhiteGray();
			p.Move(origin.x + si, origin.y + w1).Line(origin.x + si, 0).Stroke(1, c);
			p.Move(origin.x - w, origin.y - si).Line(isz.cx, origin.y - si).Stroke(1, c);
			String s = AsString(i);
			Size tsz = GetTextSize(s, fnt);
			int x = origin.x + si - tsz.cx / 2;
			if(x > nx + Zx(2)) {
				p.Text(x, origin.y + w, s, fnt).Fill(Black());
				nx = x + tsz.cx;
			}
			int y = origin.y - si - tsz.cy / 2;
			if(y < ny - Zy(2)) {
				p.Text(origin.x - tsz.cx - Zx(6), y, s, fnt).Fill(Black());
				ny = y - tsz.cy;
			}
		}

		p.Move(origin).Line(isz.cx, origin.y).Stroke(1, Black());
		p.Move(origin).Line(origin.x, 0).Stroke(1, Black());
	
		if(ok) {
			p.Translate(origin);
			p.Scale(scale, -scale);
			p.Move(0, 0);
			
			
			double k = Nvl((double)~kerf);
			if(k) {
				auto path = GetPath(k);
				for(auto pt : path)
					p.Line(pt);
				if(show_kerf)
					p.LineCap(LINECAP_ROUND).LineJoin(LINEJOIN_ROUND).Stroke(k, Blend(White(), LtRed(), 50));
				if(show_wire)
					p.Stroke(1.0 / scale, Red());
				PaintArrows(p, scale);
			}
	
			auto path = GetPath(0);
			for(auto pt : path)
				p.Line(pt);
			if(show_shape || !k && show_wire)
				p.Stroke(1.0 / scale, k ? Blue() : Red());
			
			if(!k)
				PaintArrows(p, scale);
		}
	
		preview.SetImage(p);
	}
	
	SetBar();
}

void FourAxisDlg::PaintArrows(Painter& p, double scale)
{
	int a = ~arrows;
	if(a)
		for(double i = 0; i < a; i++) {
			p.BeginOnPath(i / (a - 1));
			p.Move(0, -4.0 / scale).Line(4.0 / scale, 0).Line(0, 4.0 / scale).Close().Stroke(1.0 / scale, LtRed());
			p.End();
		}
}
