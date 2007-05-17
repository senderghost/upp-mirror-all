enum {
	CTRL_NORMAL, CTRL_HOT, CTRL_PRESSED, CTRL_DISABLED
};

struct CtrlsImgLook : Vector<Value> { // deprecated - remove after refactoring chameleon
	CtrlsImgLook& operator()(int i, int n = 4);
	CtrlsImgLook& operator()(int i, const Image& img, Color (*fn)(int i), int n = 4);
	CtrlsImgLook& operator()(int i, const Image& img, int n = 4);
	CtrlsImgLook(int i, int n = 4);
	CtrlsImgLook(int i, const Image& img, Color (*fn)(int i), int n = 4);
	CtrlsImgLook(int i, const Image& img, int n = 4);
};

void CtrlsImageLook(Value *look, int i, int n = 4);
void CtrlsImageLook(Value *look, int i, const Image& image, const Color *color, int n = 4);
void CtrlsImageLook(Value *look, int i, const Image& image, int n = 4);

String DeAmp(const char *s);

Size GetSmartTextSize(const char *text, Font font = StdFont());
int  GetSmartTextHeight(const char *s, int cx, Font font = StdFont());
void DrawSmartText(Draw& w, int x, int y, int cx, const char *text,
                   Font font = StdFont(), Color ink = DefaultInk, int accesskey = 0);

byte  ExtractAccessKey(const char *s, String& label);
bool  CompareAccessKey(byte accesskey, dword key);
byte  ChooseAccessKey(const char *s, dword used);

void DrawFocus(Draw& w, int x, int y, int cx, int cy, Color c = SColorText());
void DrawFocus(Draw& w, const Rect& r, Color c = SColorText());

void DrawHorzDrop(Draw& w, int x, int y, int cx);

Point GetDragScroll(Ctrl *ctrl, Point p, Size max);
Point GetDragScroll(Ctrl *ctrl, Point p, int max = 16);

struct DrawLabel {
	bool      push;
	bool      focus;
	bool      disabled;

	PaintRect paintrect;
	Image     limg;
	Color     lcolor;
	int       lspc;
	String    text;
	Font      font;
	Color     ink;
	Image     rimg;
	Color     rcolor;
	int       rspc;

	int       align, valign;

	int       accesskey;

	Size      GetSize() const;
	Size      Paint(Draw& w, const Rect& r, bool visibleaccesskey = true) const;
	Size      Paint(Draw& w, int x, int y, int cx, int cy, bool visibleaccesskey = true) const;

	DrawLabel();
};

Image DisabledImage(const Image& img, bool disabled = true);

class LabelBase {
protected:
	virtual void  LabelUpdate();

	DrawLabel   lbl;

public:
	LabelBase&  SetLeftImage(const Image& bmp1, int spc = 0);
	LabelBase&  SetPaintRect(const PaintRect& pr);
	LabelBase&  SetText(const char *text);
	LabelBase&  SetFont(Font font);
	LabelBase&  SetInk(Color color);
	LabelBase&  SetRightImage(const Image& bmp2, int spc = 0);
	LabelBase&  SetAlign(int align);
	LabelBase&  SetVAlign(int align);
	LabelBase&  SetImage(const Image& bmp, int spc = 0)      { SetLeftImage(bmp, spc); return *this; }

	int         GetAlign() const                             { return lbl.align; }
	int         GetVAlign() const                            { return lbl.valign; }
	PaintRect   GetPaintRect() const                         { return lbl.paintrect; }
	String      GetText() const                              { return lbl.text; }
	Font        GetFont() const                              { return lbl.font; }
	Color       GetInk() const                               { return lbl.ink; }

	Size        PaintLabel(Draw& w, const Rect& r,
	                       bool disabled = false, bool push = false, bool focus = false, bool vak = true);
	Size        PaintLabel(Draw& w, int x, int y, int cx, int cy,
	                       bool disabled = false, bool push = false, bool focus = false, bool vak = true);
	Size        GetLabelSize() const;

	virtual ~LabelBase();
};

class DisplayPopup : Ctrl {
	virtual void  Paint(Draw& w);
	virtual void  LeftDown(Point p, dword);
	virtual void  LeftDrag(Point p, dword);
	virtual void  LeftDouble(Point p, dword);
	virtual void  RightDown(Point p, dword);
	virtual void  LeftUp(Point p, dword);
	virtual void  MouseWheel(Point p, int zdelta, dword keyflags);
	virtual void  MouseLeave();
	virtual void  MouseMove(Point p, dword);

private:
	Ptr<Ctrl>      ctrl;
	Rect           item;
	Rect           slim;

	Value          value;
	Color          paper, ink;
	dword          style;
	const Display *display;
	int            margin;

	Point   Op(Point p);
	void    Sync();

public:
	void Set(Ctrl *ctrl, const Rect& item, const Value& v, const Display *display,
	         Color ink, Color paper, dword style, int margin = 0);
	void Cancel();
	bool IsOpen();
	bool HasMouse();

	DisplayPopup();
};
