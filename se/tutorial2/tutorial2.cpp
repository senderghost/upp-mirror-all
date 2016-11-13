#include "RichEdit/RichEdit.h"

using namespace Upp;

String out;

String qtf;

#define OUT(x) out << x << '\n';

void FlushLog(Vector<String>& log)
{
	if(log.GetCount() == 0)
		return;
	OUT("============ LOG");
	OUT(Join(log, "\r\n"));
	
	qtf << "&[C* \1" << Join(log, "\n") << "\1&]&";
	log.Clear();
}

void FlushDoc(String& docblock)
{
	if(docblock.GetCount() == 0)
		return;
	OUT("============= DOC");
	OUT(docblock);
	
	qtf << '\1' << docblock << "\1&";
	docblock.Clear();
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

	qtf << "&[C@b \1" << Join(code, "\n") << "\1]&";
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
	
	RichEdit edit;
	edit <<= qtf;
	TopWindow win;
	win.Add(edit.SizePos());
	win.Run();
}
