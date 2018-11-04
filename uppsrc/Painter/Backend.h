struct SpanSource {
	virtual void Get(RGBA *span, int x, int y, unsigned len) = 0;
	virtual ~SpanSource() {}
};

class ClippingLine : NoCopy {
	byte *data;
	
public:
	void Clear()                         { if(!IsFull()) delete[] data; data = NULL; }
	void Set(const byte *s, int len)     { data = new byte[len]; memcpy(data, s, len); }
	void SetFull()                       { ASSERT(!data); data = (byte *)1; }

	bool IsEmpty() const                 { return !data; }
	bool IsFull() const                  { return data == (byte *)1; }
	operator const byte*() const         { return data; }
	
	ClippingLine()                       { data = NULL; }
	~ClippingLine()                      { Clear(); }
};

struct PainterBackend {
	Rasterizer       rasterizer;
	RGBA            *pixels;
	Size             size;
	RGBA            *PixelLine(int y)          { return pixels + y * size.cx; }
	int              render_cx;
	int              mode;
	Buffer<int16>    subpixel;
	Buffer<RGBA>     span;
	Rectf            view;
	Rectf            preclip = Null;
	int              preclip_serial = -1;
	int              dopreclip;

	Vector<Buffer<ClippingLine>> clip;
	Array<ImageBuffer>           mask;

	void RenderPath(double width, SpanSource *ss, const RGBA& color,
	                const PainterPathInfo& f,
	                const char *path, const char *end,
	                LinearPathConsumer *alt);

	void Init(RGBA *pixels, Size sz, int mode, double offsety);
	
	void DropMask()             { if(mask.GetCount()) mask.Drop(); }
	void DropClip()             { if(clip.GetCount()) clip.Drop(); }
};
