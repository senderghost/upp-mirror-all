#include <Core/Core.h>

using namespace Upp;

void Error()
{
	LOG("Error!");
	Exit(1);
}

CONSOLE_APP_MAIN
{
	StdLogSetup(LOG_COUT|LOG_FILE);

	String pdf = LoadFile("/home/centrum/pdf/21328261signed.pdf");
	
	int q = pdf.FindAfter("/Contents <");
	if(q < 0)
		Error();
	
	String hex;
	while(IsXDigit(pdf[q])) {
		hex.Cat(pdf[q++]);
	}
	
	DDUMP(hex);
	
	q = pdf.FindAfter("/ByteRange [");
	if(q < 0)
		Error();
	CParser p(~pdf + q);
	
	int pos1 = p.ReadInt();
	int len1 = p.ReadInt();
	int pos2 = p.ReadInt();
	int len2 = p.ReadInt();
	
	DDUMP(pos1);
	DDUMP(len1);
	DDUMP(pos2);
	DDUMP(len2);
	
	SaveFile("/home/centrum/pdf/content", pdf.Mid(pos1, len1) + pdf.Mid(pos2, len2));
	SaveFile("/home/centrum/pdf/signature", ScanHexString(hex));

	const char *cmd =
	"openssl smime -verify -noverify "
	"-content ~/pdf/content "
	"-inform der -in ~/pdf/signature -out outfile";
	
	LOG(cmd);
	
	int code = system(cmd);
	
	DUMP(code);
	
	ASSERT(code == 0);
}
