#include "Hot4d.h"

struct GCode {
	FileOut& out;
	Pt   pos;
	int      speed;
	
	void Put(const String& s) { out.PutLine(s); }
	
	void To(Pt p);
	
	GCode(FileOut& out, int speed) : out(out), pos(0, 0), speed(speed) {};
};

String GFormat(double x)
{
#ifdef _DEBUG
	return Format("%.4f", x);
#else
	return AsString(x);
#endif
}

void GCode::To(Pt p)
{
	Pt d = p - pos;
	if(d.x || d.y) {
		String x = GFormat(d.x);
		String y = GFormat(d.y);
		Put(String() << "G1X" << x << "Y" << y << "Z" << x << "A" << y << "F" << speed);
	}
	pos = p;
}

const char *begin_source_tag = ";<<<source>>>";
const char *end_source_tag = ";>>>source<<<";


bool FourAxisDlg::Save(const char *path)
{
	if(!Accept())
		return false;

	FileOut out(path);

	if(out) {
		GCode gcode(out, ~speed);
		
		gcode.Put("G21");
		gcode.Put("G17");
		gcode.Put("G91");
		
		double k = Nvl((double)~kerf);
		for(auto p : GetPath(k, false))
			gcode.To(p);
		
		gcode.To(Pt(0, 0));

		out.PutLine("");
		DDUMP(MakeSave());
		String s = Base64Encode(MakeSave());
		DDUMP(s.GetCount());
		out.PutLine(begin_source_tag);
		while(s.GetCount()) {
			int n = min(s.GetCount(), 78);
			out.PutLine(';' + s.Mid(0, n));
			s.Remove(0, n);
		}
		out.PutLine(end_source_tag);
		out.PutLine("");

		out.Close();
		
		if(!out.IsError())
			return true;
	}

	Exclamation("Error while saving the file.");
	return false;
}

String FourAxisDlg::MakeSave()
{
	ValueMap m;
	m("type", CurrentShape().GetId())
	 ("data", CurrentShape().Save())
	 ("kerf", (double)~kerf)
	 ("feed", (double)~speed)
	;
	if(IsTapered())
		m("taper", CurrentShape(true).Save())
		 ("panel_width", (double)~panel_width)
		 ("tower_distance", (double)~tower_distance)
		 ("left_gap", (double)~left_gap)
		;
	return AsJSON(m);
}

bool FourAxisDlg::Load(const char *path)
{
	FileIn in(path);
	if(!in)
		return false;
	String src;
	while(!in.IsEof()) {
		String s = in.GetLine();
		if(s == begin_source_tag) {
			while(!in.IsEof()) {
				String l = in.GetLine();
				if(l == end_source_tag)
					break;
				src.Cat(TrimBoth(l.Mid(1)));
			}
			break;
		}
	}
	try {
		DDUMP(Base64Decode(src));
		Value m = ParseJSON(Base64Decode(src));
		int q = shape.Find(m["type"]);
		if(q < 0)
			return false;
		filepath = path;
		type <<= q;
		Type();
		CurrentShape().Load(m["data"]);
		kerf <<= m["kerf"];
		speed <<= m["feed"];
		Value h = m["taper"];
		if(!IsNull(h) && CurrentShape().IsTapered()) {
			tapered <<= true;
			Type();
			CurrentShape(true).Load(h);
			panel_width <<= m["panel_width"];
			tower_distance <<= m["tower_distance"];
			left_gap <<= m["left_gap"];
		}
	}
	catch(ValueTypeError) {
		return false;
	}
	lrufile.NewEntry(filepath);
	lrufile.Limit(16);
	Sync();
	return true;
}

bool FourAxisDlg::OpenS(const String& fp)
{
	if(Load(fp))
		return true;
	Exclamation("Opening [* \1" + fp + "\1] has failed!");
	return false;
}

/*
void FourAxisDlg::OpenFile(const String& fp)
{
	if(filepath.GetCount())
		NewInstance(fp);
	else
		OpenS(fp);
}
*/

void FourAxisDlg::NewInstance(const String& path)
{
	LocalProcess p;
#ifdef PLATFORM_POSIX
	p.DoubleFork();
#endif
	p.Start(Merge(" ", GetExeFilePath(), path));
	p.Detach();
}

void FourAxisDlg::Open()
{
	String fp = SelectFileOpen("*.nc");
	if(fp.GetCount())
		OpenFile(fp);
}

void FourAxisDlg::OpenFile(const String& fp)
{
	if(filepath.GetCount()) {
	#if PLATFORM_WIN32
		String s = Merge(" ", GetExeFilePath() + " " + fp);
		Buffer<char> cmd(s.GetCount() + 1);
		memcpy(cmd, s, s.GetCount() + 1);
		SECURITY_ATTRIBUTES sa;
		sa.nLength = sizeof(SECURITY_ATTRIBUTES);
		sa.lpSecurityDescriptor = NULL;
		sa.bInheritHandle = TRUE;
		PROCESS_INFORMATION pi;
		STARTUPINFO si;
		ZeroMemory(&si, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);
		if(CreateProcess(NULL, cmd, &sa, &sa, TRUE,
			             NORMAL_PRIORITY_CLASS|CREATE_NEW_CONSOLE,
		                 NULL, NULL, &si, &pi)) {
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
		}
	#else
		LocalProcess p;
		p.DoubleFork();
		p.Start(GetExeFilePath() + " " + fp);
		p.Detach();
	#endif
		return;
	}
	OpenS(fp);
}

bool FourAxisDlg::Save()
{
	return Save(filepath);
}

bool FourAxisDlg::SaveAs()
{
	String p = SelectFileSaveAs("*.nc");
	if(p.GetCount() && Save(p)) {
		filepath = p;
		lrufile.NewEntry(filepath);
		Sync();
		return true;
	}
	return false;
}
