#include "urepo.h"

namespace Upp {

UrepoConsole::UrepoConsole()
{
	CtrlLayoutExit(*this, "System Console");
	list.NoHeader().NoGrid().NoCursor().AddColumn();
	font = Courier(Ctrl::VertLayoutZoom(12));
	list.SetLineCy(font.Info().GetHeight());
	exit.Hide();
	cancel.Hide();
	cancel << [=] { canceled = true; };
}

void UrepoConsole::AddResult(const String& out)
{
	Vector<String> h = Split(out, CharFilterCrLf);
	for(int i = 0; i < h.GetCount(); i++) {
		String s = "    " + h[i];
		list.Add(AttrText(s).SetFont(font), s);
	}
	list.GoEnd();
}

void UrepoConsole::Log(const Value& s, Color ink)
{
	list.Add(AttrText(s).SetFont(font).NormalInk(ink), s);
}

int UrepoConsole::System(const char *cmd)
{
	if(!IsOpen())
		Open();
	list.Add(AttrText(cmd).SetFont(font().Bold()).Ink(SLtBlue()));
	int ii = list.GetCount();
	LocalProcess p;
	if(!p.Start(cmd))
		return -1;
	String out;
	canceled = false;
	cancel.Show(withcancel);
	while(p.IsRunning() && IsOpen()) {
		String h = p.Get();
		out.Cat(h);
		int lf = out.ReverseFind('\n');
		if(lf >= 0) {
			AddResult(out.Mid(0, lf + 1));
			out = out.Mid(lf + 1);
		}
		ProcessEvents();
		Sleep(h.GetCount() == 0); // p.Wait would be much better here!
		if(canceled)
			break;
	}
	cancel.Hide();
	out.Cat(p.Get());
	AddResult(out);
	ProcessEvents();
	int code = canceled ? -1 : p.GetExitCode();
	if(code)
		while(ii < list.GetCount()) {
			list.Set(ii, 0, AttrText((String)list.Get(ii, 1)).SetFont(font).Ink(SLtRed()));
			ii++;
		}
	return code;
}

int UrepoConsole::CheckSystem(const char *s)
{
	int exitcode = System(s);
	if(exitcode) {
		if(exitcode < 0)
			AddResult("Error running " + String(s));
		else
			AddResult("exitcode = " + FormatInt(exitcode));
	}
	return exitcode;
}

int UrepoConsole::Git(const char *dir, const char *command)
{
	String h = GetCurrentDirectory();
	SetCurrentDirectory(dir);
	int code = CheckSystem(String() << "git " << command);
	SetCurrentDirectory(h);
	return code;
}

};