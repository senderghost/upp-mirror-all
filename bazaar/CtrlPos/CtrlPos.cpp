#include "CtrlPos.h"

void CtrlPos::DrawAlignHandle(Draw& w, const Rect& _r, const Rect& r, const Ctrl::LogPos& pos, const Color& col)
{
	Point p;
	bool q;
	Size rz = r.GetSize();
	Color col2 = Blend(col, Black);

	p = r.CenterLeft();
	p.y -= rz.cy/4;
	q = (pos.x.GetAlign()&Ctrl::LEFT);
	w.DrawLine(p, Point(_r.left, p.y), (q)?(PEN_SOLID):(PEN_DOT), (q)?(col):(col2));

	p = r.CenterRight();
	p.y += rz.cy/4;
	q = (pos.x.GetAlign()&Ctrl::RIGHT);
	w.DrawLine(p, Point(_r.right, p.y), (q)?(PEN_SOLID):(PEN_DOT), (q)?(col):(col2));

	p = r.TopCenter();
	p.x -= rz.cx/4;
	q = (pos.y.GetAlign()&Ctrl::TOP);
	w.DrawLine(p, Point(p.x, _r.top), (q)?(PEN_SOLID):(PEN_DOT), (q)?(col):(col2));

	p = r.BottomCenter();
	p.x += rz.cx/4;
	q = (pos.y.GetAlign()&Ctrl::BOTTOM);
	w.DrawLine(p, Point(p.x, _r.bottom), (q)?(PEN_SOLID):(PEN_DOT), (q)?(col):(col2));
}

bool CtrlPos::GetAlignMode(const Rect& _r, const Rect& r, const Point& pp, Ctrl::LogPos& pos, int handsize)
{
	int size = handsize+2;
	Rect c;
	Point p;
	int q;
	Size rz = r.GetSize();
	
	q = pos.x.GetAlign();
	
	p = r.CenterLeft();
	p.y -= rz.cy/4;
	c = Rect(p, Point(_r.left, p.y)); c.InflateVert(size); c.Normalize();
	if(c.Contains(pp)) { q&= ~Ctrl::LEFT; q|= (pos.x.GetAlign()&Ctrl::LEFT)?(0):(Ctrl::LEFT); pos.x.SetAlign(q); return true; }

	p = r.CenterRight();
	p.y += rz.cy/4;
	c = Rect(p, Point(_r.right, p.y)); c.InflateVert(size); c.Normalize();
	if(c.Contains(pp)) { q&= ~Ctrl::RIGHT; q|= (pos.x.GetAlign()&Ctrl::RIGHT)?(0):(Ctrl::RIGHT); pos.x.SetAlign(q); return true; }

	q = pos.y.GetAlign();
	
	p = r.TopCenter();
	p.x -= rz.cx/4;
	c = Rect(p, Point(p.x, _r.top)); c.InflateHorz(size); c.Normalize();
	if(c.Contains(pp)) { q&= ~Ctrl::TOP; q|= (pos.y.GetAlign()&Ctrl::TOP)?(0):(Ctrl::TOP); pos.y.SetAlign(q); return true; }

	p = r.BottomCenter();
	p.x += rz.cx/4;
	c = Rect(p, Point(p.x, _r.bottom)); c.InflateHorz(size); c.Normalize();
	if(c.Contains(pp)) { q&= ~Ctrl::BOTTOM; q|= (pos.y.GetAlign()&Ctrl::BOTTOM)?(0):(Ctrl::BOTTOM); pos.y.SetAlign(q); return true; }
	
	return false;
}

void CtrlPos::Paint(Draw& w)
{
	Size sz = GetSize();
	
	if(!IsTransparent())
		w.DrawRect(0,0,sz.cx,sz.cy, SColorFace());

	if(IsEnabled() && !IsEmpty())
	{
		Ctrl* c = Get().GetFirstChild();
		while(c)
		{
			if(!c->InFrame())
			{
				Rect r = c->GetRect();
				r.Offset(CtrlMover::GetOffset(*(c->GetParent()), Get()));
				r.Inflate(1);
				RectCtrl::DrawHandleFrame(w, r, LtGray, 1);
			}
			c = c->GetNext();	
		}
	}
	
	Ctrl* c = GetCtrl();
	if(!c) return;

	Rect r = c->GetRect();
	Point op = CtrlMover::GetOffset(*(c->GetParent()), Get());
	r.Offset(op);

	RectCtrl::DrawHandleFrame(w, r, style->framecol, style->framesize);

	Rect _r;
	if(c->GetParent())
	{
		_r = c->GetParent()->GetView();
		Point opr = _r.TopLeft();
		_r.Offset(op-opr);
	}
	else _r = sz;
	DrawAlignHandle(w, _r, r, c->GetPos(), style->framecol);

	RectCtrl::DrawHandle(w, r, style->handcol, style->handsize);

	if(pressed)// && moving)
		RectCtrl::DrawRectInfo(w, Point(10,10), r, style->framecol, style->textcol);
}

