#include "Skylark.h"

#define LLOG(x) LOG(x)
#define LTIMING(x) RTIMING(x)

Http::Http(SkylarkApp& app)
:	app(app)
{
	code = 200;
	content_type = "text/html; charset=UTF-8";
	session_dirty = false;
	lang = LNG_ENGLISH;
}

void Http::ParseRequest(const char *p)
{
	while(*p) {
		const char *last = p;
		while(*p && *p != '=' && *p != '&')
			p++;
		String key = UrlDecode(last, p);
		if(*p == '=')
			p++;
		last = p;
		while(*p && *p != '&')
			p++;
		var.GetAdd(key) = UrlDecode(last, p);
		if(*p)
			p++;
	}
}

String HttpResponse(int code, const char *phrase, const String& data, const char *content_type,
                    const char *cookies)
{
	String r;
	r <<
		"HTTP/1.0 " << code << ' ' << phrase << "\r\n"
		"Date: " <<  WwwFormat(GetUtcTime()) << "\r\n"
		"Server: U++\r\n"
		"Content-Length: " << data.GetCount() << "\r\n"
		"Connection: close\r\n"
		<< cookies;
	if(content_type)
		r << "Content-Type: " << content_type << "\r\n";
	r << "\r\n" << data;
	return r;
}

Http& Http::SetRawCookie(const char *id, const String& value, Time expires,
                         const char *path, const char *domain, bool secure,
                         bool httponly)
{
	var.GetAdd(id) = value;
	String& c = cookies.GetAdd(id);
	c.Clear();
	c << "Set-Cookie:" << ' ' << id << '=' << value;
	if(!IsNull(expires))
		c << "; " << WwwFormat(expires);
	c << "; Path=" << (path && *path ? path : "/");
	if(domain && *domain)
		c << "; Domain=" << domain;
	if(secure)
		c << "; Secure";
	if(httponly)
		c << "; HttpOnly";
	c << "\r\n";
	return *this;
}

int Http::Int(const char *id) const
{
	Value v = operator[](id);
	if(v.Is<int>())
		return v;
	if(IsString(v))
		return ScanInt((String)v);
	if(IsNull(v))
		return Null;
	if(IsNumber(v)) {
		double d = v;
		if(d > INT_MIN && d <= INT_MAX)
			return (int)d;
	}
	return Null;
}

int Http::Int(int i) const
{
	return ScanInt(operator[](i));
}

String HttpAsString(const Value& v)
{
	if(v.Is<RawHtmlText>())
		return v.To<RawHtmlText>().text;
	return AsString(v);
}

Http& Http::Content(const char *s, const Value& data)
{
	content_type = s;
	response = HttpAsString(data);
	return *this;
}

Http& Http::operator<<(const Value& s)
{
	response << HttpAsString(s);
	return *this;
}

Http& Http::SetCookie(const char *id, const String& value, Time expires,
                      const char *path, const char *domain, bool secure, bool httponly)
{
	return SetRawCookie(id, UrlEncode(value), expires, path, domain, secure);
}

