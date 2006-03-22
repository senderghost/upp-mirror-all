#include "LayDes.h"

void ItemProperty::Paint(Draw& w)
{
	Size sz = GetSize();
	w.DrawRect(sz, SWhiteGray);
	w.DrawRect(0, GetHeight() - 1, sz.cx, 1, SBlack);
	w.DrawText(2,
	           (EditField::GetStdHeight() + 6 - w.GetTextSize(name, Arial(11)).cy) / 2, name,
	           GetData() == defval ? Arial(11) : Arial(11).Bold());
}

int ItemProperty::GetHeight() const
{
	return EditField::GetStdHeight() + 5;
}

bool ItemProperty::PlaceFocus(dword, int) { return false; }

void     ItemProperty::Read(CParser& p, byte charset)
{
}

String   ItemProperty::Save(byte charset) const
{
	return Null;
}

VectorMap<String, ItemProperty *(*)()>& ItemProperty::Factory()
{
	return Single< VectorMap<String, ItemProperty *(*)()> >();
}

void ItemProperty::Register(const char *name, ItemProperty *(*cr)())
{
	ASSERT(Factory().Find(name) < 0);
	Factory().Add(name, cr);
}

String ReadPropertyParam(CParser& p)
{
	const char *b = p.GetPtr();
	int level = 0;
	while(!p.IsEof()) {
		if(p.IsChar(';'))
			break;
		if(p.IsChar(')') && level == 0)
			break;
		if(p.Char(')')) {
			if(level == 0)
				break;
			level--;
		}
		else
		if(p.Char('('))
			level++;
		else
			p.SkipTerm();
	}
	return TrimLeft(TrimRight(String(b, p.GetPtr())));
}

ItemProperty *ItemProperty::Create(const String& name)
{
	int q = Factory().Find(name);
	if(q >= 0)
		return (*Factory()[q])();
	return NULL;
}

void RawProperty::Read(CParser& p, byte)
{
	editor.SetData(ToUnicode(ReadPropertyParam(p), CHARSET_WIN1252));
}

String RawProperty::Save(byte) const
{
	String s = ~editor;
	CParser p(s);
	int level = 0;
	while(!p.IsEof()) {
		if(p.Char('('))
			level++;
		else
		if(p.Char(')'))
			level--;
		else
			p.SkipTerm();
	}
	if(level < 0)
		s = String('(', -level) + s;
	else
		s = String(')', level) + s;
	return s;
}

struct IntProperty : public EditorProperty<EditInt> {
	virtual void   Read(CParser& p, byte) {
		if(p.Id("Null"))
			editor.SetData(Null);
		else
			editor.SetData(p.ReadInt());
	}
	virtual String Save(byte) const {
		int q = ~editor;
		return IsNull(q) ? "Null" : AsString(q);
	}

	IntProperty() {
		Add(editor.HSizePos(100, 2).TopPos(2));
	}

	static ItemProperty *Create() { return new IntProperty; }
};

struct DoubleProperty : public EditorProperty<EditDouble> {
	virtual void   Read(CParser& p, byte) {
		if(p.Id("Null"))
			editor.SetData(Null);
		else
			editor.SetData(p.ReadDouble());
	}
	virtual String Save(byte) const {
		return FormatDouble(~editor, 10);
	}

	DoubleProperty() {
		Add(editor.HSizePos(100, 2).TopPos(2));
	}

	static ItemProperty *Create() { return new DoubleProperty; }
};

struct StringProperty : public EditorProperty<EditString> {
	virtual void     Read(CParser& p, byte) {
		if(p.Id("Null"))
			editor.SetData(Null);
		else
			editor.SetData(p.ReadString());
	}
	virtual String   Save(byte) const {
		return AsCString(~editor);
	}
	StringProperty() {
		Add(editor.HSizePos(100, 2).TopPos(2));
	}

	static ItemProperty *Create() { return new StringProperty; }
};

struct BoolProperty : public EditorProperty<Option> {
	virtual void Read(CParser& p, byte) {
		if(p.Id("true"))
			editor.SetData(1);
		else {
			p.Id("false");
			editor.SetData(0);
		}
	}
	virtual String   Save(byte) const {
		return (int)~editor ? "true" : "false";
	}
	BoolProperty() {
		Add(editor.HSizePos(100, 2).TopPos(3));
	}

	static ItemProperty *Create() { return new BoolProperty; }
};

struct ColorProperty : public EditorProperty<ColorPusher> {
	virtual String   Save(byte) const           { return FormatColor(~editor); }
	virtual void     Read(CParser& p, byte);

	void FontChanged();
	void Perform();

	typedef ColorProperty CLASSNAME;

	ColorProperty() {
		Add(editor.HSizePos(100, 2).TopPos(2));
		editor.WithText().SColors().NullText("Null").Track();
	}

	static ItemProperty *Create() { return new ColorProperty; }
};

void ColorProperty::Read(CParser& p, byte)
{
	if(p.Id("Null")) {
		editor.SetData(Null);
		return;
	}
	p.Char(':');
	editor.SetData(ReadColor(p));
}

INITBLOCK
{
	ItemProperty::Register("raw", RawProperty::Create);
	ItemProperty::Register("int", IntProperty::Create);
	ItemProperty::Register("double", DoubleProperty::Create);
	ItemProperty::Register("String", StringProperty::Create);
	ItemProperty::Register("bool", BoolProperty::Create);
	ItemProperty::Register("Color", ColorProperty::Create);

	void RegisterTextProperties(); RegisterTextProperties();
	void RegisterFontProperty(); RegisterFontProperty();
}
