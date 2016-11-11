#include "Tutorial.h"

CONSOLE_APP_MAIN
{
	void Logging(); Logging();
	
	String log = LoadFile(GetStdLogPath());
	StringStream ss(log);

	String sourcefile;
	Vector<String> source;
	bool   newfile = true;
	int    li = 0;

	while(!ss.IsEof()) {
		String ln = ss.GetLine();
		if(ln.StartsWith("-=>")) {
			String path, line;
			SplitTo(ln.Mid(4), '@', path, line);
			
			if(path != sourcefile) {
				sourcefile = path;
				li = 0;
				source = Split(Filter(LoadFile(path), [](int c)->int { return c == '\r' ? 0 : c; }), '\n', false);
				newfile = true;
			}
			
			int ln = atoi(line) - 1;
			while(li < source.GetCount() && li <= ln) {
				String h = source[li++];
				if(h.StartsWith("\t//")) {
					while(li < source.GetCount() && !source[li].StartsWith("\t//")) {
						OUT("SRC: " << source[li++]);
					}
					OUT("DOC: " << h.Mid(4));
					newfile = false;
				}
				else
				if(!newfile) {
					while(li < source.GetCount() && !source[li].StartsWith("\t//")) {
						OUT("SRC: " << source[li++]);
					}
				}
			}
		}
		else
		if(sourcefile.GetCount())
			OUT("LOG: " << ln);
	}
}
