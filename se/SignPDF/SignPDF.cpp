#include <Core/Core.h>
#include <Core/SSL/SSL.h>

#include <openssl/bio.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/err.h>

using namespace Upp;

/*
String QtfAsPdf(const RichText& txt, int cx, int cy, int margin)
{
	Size pagesize(cx, cy);
	DrawingPageDraw pd;
	pd.size = pagesize;
	PaintInfo paintinfo;
	paintinfo.top = PageY(0, 0);
	paintinfo.bottom = PageY(INT_MAX, INT_MAX);
	paintinfo.indexentry = Null;
	paintinfo.hyperlink = Null;
	txt.Paint(pd, pagesize, paintinfo);
	pd.Flush();
	return Pdf(pd.page, pagesize, margin);
}

String QtfAsPdf(const String& qtf, int cx, int cy, int margin)
{
	return QtfAsPdf(ParseQTF(qtf), cx, cy, margin);
}
*/

String data;

void Error()
{
	ERR_load_crypto_strings();
	SslStream out;
	ERR_print_errors(out);
	LOG("OpenSSL errors: " << out.GetResult());
	ASSERT(0);
}

String Test1()
{
	SslCertificate x509;
	SslKey pkey;
	if(!x509.Load(LoadFile(GetDataFile("server.crt"))))
		Error();
	if(!pkey.Load(LoadFile(GetDataFile("server.key"))))
		Error();

    BIO *in = BIO_new_file(GetDataFile("SignPDF.cpp"), "rb");

    if (!in)
		Error();

    /* Sign content */
    PKCS7 *p7 = PKCS7_sign(x509, pkey, NULL, in, PKCS7_DETACHED|PKCS7_STREAM|PKCS7_BINARY);

    if (!p7)
        Error();

	SslStream out;
	out.CreateBuffer();
//    out = BIO_new_file("smout.txt", "w");
  //  if (!out)
    //    Error();

    /* Write out S/MIME message */

    if (!SMIME_write_PKCS7(out, p7, in, PKCS7_DETACHED|PKCS7_STREAM|PKCS7_BINARY))
        Error();
  
    BIO_free(in);
  
    DDUMPHEX(out.GetResult());
    DLOG("=================================");
    DDUMP(out.GetResult());
    
    String s = out.GetResult();
    
    String tag = ".p7s\"";
    int pos1 = s.ReverseFind(tag) + tag.GetCount();
    int pos2 = s.Find("----", pos1);
    
    s = s.Mid(pos1, pos2 - pos1);
    DDUMP(s);
    DDUMP(s.GetCount());
    
    String bin = Base64Decode(s);
    
    DDUMP(bin.GetCount());
    DDUMPHEX(bin);
   
    PKCS7_free(p7);
 
	return bin;
}

String Test2()
{
	SslCertificate x509;
	SslKey pkey;
	if(!x509.Load(LoadFile(GetDataFile("server.crt"))))
		Error();
	if(!pkey.Load(LoadFile(GetDataFile("server.key"))))
		Error();

	SslStream in;
	in.OpenBuffer(data, data.GetCount());

    if (!in)
		Error();

    /* Sign content */
    PKCS7 *p7 = PKCS7_sign(x509, pkey, NULL, in, PKCS7_DETACHED|PKCS7_STREAM|PKCS7_BINARY);

    if (!p7)
        Error();

	SslStream out;
	out.CreateBuffer();
//    out = BIO_new_file("smout.txt", "w");
  //  if (!out)
    //    Error();

    /* Write out S/MIME message */

    if (!SMIME_write_PKCS7(out, p7, in, PKCS7_DETACHED|PKCS7_STREAM|PKCS7_BINARY))
        Error();
  
//    BIO_free(in);
  
    DDUMPHEX(out.GetResult());
    DLOG("=================================");
    DDUMP(out.GetResult());
    
    String s = out.GetResult();
    
    String tag = "filename=\"smime.p7s\"";
    int pos1 = s.ReverseFind(tag) + tag.GetCount();
    int pos2 = s.Find("----", pos1);
    
    s = s.Mid(pos1, pos2 - pos1);
    DDUMP(s);
    DDUMP(s.GetCount());
    
    String bin = Base64Decode(s);
    
    DDUMP(bin.GetCount());
    DDUMPHEX(bin);

    PKCS7_free(p7);
    
	return bin;
}

