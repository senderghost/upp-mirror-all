#include <Core/Core.h>

using namespace Upp;

class WebSocket2 {
	String     error;

	TcpSocket  socket;
	
	String     uri;
	IpAddrInfo addrinfo;
	bool       ssl;

	String     data;
	int        data_pos;

	int        max_chunk;

	int        opcode;
	int64      length;
	bool       mask;
	int        key[4];

	struct Input : Moveable<Input> {
		bool   text;
		bool   fin;
		String data;
	};
	
	BiVector<Input>  in_queue;
	
	BiVector<String> out_queue;
	int              out_at;
	
	bool             close_sent;
	bool             close_received;

	enum {
		HTTP_REQUEST_HEADER = -100,
		HTTP_RESPONSE_HEADER = -101,
		READING_FRAME_HEADER = -102,
		DNS = -103,
		SSL_HANDSHAKE = -104,

		FIN = 0x80,
		TEXT = 0x1,
		BINARY = 0x2,
		CLOSE = 0x8,
		PING = 0x9,
		PONG = 0xa,
	};

	void Clear();
	void Error(const String& error);

	void Output();

	void StartConnect();
	void Dns();
	bool ReadHttpHeader();
	void ResponseHeader();
	void RequestHeader();
	void FrameHeader();
	void FrameData();

	int GetFinIndex() const;

	void   SendRaw(int hdr, const String& data);

public:
	WebSocket2& NonBlocking(bool b = true)              { socket.Timeout(b ? 0 : Null); return *this; }
	
	bool   IsError()        { return socket.IsError() || error.GetCount(); }
	String GetError() const { return Nvl(socket.GetErrorDesc(), error); }
	
	void   Do();
	
	void   Accept(TcpSocket& listener_socket);
	void   Connect(const String& url);

	bool   IsContinued() const { return !IsFin(); }
	bool   IsFin() const       { return IsMessage() && in_queue.Head().fin; }

	bool   IsMessage() const   { return in_queue.GetCount(); }
	bool   IsText() const      { return IsMessage() && in_queue.Head().text; }
	bool   IsBinary() const    { return IsMessage() && !in_queue.Head().text; }
	bool   IsFullMessage() const;

	String Peek();
	String Fetch();
	
	String PeekFull();
	String FetchFull();
	
//	bool   IsClosed() const  { return GetOpCode() == CLOSE; }
//	String GetData() const   { return data; }

	bool   IsOutputEmpty() const                   { return out_queue.GetCount() == 0; }

	void   SendText(const String& data)            { SendRaw(FIN|TEXT, data); }
	void   SendBinary(const String& data)          { SendRaw(FIN|BINARY, data); }

	void   SendClose(const String& msg = Null);
	bool   IsClosed()                              { return close_sent && close_received && out_queue.GetCount() == 0; }

	WebSocket2();
};
