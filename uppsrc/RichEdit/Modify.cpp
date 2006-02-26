#include "RichEdit.h"

bool RichEdit::InvalidRange(int l, int h)
{
	return !InSameTxt(text.GetRichPos(min(l, h)), text.GetRichPos(max(l, h)));
}

void RichEdit::AddUndo(UndoRec *ur)
{
	redo.Clear();
	SetModify();
	incundoserial = true;
	while(undo.GetCount() > undosteps)
		undo.DropHead();
	found = false;
	ur->cursor = cursor;
	ur->serial = undoserial;
	undo.AddTail(ur);
}

void RichEdit::SaveStylesUndo()
{
	AddUndo(new UndoStyles(text));
}

void RichEdit::SaveStyleUndo(const Uuid& id)
{
	AddUndo(new UndoStyle(text, id));
}

void RichEdit::SaveFormat(int pos, int count)
{
	Limit(pos, count);
	AddUndo(new UndoFormat(text, pos, count));
}

void RichEdit::SaveFormat()
{
	int pos, count;
	if(IsSelection()) {
		if(tablesel) {
			SaveTable(tablesel);
			return;
		}
		pos = min(cursor, anchor);
		count = abs(cursor - anchor);
	}
	else {
		pos = cursor;
		count = 0;
	}
	SaveFormat(pos, count);
}

void RichEdit::Limit(int& pos, int& count)
{
	int h = pos + count;
	pos = min(GetLength(), pos);
	count = min(GetLength(), h) - pos;
}

void RichEdit::ModifyFormat(int pos, const RichText::FormatInfo& fi, int count)
{
	if(IsReadOnly())
		return;
	Limit(pos, count);
	SaveFormat(pos, count);
	text.ApplyFormatInfo(pos, fi, count);
}

void RichEdit::Remove(int pos, int len, bool joinnext)
{
	if(IsReadOnly())
		return;
	Limit(pos, len);
	if(InvalidRange(pos, pos + len))
		return;
	AddUndo(new UndoRemove(text, pos, len));
	RichText::FormatInfo fmt;
	RichPara::Format f = text.GetRichPos(pos).format;
	if(joinnext)
		fmt.Set(f);
	text.Remove(pos, len);
	if(!joinnext)
		fmt.Set(text.GetRichPos(pos).format);
	fmt.newpage = f.newpage;
	ModifyFormat(pos, fmt, 0);
}

void RichEdit::Insert(int pos, const RichText& txt, bool typing)
{
	if(IsReadOnly())
		return;
	int l = text.GetLength();
	text.Insert(pos, txt);
	l = text.GetLength() - l;
	if(undo.GetCount()) {
		UndoRec& u = undo.Tail();
		if(typing) {
			UndoInsert *ui = dynamic_cast<UndoInsert *>(&u);
			if(ui && ui->length > 0 && ui->typing && ui->pos + ui->length == pos) {
				ui->length += l;
				return;
			}
		}
	}
	AddUndo(new UndoInsert(pos, l, typing));
}

void RichEdit::Undo()
{
	if(IsReadOnly())
		return;
	if(undo.IsEmpty()) return;
	CancelSelection();
	int serial = undo.Tail().serial;
	int c = cursor;
	while(undo.GetCount()) {
		UndoRec& u = undo.Tail();
		if(u.serial != serial) break;
		UndoRec *r = u.GetRedo(text);
		r->serial = u.serial;
		r->cursor = cursor;
		redo.Add(r);
		u.Apply(text);
		c = u.cursor;
		undo.DropTail();
	}
	ReadStyles();
	Move(c);
}

void RichEdit::Redo()
{
	if(IsReadOnly())
		return;
	if(redo.IsEmpty()) return;
	NextUndo();
	CancelSelection();
	int serial = redo.Top().serial;
	int c = cursor;
	while(redo.GetCount()) {
		UndoRec& r = redo.Top();
		if(r.serial != serial) break;
		UndoRec *u = r.GetRedo(text);
		u->serial = r.serial;
		u->cursor = cursor;
		undo.AddTail(u);
		r.Apply(text);
		c = r.cursor;
		redo.Drop();
	}
	ReadStyles();
	Move(c);
}

void RichEdit::Copy()
{
	if(IsSelection()) {
		ClearClipboard();
		if(tablesel) {
			RichTable tab = text.CopyTable(tablesel, cells);
			RichText h;
			h.SetStyles(text.GetStyles());
			h.CatPick(tab);
			h.WriteClipboard();
		}
		else
			text.Copy(min(cursor, anchor), abs(cursor - anchor)).WriteClipboard();
	}
	else
	if(objectpos >= 0) {
		RichObject o = GetRichObject();
		o.GetType().WriteClipboard(o.GetData());
	}
}

void RichEdit::Cut()
{
	if(IsReadOnly())
		return;
	Copy();
	if(IsSelection())
		RemoveSelection();
	else
	if(objectpos >= 0) {
		Remove(cursor, 1);
		Move(cursor, false);
	}
}

