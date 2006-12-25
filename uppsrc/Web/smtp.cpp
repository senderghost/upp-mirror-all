#include "Web.h"
#pragma hdrstop

NAMESPACE_UPP

//#define SMTP_DEBUG // uncomment this line to turn on LOG-based SMTP emulation
#define SMTP_LOG // uncomment this line to turn on command-line based logging of SMTP communication

static String GetDelimiter(const char *b, const char *e, const String& init = Null)
{
	static const char delimiters[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef"
		"ghijklmnopqrstuvxyz()+/:?0123456"
		"789abcdefghijklmnopqrstuvwxyzABC"
		"DEFGHIJKLMNOPQRSTUVWXYZ012345678";

	String out = init;
	if(b == e)
		return out;
	if(IsNull(out))
		out.Cat(delimiters[*b++ & 0x7F]);
	int l = out.GetLength();
	for(; b != e; b++)
	{
		b = (const char *)memchr(b, *out, e - b);
		if(!b || e - b < l)
			return out;
		if(!memcmp(b, out, l))
		{
			if(e - b == l)
				return out + '/';
			out.Cat(delimiters[b[l] & 0x7F]);
		}
	}
	return out;
}

static void Send(Socket& socket, const String &s, String *transcript = 0, int timeout = 60)
{
#ifdef SMTP_LOG
	puts("Command: " + s);
#endif
	if(transcript && !s.IsEmpty())
	{
		transcript -> Cat(s);
		if(*s.Last() != '\n')
			transcript -> Cat('\n');
	}
#ifdef SMTP_DEBUG
	GetVppLog().Put(s);
	return;
#endif
	dword end_time = (timeout >= 0 ? GetTickCount() + 1000 * timeout : 0xFFFFFFFF);
	const char *p = s.Begin(), *e = s.End();
	while(p != e)
	{
		if(GetTickCount() > end_time)
			throw Exc("Porucha komunikace: vypr�el �asov� limit.");

		int amount = socket.WriteRaw(p, e - p), err;
		if(amount > 0)
		{ // some data has been sent - reset timeout
			p += amount;
			end_time = (timeout >= 0 ? GetTickCount() + 1000 * timeout : 0xFFFFFFFF);
		}
		else if(amount == 0)
			throw Exc("Chyba p�i z�pisu dat do socketu: komunika�n� kan�l byl uzav�en.");
		else if((err = Socket::GetErrorCode()) != SOCKERR(EWOULDBLOCK)) {
			String str;
			throw Exc(str << "Chyba p�i z�pisu dat do socketu, k�d chyby: " << err);
		}
		else
			Sleep(100);
	}
}

static String SendRecv(Socket& socket, const String& s, String *transcript = 0, int timeout = 60)
{
	Send(socket, s, transcript, timeout);
#ifdef SMTP_DEBUG
	return "250 OK";
#endif
	String dest;
	dword end_time = (timeout >= 0 ? GetTickCount() + 1000 * timeout : 0xFFFFFFFF);
	for(;;)
	{
		if(GetTickCount() > end_time)
			throw Exc("Porucha komunikace: vypr�el �asov� limit.");
		char buffer[100];
		int amount = socket.ReadRaw(buffer, sizeof(buffer)), err;
		if(amount > 0)
		{
			dest.Cat(buffer, amount);
			while(--amount >= 0)
				if(buffer[amount] == '\n')
				{
					if(transcript && !dest.IsEmpty())
					{
						transcript -> Cat(dest);
						if(*dest.Last() != '\n')
							transcript -> Cat('\n');
					}
#ifdef SMTP_LOG
					puts("Reply: " + dest);
#endif
					return dest;
				}
		}
		else if(amount == 0)
			throw Exc("Chyba p�i �ten� dat ze socketu: komunika�n� kan�l byl uzav�en.");
		else if((err = Socket::GetErrorCode()) != SOCKERR(EWOULDBLOCK)) {
			String str;
			throw Exc(str << "Chyba p�i �ten� dat ze socketu, k�d chyby: " << err);
		}
		else
			Sleep(100);
	}
}

static void SendRecvOK(Socket& socket, const String& s, String *transcript = 0, int timeout = 60)
{
	String ans = SendRecv(socket, s, transcript, timeout);
	if(ans[0] != '2' || ans[1] != '5' || ans[2] != '0')
		throw Exc(ans);
}

//////////////////////////////////////////////////////////////////////
// SmtpMail::

SmtpMail::SmtpMail()
: port(25)
, no_header(false)
, no_header_sep(false)
, time_sent(GetSysTime())
{
}

static const char default_mime[] = "application/octet-stream";

SmtpMail& SmtpMail::AttachFile(const char *filename, const char *mime)
{
	Attachment& attach = attachments.Add();
	attach.name = GetFileNamePos(filename);
	attach.mime = (mime ? mime : default_mime);
	attach.file = filename;
	return *this;
}

SmtpMail& SmtpMail::Attach(const char *name, String data, const char *mime)
{
	Attachment& attach = attachments.Add();
	attach.name = name;
	attach.mime = (mime ? mime : default_mime);
	attach.data = data;
	return *this;
}

bool SmtpMail::Send()
{
	Socket socket;
	String ipaddr;

	try
	{
		if(IsNull(host))
			throw Exc("Hostitel nen� zad�n.");

		if(to.IsEmpty())
			throw Exc("Nen� zad�n p��jemce.");

#ifdef SMTP_DEBUG
		ipaddr = "1.2.3.4";
#else
		Socket::Init();
		dword my_addr;
		if(!ClientSocket(socket, host, port, true, &my_addr, 10000, true))
			throw Exc(NFormat("Nelze otev��t socket %s:%d: %s", host, port, Socket::GetErrorText()));

		ipaddr
			<< (int)((my_addr >>  0) & 0xFF) << '.'
			<< (int)((my_addr >>  8) & 0xFF) << '.'
			<< (int)((my_addr >> 16) & 0xFF) << '.'
			<< (int)((my_addr >> 24) & 0xFF);
#endif

		String *trans_ptr = (transcript ? &transcript_text : 0);
		String ans;

		// receive initial message & send hello
		SendRecv(socket, Null, trans_ptr, 30);
		String org;
		int pos = from.Find('@');
		if(pos >= 0)
		{
			int start = ++pos, len = from.GetLength();
			while(pos < len && from[pos] != '>')
				pos++;
			org = from.Mid(start, pos - start);
		}
		else
			org << ipaddr;

		SendRecvOK(socket, "HELO " + org + "\r\n", trans_ptr);
		SendRecvOK(socket, "MAIL FROM:<" + from + ">\r\n", trans_ptr);
		for(int i = 0; i < to.GetCount(); i++)
			SendRecv(socket, "RCPT TO:<" + to[i] + ">\r\n", trans_ptr);
		ans = SendRecv(socket, "DATA\r\n", trans_ptr);
#ifndef SMTP_DEBUG
		if(memcmp(ans, "354", 3))
			throw Exc(ans);
#endif

		String delimiter = GetDelimiter(text.Begin(), text.End(), "?");
		bool multi = !attachments.IsEmpty();

		{ // format message
			String msg;
			if(!no_header)
			{ // generate message header
				msg << "From: " << from << "\r\n";
				static const AS as_list[] = { TO, CC, BCC };
				static const char *as_name[] = { "To", "CC", "BCC" };
				for(int a = 0; a < __countof(as_list); a++)
				{
					int pos = 0;
					for(int i = 0; i < as.GetCount(); i++)
						if(as[i] == as_list[a])
						{
							if(pos && pos + to[i].GetLength() >= 70)
							{
								msg << "\r\n     ";
								pos = 5;
							}
							else if(pos)
							{
								msg << ", ";
								pos += 2;
							}
							else
							{
								msg << as_name[a] << ": ";
								pos = strlen(as_name[a]) + 2;
							}
							msg << to[i];
						}
					if(pos)
						msg << "\r\n";
				}
				if(!IsNull(subject))
					msg << "Subject: " << subject << "\r\n";
				if(!IsNull(reply_to))
					msg << "Reply-To: " << reply_to << "\r\n";
				if(!IsNull(time_sent))
				{
					static const char *dayofweek[] =
					{ "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
					static const char *month[] =
					{ "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
					msg << "Date: "
						<< dayofweek[DayOfWeek(time_sent)] << ", "
						<< (int)time_sent.day << ' ' << month[time_sent.month - 1] << ' ' << (int)time_sent.year
						<< ' ' << Sprintf("%2d:%02d:%02d +0100", time_sent.hour, time_sent.minute, time_sent.second)
						<< "\r\n";
				}
				if(multi)
					msg << "Content-Type: Multipart/mixed; boundary=\"" << delimiter << "\"\r\n"
						"\r\n"
						"--" << delimiter << "\r\n"
						"Content-Type: " << (*mime ? ~mime : "text/plain; charset=Windows-1250") << "\r\n"
						"Content-Transfer-Encoding: quoted-printable\r\n"
						;
				if(!no_header_sep)
					msg << "\r\n"; // message separator
			}

			bool begin = true;
			for(const char *p = text.Begin(), *e = text.End(); p != e; p++)
				if(*p >= 33 && *p <= 126 && *p != '=' && (*p != '.' || !begin))
				{
					msg.Cat(*p);
					begin = false;
				}
				else if(*p == '.' && begin)
				{
					msg.Cat("..");
					begin = false;
				}
				else if(*p == ' ' && p + 1 != e && p[1] != '\r' && p[1] != '\n')
				{
					msg.Cat(' ');
					begin = false;
				}
				else if(*p == '\r')
					;
				else if(*p == '\n')
				{
					msg.Cat("\r\n");
					begin = true;
				}
				else
				{
					static const char hex[] = "0123456789ABCDEF";
					msg.Cat('=');
					msg.Cat(hex[(*p >> 4) & 15]);
					msg.Cat(hex[*p & 15]);
				}

			if(!begin)
				msg.Cat("\r\n");
			if(multi)
			{
				for(int i = 0; i < attachments.GetCount(); i++)
				{
					const Attachment& a = attachments[i];
					One<Stream> source;
					if(!IsNull(a.file))
					{
						One<FileIn> fi = new FileIn(a.file);
						if(fi -> IsOpen())
							source = -fi;
					}
					else
						source = new StringStream(a.data);
					msg << "--" << delimiter << "\r\n"
						"Content-Type: " << a.mime << "; name=\"" << a.name << "\"\r\n"
						"Content-Transfer-Encoding: base64\r\n"
						"Content-Disposition: attachment; filename=\"" << a.name << "\"\r\n"
						"\r\n";

					char buffer[54];
					for(int c; (c = source -> Get(buffer, sizeof(buffer))) != 0;)
					{
						msg.Cat(Base64Encode(buffer, buffer + c));
						msg.Cat('\r');
						msg.Cat('\n');
						if(msg.GetLength() >= 65536)
						{
							UPP::Send(socket, msg, trans_ptr);
							msg = Null;
						}
					}
				}
				msg << "--" << delimiter << "--\r\n";
			}
			msg.Cat(".\r\n");
			SendRecvOK(socket, msg, trans_ptr);
		}

		SendRecv(socket, "QUIT\r\n", trans_ptr);
		return true;
	}
	catch(Exc e)
	{
		error = e;
		return false;
	}
}

END_UPP_NAMESPACE
