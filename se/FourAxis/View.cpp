#include "Hot4d.h"

View::View()
{
	SetFrame(ViewFrame());
}

void View::Paint(Draw& w)
{
	w.DrawImage(0, 0, img);
}

void View::LeftDown(Point p, dword)
{
	if(fa) fa->ViewDown(p);
}

void View::LeftUp(Point p, dword)
{
	if(fa) fa->ViewUp(p);
}

void View::MouseMove(Point p, dword)
{
	if(fa) fa->ViewMove(p);
}

void View::MouseWheel(Point p, int zdelta, dword)
{
	if(fa) fa->ViewWheel(p, zdelta);
}

void View::LeftDrag(Point p, dword)
{
	if(fa) fa->ViewDrag(p);
}

void View::LeftHold(Point p, dword)
{
	if(fa) fa->ViewDrag(p);
}

void FourAxisDlg::ViewDown(Point p)
{
	drag = false;
	click = p;
	click_org = org;
}

void FourAxisDlg::ViewUp(Point p)
{
	if(!drag)
		CurrentShape().AddPoint(GetViewPos(p));
	drag = false;
}

void FourAxisDlg::ViewMove(Point p)
{
	if(drag) {
		org = p - click + click_org;
		Sync();
		view.Sync();
	}
	info = AsString(GetViewPos(p));
}

void FourAxisDlg::ViewWheel(Point p, int zdelta)
{
	Zoom(sgn(zdelta), p);
}

void FourAxisDlg::ViewDrag(Point p)
{
	view.SetCapture();
	drag = true;
}

Pointf FourAxisDlg::GetViewPos(Point p)
{
	Point origin = ViewOrigin();
	p -= org;
	return Pointf(p.x - origin.x, origin.y - p.y) / (double)~scale;
}

void FourAxisDlg::Zoom(int dir, Point p)
{
	Pointf pos = GetViewPos(p);
	scale.SetIndex(minmax(scale.GetIndex() + dir, 0, scale.GetCount() - 1));

	Point origin = ViewOrigin();
	
	double z = (double)~scale;
	Point p1;
	p1.x = int(origin.x + z * pos.x);
	p1.y = int(origin.y - z * pos.y);
	org = p - p1;

	Sync();
}

void FourAxisDlg::ViewPars(Font& fnt, int& w, Point& origin) const
{
	Size isz = view.GetSize();
	fnt = Arial(Zy(12));
	w = Zx(4);
	origin = Pointf(GetTextSize("9999", fnt).cx + w, isz.cy - fnt.GetLineHeight() - w);
}

Point FourAxisDlg::ViewOrigin() const
{
	Font fnt;
	int w;
	Point origin;
	ViewPars(fnt, w, origin);
	return origin;
}

void FourAxisDlg::Sync()
{
	Title(filepath);
	
	org.x = min(org.x, 0);
	org.y = max(org.y, 0);

	Size isz = view.GetSize();

	double scale = ~this->scale;
	
	if(isz.cx > 0 && isz.cy > 0 && scale > 0) {
		
		bool ok = true;
		for(auto q = GetFirstChild(); q; q = q->GetNext())
			if(q->GetData().IsError())
				ok = false;
	
		Font fnt;
		int w;
		Point origin;
		ViewPars(fnt, w, origin);
		
		ImagePainter p(isz);
	
		p.Translate(0.5, 0.5);
		p.Clear(White());
	
		double ny = INT_MAX;
		double nx = INT_MIN;
		p.Begin();
		for(int i = 0;; i += 5) {
			double si = i * scale;

			double px = origin.x + si + org.x;
			double py = origin.y - si + org.y;
			
			if(px > isz.cx && py < 0 || i > 2000)
				break;

			String s = AsString(i);
			Size tsz = GetTextSize(s, fnt);
			bool ten = i % 10 == 0;
			int w1 = Zx(ten ? 4 : 2);
			Color c = ten ? LtGray() : WhiteGray();

			if(px >= origin.x)
				p.Move(px, origin.y + w1).Line(origin.x + si + org.x, 0).Stroke(1, c);
			double x = px - tsz.cx / 2;
			if(x > nx + Zx(2)) {
				if(px >= origin.x)
					p.Text(x, origin.y + w, s, fnt).Fill(Black());
				nx = x + tsz.cx;
			}
			
			if(py <= origin.y)
				p.Move(origin.x - w, py).Line(isz.cx, py).Stroke(1, c);
			double y = py - tsz.cy / 2;
			if(y < ny - Zy(2)) {
				if(py <= origin.y)
					p.Text(origin.x - tsz.cx - Zx(6), y, s, fnt).Fill(Black());
				ny = y - tsz.cy;
			}
		}
		p.End();

		p.Move(origin).Line(isz.cx, origin.y).Stroke(1, Black());
		p.Move(origin).Line(origin.x, 0).Stroke(1, Black());
	
		p.Begin();
		p.RectPath(origin.x, 0, isz.cx - origin.x, origin.y);
		p.Clip();
	
		if(ok) {
			p.Translate(org.x, org.y);
			p.Translate(origin);
			p.Scale(scale, -scale);

			double k = Nvl((double)~kerf);
			if(k) {
				auto path = GetPath(k);
				if(show_kerf || show_wire) {
					p.Move(0, 0);
					for(auto pt : path)
						p.Line(pt);
					if(show_kerf)
						p.LineCap(LINECAP_ROUND).LineJoin(LINEJOIN_ROUND).Stroke(k, Blend(White(), LtRed(), 50));
					if(show_wire)
						p.Stroke(1.0 / scale, Red());
				}
				PaintArrows(p, path, scale);
			}
	
			auto path = GetPath(0);
			if(show_shape || !k && show_wire) {
				p.Move(0, 0);
				for(auto pt : path)
					p.Line(pt);
				p.Stroke(1.0 / scale, k ? Blue() : Red());
			}
			
			if(show_points)
				for(auto pt : path) {
					p.Move(pt + Pointf(-3, -3) / scale).Line(pt + Pointf(3, 3) / scale)
					 .Move(pt + Pointf(-3, 3) / scale).Line(pt + Pointf(3, -3) / scale)
					 .Stroke(1.0 / scale, Black());
				}
			
			if(!k)
				PaintArrows(p, path, scale);
		}
		p.End();
	
		view.img = p;
		view.Refresh();
	}
	
	SetBar();
}

void FourAxisDlg::PaintArrows(Painter& p, const Vector<Pointf>& path, double scale)
{
	if(!show_arrows)
		return;
	
	double len = PathLength(path);
	
	int n = int(len / 30 * scale);
	
	for(int i = 0; i < n; i++) {
		Pointf dir;
		Pointf f = AtPath(path, i * len / n, &dir);
		p.Begin();
		p.Translate(f);
		p.Rotate(Bearing(dir));
		p.Move(0, -4.0 / scale).Line(4.0 / scale, 0).Line(0, 4.0 / scale).Fill(LtBlue());
		p.End();
	}
	
/*
	int a = ~arrows;
	if(a)
		for(double i = 0; i < a; i++) {
			p.BeginOnPath(i / (a - 1));
			p.Move(0, -4.0 / scale).Line(4.0 / scale, 0).Line(0, 4.0 / scale).Close().Stroke(1.0 / scale, LtRed());
			p.End();
		}
*/
}
