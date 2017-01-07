#include "Hot4d.h"

struct GCode {
	FileOut& out;
	Pointf   pos;
	int      speed;
	
	void Put(const String& s) { out.PutLine(s); LOG(s); }
	
	void To(Pointf p);
	
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

void GCode::To(Pointf p)
{
	Pointf d = p - pos;
	String x = GFormat(d.x);
	String y = GFormat(d.y);
	Put(String() << "G1X" << x << "Y" << y << "Z" << x << "A" << y << "F" << speed);
	pos = p;
}

const char *begin_source_tag = ";<<<source>>>";
const char *end_source_tag = ";>>>source<<<";

FourAxisDlg::FourAxisDlg()
{
	CtrlLayout(*this, "4 axis CNC G-code generator");
	
	WhenClose = [=] { Exit(); };
	
//	save_as << [=] { Save(); };
	
	speed <<= 140;
	
	for(auto i : { 1, 2, 3, 5, 10, 20, 30, 50, 100 })
		scale.Add(i, AsString(i) + " pixels / mm");
	scale <<= 5;

	AddShape(rod);
	AddShape(text);
	AddShape(angle);
	AddShape(wing);
	
	type << [=] { Type(); };
	type <<= 0;

	arrows.Add(0, "None");
	for(int i = 0; i < 100; i += 4)
		arrows.Add(i, AsString(i));
	arrows <<= 16;
	
	show_shape <<= true;

	for(Ctrl *q = GetFirstChild(); q; q = q->GetNext())
		*q << [=] { Sync(); };

	for(int i = 0; i < shape.GetCount(); i++)
		for(Ctrl *q = shape[i]->GetFirstChild(); q; q = q->GetNext())
			*q << [=] { Sync(); };

	preview.SetFrame(ViewFrame());
	
	kerf.NullText("0");
	
	Type();
}

void FourAxisDlg::Save(const char *path)
{
	if(!Accept())
		return;

	FileOut out(path);

	if(!out)
		return;

	out.PutLine("");
	String s = Base64Encode(MakeSave());
	out.PutLine(begin_source_tag);
	while(s.GetCount()) {
		int n = min(s.GetCount(), 78);
		out.PutLine(';' + s.Mid(0, n));
		s.Remove(0, n);
	}
	out.PutLine(end_source_tag);
	out.PutLine("");
	
	GCode gcode(out, ~speed);
	
	gcode.Put("G21");
	gcode.Put("G17");
	gcode.Put("G91");
	
	double k = Nvl((double)~kerf);
	for(auto p : GetPath(k))
		gcode.To(p);
	
	gcode.To(Pointf(0, 0));
}

String FourAxisDlg::MakeSave()
{
	ValueMap m;
	m("type", CurrentShape().GetId());
	m("data", CurrentShape().Save());
	return AsJSON(m);
}

Shape& FourAxisDlg::CurrentShape()
{
	return *shape[~type];
}

void FourAxisDlg::Type()
{
	for(int i = 0; i < shape.GetCount(); i++)
		shape[i]->Show(~type == i);
	Sync();
}

void FourAxisDlg::AddShape(Shape& s)
{
	shape.Add(s.GetId(), &s);
	type.Add(type.GetCount(), s.GetName());
	shape_dlg.Add(s);
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
	Value m = ParseJSON(Base64Decode(src));
	int q = shape.Find(m["type"]);
	if(q < 0)
		return false;
	filepath = path;
	type <<= q;
	Type();
	CurrentShape().Load(m["data"]);
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

void FourAxisDlg::OpenFile(const String& fp)
{
	if(filepath.GetCount()) {
		LocalProcess p;
	#ifdef PLATFORM_POSIX
		p.DoubleFork();
	#endif
		p.Start(GetExeFilePath() + " " + fp);
		p.Detach();
		return;
	}
	OpenS(fp);
}

void FourAxisDlg::Open()
{
	String fp = SelectFileOpen("*.nc");
	if(fp.GetCount())
		OpenFile(fp);
}

void FourAxisDlg::Save()
{
	Save(filepath);
}

void FourAxisDlg::SaveAs()
{
	filepath = SelectFileSaveAs("*.nc");
	if(filepath.GetCount()) {
		Save(filepath);
		lrufile.NewEntry(filepath);
	}
}

void FourAxisDlg::Exit()
{
	if(filepath.GetCount() == 0)
		SaveAs();
	else
		Save();
	Break();
}

void FourAxisDlg::Serialize(Stream& s)
{
	SerializeGlobalConfigs(s);
	s % lrufile;
}

GUI_APP_MAIN
{
	FourAxisDlg dlg;

	LoadFromFile(dlg);

	const Vector<String>& cmdline = CommandLine();
	int argc = cmdline.GetCount();

	if(argc == 1 && ToLower(GetFileExt(cmdline[0])) == ".nc") {
		PromptOK(cmdline[0]);
		dlg.OpenMain();
		if(!dlg.OpenS(cmdline[0]))
			return;
	}

	dlg.Run();
	
	StoreToFile(dlg);
}
