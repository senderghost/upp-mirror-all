class Pusher : public Ctrl {
public:
	virtual void   CancelMode();
	virtual void   LeftDown(Point, dword);
	virtual void   MouseMove(Point, dword);
	virtual void   MouseLeave();
	virtual void   LeftRepeat(Point, dword);
	virtual void   LeftUp(Point, dword);
	virtual void   GotFocus();
	virtual void   LostFocus();
	virtual void   State(int);
	virtual String GetDesc();
	virtual bool   Key(dword key, int);
	virtual bool   HotKey(dword key);
	virtual dword  GetAccessKeys() const;
	virtual void   AssignAccessKeys(dword used);

private:
	bool    push:1;
	bool    keypush:1;

	void    EndPush();

protected:
	byte    accesskey;
	String  label;
	Font    font;

	void    KeyPush();
	bool    IsPush() const                                  { return push || keypush; }
	bool    IsKeyPush()                                     { return keypush; }
	bool    FinishPush();

protected:
	virtual void  RefreshPush();
	virtual void  RefreshFocus();
	virtual void  PerformAction();

public:
	Pusher&  SetFont(Font fnt);
	Pusher&  SetLabel(const char *text);

	void     PseudoPush();

	int GetVisualState() const;

	Callback WhenPush;
	Callback WhenRepeat;

	Pusher();
	virtual ~Pusher();
};


class Button : public Pusher {
public:
	virtual void   Paint(Draw& draw);
	virtual bool   Key(dword key, int);
	virtual bool   HotKey(dword key);
	virtual void   MouseEnter(Point, dword);
	virtual void   MouseLeave();
	virtual dword  GetAccessKeys() const;
	virtual void   AssignAccessKeys(dword used);
	virtual void   Layout();
	virtual void   GotFocus();
	virtual void   LostFocus();
	virtual int    OverPaint() const;

public:
	struct Style : ChStyle<Style> {
		Value look[4];
		Color monocolor[4], textcolor[4];
		Point pressoffset;
		int   focusmargin;
		int   overpaint;
		Font  font;
		Image ok, cancel, exit;
	};

protected:
	enum { NORMAL, OK, CANCEL, EXIT };
	const Style *style;
	Image   img;
	bool    monoimg;
	byte    type;

	void  RefreshOK(Ctrl *p);
	const Style *St() const;

public:
	Button&  SetImage(const Image& img);
	Button&  SetMonoImage(const Image& img);

	static const Style& StyleNormal();
	static const Style& StyleOk();
	static const Style& StyleEdge();
	static const Style& StyleLeftEdge();
	static const Style& StyleScroll();

	Button&  SetStyle(const Style& s);
	Button&  AutoStyle();

	Button&  NormalStyle()                        { return SetStyle(StyleNormal()); }
	Button&  EdgeStyle()                          { return SetStyle(StyleEdge()); }
	Button&  LeftEdgeStyle()                      { return SetStyle(StyleLeftEdge()); }
	Button&  ScrollStyle()                        { return SetStyle(StyleScroll()); }

	Button&  Ok();
	Button&  Cancel();
	Button&  Exit();
	Button&  Normal()                             { type = NORMAL; Refresh(); return *this; }

	Button();
	virtual ~Button();
};

Color ButtonMonoColor(int i);

class SpinButtons : public CtrlFrame {
public:
	virtual void FrameLayout(Rect& r);
	virtual void FrameAddSize(Size& sz);
	virtual void FrameAdd(Ctrl& ctrl);
	virtual void FrameRemove();

public:
	struct Style : ChStyle<Style> {
		Button::Style inc;
		Button::Style dec;
		int           width;
	};

private:
	bool         visible;
	const Style *style;

public:
	Button inc;
	Button dec;

	void         Show(bool s = true);

	static const Style& StyleDefault();

	SpinButtons& SetStyle(const Style& s);

	SpinButtons();
	virtual ~SpinButtons();
};

class Option : public Pusher {
public:
	virtual void   Paint(Draw& draw);
	virtual Size   GetMinSize() const;
	virtual void   SetData(const Value& data);
	virtual Value  GetData() const;
	virtual void   MouseEnter(Point, dword);
	virtual void   MouseLeave();

protected:
	virtual void  RefreshPush();
	virtual void  RefreshFocus();
	virtual void  PerformAction();

protected:
	Image  edge, edged;
	int    option;
	bool   switchimage;
	bool   threestate;
	bool   notnull;
	bool   blackedge;

public:
	void   Set(int b);
	int    Get() const                            { return option; }

	operator int() const                          { return option; }
	void operator=(int b)                         { Set(b); }