String Test3()
{
	TIMING("Test3");

	SslCertificate x509;
	SslKey pkey;
	if(!x509.Load(LoadFile(GetDataFile("server.crt"))))
		Error();
	if(!pkey.Load(LoadFile(GetDataFile("server.key"))))
		Error();

	SslStream in;
	in.OpenBuffer(data, data.GetCount());

    if (!in)
		Error();

    /* Sign content */
    PKCS7 *p7 = PKCS7_sign(x509, pkey, NULL, in, PKCS7_DETACHED|PKCS7_STREAM|PKCS7_BINARY);

    if (!p7)
        Error();

	SslStream out;
	out.CreateBuffer();
//    out = BIO_new_file("smout.txt", "w");
  //  if (!out)
    //    Error();

    /* Write out S/MIME message */

    if (!SMIME_write_PKCS7(out, p7, in, PKCS7_DETACHED|PKCS7_STREAM|PKCS7_BINARY))
        Error();

	SslStream out1;
	out1.CreateBuffer();
	i2d_PKCS7_bio(out1, p7);
  
//    BIO_free(in);
  
    PKCS7_free(p7);
    
	return out1.GetResult();
}

CONSOLE_APP_MAIN
{
	data = LoadFile(GetDataFile("SignPDF.cpp"));

	String s = Test1();
	ASSERT(s == Test2());
//	ASSERT(s == Test3());
	ASSERT(s == GetP7Signature(data, LoadDataFile("server.crt"), LoadDataFile("server.key")));
	
	DDUMP(GetP7Signature(String(), LoadDataFile("server.crt"), LoadDataFile("server.key")).GetCount());
	DDUMP(GetP7Signature(String("a"), LoadDataFile("server.crt"), LoadDataFile("server.key")).GetCount());
	DDUMP(GetP7Signature(data, LoadDataFile("server.crt"), LoadDataFile("server.key")).GetCount());
	DDUMP(GetP7Signature(data + data, LoadDataFile("server.crt"), LoadDataFile("server.key")).GetCount());
}


#if 0
CONSOLE_APP_MAIN
{
	String data = LoadFile(GetDataFile("SignPDF.cpp"));

	SslCertificate x509;
	if(!x509.Load(LoadFile(GetDataFile("server.crt"))))
		Error();

	SslKey pkey;
	if(!pkey.Load(LoadFile(GetDataFile("server.key"))))
		Error();

	EVP_add_digest(EVP_sha1());

	PKCS7 *p7 = PKCS7_new();

	PKCS7_set_type(p7, NID_pkcs7_signed);
/*	
	PKCS7_SIGNER_INFO *si = PKCS7_add_signature(p7, x509, pkey, EVP_sha1());

	PKCS7_add_signed_attribute(si, NID_pkcs9_contentType, V_ASN1_OBJECT, OBJ_nid2obj(NID_pkcs7_data));

	if(!si) Error();
*/	
	PKCS7_add_certificate(p7, x509);

	PKCS7_content_new(p7, NID_pkcs7_data);

	PKCS7_set_detached(p7, 1);

	BIO *p7bio = PKCS7_dataInit(p7,NULL);

	if(!p7bio)
		Error();

	DDUMP(data.GetCount());
	BIO_write(p7bio, ~data, data.GetCount());

	if (!PKCS7_dataFinal(p7, p7bio)) Error();

	BIO_free(p7bio);
	
	SslStream out1, out2;
	out1.CreateBuffer();
	out2.CreateBuffer();

	i2d_PKCS7_bio(out1, p7);
	PEM_write_bio_PKCS7(out2, p7);

	PKCS7_free(p7);

	DDUMP(HexString(out1.GetResult()));
	
	String pem = out2.GetResult();
	DDUMP(pem);
	
	StringStream ss(pem);
	ss.GetLine();
	String b64;
	for(;;) {
		String s = ss.GetLine();
		if(s.GetCount() == 0 || *s == '-')
			break;
		b64 << s;
	}
	DDUMP(HexString(Base64Decode(b64)));
}
#endif