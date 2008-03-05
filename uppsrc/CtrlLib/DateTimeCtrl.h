enum
{
	SUNDAY    = 0,
	MONDAY    = 1,
	TUESDAY   = 2,
	WEDNESDAY = 3,
	THURSDAY  = 4,
	FRIDAY    = 5,
	SATURDAY  = 6
};

class FlatButton : public Pusher {
public:
	Image img;
	Color fg, bg, hl;
	bool left;
	bool drawedge;

	FlatButton();

	void DrawFrame(Draw &w, const Rect &r, Color lc, Color tc, Color rc, Color bc);
	virtual void Paint(Draw &w);
	virtual void MouseEnter(Point p, dword kflags) {
		Refresh();
		Pusher::MouseEnter(p, kflags);
	}
	virtual void MouseLeave() {
		Refresh();
		Pusher::MouseLeave();
	}

	FlatButton& SetImage(const Image &_img) {
		img = _img;
		Refresh();
		return *this;
	}

	FlatButton& SetLeft()           { left = true;  return *this; }
	FlatButton& SetRight() 			{ left = false;	return *this; }
	FlatButton& DrawEdge(bool b) 	{ drawedge = b;	return *this; }
};

class FlatSpin : public Ctrl
{
private:
	FlatButton left;
	FlatButton right;
	String text;
	Size tsz;
	Font font;
	bool selected;
	bool selectable;

public:
	FlatSpin();
	void SetText(const String& s);
	void SetTips(const char *tipl, const char *tipr);
	void SetCallbacks(const Callback &cbl, const Callback& cbr);

	FlatSpin& Selectable(bool b = true);
	int GetWidth(const String& s, bool with_buttons = true);
	void SetFont(const Font& fnt);

	virtual void MouseMove(Point p, dword keyflags);
	virtual void MouseLeave();
	virtual void LeftDown(Point p, dword keyflags);
	virtual void Layout();
	virtual void Paint(Draw& w);
	virtual Image CursorImage(Point p, dword keyflags);

	typedef FlatSpin CLASSNAME;
};

class PopUpCtrl : public Ctrl
{
private:
	bool popup;
public:
	PopUpCtrl() : popup(false) {}

	Callback WhenPopDown;
	Callback WhenDeactivate;
	virtual void Deactivate();
	virtual Size ComputeSize() = 0;
	virtual void Reset() {}

	void PopUp(Ctrl *owner, const Rect& rt);
	Size GetPopUpSize() { return ComputeSize(); }

	bool IsPopUp() const;
	void SetPopUp(bool b = true);
};

class Calendar : public PopUpCtrl
{
public:
	struct Style : ChStyle<Style> {
		Color header;

		Color bgmain;
		Color bgtoday;
		Color bgselect;

		Color fgmain;
		Color fgtoday;
		Color fgselect;
		Color outofmonth;
		Color curdate;
		Color today;
		Color selecttoday;
		Color cursorday;
		Color selectday;
		Color line;
		Color dayname;
		Color week;
		Font font;
	};

protected:
	const Style *style;
	const Style *St() const;

private:
	typedef Calendar CLASSNAME;

	FlatSpin spin_year;
	FlatSpin spin_month;
	FlatSpin spin_all;

	static const int cols = 7;
	static const int rows = 6;

	static const Point nullday;
	int bs; //border size
	int hs; //header vertical size
	int ts; //today vertical size
	float colw;
	float rowh;
	int cw, rh;

	int col;
	int row;
	int lastrow;

	int fh;

	int days[rows][cols];

	Point newday;
	Point oldday;
	Point prevday;
	Point curday, firstday;

	String stoday;
	Size sztoday;
	String curdate;

	bool selall;
	bool istoday;
	bool wastoday;
	bool time_mode;
	bool swap_month_year;
	bool one_button;

	Time view;
	Time today;
	Time sel;

	int first_day;

	void OnMonthLeft();
	void OnMonthRight();
	void OnYearLeft();
	void OnYearRight();

	void UpdateFields();

	bool MouseOnToday(Point p);
	bool MouseOnHeader(Point p);

	virtual void LeftDown(Point p, dword keyflags);
	virtual void MouseMove(Point p, dword keyflags);
	virtual void Paint(Draw &w);
	virtual bool Key(dword key, int count);
	virtual void MouseLeave();
	virtual void State(int reason);
	virtual Image CursorImage(Point p, dword keyflags);

	int& Day(int x, int y) { return days[y][x]; }
	int& Day(Point p) 	   { return days[p.y][p.x]; }
	Point GetDay(Point p);

	void RefreshDay(Point p);
	void RefreshToday();
	void RefreshHeader();
	virtual Size ComputeSize();

public:
	Calendar();
	Callback1<Time &> WhenTime;

	static const Style& StyleDefault();

	void Reset();

