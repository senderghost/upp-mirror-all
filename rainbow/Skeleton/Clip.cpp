#include <CtrlCore/CtrlCore.h>
#include <plugin/bmp/bmp.h>

#ifdef GUI_EMPTY

NAMESPACE_UPP

#define LLOG(x)  // LOG(x)

void ClearClipboard()
{
	GuiLock __;
}

void AppendClipboard(int format, const byte *data, int length)
{
	GuiLock __;
}

void AppendClipboard(const char *format, const byte *data, int length)
{
	GuiLock __;
}

void AppendClipboard(const char *format, const String& data)
{
	GuiLock __;
	AppendClipboard(format, data, data.GetLength());
}

void AppendClipboard(const char *format, const Value& data, String (*render)(const Value&))
{
	GuiLock __;
}

String ReadClipboard(const char *format)
{
	GuiLock __;
	return Null;
}

void AppendClipboardText(const String& s)
{
	AppendClipboard("text", ToSystemCharset(s));
}

void AppendClipboardUnicodeText(const WString& s)
{
	AppendClipboard("wtext", (byte *)~s, 2 * s.GetLength());
}

const char *ClipFmtsText()
{
	return "wtext;text";
}

String GetString(PasteClip& clip)
{
	GuiLock __;
	if(clip.Accept("wtext")) {
		String s = ~clip;
		return WString((const wchar *)~s, wstrlen((const wchar *)~s)).ToString();
	}
	if(clip.IsAvailable("text"))
		return ~clip;
	return Null;
}

WString GetWString(PasteClip& clip)
{
	GuiLock __;
	if(clip.Accept("wtext")) {
		String s = ~clip;
		return WString((const wchar *)~s, wstrlen((const wchar *)~s));
	}
	if(clip.IsAvailable("text"))
		return (~clip).ToWString();
	return Null;
}


bool AcceptText(PasteClip& clip)
{
	return clip.Accept(ClipFmtsText());
}

static String sText(const Value& data)
{
	return data;
}

static String sWText(const Value& data)
{
	return Unicode__(WString(data));
}

void Append(VectorMap<String, ClipData>& data, const String& text)
{
	data.GetAdd("text", ClipData(text, sText));
	data.GetAdd("wtext", ClipData(text, sWText));
}

void Append(VectorMap<String, ClipData>& data, const WString& text)
{
	data.GetAdd("text", ClipData(text, sText));
	data.GetAdd("wtext", ClipData(text, sWText));
}

String GetTextClip(const WString& text, const String& fmt)
{
	if(fmt == "text")
		return text.ToString();
	if(fmt == "wtext")
		return Unicode__(text);
	return Null;
}

String GetTextClip(const String& text, const String& fmt)
{
	if(fmt == "text")
		return text;
	if(fmt == "wtext")
		return Unicode__(text.ToWString());
	return Null;
}

String ReadClipboardText()
{
	return ReadClipboardUnicodeText().ToString();
}

WString ReadClipboardUnicodeText()
{
	return Null;
}

bool IsClipboardAvailable(const char *id)
{
	return false;
}

bool IsClipboardAvailableText()
{
	return false;
}

const char *ClipFmtsImage()
{
	static const char *q;
	ONCELOCK {
		static String s = "dib;" + ClipFmt<Image>();
		q = s;
	}
	return q;
}

bool AcceptImage(PasteClip& clip)
{
	GuiLock __;
	return clip.Accept(ClipFmtsImage());
}

Image GetImage(PasteClip& clip)
{
	GuiLock __;
	Image m;
	if(Accept<Image>(clip)) {
		LoadFromString(m, ~clip);
		if(!m.IsEmpty())
			return m;
	}
	return Null;
}

Image ReadClipboardImage()
{
	GuiLock __;
	PasteClip d = Ctrl::Clipboard();
	return GetImage(d);
}

String sImage(const Value& image)
{
	Image img = image;
	return StoreAsString(const_cast<Image&>(img));
}

String GetImageClip(const Image& img, const String& fmt)
{
	GuiLock __;
	if(img.IsEmpty()) return Null;
	if(fmt == ClipFmt<Image>())
		return sImage(img);
	return Null;
}

void AppendClipboardImage(const Image& img)
{
	GuiLock __;
	if(img.IsEmpty()) return;
	AppendClipboard(ClipFmt<Image>(), img, sImage);
}

bool AcceptFiles(PasteClip& clip)
{
	if(clip.Accept("files")) {
		clip.SetAction(DND_COPY);
		return true;
	}
	return false;
}

bool IsAvailableFiles(PasteClip& clip)
{
	return clip.IsAvailable("files");
}

Vector<String> GetFiles(PasteClip& clip)
{
	GuiLock __;
	Vector<String> f;
	return f;
}

bool PasteClip::IsAvailable(const char *fmt) const
{
	return false;
}

String PasteClip::Get(const char *fmt) const
{
	return Null;
}

void PasteClip::GuiPlatformConstruct()
{
}

END_UPP_NAMESPACE

#endif
