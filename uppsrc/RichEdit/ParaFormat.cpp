#include "RichEdit.h"

NAMESPACE_UPP

struct ParaFormatDlg : public WithParaFormatLayout<TopWindow> {
	ParaFormatting para;

	String header_qtf, footer_qtf;

	void Sync() {
		header_footer.SetFont(StdFont().Bold(header_qtf.GetCount() || footer_qtf.GetCount()));
	}
	
	ParaFormatDlg() {
		CtrlLayoutOKCancel(*this, t_("Paragraph format"));
		ActiveFocus(para.before);
		header_footer << [=] { EditRichHeaderFooter(header_qtf, footer_qtf); Sync(); };
	}
};

void RichEdit::ParaFormat()
{
	ParaFormatDlg d;
	d.para.Set(unit, formatinfo);
	bool hdrftr = !IsSelection();
	d.header_footer.Show(hdrftr);
	if(hdrftr) {
		d.header_qtf = formatinfo.header_qtf;
		d.footer_qtf = formatinfo.footer_qtf;
		d.Sync();
	}
	if(d.Execute() != IDOK || !d.para.IsChanged() &&
	   (!hdrftr || d.header_qtf == formatinfo.header_qtf && d.footer_qtf == formatinfo.footer_qtf))
		return;
	dword v = d.para.Get(formatinfo);
	if(hdrftr) {
		formatinfo.header_qtf = d.header_qtf;
		formatinfo.footer_qtf = d.footer_qtf;
		v |= RichText::HEADER_QTF|RichText::FOOTER_QTF;
	}
	if(v) ApplyFormat(0, v);
}

struct sCompareLess {
	bool operator()(const Value& a, const Value& b) const {
		return CompareNoCase(String(a), String(b)) < 0;
	}
};

void RichEdit::ReadStyles()
{
	int i;
	style.Clear();
	Vector<Uuid> id;
	Vector<String> name;
	for(i = 0; i < text.GetStyleCount(); i++) {
		id.Add(text.GetStyleId(i));
		name.Add(text.GetStyle(i).name);
	}
	IndexSort(name, id, sCompareLess());
	for(i = 0; i < id.GetCount(); i++)
		style.Add(id[i], name[i]);
}

int RichEdit::CompareStyle(const Value& a, const Value& b)
{
	return CompareNoCase(String(a), String(b));
}

void RichEdit::SetStyle()
{
	if(!IsSelection()) {
		NextUndo();
		WithSetStyleLayout<TopWindow> d;
		CtrlLayoutOKCancel(d, t_("Set style"));
		d.newstyle <<= d.Breaker(IDYES);
		d.style.AddKey();
		d.style.AddColumn();
		d.style.NoHeader().NoGrid();
		for(int i = 0; i < text.GetStyleCount(); i++)
			d.style.Add(text.GetStyleId(i), text.GetStyle(i).name);
		d.style.Sort(1, CompareStyle);
		int q = d.style.Find(RichStyle::GetDefaultId());
		if(q >= 0)
			d.style.SetDisplay(q, 0, Single<DisplayDefault>());
		d.style.FindSetCursor(formatinfo.styleid);
		RichStyle cs;
		cs.format = formatinfo;
		cs.format.sscript = 0;
		cs.format.link.Clear();
		cs.format.indexentry.Clear();
		cs.format.language = LNG_ENGLISH;
		cs.format.label.Clear();

		Uuid id;
		switch(d.Run()) {
		case IDCANCEL:
			return;
		case IDOK:
			if(d.style.IsCursor()) {
				id = d.style.GetKey();
				const RichStyle& st = text.GetStyle(id);
				cs.name = st.name;
				cs.next = st.next;
				SaveStyleUndo(id);
				break;
			}
			return;
		case IDYES:
			String newname;
			if(EditText(newname, Format(t_("New style no. %d"), text.GetStyleCount()),
			            "Name", CharFilterAscii128)) {
				cs.name = newname;
				id = Uuid::Create();
				cs.next = id;
				SaveStylesUndo();
				break;
			}
			return;
		}
		text.SetStyle(id, cs);
		ReadStyles();
		formatinfo.styleid = id;
		SaveFormat(GetCursor(), 0);
		text.ReStyle(GetCursor(), id);
		Finish();
	}
}

void RichEdit::Styles()
{
	NextUndo();
	StyleManager s;
	s.Setup(ffs, unit);
	s.Set(text);
	if(s.Execute() != IDOK || !s.IsChanged())
		return;
	SaveStylesUndo();
	SetModify();
	s.Get(text);
	ReadStyles();
	Finish();
}

void RichEdit::ApplyStylesheet(const RichText& r)
{
	NextUndo();
	SaveStylesUndo();
	text.OverrideStyles(r.GetStyles(), false, false);
	ReadStyles();
	Finish();
}

END_UPP_NAMESPACE