	int	 DayOfWeek(int day, int month, int year, int zelleroffset = 2);
	int  WeekOfYear(int day, int month, int year);

	virtual Value GetData() const			{ return sel;          }
	virtual void  SetData(const Value& v)   { time_mode ? SetTime((Time) v) : SetDate((Date) v); }

	Date GetDate() const;
	void SetDate(int y, int m, int d);
	void SetDate(const Date &dt);

	Date GetTime() const;
	void SetTime(int y, int m, int d, int h, int n, int s);
	void SetTime(const Time &tm);

	Date GetCursor() const			   { return view; 				  }
	bool HasCursor() const			   { return view.day != 0;        }

	Date GetView() const			   { return Date(view.year, view.month, view.day ? view.day : 1); }
	void SetView(const Time &v);

	Calendar& SetStyle(const Style& s);
	Calendar& SelectAll(bool b = true)     { selall = b; return *this;       }
	Calendar& NoSelectAll()                { selall = false; return *this;   }
	Calendar& FirstDay(int n = MONDAY)     { first_day = n; return *this;    }
	Calendar& TimeMode(bool b = true)      { time_mode = b; return *this;    }
	Calendar& SwapMonthYear(bool b = true) { swap_month_year = b; return *this; }
	Calendar& OneButton(bool b = true)     { one_button = b; return *this;   }
	Calendar& NoOneButton()                { one_button = false; return *this;   }

	void PopUp(Ctrl *owner, Rect &rt);
};

struct LineCtrl : Ctrl
{
	int pos, real_pos;

	virtual void Paint(Draw& w);
	void SetPos(Point p);
	int GetPos();
	void SetPos(int p);

	virtual void LeftDown(Point p, dword keyflags);
	virtual void MouseMove(Point p, dword keyflags);
	virtual void LeftUp(Point p, dword keyflags);
	LineCtrl();
};

class Clock : public PopUpCtrl
{
public:
	struct Style : ChStyle<Style> {
		Color header;
		Color bgmain;
		Color fgmain;

		Color arrowhl;
		Color arrowhour;
		Color arrowminute;
		Color arrowsecond;

		Font font;
	};

protected:
	const Style *style;
	const Style *St() const;

private:
	FlatSpin spin_hour;
	FlatSpin spin_minute;
	EditIntSpin ed_hour, ed_minute;
	LineCtrl ln_hour, ln_minute;

	//int hour, minute, second;
	Time sel;
	int hs;
	int dir;
	bool accept_time;

	struct Line {
		Point s, e;
	};

	struct MinMax {
		int diff;
		int value;
	};

	Line lines[3];
	Size sz;
	Point cm; //circle middle
	Point cf; //circle factor

	int64 cur_time;
	int   cur_line;
	int   prv_line;
	int   cur_hour;
	int   cur_minute;
	int   cur_second;
	int   cur_point;
	int   prv_point;

	bool seconds;
	bool colon;

	void PaintPtr(int n, Draw& w, Point p, double pos, double m, int d, Color color, Point cf);
	void PaintCenteredText(Draw& w, int x, int y, const char *text, Font fnt, Color c);
	void PaintCenteredImage(Draw &w, int x, int y, const Image& img);

	void SetHourEdit();
	void SetMinuteEdit();
	void SetHourLine();
	void SetMinuteLine();
	void SetHourLeft();
	void SetHourRight();
	void SetMinuteLeft();
	void SetMinuteRight();

	MinMax SetMinMax(int v, int min, int max);
	void UpdateFields();
	void UpdateTime();
	int  IncFactor(int dir, int pp, int cp);

	int  GetDir(int prev_point, int cur_point);
	int  GetPointedLine(Point p);
	int  GetPoint(Point p, double tolerance = 4.0);
	bool IsCircle(Point p, Point s, int r);
	bool IsLine(Point s, Point e, Point p, double tolerance = 3.0);
	void CalcSizes();

	void Timer();

public:

	virtual bool Key(dword key, int count);
	virtual void Paint(Draw& w);
	virtual void State(int reason);
	virtual void LeftDown(Point p, dword keyflags);
	virtual void LeftUp(Point p, dword keyflags);
	virtual void MouseMove(Point p, dword keyflags);
	virtual Image CursorImage(Point p, dword keyflags);
	virtual Size ComputeSize();

	virtual Value GetData() const;
	virtual void  SetData(const Value& v);

	Time GetTime() const;
	void SetTime(int h, int n, int s);
	void SetTime(const Time& tm);

	static const Style& StyleDefault();

	void Reset();

	int GetHour() const   { return sel.hour;   }
	int GetMinute() const { return sel.minute; }
	int GetSecond() const { return sel.second; }

