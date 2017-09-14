#include "NewWebSocket.h"

#define LLOG(x)  DLOG(x)

using namespace Upp;

void WebSocket::Reset()
{
	opcode = 0;
	data.Clear();
	data_pos = 0;
	in_queue.Clear();
	out_queue.Clear();
	out_at = 0;
	max_chunk = 10 * 1024 * 1024;
	socket.Clear();
	error.Clear();
}

void WebSocket2::Error(const String& err)
{
	LLOG("ERROR: " << err);
	error = err;
}

void WebSocket::Accept(TcpSocket& listen_socket)
{
	if(!socket.Accept(listen_socket)) {
		Error("Accept has failed");
		return;
	}
	Reset();
	opcode = HTTP_REQUEST_HEADER;
}

bool WebSocket::ReadHttpHeader()
{
	for(;;) {
		int c = socket.Get();
		if(c < 0)
			return false;
		else
			data.Cat(c);
		if(data.GetCount() == 2 && data[0] == '\r' && data[1] == '\n') { // header is empty
			Error("Empty HTTP header");
			return false;
		}
		if(data.GetCount() >= 3) {
			const char *h = data.Last();
			if(h[0] == '\n' && h[-1] == '\r' && h[-2] == '\n') { // empty ending line after non-empty header
				return true;
			}
		}
		if(data.GetCount() > 100000) {
			Error("HTTP header size exceeded");
			return false;
		}
	}
}

void WebSocket::RequestHeader()
{
	if(ReadHttpHeader()) {
		LLOG(data);
		HttpHeader hdr;
		if(!hdr.Parse(data)) {
			Error("Invalid HTTP header");
			return;
		}
		String dummy;
		hdr.Request(dummy, uri, dummy);
		String key = hdr["sec-websocket-key"];
		if(IsNull(key)) {
			Error("Invalid HTTP header: missing sec-websocket-key");
			return;
		}
	
		byte sha1[20];
		SHA1(sha1, key + "258EAFA5-E914-47DA-95CA-C5AB0DC85B11");
		
		out_queue.AddTail(
			"HTTP/1.1 101 Switching Protocols\r\n"
			"Upgrade: websocket\r\n"
			"Connection: Upgrade\r\n"
			"Sec-WebSocket-Accept: " + Base64Encode((char *)sha1, 20) + "\r\n\r\n"
		);
		
		LLOG("HTTP request header received, sending response");
		data.Clear();
		opcode = READING_FRAME_HEADER;
	}
}

void WebSocket::ResponseHeader()
{
	if(ReadHttpHeader()) {
		LLOG(data);
		if(ToLower(data).Find("upgrade: websocket") < 0) {
			Error("Invalid server response HTTP header");
			return;
		}
		LLOG("HTTP response header received");
		opcode = READING_FRAME_HEADER;
		data.Clear();
	}
}

void WebSocket::FrameHeader()
{
	for(;;) {
		int c = socket.Get();
		if(c < 0)
			return;
		data.Cat(c);
		
		LLOG("Receiving frame header, current header len: " << data.GetCount());

		int ii = 0;
		bool ok = true;
		auto Get = [&]() -> byte {
			if(ii < data.GetCount())
				return data[ii++];
			ok = false;
			return 0;
		};
		auto GetLen = [&](int count) -> int64 {
			int64 len = 0;
			while(count--)
				len = (len << 8) | Get();
			return len;
		};
		int new_opcode = Get();
		length = Get();
		mask = length & 128;
		length &= 127;
		if(length == 127)
			length = GetLen(8);
		if(length == 126)
			length = GetLen(2);
		if(mask) {
			key[0] = Get();
			key[1] = Get();
			key[2] = Get();
			key[3] = Get();
		}

		if(ok) {
			opcode = new_opcode;
			data.Clear();
			data_pos = 0;
			LLOG("Frame header received, len: " << length << ", code " << opcode);
			return;
		}
	}
}

