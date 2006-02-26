#ifndef __Debuggers__
#define __Debuggers__

#include <ide/Common/Common.h>

#include <HexView/HexView.h>

#define  IMAGECLASS DbgImg
#define  IMAGEFILE  <ide/Debuggers/Debuggers.iml>
#include <Draw/iml_header.h>

#define  LAYOUTFILE    <ide/Debuggers/Gdb.lay>
#include <CtrlCore/lay.h>

class DbgDisas : public Ctrl {
public:
	virtual void Paint(Draw& w);
	virtual void Layout();
	virtual void LeftDown(Point p, dword);
	virtual void MouseWheel(Point, int zdelta, dword);
	virtual bool Key(dword key, int);
	virtual void GotFocus();
	virtual void LostFocus();

private:
	Index<dword> addr;
	struct Inst : Moveable<Inst> {
		String code;
		String args;
	};

	ScrollBar    sb;
	Vector<Inst> inst;
	Index<dword> taddr;
	int          codecx;
	dword        low, high;
	int          cursor;
	int          ip;
	Image        ipimg;

	Size GetBox() const;
	void Scroll();

	typedef DbgDisas CLASSNAME;

public:
	Callback WhenCursor;
	Callback WhenFocus;

	void  Clear();
	void  Add(dword adr, const String& code, const String& args);
	void  AddT(dword tadr)              { taddr.Add(tadr); }

	void  Set(const String& s);
	bool  InRange(dword adr)            { return addr.Find(adr) >= 0; }
	void  SetCursor(dword adr);
	dword GetCursor() const             { return cursor >= 0 ? addr[cursor] : 0; }
	void  SetIp(dword adr, const Image& img);

	DbgDisas();
};

struct Dbg : Debugger, Ctrl {
	virtual void Stop();
	virtual bool IsFinished();

	One<Host>          host;
	One<SlaveProcess>  dbg;

	FrameBottom<WithRegistersLayout<StaticRect> > regs;

	Vector<String>     regname;
	Vector<Label *>    reglbl;

	DbgDisas           disas;

	EditString         watchedit;
	DropList           frame;
	TabCtrl            tab;
	ArrayCtrl          locals;
	ArrayCtrl          watches;
	ArrayCtrl          autos;
	Label              dlock;

	WithQuickwatchLayout<TopWindow> quickwatch;

	String             file;
	int                line;
	dword              addr;

	FileOut            log;

	void      AddReg(const char *reg, Label *lbl) { regname.Add(reg); reglbl.Add(lbl); }

	String    GetHostPath(const String& path)   { return host->GetHostPath(path); }
	String    GetLocalPath(const String& path)  { return host->GetLocalPath(path); }

	void      Lock();
	void      Unlock();

	String    Cmd(const char *command);
	String    FastCmd(const char *command);

	virtual bool      Result(String& result, const String& s) = 0;

	typedef Dbg CLASSNAME;

	Dbg();
};

struct RedDisplay : public Display {
	void Paint(Draw& w, const Rect& r, const Value& q,
	           Color ink, Color paper, dword s) const;
};

const char *FindTag(const char *txt, const char *tag);
const char *AfterTag(const char *txt, const char *tag);
const char *AfterHeading(const char *txt, const char *heading);
VectorMap<String, String> DataMap(const ArrayCtrl& data);
void MarkChanged(const VectorMap<String, String>& m, ArrayCtrl& data);

struct Gdb : Dbg {
	virtual bool Result(String& result, const String& s);
	virtual void DebugBar(Bar& bar);
	virtual bool SetBreakpoint(const String& filename, int line, const String& bp);
	virtual bool RunTo();
	virtual void Run();
	virtual bool Key(dword key, int count);

	String          autoline;
	bool            firstrun;

	bool      TryBreak(const char *command);
	void      CheckEnd(const char *result);

	void      Step(const char *cmd);

	String    Cmdp(const char *cmdline, bool fr = false);

	void      DoRunTo() { RunTo(); }

	void      SetDisas(const String& text);
	void      SyncDisas(bool fr);

	void      DisasCursor();
	void      DisasFocus();
	void      DropFrames();
	void      ShowFrame();


	String    Print(const String& exp);
	void      Locals();
	void      Watches();
	void      Autos();
	void      Data();

	void      QuickWatch();

	bool      Create(One<Host> host, const String& exefile, const String& cmdline);

	typedef Gdb CLASSNAME;

	virtual ~Gdb();
};

#ifdef COMPILER_MSC
#include "Pdb.h"
#endif

#endif