	Clock& SetStyle(const Style& s);
	Clock& Seconds(bool b = true)    { seconds = b; return *this; }
	Clock& NoSeconds()               { return Seconds(false); }
	Clock& Colon(bool b = true)      { colon = b; return *this; }
	Clock& NoColon()                 { return Colon(false); }

	Clock();

	typedef Clock CLASSNAME;
};

class CalendarClock : public Ctrl
{
private:
	int mode;

	Size calendar_size;
	Size clock_size;
	Size sz;

public:
	enum {
		MODE_DATE = 0,
		MODE_TIME = 1
	};

	typedef CalendarClock CLASSNAME;

	Calendar calendar;
	Clock clock;

	CalendarClock(int m = MODE_TIME);
	Callback WhenPopDown;

	virtual void Deactivate();
	virtual bool Key(dword key, int count);
	virtual void Layout();

	Size ComputeSize();
	Size GetCalendarClockSize() { return ComputeSize(); }
	void UpdateTime(Time &tm);

	void PopUp(Ctrl *owner, const Rect& rt);
};

template<class T>
class DateTimeCtrl : public T {
	MultiButtonFrame drop;
	CalendarClock cc;

	int mode;

	void OnCalendarChoice() {
		this->SetData(~cc.calendar);
		this->WhenAction();
	}

	void OnClockChoice() {
		this->SetData(~cc.clock);
		this->WhenAction();
	}

	void OnClose() {
		this->SetFocus();
	}

	void OnDrop() {
		if(!this->IsEditable())
			return;

		Size sz = cc.GetCalendarClockSize();

		int width = sz.cx;
		int height = sz.cy;

		Rect rw = Ctrl::GetWorkArea();
		Rect rs = this->GetScreenRect();
		Rect r;
		r.left   = rs.left;
		r.right  = rs.left + width;
		r.top    = rs.bottom;
		r.bottom = rs.bottom + height;

		if(r.bottom > rw.bottom)
		{
			r.top = rs.top - height;
			r.bottom = rs.top;
		}
		if(r.right > rw.right)
		{
			int diff;
			if(rs.right <= rw.right)
				diff = rs.right - r.right;
			else
				diff = rw.right - r.right;

			r.left += diff;
			r.right += diff;
		}
		if(r.left < rw.left)
		{
			int diff = rw.left - r.left;
			r.left += diff;
			r.right += diff;

		}
		cc.PopUp(this, r);
		cc.calendar <<= this->GetData();
		cc.clock <<= this->GetData();
	}

public:
	typedef DateTimeCtrl CLASSNAME;

	DateTimeCtrl(int m) : cc(m) {
		drop.AddTo(*this);
		drop.AddButton().Main() <<= THISBACK(OnDrop);
		drop.NoDisplay();
		drop.SetStyle(drop.StyleFrame());
		cc.calendar   <<= THISBACK(OnCalendarChoice);
		cc.clock      <<= THISBACK(OnClockChoice);
		cc.WhenPopDown  = THISBACK(OnClose);
	}

	virtual void GotFocus()  { drop.RefreshFrame(); }
	virtual void LostFocus() { drop.RefreshFrame(); }
	virtual Size GetMinSize() const { return drop.GetMinSize(); }

	DateTimeCtrl& SetCalendarStyle(const Calendar::Style& style)   { cc.calendar.SetStyle(style); return *this;  }
	DateTimeCtrl& SetClockStyle(const Clock::Style& style)         { cc.clock.SetStyle(style); return *this;  }
	DateTimeCtrl& SetButtonStyle(const MultiButton::Style& style)  { drop.SetStyle(style); return *this; }
	DateTimeCtrl& SelectAll(bool b = true)                         { cc.calendar.SelectAll(b); return *this;     }
	DateTimeCtrl& NoSelectAll()     						       { cc.calendar.SelectAll(false); return *this; }
	DateTimeCtrl& Seconds(bool b = true)                           { cc.clock.Seconds(b); return *this; }
	DateTimeCtrl& NoSeconds()                                      { cc.clock.Seconds(false); return *this; }
	DateTimeCtrl& Colon(bool b = true)                             { cc.clock.Colon(b); return *this; }
	DateTimeCtrl& NoColon()                                        { cc.clock.Colon(false); return *this; }
	DateTimeCtrl& SwapMonthYear(bool b = true)                     { cc.calendar.SwapMonthYear(b); return *this; }
	DateTimeCtrl& OneButton(bool b = true)                         { cc.calendar.OneButton(true); return *this; }
	DateTimeCtrl& NoOneButton()                                    { cc.calendar.OneButton(false); return *this; }
};

class DropDate : public DateTimeCtrl<EditDate>
{
public:
	DropDate();
	DropDate& SetDate(int y, int m, int d);
};

class DropTime : public DateTimeCtrl<EditTime>
{
public:
	DropTime();
	DropTime& SetTime(int y, int m, int d, int h, int n, int s);
};
