#include <Core/Core.h>
#include <plugin/lz4/lz4.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
	StdLogSetup(LOG_COUT|LOG_FILE);
	for(int co = 0; co < 2; co++)
		for(int pass = 0; pass < 2; pass++) {
			FileIn in("C:/xxx/xxx/upp-x11-src-9052.tar");
			
			String s;
			LZ4CompressStream lz4;
			StringStream ss;
			lz4.Open(ss);
			lz4.Concurrent(co);
			while(!in.IsEof()) {
				if(pass) {
					s.Cat(in.Term());
					lz4.Put(in.Get());
				}
				else {
					String h = in.Get(Random(2 * 1024*1024));
					s.Cat(h);
					lz4.Put(h);
				}
			}
			lz4.Close();
			
			DDUMP(lz4.IsError());
			
			String c = ss.GetResult();
			String d = LZ4Decompress(c);
			
			DDUMP(c.GetCount());
			DDUMP(s.GetCount());
			DDUMP(d.GetCount());
			
			DDUMPHEX(s.Mid(0, 100));
			DDUMPHEX(d.Mid(0, 100));
			
			SaveFile("c:/xxx/s.bin", s);
			SaveFile("c:/xxx/d.bin", d);
			
			ASSERT(d == s);
		}
	
	DLOG("============== OK");
}