void Http::ReadMultiPart(const String& buffer)
{
	const char *p = buffer;
	while(p[0] != '-' || p[1] != '-') {
		while(*p != '\n')
			if(*p++ == 0)
				return; // end of file, boundary not found
		p++;
	}
	String delimiter;
	{ // read multipart delimiter
		const char *b = (p += 2);
		while(*p && *p++ != '\n')
			;
		const char *e = p;
		while(e > b && (byte)e[-1] <= ' ')
			e--;
		delimiter = String(b, e);
	}

	int delta = 4 + delimiter.GetLength();
	const char *e = buffer.End();
	if(e - p < delta)
		return;
	e -= delta;
	while(p < e) { // read individual parts
		String filename, content_type, name;
		while(!MemICmp(p, "content-", 8)) { // parse content specifiers
			p += 8;
			if(!MemICmp(p, "disposition:", 12)) {
				p += 12;
				while(*p && *p != '\n')
					if((byte)*p <= ' ')
						p++;
					else { // fetch key-value pair
						const char *kp = p;
						while(*p && *p != '\n' && *p != '=' && *p != ';')
							p++;
						const char *ke = p;
						String value;
						if(*p == '=') {
							const char *b = ++p;
							if(*p == '\"') { // quoted value
								b++;
								while(*++p && *p != '\n' && *p != '\"')
									;
								value = String(b, p);
								if(*p == '\"')
									p++;
							}
							else {
								while(*p && *p != '\n' && *p != ';')
									p++;
								value = String(b, p);
							}
						}
						if(ke - kp == 4 && !MemICmp(kp, "name", 4))
							name = value;
						else if(ke - kp == 8 && !MemICmp(kp, "filename", 8))
							filename = value;
						if(*p == ';')
							p++;
					}
			}
			else if(!MemICmp(p, "type:", 5)) {
				p += 5;
				while(*p && *p != '\n' && (byte)*p <= ' ')
					p++;
				const char *b = p;
				while(*p && *p != '\n')
					p++;
				const char *e = p;
				while(e > b && (byte)e[-1] <= ' ')
					e--;
				content_type = String(b, e);
			}
				;
			while(*p && *p++ != '\n')
				;
		}
		if(*p++ != '\r' || *p++ != '\n')
			return;
		const char *b = p;
		while(p < e) {
			p = (const char *)memchr(p, '\r', e - p);
			if(!p)
				return;
			if(p[0] == '\r' && p[1] == '\n' && p[2] == '-' && p[3] == '-'
				&& !memcmp(p + 4, delimiter, delimiter.GetLength()))
				break;
			p++;
		}
		if(!name.IsEmpty()) { // add variables
			if(!filename.IsEmpty())
				var.GetAdd(name + ".filename") = filename;
			if(!content_type.IsEmpty())
				var.GetAdd(name + ".content_type") = content_type;
			var.Add(name, String(b, p));
		}
		p += delta;
		while(*p && *p++ != '\n')
			;
	}
}

static const char hex_digits[] = "0123456789ABCDEF";

void UrlEncode(StringBuffer& out, const String& s)
{
	static bool ok[256];
	ONCELOCK {
		for(int ch = 0; ch < 256; ch++)
			ok[ch] = IsAlNum(ch) || ch == ',' || ch == '.' || ch == '-' || ch == '_';
	}
	const char *p = s, *e = s.End();
	for(; p < e; p++)
	{
		const char *b = p;
		while(p < e && ok[(byte)*p])
			p++;
		if(p > b)
			out.Cat(b, int(p - b));
		if(p >= e)
			break;
		if(*p == ' ')
			out << '+';
		else
			out << '%' << hex_digits[(*p >> 4) & 15] << hex_digits[*p & 15];
	}
}

void MakeLink(StringBuffer& out, const Vector<String>& part, const Vector<Value>& arg)
{
	LTIMING("MakeLink");
	out.Cat("/");
	for(int i = 0; i < part.GetCount(); i++) {
		const String& p = part[i];
		if(i)
			out << '/';
		int q = (byte)*p;
		if(q < 32) {
			if(q >= 0 && q < arg.GetCount())
				UrlEncode(out, AsString(arg[q]));
		}
		else
			UrlEncode(out, p);
	}
	bool get = false;
	for(int i = 0; i < arg.GetCount(); i++)
		if(IsValueMap(arg[i])) {
			if(get)
				out << '&';
			else
				out << '?';
			get = true;
			ValueMap m = arg[i];
			for(int i = 0; i < m.GetCount(); i++) {
				if(i)
					out << '&';
				UrlEncode(out, AsString(m.GetKeys()[i]));
				out << '=';
				UrlEncode(out, AsString(m.GetValues()[i]));
			}
		}
}

Http& Http::RenderResult(const String& template_name)
{
	LTIMING("Render");
	response << ::Render(GetTemplate(template_name), this, var.GetValues());
	return *this;
}

Http& Http::Redirect(void (*view)(Http&), const Vector<Value>& arg)
{
	Redirect(MakeLink(view, arg));
	return *this;
}

Http& Http::Redirect(void (*view)(Http&))
{
	Vector<Value> arg;
	Redirect(view, arg);
	return *this;
}

Http& Http::Redirect(void (*view)(Http&), const Value& v1)
{
	Vector<Value> arg;
	arg.Add(v1);
	Redirect(view, arg);
	return *this;
}

Http& Http::Redirect(void (*view)(Http&), const Value& v1, const Value& v2)
{
	Vector<Value> arg;
	arg.Add(v1);
	arg.Add(v2);
	Redirect(view, arg);
	return *this;
}
