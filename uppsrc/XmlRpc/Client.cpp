#include "XmlRpc.h"

#define LLOG(x)  // LOG(x)

XmlRpcCall& XmlRpcCall::URL(const char *url)
{
	shorted = true;
	if(url && *url) {
		server.URL(url);
		shorted = false;
	}
	shouldExecute = true;
	return *this;
}

XmlRpcCall& XmlRpcCall::Method(const char *name)
{
	shouldExecute = true;
	method = name;
	data.Reset();
	error.Clear();
	return *this;
}

XmlRpcCall::XmlRpcCall(const char *url)
{
	URL(url);
	server.ContentType("text/xml");
	timeout = 30000;
}

XmlRpcCall::XmlRpcCall()
{
	URL(NULL);
	server.ContentType("text/xml");
	timeout = 30000;
}

String XmlRpcExecute(const String& request, const char *group, const char *peeraddr);

Value XmlRpcCall::Execute()
{
	if(!shouldExecute)
		return Value();
	shouldExecute = false;
	String request = XmlHeader();
	request << XmlTag("methodCall")(XmlTag("methodName")(method) + FormatXmlRpcParams(data.out));
	String response;
	if(shorted)	
		response = XmlRpcExecute(request, "", "127.0.0.1");
	else
		response = server.Post(request).TimeoutMsecs(timeout).ExecuteRedirect();
	LLOG("response: " << response);
	if(IsNull(response)) {
		faultCode = XMLRPC_CLIENT_HTTP_ERROR;
		faultString = server.GetError();
		error = "Http request failed: " + faultString;
		LLOG(error);
		return ErrorValue(error);
	}
	XmlParser p(response);
	try {	
		p.ReadPI();
		p.PassTag("methodResponse");
		if(p.Tag("fault")) {
			Value m = ParseXmlRpcValue(p);
			if(IsValueMap(m)) {
				ValueMap mm = m;
				faultString = mm["faultString"];
				faultCode = mm["faultCode"];
				error.Clear();
				error << "Failed '" << faultString << "' (" << faultCode << ')';
				LLOG(s);
				return ErrorValue(error);
			}
		}
		else {
			data.in = ParseXmlRpcParams(p);
			data.ii = 0;
			p.PassEnd();
		}
	}
	catch(XmlError e) {
		String s;
		faultString = e;
		faultCode = XMLRPC_CLIENT_XML_ERROR;
		error.Clear();
		error << "XML Error: " << faultString;
		LLOG(error << ": " << p.GetPtr());
		return ErrorValue(error);
	}
	return data.in.GetCount() ? data.in[0] : Null;
}

void XmlRpcCall::ClearError()
{
	faultCode = 0;
	faultString.Clear();
	error.Clear();
}