void CtrlPos::LeftDown(Point p, dword keyflags)
{
	SetCapture();
	moving = false;
	pressed = (keyflags & K_MOUSELEFT);

	if(GetCtrl())
	{
		//if already found prepare moving
		Ctrl& c = *GetCtrl();
		ASSERT(!c.InFrame());
		xpos = c.GetPos();
		xp = p;
	
		Size sz = GetSize();

		Rect r = c.GetRect();
		Point op = CtrlMover::GetOffset(*(c.GetParent()), Get());
		if(c.InView())
		r.Offset(op);

		Ctrl::LogPos pos = xpos;
		Rect rr(r); rr.Inflate(style->handsize+2);

		Rect _r;
		if(c.GetParent())
		{
			_r = c.GetParent()->GetView();
			Point opr = _r.TopLeft();
			_r.Offset(op-opr);
		}
		else _r = sz;

		if(GetAlignMode(_r, rr, p, pos, style->handsize))
		{
			pos = LogPosPopUp::ReAlign(c, pos);		
			c.SetPos(pos);
			Action();
			Refresh();
			return;
		}
		else if((mode = RectCtrl::GetMode(r, p, keyflags, style->handsize)) != RectCtrl::NONE)
		{
			ci = RectCtrl::SetCursor(mode, keyflags, ci);
			Refresh();
			return;
		}
	}
	CtrlFinder::LeftDown(p, keyflags);
	if(GetCtrl() == &Get()) //may  not move base
	{
		ClearCtrl();
		Action();
	}
	if(GetCtrl() && GetCtrl()->InFrame())
	{
		ClearCtrl(); //may not move frames
		Action();
	}
	Refresh();
}

void CtrlPos::MouseMove(Point p, dword keyflags)
{
	moving = true;
	pressed = (keyflags & K_MOUSELEFT);
	//int m = RectCtrl::GetMode(r, p, keyflags, style->handsize);
	//ci = RectCtrl::SetCursor(m, keyflags);
	if(!GetCtrl()) return;
	Ctrl& c = *GetCtrl();

	if(pressed && mode != RectCtrl::NONE) 
	{
		Size sz = GetSize();

		if(keyflags & K_ALT)
		{
			Ctrl* par = c.GetParent();
			Ctrl* prevc = c.GetPrev();

			//info not available after Remove();
			//Rect of source parent
			Rect rs;
			rs.Clear();
			if(par)
			{
				rs = par->GetRect();
				Point ops = CtrlMover::GetOffset(*(par->GetParent()), Get());
				if(par->InView()) rs.Offset(ops);
			}
			else
				rs.Clear();

			c.Remove(); //prevent moving control from finding when searching new parent
			Point pt(p);
			Ctrl* pc = GetCtrl(Get(), pt, flags | DEEP);
			if(!pc) pc = &Get();
			if(pc != par)
			{
				//convert xpos
				//Rect of destination parent
				Rect rd = pc->GetRect();
				Point opd = CtrlMover::GetOffset(*(pc->GetParent()), Get());
				if(pc->InView()) rd.Offset(opd);

				//the source xpos' Rect
				Rect r = LogPosPopUp::CtrlRect(xpos, sz);
				r.Offset(rs.TopLeft()-rd.TopLeft());
				xpos = LogPosPopUp::MakeLogPos(xpos, r, pc->GetSize());
				
				pc->Add(c);
			}
			else
				par->AddChild(&c, prevc);
		}

		Rect r = LogPosPopUp::CtrlRect(xpos, sz);
		RectCtrl::CalcRect(r, p-xp, keyflags, mode, g);
		r.Normalize();
		Ctrl::LogPos pos = LogPosPopUp::MakeLogPos(xpos, r, sz);
		GetCtrl()->SetPos(pos);
		Action();
		Refresh();
	}
}

void CtrlPos::LeftUp(Point p, dword keyflags)
{
	ReleaseCapture();
	pressed = false;
	moving = false;
	//xpos.SetNull();
	xp.SetNull();
	mode = RectCtrl::NONE;
	ci = RectCtrl::SetCursor(mode, keyflags, ci);
	Refresh();
}

void CtrlPos::RightDown(Point p, dword keyflags)
{
	//cancel
	ReleaseCapture();
	//pressed = false;
	//moving = false;
	////xpos.SetNull();
	//xp.SetNull();
	int m = mode;
	mode = RectCtrl::NONE;
	ci = RectCtrl::SetCursor(mode, keyflags, ci);
	if(!GetCtrl()) return;

	if(m != RectCtrl::NONE)
	{
		GetCtrl()->SetPos(xpos);
		Action();
		Refresh();
	}
}

void CtrlPos::MouseWheel(Point p, int zdelta, dword keyflags)
{
	//if(!IsEditable()) return;
	//if(!HasFocus()) SetFocus();
	if(!GetCtrl()) return;
	Ctrl& c = *GetCtrl();
	
	int i = zdelta/120;

	for(; i<0; ++i)
	{
		Ctrl* p = c.GetNext();
		c.GetParent()->AddChild(&c, p);
		c.Refresh();
	}
	for(; i>0; --i)
	{
		Ctrl* p = c.GetPrev();
		c.GetParent()->AddChildBefore(&c, p);
		c.Refresh();
	}
	
}

void CtrlPos::Updated()
{
	//refresh the view of the currently selected ctrl
}

void CtrlPos::State(int reason)
{
	if(reason != ENABLE) return;
	if(!IsEnabled()) { ClearCtrl(); Refresh(); }
}

void CtrlPos::Clear()
{
	V::Clear();
	Refresh();	
}

CtrlPos::CtrlPos()
	: pressed(false), moving(false), mode(RectCtrl::NONE), g(4,4)
{
	BackPaint();
	style = &RectCtrl::StyleDefault();
	//xpos.SetNull();
	xp.SetNull();
}
