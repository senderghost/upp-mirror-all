#include "Wpp.h"

#define LLOG(x) LOG(x)

static String ReadLine(Socket& s)
{
	String t = s.ReadUntil('\n');
	if(*t.Last() == '\r')
		t.Trim(t.GetCount() - 1);
	LLOG(t);
	return t;
}

bool Http::Read(Socket& http)
{ // Add length sanity check here...
	String s = ReadLine(http);
	Vector<String> h = Split(s, ' '); // Optimize!
	if(h.GetCount() != 3)
		return false;
	method = h[0];
	uri = h[1];
	version = h[2];
	hdrfield.Clear();
	for(;;) {
		s = ReadLine(http);
		if(s.IsEmpty()) break;
		int q = s.Find(':');
		if(q >= 0)
			hdrfield.Add(ToLower(s.Mid(0, q))) = TrimLeft(s.Mid(q + 1));
	}
	return !http.IsError();
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
		request.GetAdd(key) = UrlDecode(last, p);
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
	cookies << "Set-Cookie:" << ' ' << id << '=' << value;
	if(!IsNull(expires))
		cookies << "; " << WwwFormat(expires);
	if(path && *path)
		cookies << "; Path=" << path;
	if(domain && *domain)
		cookies << "; Domain=" << domain;
	if(secure)
		cookies << "; Secure";
	if(httponly)
		cookies << "; HttpOnly";
	cookies << "\r\n";
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
				request.GetAdd(name + ".filename") = filename;
			if(!content_type.IsEmpty())
				request.GetAdd(name + ".content_type") = content_type;
			request.Add(name, String(b, p));
		}
		p += delta;
		while(*p && *p++ != '\n')
			;
	}
}
