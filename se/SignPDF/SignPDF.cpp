#include <Core/Core.h>
#include <Core/SSL/SSL.h>

#include <PdfDraw/PdfDraw.h>

#include <RichText/RichText.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
	PdfDraw pdf;
	
	PdfSignatureInfo f;

	f.cert = LoadDataFile("server.crt");
	f.pkey = LoadDataFile("server.key");

//	f.cert = LoadFile("C:/u/nos.data/public.pem");
//	f.pkey = LoadFile("C:/u/nos.data/private2.pem");
	
	f.name = "John Smith";
	f.location = "Berlin";
	f.reason = "I'd like to sign this pdf";
	f.contact_info = "Email me!";

	String fn = GetHomeDirFile("test.pdf");
	
	SaveFile(fn, Pdf(ParseQTF(
			"[9* Hello world!&&&[^www.ultimatepp.org^ URL]^^&&&&&[^<<signature>>^ Signature]"
			),
	         Size(3968, 6074), 200, false, &f));
/*	
	pdf.DrawText(200, 200, "Hello world!", Serif(200), Magenta());

	SaveFile(fn, pdf.Finish(&f));
*/
	LaunchWebBrowser(fn);
}