void WebSocket::FrameData()
{
	Buffer<char> buffer(32768);
	for(;;) {
		int n = socket.Get(~buffer, (int)min(length - data_pos, (int64)32768));
		if(n == 0)
			return;
		if(mask)
			for(int i = 0; i < n; i++) // TODO: Optimize
				buffer[i] ^= key[(i + data_pos) & 3];
		data.Cat(~buffer, n); // TODO: Split long data
		data_pos += n;
		LLOG("Frame data chunk received, chunk len: " << n);
		if(data_pos >= length) {
			LLOG("Frame data received");
			int op = opcode & 15;
			switch(op) {
			case PING:
				LLOG("PING");
				SendRaw(PONG, data);
				break;
			case CLOSE:
				LLOG("CLOSE");
				SendRaw(CLOSE, data);
				break;
			default:
				Input& m = in_queue.AddTail();
				m.fin = opcode & FIN;
				m.text = op == TEXT;
				m.data = data;
				LLOG((m.text ? "TEXT" : "BINARY") << ", input queue count is now " << in_queue.GetCount());
				break;
			}
			data.Clear();
			opcode = READING_FRAME_HEADER;
			return;
		}
	}
}

void WebSocket::Output()
{
	while(out_queue.GetCount()) {
		const String& s = out_queue.Head();
		int n = socket.Put(~s + out_at, s.GetCount() - out_at);
		if(n == 0)
			break;
		LLOG("Sent " << n << " bytes");
		out_at += n;
		if(out_at >= s.GetCount()) {
			out_at = 0;
			out_queue.DropHead();
			LLOG("Block sent complete, " << out_queue.GetCount() << " remaining blocks in queue");
		}
	}
}

void WebSocket::Do()
{
	if(IsError())
		return;
	Output();
	int prev_opcode = opcode;
	switch(opcode) {
	case HTTP_REQUEST_HEADER:
		RequestHeader();
		break;
	case HTTP_RESPONSE_HEADER:
		ResponseHeader();
		break;
	case READING_FRAME_HEADER:
		FrameHeader();
		break;
	default:
		FrameData();
		break;
	}
}

String WebSocket2::PeekMessage()
{
	return in_queue.GetCount() ? in_queue.Head().data : String::GetVoid();
}

String WebSocket2::GetMessage()
{
	if(in_queue.GetCount()) {
		String data = in_queue.Head().data;
		in_queue.DropHead();
		return data;
	}
	return String::GetVoid();
}

int WebSocket2::GetFinIndex() const
{
	for(int i = 0; i < in_queue.GetCount(); i++)
		if(in_queue[i].fin)
			return i;
	return -1;
}

String WebSocket2::PeekFullMessage()
{
	int fi = GetFinIndex();
	if(fi < 0)
		return String::GetVoid();
	String data;
	for(int i = 0; i <= fi; i++)
		data.Cat(in_queue[i].data);
	return data;
}

String WebSocket2::GetFullMessage()
{
	int fi = GetFinIndex();
	if(fi < 0)
		return String::GetVoid();
	String data;
	for(int i = 0; i <= fi; i++) {
		data.Cat(in_queue.Head().data);
		in_queue.DropHead();
	}
	return data;
}

void WebSocket::SendRaw(int hdr, const String& data)
{
	if(IsError())
		return;
	
	String header;
	header.Cat(hdr);
	int len = data.GetCount();
	if(len > 65535) {
		header.Cat(127);
		header.Cat(0);
		header.Cat(0);
		header.Cat(0);
		header.Cat(0);
		header.Cat(byte(len >> 24));
		header.Cat(byte(len >> 16));
		header.Cat(byte(len >> 8));
		header.Cat(byte(len));
	}
	else
	if(len > 125) {
		header.Cat(126);
		header.Cat(byte(len >> 8));
		header.Cat(byte(len));
	}
	else
		header.Cat((int)len);

	out_queue.AddTail(header);
	out_queue.AddTail(data);
}

void WebSocket::Connect(const String& url)
{ // TODO: make async!
	if(!socket.Connect(url, 80)) {
		Error("Connect has failed");
		return;
	}

	String h;
	for(int i = 0; i < 20; i++)
		h.Cat(Random());

	out_queue.AddTail(
		"GET ws://echo.websocket.org HTTP/1.1\r\n" // TODO
		"Host: echo.websocket.org\r\n" // TODO
		"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
		"Accept-Language: cs,en-US;q=0.7,en;q=0.3\r\n"
		"Sec-WebSocket-Version: 13\r\n"
		"Sec-WebSocket-Extensions: permessage-deflate\r\n"
		"Sec-WebSocket-Key: " + Base64Encode(h) + "\r\n"
		"Connection: keep-alive, Upgrade\r\n"
		"Pragma: no-cache\r\n"
		"Cache-Control: no-cache\r\n"
		"Upgrade: websocket\r\n\r\n"
	);
	
	opcode = HTTP_RESPONSE_HEADER;
}
