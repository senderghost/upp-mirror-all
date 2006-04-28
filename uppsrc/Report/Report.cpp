#include "Report.h"

Report::Report()
{
	Clear();
}

Report::Report(int cx, int cy)
{
	SetPageSize(cx, cy);
}

Report::Report(const Size &sz)
{
	SetPageSize(sz);
}

Report& Report::SetPageSize(Size sz)
{
	page.Clear();
	header = footer = Null;
	headercy = footercy = headerspc = footerspc = 0;
	pagei = -1;
	Page(0);
	Create(sz);
	StartPage(0);
	return *this;
}

void Report::Clear()
{
	SetPageSize(3968, 6074);
}

Draw& Report::Info()
{
	return *this;
}

Rect Report::GetPageRect()
{
	Rect r = GetSize();
	r.top += headercy + headerspc;
	r.bottom -= footercy + footerspc;
	return r;
}

void Report::PaintHF(Draw& w, int y, const char *qtf, int i)
{
	RichText txt = ParseQTF(FormatHF(qtf, i));
	txt.Paint(w, 0, y, GetSize().cx);
}

void Report::StartPage(int i)
{
	DrawingDraw dw;
	PaintHF(dw, 0, header, i);
	PaintHF(dw, GetSize().cy - footercy, footer, i);
	Drawing& g = page.At(i);
	g = dw;
	g.SetSize(GetSize());
	Create(GetSize());
	y = GetPageRect().top;
}

Draw& Report::Page(int i)
{
	ASSERT(i >= 0);
	if(i != pagei) {
		Flush();
		pagei = i;
		while(page.GetCount() <= pagei)
			StartPage(page.GetCount());
		y = GetPageRect().top;
		Create(GetSize());
	}
	return *this;
}

String  Report::FormatHF(const char *s, int pageno)
{
	String result;
	while(*s) {
		if(s[0] == '$' && s[1] == '$') {
			if(s[2] == 'P')
				result.Cat(Format("%d", pageno + 1));
			if(s[2] == 'D')
				result.Cat(Format(GetSysDate()));
			s += 3;
		}
		result.Cat(*s++);
	}
	return result;
}

int Report::GetHeightHF(const char *s)
{
	RichText txt = ParseQTF(FormatHF(s, 9999));
	return txt.GetHeight(GetSize().cx);
}

Report& Report::Header(const char *qtf, int spc)
{
	header = qtf;
	headerspc = spc;
	headercy = GetHeightHF(qtf);
	RestartPage();
	return *this;
}

Report& Report::Footer(const char *qtf, int spc)
{
	footer = qtf;
	footerspc = spc;
	footercy = GetHeightHF(qtf);
	RestartPage();
	return *this;
}

void Report::RestartPage()
{
	page.SetCount(pagei + 1);
	StartPage(pagei);
}

void Report::Flush()
{
	if(pagei >= 0) {
		Drawing dw = GetResult();
		page.At(pagei).Append(dw);
		Create(GetSize());
	}
}

Report& Report::Landscape()
{
	Size sz = GetSize();
	SetPageSize(sz.cy, sz.cx);
	return *this;
}

void Report::Put(const RichText& txt)
{
	PageY py(pagei, y);
	PaintInfo paintinfo;
	paintinfo.top = PageY(0, 0);
	paintinfo.bottom = PageY(INT_MAX, INT_MAX);
	paintinfo.indexentry = Null;
	paintinfo.hyperlink = Null;
	txt.Paint(*this, py, GetPageRect(), paintinfo);
	py = txt.GetHeight(py, GetPageRect());
	Page(py.page);
	y = py.y;
}

void Report::Put(const char *qtf)
{
	Put(ParseQTF(qtf));
}