void RichEdit::PasteText(const RichText& text)
{
	RemoveSelection();
	Insert(cursor, text, false);
	ReadStyles();
	Move(cursor + text.GetLength(), false);
}

struct ToParaIterator : RichText::Iterator {
	RichPara para;
	bool     space;

	virtual bool operator()(int pos, const RichPara& p) {
		for(int i = 0; i < p.GetCount(); i++) {
			const RichPara::Part& part = p[i];
			if(part.IsText()) {
				const wchar *s = part.text;
				while(*s) {
					while(*s && *s <= ' ') {
						space = true;
						s++;
					}
					const wchar *t = s;
					while(*s > ' ') s++;
					if(s > t) {
						if(space)
							para.Cat(" ", part.format);
						para.Cat(WString(t, s), part.format);
						space = false;
					}
				}
			}
		}
		space = true;
		return false;
	}

	ToParaIterator() { space = false; }
};

void RichEdit::ToPara()
{
	if(IsReadOnly())
		return;
	if(!IsSelection() || tablesel)
		return;
	NextUndo();
	RichText txt = text.Copy(min(cursor, anchor), abs(cursor - anchor));
	ToParaIterator it;
	txt.Iterate(it);
	RichText h;
	h.SetStyles(txt.GetStyles());
	h.Cat(it.para);
	PasteText(h);
}

void RichEdit::RemoveText(int count)
{
	CancelSelection();
	Remove(cursor, count);
	Finish();
}

RichText RichEdit::CopyText(int pos, int count) const
{
	return text.Copy(pos, count);
}

void RichEdit::Paste()
{
	if(IsReadOnly())
		return;
	int stylei = 0;
	RichText clip = RichText::ReadClipboard(formatinfo);
	if(!clip.IsEmpty()) {
		if(clip.GetPartCount() == 1 && clip.IsTable(0)) {
			CancelSelection();
			if(cursorp.table) {
				NextUndo();
				SaveTable(cursorp.table);
				text.PasteTable(cursorp.table, cursorp.cell, clip.GetTable(0));
				Finish();
				return;
			}
		}
		clip.Normalize();
		PasteText(clip);
		return;
	}
	for(int i = 0; i < RichObject::GetTypeCount(); i++) {
		RichObjectType& rt = RichObject::GetType(i);
		Value data = rt.ReadClipboard();
		if(!IsNull(data)) {
			RichPara p;
			p.Cat(RichObject(&rt, data, pagesz), formatinfo);
			RichText clip;
			clip.Cat(p);
			PasteText(clip);
			break;
		}
	}
}

struct RichObjectExchangeSimple : RichObjectExchange
{
	RichObjectExchangeSimple() : write(false) {}

	virtual RichObject GetRichObject() const                  { return object; }
	virtual void       SetRichObject(const RichObject& data)  { object = data; write = true; }

	RichObject         object;
	bool               write;
};

void RichEdit::InsertObject(int type)
{
	RichObjectType& richtype = RichObject::GetType(type);
	RichObjectExchangeSimple simple;
	simple.object = RichObject(&richtype, Value());
	richtype.DefaultAction(simple);
	if(simple.write) {
		RichText::FormatInfo finfo = GetFormatInfo();
		RemoveSelection();
		RichPara p;
		p.Cat(simple.object, finfo);
		RichText clip;
		clip.Cat(p);
		Insert(GetCursor(), clip, false);
		Finish();
	}
}

void RichEdit::ReplaceObject(const RichObject& obj)
{
	Remove(objectpos, 1);
	RichPara p;
	p.Cat(obj, formatinfo);
	RichText clip;
	clip.Cat(p);
	Insert(objectpos, clip, false);
	Finish();
	objectrect = GetObjectRect(objectpos);
}

RichObject RichEdit::GetRichObject() const
{
	return text.GetRichPos(objectpos).object;
}

void RichEdit::SetRichObject(const RichObject& object)
{
	ReplaceObject(object);
}

void RichEdit::Select(int pos, int count)
{
	found = false;
	Move(pos);
	Move(pos + count, true);
}

void RichEdit::InsertLine()
{
	if(IsReadOnly())
		return;
	RichText::FormatInfo b = formatinfo;
	RichText h;
	h.SetStyles(text.GetStyles());
	RichPara p;
	p.format = formatinfo;
	h.Cat(p);
	h.Cat(p);
	bool st = cursorp.paralen == cursorp.posinpara;
	Insert(cursor, h, false);
	anchor = cursor = cursor + 1;
	formatinfo.newpage = false;
	formatinfo.label.Clear();
	if(st) {
		formatinfo.styleid = text.GetStyle(b.styleid).next;
		ApplyFormat(0, RichText::STYLE|RichText::NEWPAGE|RichText::LABEL);
		return;
	}
	ApplyFormat(0, RichText::NEWPAGE|RichText::LABEL);
	objectpos = -1;
}
