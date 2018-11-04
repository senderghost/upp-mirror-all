class BufferPainter : public PainterFrontend {
protected:
	virtual void   ClearOp(const RGBA& color);

	virtual void   FillOp(const RGBA& color);
	virtual void   FillOp(const Image& image, const Xform2D& transsrc, dword flags);
	virtual void   FillOp(const Pointf& p1, const RGBA& color1,
	                      const Pointf& p2, const RGBA& color2,
	                      int style);
	virtual void   FillOp(const RGBA& color1, const RGBA& color2, const Xform2D& transsrc,
	                      int style);
	virtual void   FillOp(const Pointf& f, const RGBA& color1,
	                      const Pointf& c, double r, const RGBA& color2,
	                      int style);
	virtual void   FillOp(const Pointf& f, const RGBA& color1, const RGBA& color2,
	                      const Xform2D& transsrc, int style);

	virtual void   StrokeOp(double width, const RGBA& rgba);
	virtual void   StrokeOp(double width, const Image& image, const Xform2D& transsrc,
	                        dword flags);
	virtual void   StrokeOp(double width, const Pointf& p1, const RGBA& color1,
	                        const Pointf& p2, const RGBA& color2,
	                        int style);
	virtual void   StrokeOp(double width, const RGBA& color1, const RGBA& color2,
	                        const Xform2D& transsrc,
	                        int style);
	virtual void   StrokeOp(double width, const Pointf& f, const RGBA& color1,
	                        const Pointf& c, double r, const RGBA& color2,
	                        int style);
	virtual void   StrokeOp(double width, const Pointf& f,
	                        const RGBA& color1, const RGBA& color2,
	                        const Xform2D& transsrc, int style);

	virtual void   ClipOp();

	virtual void   BeginMaskOp();
	virtual void   BeginOnPathOp(double q, bool abs);
	virtual void   EndOp();

private:
	Size                       size;

	LinearPathConsumer        *alt = NULL;
	double                     alt_tolerance = Null;

	Vector<Vector<PathLine>>   onpathstack;
	Vector<double>             pathlenstack;
	
	Image                      gradient;
	RGBA                       gradient1, gradient2;
	int                        gradientn;

	Vector<PathLine>           onpath;
	double                     pathlen;
	
	PainterBackend             backend;
	
	struct CoEntry {
		String          path;
		PainterPathInfo pf;
		double          width;
		RGBA            color;
		int             bands; // how many bands yet have to render this entry, remove head if zero
	};
	
	struct CoBand {
		PainterBackend backend;
		int            at = 0; 
		bool           owned = false; // bands is being rendered on
	};
	
	struct CoWorkNE : CoWork {
		~CoWorkNE() noexcept(true) {}
	};
	
	CoWorkNE           cw;
	Mutex              co_mutex;
	int                co_first = 0;
	BiArray<CoEntry>   co_queue; // queue of commands to do
	Array<CoBand>      co_band; // backends for horizontal bands
	int                co_processors = 0;

	static void      ApproximateChar(LinearPathConsumer& t, const CharData& ch, double tolerance);
	Buffer<ClippingLine> RenderPath(double width, SpanSource *ss, const RGBA& color);
	void             RenderImage(double width, const Image& image, const Xform2D& transsrc,
	                             dword flags);
	void             RenderRadial(double width, const Pointf& f, const RGBA& color1,
	                              const Pointf& c, double r, const RGBA& color2,
	                              const Xform2D& m, int style);
	void             RenderRadial(double width, const Pointf& f, const RGBA& color1, const RGBA& color2,
	                              const Xform2D& transsrc, int style);
	void             MakeGradient(RGBA color1, RGBA color2, int cx);
	void             Gradient(const RGBA& color1, const RGBA& color2, const Pointf& p1, const Pointf& p2);
	void             FinishMask();

public:
//	ImageBuffer&       GetBuffer()                             { return ib; }
//	const ImageBuffer& GetBuffer() const                       { return ib; }


	BufferPainter&     PreClip(bool b = true)                  { backend.dopreclip = dopreclip = b; return *this; }
	BufferPainter&     PreClipDashed()                         { backend.dopreclip = dopreclip = 2; return *this; }
	BufferPainter&     Co();
	
	void Finish()                                              { if(co_band.GetCount()) cw.Finish(); }

	BufferPainter(RGBA *pixels, Size sz, int mode = MODE_ANTIALIASED, int offsety = 0);
	BufferPainter(ImageBuffer& ib, int mode = MODE_ANTIALIASED);
	BufferPainter(LinearPathConsumer& t, double tolerance = Null);
	
	~BufferPainter()                                           { Finish(); }
};

Image CoPaint(Size sz, Event<BufferPainter&> paint, int bands = CPU_Cores());

#include "Interpolator.hpp"
