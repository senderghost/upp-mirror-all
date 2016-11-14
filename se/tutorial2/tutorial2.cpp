#include "RichEdit/RichEdit.h"

using namespace Upp;

String out;

int    major = 0;
int    minor = 0;
String qtf =
"[ $$0,0#00000000000000000000000000000000:Default]"
"[a83;*R6 $$1,3#31310162474203024125188417583966:caption]"
"[H4;b83;*4 $$2,3#07864147445237544204411237157677:title]"
"[b42;a42;ph2 $$3,3#45413000475342174754091244180557:text]"
"[l321;C@5;1 $$4,4#20902679421464641399138805415013:code]"
"[l321;b83;a83;*C$7;2 $$5,5#07531550463529505371228428965313:result`-line]"
"[l321;*C$7;2 $$6,6#03451589433145915344929335295360:result]"
"[b73;*3 $$2,3#07864147445237544204111237153677:subtitle]"
;

#define OUT(x) out << x << '\n';

void FlushDoc(String& docblock)
{
	docblock = TrimBoth(docblock);
	if(docblock.GetCount() == 0)
		return;
	OUT("============= DOC");
	OUT(docblock);
	
	String style = "[s3;";
	if(docblock.StartsWith("..")) {
		docblock = AsString(major) + "." + AsString(++minor) + ' ' + TrimBoth(docblock.Mid(2));
		style = "[s7;";
	}
	else
	if(docblock.StartsWith(".")) {
		docblock = AsString(++major) + "." + ' ' + TrimBoth(docblock.Mid(1));
		minor = 0;
		style = "[s2;";
	}
	
	qtf << style << " \1" << docblock << "\1&]";
	docblock.Clear();
}

void FlushLog(Vector<String>& log)
{
	if(log.GetCount() == 0)
		return;
	OUT("============ LOG");
	OUT(Join(log, "\r\n"));
	
	qtf << "[s5; \1" << Join(log, "\n") << "\1&]";
	log.Clear();
}

void FlushCode(Vector<String>& code)
{
	while(code.GetCount() && TrimBoth(code[0]).GetCount() == 0)
		code.Remove(0);
	while(code.GetCount() && TrimBoth(code.Top()).GetCount() == 0)
		code.Drop();
	if(code.GetCount() == 0)
		return;
	OUT("============= CODE");
	OUT(Join(code, "\r\n"));

	qtf << "&[s4; \1" << Join(code, "\n") << "\1]&";
	code.Clear();
}

GUI_APP_MAIN
{
	void Logging(); Logging();
	
	String log = LoadFile(GetStdLogPath());
	StringStream ss(log);

	VectorMap<String, Vector<Tuple<int, String>>> logline;

	while(!ss.IsEof()) {
		String ln = ss.GetLine();
		if(ln.StartsWith("-=>")) {
			String path, line;
			SplitTo(ln.Mid(4), '@', path, line);
			logline.GetAdd(path).Add(MakeTuple(atoi(line) - 1, ss.GetLine()));
		}
	}
	
	for(auto& f : ~logline) {
		Sort(f.value);
		
		DDUMPC(f.value);
		
		Vector<String> src = Split(Filter(LoadFile(f.key), [] (int c) { return c == '\r' ? 0 : c; }), '\n', false);
		int i = 0;
		int logi = 0;
		bool wasdoc = false;
		Vector<String> code;
		while(i < src.GetCount()) {
			String block;
			while(i < src.GetCount() && TrimLeft(src[i]).StartsWith("//")) {
				FlushCode(code);
				Vector<String> logblock;
				DDUMP(logi);
				DDUMP(i);
				while(logi < f.value.GetCount() && f.value[logi].a <= i)
					logblock.Add(f.value[logi++].b);
				FlushLog(logblock);
				
				String line = src[i++];
				int q = line.FindAfter("//");
				if(TrimRight(line).GetCount() > q) {
					if(block.GetCount())
						block << ' ';
					block << TrimBoth(line.Mid(q));
				}
				else
					FlushDoc(block);
				wasdoc = true;
			}
			FlushDoc(block);
			while(i < src.GetCount() && !TrimLeft(src[i]).StartsWith("//"))
				code.Add(src[i++]);
			if(!wasdoc)
				code.Clear();
		}
	}
	
	LOG("--------------------------------------------");
	LOG(out);
	
	LOG("--------------------------------------------");
	LOG(qtf);
	
	RichEditWithToolBar edit;
	edit <<= qtf;
	TopWindow win;
	win.Add(edit.SizePos());
	win.Run();
}
