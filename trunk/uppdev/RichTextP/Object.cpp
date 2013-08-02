#include "RichText.h"

NAMESPACE_UPP

RichObjectType::RichObjectType() {}
RichObjectType::~RichObjectType() {}

String RichObjectType::GetCreateName() const
{
	return Null;
}

Size RichObjectType::GetDefaultSize(const Value& data, Size maxsize) const
{
	if(IsNull(data)) return Size(0, 0);
	Size psz = GetPhysicalSize(data);
	if((psz.cx | psz.cy) == 0)
		psz = 625 * GetPixelSize(data) / 100;
	Size sz;
	for(int i = 1; i < 10000; i++) {
		sz = psz / i;
		if(sz.cx <= maxsize.cx && sz.cy <= maxsize.cy)
			break;
	}
	return sz;
}

Value RichObjectType::Read(const String& s) const
{
	return s;
}

String RichObjectType::Write(const Value& v) const
{
	return v;
}

bool RichObjectType::Accept(PasteClip& clip)
{
	return false;
}

Value RichObjectType::Read(PasteClip& clip)
{
	return Null;
}

String RichObjectType::GetClipFmts() const
{
	return Null;
}

String RichObjectType::GetClip(const Value& data, const String& fmt) const
{
	return Null;
}

void RichObjectType::Menu(Bar& bar, RichObject& data) const {}
void RichObjectType::DefaultAction(RichObject& data) const {}
Size RichObjectType::GetPhysicalSize(const Value& data) const { return Size(0, 0); }
Size RichObjectType::GetPixelSize(const Value& data) const { return Size(1, 1); }
void RichObjectType::Paint(const Value& data, Draw& w, Size sz) const {}

Image RichObjectType::ToImage(const Value& data, Size sz) const
{
	ImageDraw w(sz);
	Paint(data, w, sz);
	return w;
}

String RichObjectType::GetLink(const Value& data, Point pt, Size sz) const
{
	return Null;
}

void RichObject::InitSize(int cx, int cy)
{
	Size sz;
	Size phsz = GetPixelSize();
	if(cx || cy)
		sz = GetRatioSize(phsz, cx, cy);
	else
		sz = phsz;
	if(sz.cx > 2000 || sz.cy > 2000)
		sz = sz.cx > sz.cy ? GetRatioSize(phsz, 2000, 0)
		                   : GetRatioSize(phsz, 0, 2000);
	SetSize(sz);
}

typedef VectorMap<String, RichObjectType *> RichObjectHT;

GLOBAL_VAR(RichObjectHT, RichObject::Map);

void RichObject::NewSerial()
{
	INTERLOCKED {
		static int64 s;
		serial = ++s;
	}
}

void RichObject::Register(const char *name, RichObjectType *type)
{
	AssertST();
	Map().FindAdd(name, type);
}

void RichObject::Paint(Draw& w, Size sz) const
{
	if(type)
		type->Paint(data, w, sz);
	else {
		w.DrawRect(sz, SColorFace());
		DrawFrame(w, sz, SColorText());
		w.DrawText(2, 2, type_name);
	}
}

Image RichObject::ToImage(Size sz) const
{
	if(type)
		return type->ToImage(data, sz);
	else {
		ImageDraw w(sz);
		Paint(w, sz);
		return w;
	}
}

struct UnknownRichObject : RichObjectType {
	virtual String GetTypeName(const Value&) const;
};

String UnknownRichObject::GetTypeName(const Value&) const
{
	return Null;
}

const RichObjectType& RichObject::GetType() const
{
	if(type)
		return *type;
	return Single<UnknownRichObject>();
}

void   RichObject::Set(RichObjectType *_type, const Value& _data, Size maxsize)
{
	Clear();
	type = _type;
	if(type) {
		data = _data;
		physical_size = type->GetPhysicalSize(data);
		pixel_size = type->GetPixelSize(data);
		size = type->GetDefaultSize(data, maxsize);
	}
	NewSerial();
}

bool   RichObject::Set(const String& _type_name, const Value& _data, Size maxsize)
{
	NewSerial();
	type_name = _type_name;
	RichObjectType *t = Map().Get(type_name, NULL);
	if(t) {
		Set(t, _data);
		return true;
	}
	else {
		Clear();
		data = _data;
		physical_size = pixel_size = size = Size(64, 64);
	}
	return false;
}

bool   RichObject::Read(const String& _type_name, const String& _data, Size sz)
{
	NewSerial();
	type_name = _type_name;
	RichObjectType *t = Map().Get(type_name, NULL);
	if(t) {
		Clear();
		type = t;
		data = type->Read(_data);
		physical_size = type->GetPhysicalSize(data);
		pixel_size = type->GetPixelSize(data);
		size = sz;
		return true;
	}
	data = _data;
	physical_size = pixel_size = size = sz;
	return false;
}

String RichObject::GetTypeName() const
{
	return type ? type->GetTypeName(data) : type_name;
}

void   RichObject::Clear()
{
	NewSerial();
	keepratio = true;
	type = NULL;
	data = Value();
	size = physical_size = pixel_size = Size(0, 0);
	ydelta = 0;
	type_name.Clear();
}

RichObject::RichObject()
{
	Clear();
}

RichObject::RichObject(RichObjectType *type, const Value& data, Size maxsize)
{
	Set(type, data, maxsize);
}

RichObject::RichObject(const String& type, const Value& data, Size maxsize)
{
	Set(type, data, maxsize);
}

