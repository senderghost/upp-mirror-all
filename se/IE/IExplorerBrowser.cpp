#include "IE.h" 

#ifdef PLATFORM_WIN32

NAMESPACE_UPP

void InternetExplorerBrowser::Quit()
{
	IIWebBrowser webBrowser(this);
	if(webBrowser)
		webBrowser->Quit();
}

InternetExplorerBrowser::~InternetExplorerBrowser()
{
	Quit();
}


void InternetExplorerBrowser::Created()
{
	IIWebBrowser webBrowser(this);
	if(!webBrowser)
		return;
	
	if(set == SETURL) {
		OleStr url;
		if(!url.Set(data))
			return;
		webBrowser->Navigate2(url, 0, 0, 0, 0);
	}
	
	if(set == SETHTML) {
		CBSTR pbstrLocationURL;
		if(webBrowser->get_LocationURL((BSTR *)pbstrLocationURL) != S_OK) {
			OleStr url;
			url.Set("about:blank");
			webBrowser->Navigate2(url, 0, 0, 0, 0);
		}
		bool ret = false;
		LPDISPATCH lpDisp;
		if(!webBrowser->get_Document(&lpDisp)) {
			IHTMLDocument2 *htmDoc2;
			if(!lpDisp->QueryInterface(IID_IHTMLDocument2, (void**)&htmDoc2)) {
				SAFEARRAY *sfArray;
				static const SAFEARRAYBOUND abound = {1, 0};
				if((sfArray = SafeArrayCreate(VT_VARIANT, 1, (SAFEARRAYBOUND*)&abound))) {
					VARIANT	*pVar;
					if(!SafeArrayAccessData(sfArray, (void**)&pVar)) {
						pVar->vt = VT_BSTR;
						if(!BSTRSet(data, pVar->bstrVal))
							ret = false;
						else {
							ret = true;
							htmDoc2->write(sfArray);
							htmDoc2->close();
						}
					}
					SafeArrayDestroy(sfArray);
				}
				htmDoc2->Release();
			}
			lpDisp->Release();
		}
	}

	webBrowser->put_Silent(silent ? VARIANT_TRUE : VARIANT_FALSE);
}

void InternetExplorerBrowser::Browse(const String& url)
{
	set = SETURL;
	data = url;
	Created();
}

void InternetExplorerBrowser::Silent(bool b)
{
	silent = b;
	Created();
}

void InternetExplorerBrowser::ShowHTML(const String &html) {
	set = SETHTML;
	data = html;
	Created();
}

bool InternetExplorerBrowser::GoForward() {
	IIWebBrowser webBrowser(this);
	return webBrowser && webBrowser->GoForward() == S_OK;
}

bool InternetExplorerBrowser::GoBack() {
	IIWebBrowser webBrowser(this);
	return webBrowser && webBrowser->GoBack() == S_OK;
}


bool InternetExplorerBrowser::GoHome() {
	IIWebBrowser webBrowser(this);
	return webBrowser && webBrowser->GoHome() == S_OK;
}

bool InternetExplorerBrowser::RefreshPage() {
	IIWebBrowser webBrowser(this);
	return webBrowser && webBrowser->Refresh() == S_OK;
}

bool InternetExplorerBrowser::Stop() {
	IIWebBrowser webBrowser(this);
	return webBrowser && webBrowser->Stop() == S_OK;
}

String InternetExplorerBrowser::GetLocation() {
	IIWebBrowser webBrowser(this);
	if(!webBrowser)
		return "";
	
	CBSTR pbstrLocationURL;
	if (webBrowser->get_LocationURL((BSTR *)pbstrLocationURL) != S_OK)
		return "";
	
	return pbstrLocationURL.ToString();
}

String InternetExplorerBrowser::GetTitle() {
	IIWebBrowser webBrowser(this);
	if(!webBrowser)
		return "";
	
	CBSTR pbstrLocationURL;
	if(webBrowser->get_LocationName((BSTR *)pbstrLocationURL) != S_OK)
		return "";
	
	return pbstrLocationURL.ToString();
}

bool InternetExplorerBrowser::GetOffline(bool &offline) {
	IIWebBrowser webBrowser(this);
	if (!webBrowser)
		return false;
	
	VARIANT_BOOL voffline;
	if (webBrowser->get_Offline(&voffline) != S_OK)
		return false;
	
	offline = (voffline == VARIANT_TRUE) ? true : false;
	return true;
}

String InternetExplorerBrowser::GetReadyState() {
	IIWebBrowser webBrowser(this);
	if (!webBrowser)
		return "";
	
	READYSTATE readystate;
	if (webBrowser->get_ReadyState(&readystate) != S_OK)
		return "";
	
	switch (readystate) {
	case READYSTATE_UNINITIALIZED:	return "Uninitialized";	// Default initialization state
  	case READYSTATE_LOADING:		return "Loading";		// Object is currently loading its properties
  	case READYSTATE_LOADED:			return "Loaded";		// Object was initialized
  	case READYSTATE_INTERACTIVE:	return "Interactive";	// Object is interactive, but not all its data is available
  	case READYSTATE_COMPLETE:		return "Complete";		// Object has received all its data
  	default:						return "Unknown";
	}
}

END_UPP_NAMESPACE

#endif
