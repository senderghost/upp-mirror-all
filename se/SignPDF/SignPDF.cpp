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

//	f.cert = LoadDataFile("C:/u/nos.data/public.pem");
//	f.pkey = LoadDataFile("C:/u/nos.data/private2.pem");
	
	f.name = "John Smith";
	f.location = "Berlin";
	f.reason = "I'd like to sign this pdf";
	f.contact_info = "Email me!";
	
	pdf.DrawText(200, 200, "Hello world!", Serif(200), Magenta());

	String fn = GetHomeDirFile("test.pdf");
	SaveFile(fn, pdf.Finish(f));

	system("acroread " + fn);
}