struct RichObjectTypeDrawingCls : public RichObjectType
{
	virtual String GetTypeName(const Value&) const;
	virtual Size   GetPhysicalSize(const Value& data) const;
	virtual Size   GetPixelSize(const Value& data) const;
	virtual void   Paint(const Value& data, Draw& w, Size sz) const;
	virtual Value  Read(const String& s) const;
	virtual String Write(const Value& v) const;

	struct Data
	{
		void    Serialize(Stream& stream);

		Drawing drawing;
		Size    dot_size;
	};
};

RichObjectType *RichObjectTypeDrawing() { return &Single<RichObjectTypeDrawingCls>(); }

void RichObjectTypeDrawingCls::Data::Serialize(Stream& stream)
{
	int version = 1;
	stream % version % dot_size % drawing;
}

String RichObjectTypeDrawingCls::GetTypeName(const Value&) const
{
	return "Drawing";
}

RichObject CreateDrawingObject(const Drawing& dwg, Size dot_size, Size out_size)
{
	RichObjectTypeDrawingCls::Data data;
	data.drawing = dwg;
	data.dot_size = dot_size;
	RichObject obj(RichObjectTypeDrawing(), RawToValue(data));
	if(!IsNull(out_size))
		obj.SetSize(out_size);
	return obj;
}

RichObject CreateDrawingObject(const Drawing& dwg, int cx, int cy)
{
	Size dsz = dwg.GetSize();
	return CreateDrawingObject(dwg, dsz, cx || cy ? GetRatioSize(dsz, cx, cy) : dsz);
}

Size RichObjectTypeDrawingCls::GetPixelSize(const Value& data) const
{
	if(IsTypeRaw<Data>(data))
		return ValueTo<Data>(data).drawing.GetSize(); // dot_size; TRC 08/04/04
	return Size(0, 0);
}

Size RichObjectTypeDrawingCls::GetPhysicalSize(const Value& data) const
{
	if(IsTypeRaw<Data>(data))
		return ValueTo<Data>(data).dot_size;
	return Size(0, 0);
}

Value RichObjectTypeDrawingCls::Read(const String& s) const
{
	Data data;
	StringStream ss(s);
	ss % data;
	if(ss.IsError())
		return Value();
	return RawToValue(data);
}

String RichObjectTypeDrawingCls::Write(const Value& v) const
{
	if(IsTypeRaw<Data>(v))
	{
		StringStream ss;
		ss % const_cast<Data&>(ValueTo<Data>(v));
		return ss;
	}
	return Null;
}

void RichObjectTypeDrawingCls::Paint(const Value& data, Draw& w, Size sz) const
{
	w.DrawRect(sz, White);
	if(IsTypeRaw<Data>(data))
		w.DrawDrawing(Rect(sz), ValueTo<Data>(data).drawing);
}

INITBLOCK {
	RichObject::Register("Drawing", &Single<RichObjectTypeDrawingCls>());
};

struct RichObjectTypePNGCls : public RichObjectType
{
	virtual String GetTypeName(const Value&) const;
	virtual Size   GetPhysicalSize(const Value& data) const;
	virtual Size   GetPixelSize(const Value& data) const;
	virtual void   Paint(const Value& data, Draw& w, Size sz) const;
	virtual Value  Read(const String& s) const;
	virtual String Write(const Value& v) const;
};

RichObjectType *RichObjectTypePNG() { return &Single<RichObjectTypePNGCls>(); }

String RichObjectTypePNGCls::GetTypeName(const Value&) const
{
	return "PING";
}

RichObject CreatePNGObject(const Image& img, Size dot_size, Size out_size)
{
	RichObject obj(RichObjectTypePNG(), PNGEncoder().SaveString(img));
	if(!IsNull(out_size))
		obj.SetSize(out_size);
	return obj;
}

RichObject CreatePNGObject(const Image& img, int cx, int cy)
{
	Size dsz = img.GetSize();
	return CreatePNGObject(img, dsz, cx || cy ? GetRatioSize(dsz, cx, cy) : dsz);
}

Size RichObjectTypePNGCls::GetPixelSize(const Value& data) const
{
	if(IsString(data)) {
		StringStream strm(data);
		One<StreamRaster> ras = StreamRaster::OpenAny(strm);
		if(!!ras)
			return ras->GetSize();
	}
	return Size(0, 0);
}

Size RichObjectTypePNGCls::GetPhysicalSize(const Value& data) const
{
	if(IsString(data)) {
		StringStream strm(data);
		One<StreamRaster> ras = StreamRaster::OpenAny(strm);
		if(!!ras)
			return ras->GetInfo().dots;
	}
	return Size(0, 0);
}

Value RichObjectTypePNGCls::Read(const String& s) const
{
	return s;
}

String RichObjectTypePNGCls::Write(const Value& v) const
{
	return v;
}

void RichObjectTypePNGCls::Paint(const Value& data, Draw& w, Size sz) const
{
	if(IsString(data)) {
		StringStream strm(data);
		One<StreamRaster> ras = StreamRaster::OpenAny(strm);
		if(!!ras) {
			w.DrawRect(sz, White);
			w.DrawImage(Rect(sz), ras->GetImage());
			return;
		}
	}
	w.DrawRect(sz, LtRed());
}

INITBLOCK {
	RichObject::Register("PING", &Single<RichObjectTypePNGCls>());
};

END_UPP_NAMESPACE