	Option& BlackEdge(bool b = true)              { blackedge = b; Refresh(); return *this; }
	Option& SwitchImage(bool b = true)            { switchimage = b; Refresh(); return *this; }
	Option& ThreeState(bool b = true)             { threestate = b; notnull = false; return *this; }
	Option& NotNull(bool nn = true)               { notnull = nn; Refresh(); return *this; }
	Option& NoNotNull()                           { return NotNull(false); }

	Option();
	virtual ~Option();
};

class ButtonOption : public Ctrl {
public:
	virtual void  Paint(Draw& w);
	virtual void  LeftDown(Point, dword);
	virtual void  LeftUp(Point, dword);
	virtual void  MouseMove(Point, dword);
	virtual void  MouseEnter(Point, dword);
	virtual void  MouseLeave();
	virtual void  SetData(const Value& v);
	virtual Value GetData() const;
	virtual void  Serialize(Stream& s);

public:
	struct Style : ChStyle<Style> {
		Value look[4];
	};

private:
	Image        image;
	Image        image1;
	const Style *style;
	bool         option;
	bool         push;

public:
	ButtonOption&  SetImage(const Image& img)                 { image = img; Refresh(); return *this; }
	ButtonOption&  SetImage(const Image& m, const Image& m1)  { image = m; image1 = m1; Refresh(); return *this; }
	void operator=(const Image& img)                          { SetImage(img); }

	void Set(bool b)                                          { option = b; UpdateRefresh(); }
	bool Get() const                                          { return option; }

	void operator=(bool b)                                    { Set(b); }
	operator bool() const                                     { return Get(); }

	ButtonOption& SetStyle(const Style& s)                    { style = &s; Refresh(); return *this; }
	ButtonOption& AutoStyle()                                 { style = NULL; Refresh(); return *this; }

	ButtonOption();
};

class Switch : public Ctrl {
public:
	virtual void   Paint(Draw& draw);
	virtual void   CancelMode();
	virtual void   MouseMove(Point p, dword keyflags);
	virtual void   LeftDown(Point p, dword keyflags);
	virtual void   LeftUp(Point p, dword keyflags);
	virtual void   MouseLeave();
	virtual bool   Key(dword key, int count);
	virtual bool   HotKey(dword key);
	virtual dword  GetAccessKeys() const;
	virtual void   AssignAccessKeys(dword used);
	virtual void   SetData(const Value& data);
	virtual Value  GetData() const;
	virtual void   GotFocus();
	virtual void   LostFocus();

public:
	struct Case : Moveable<Case> {
		String label;
		Value  value;
		int    accesskey;
		bool   enabled;

		Case()         { accesskey = 0; enabled = true; }
	};

private:
	Font         font;
	Value        value;
	int          pushindex;
	Array<Case>  cs;
	Vector<int>  posx;
	int          linecy;
	int          light;

	int   GetIndex();
	int   GetIndex(Point p);
	bool  DoHot(dword key);
	void  Updates();
	void  RefreshCase(int i);

	Rect    GetCaseRect(int i) const;
	Rect    GetCheckRect(int i) const;

public:
	Switch& SetLabel(int i, const char *text);
	Switch& SetLabel(const char *text);
	Switch& Set(int i, const Value& val, const char *text);
	Switch& Set(int i, const Value& val);
	Switch& Add(const Value& val, const char *text);
	Switch& Add(const char *text);

	void    EnableCase(int i, bool enable = true);
	void    DisableCase(int i)                                  { EnableCase(i, false); }

	void    EnableValue(const Value& val, bool enable = true);
	void    DisableValue(const Value& val)                      { EnableValue(val, false); }

	void  Reset()                                               { cs.Clear(); }

	const Array<Case>& GetCases() const                         { return cs; }

	operator int() const                                        { return GetData(); }
	void operator=(const Value& v)                              { SetData(v); }

	Switch& SetFont(Font f)                                     { font = f; return *this; }
	Font    GetFont() const                                     { return font; }

	Switch();
	virtual ~Switch();
};

class DataPusher : public Pusher
{
public:
	virtual void   Paint(Draw& draw);

protected:
	const Convert *convert;
	const Display *display;
	Value          data;

protected:
	virtual void   PerformAction();
	virtual void   DoAction();

public:
	Callback       WhenPreAction;

	DataPusher(const Convert& convert = NoConvert(), const Display& display = StdDisplay());
	DataPusher(const Display& display);
	virtual ~DataPusher();

	DataPusher&    SetConvert(const Convert& _convert) { convert = &_convert; Refresh(); return *this; }
	const Convert& GetConvert() const                  { return *convert; }

	DataPusher&    SetDisplay(const Display& _display) { display = &_display; Refresh(); return *this; }
	const Display& GetDisplay() const                  { return *display; }

	virtual Value  GetData() const;
	virtual void   SetData(const Value& value);

	void           SetDataAction(const Value& value);
};
