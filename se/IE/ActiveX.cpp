#include "IE.h"

#ifdef PLATFORM_WIN32

NAMESPACE_UPP

bool BSTRSet(const String str, BSTR &bstr) {
	wchar_t *buffer;
	DWORD size = MultiByteToWideChar(CP_UTF8, 0, str, -1, 0, 0);
	if (!(buffer = (wchar_t *)GlobalAlloc(GMEM_FIXED, sizeof(wchar_t) * size)))
		return false;

	MultiByteToWideChar(CP_UTF8, 0, str, -1, buffer, size);
	bstr = SysAllocString(buffer);
	GlobalFree(buffer);
	if (!bstr)
		return false;
	return true;
}

String BSTRGet(BSTR &bstr) {
	if (!bstr)
		return Null;
	
	char *buffer;
	DWORD size = SysStringLen(bstr);
	if (!(buffer = (char *)GlobalAlloc(GMEM_FIXED, sizeof(wchar_t) * size)))
		return Null;
	
	size_t i = wcstombs(buffer, bstr, size);
	buffer[i] = 0;
	
	String ret = buffer;
	GlobalFree(buffer);
	return ret;
}

OleStr::OleStr() {
    VariantInit(&var);
    VariantClear(&var);
}

OleStr::~OleStr() {
	SysFreeString(var.bstrVal);
}

bool OleStr::Set(const String str) {
	var.vt = VT_BSTR;
	return BSTRSet(str, var.bstrVal);
}

CBSTR::~CBSTR() {
	SysFreeString(bstr);
}

bool CBSTR::Set(const String str) {
	return BSTRSet(str, bstr);
}

DHCtrlActiveX::DHCtrlActiveX(CLSID clsid, const String name, bool status) : 
						oleObj(0), pClientSite(0), clsid(clsid), name(name), status(status) {}

DHCtrlActiveX::~DHCtrlActiveX(void) {
	Detach();
}

DHCtrlActiveX &DHCtrlActiveX::SetStatus(bool _status) {
	status = _status;
	if (status) {
		Attach(GetHWND());
		EnableWindow(GetHWND(), true);
		BackPaint(NOBACKPAINT);
	} else {
		Detach();
		BackPaint(FULLBACKPAINT);
	}
	return *this;
};
          
void *DHCtrlActiveX::QueryInterface(const IID iid) {
	void *ret;
	if (!oleObj || !status)
		return NULL;
	if (S_OK != oleObj->QueryInterface(iid, &ret))
		return NULL;
	return ret;
}

Rect PixelToHiMetric(const Rect& _rc)
{
	static bool s_initialized = false;
	static int s_pixelsPerInchX, s_pixelsPerInchY;
	if(!s_initialized)
	{
		HDC hdc = ::GetDC(0);
		s_pixelsPerInchX = ::GetDeviceCaps(hdc, LOGPIXELSX);
		s_pixelsPerInchY = ::GetDeviceCaps(hdc, LOGPIXELSY);
		::ReleaseDC(0, hdc);
		s_initialized = true;
	}

	Rect rc;
	rc.left = MulDiv(2540, _rc.left, s_pixelsPerInchX);
	rc.top = MulDiv(2540, _rc.top, s_pixelsPerInchY);
	rc.right = MulDiv(2540, _rc.right, s_pixelsPerInchX);
	rc.bottom = MulDiv(2540, _rc.bottom, s_pixelsPerInchY);
	return rc;
}

	
void DHCtrlActiveX::DoResize() {
	if(pClientSite && pClientSite->hwnd && oleObj && status) {
		Rect rect;
		GetClientRect(pClientSite->hwnd, rect);
		IOleInPlaceObject *inplace = (IOleInPlaceObject *)QueryInterface(IID_IOleInPlaceObject);
		if (inplace) {
			Rect r = PixelToHiMetric(rect);
			SIZEL sz;
			sz.cx = r.Width();
			sz.cy = r.Height();
			oleObj->SetExtent(DVASPECT_CONTENT, &sz);

			inplace->SetObjectRects(rect, rect);
			inplace->Release();
		}
	}
}

void DHCtrlActiveX::Created()
{
}

void DHCtrlActiveX::Detach() {
	if(oleObj) {
		oleObj->Release();
		oleObj = NULL;
	}

	if(pClientSite) {
		CloseHWND();
		pClientSite->Release();
		pClientSite = NULL;
	}
}

bool DHCtrlActiveX::Attach(HWND hwnd) {
	if (hwnd == (HWND)-1 || hwnd == 0 || !status)
		return false;

	Detach();
	
	EnableWindow(hwnd, true);

	AXStorage *storage = new AXStorage;

	pClientSite = new AXClientSite;
	pClientSite->hwnd = hwnd;
 
	if(!OleCreate(clsid, IID_IOleObject, OLERENDER_DRAW, 0, (IOleClientSite *)pClientSite, storage, (void**)&oleObj)) {
		oleObj->SetHostNames(name.ToWString(), 0);
		RECT rect;
		oleObj->SetClientSite(pClientSite);
		GetClientRect(hwnd, &rect);
		if(!OleSetContainedObject((IUnknown *)oleObj, TRUE)) {
		#if 0
			IEnumOLEVERB *enumVerbs = 0;
			oleObj->EnumVerbs(&enumVerbs);
			if (enumVerbs) {
				enumVerbs->Reset();
				ULONG c;
				OLEVERB verb;
				while(enumVerbs->Next(1, &verb, &c) == S_OK) {
					if (!verb.lpszVerbName)
						continue;
					DDUMP(WString(verb.lpszVerbName));
				}
				enumVerbs->Release();
			}
		#endif
			if(!oleObj->DoVerb(OLEIVERB_INPLACEACTIVATE, NULL, (IOleClientSite *)pClientSite, -1, hwnd, &rect)) {
				storage->Release();
				Created();
				return true;
			}
		}
	}
	Detach();
	storage->Release();
	return false;
}

LRESULT DHCtrlActiveX::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if(message == WM_ERASEBKGND)
		return TRUE;
	return DHCtrl::WindowProc(message, wParam, lParam);
}

void DHCtrlActiveX::NcCreate(HWND hwnd)
{
	Attach(hwnd);
	DHCtrl::NcCreate(hwnd);
}

bool DHCtrlActiveX::PreprocessMessage(MSG& msg)
{
	bool r = false;
	if(::IsChild(hwnd, msg.hwnd)) {
		IOleInPlaceActiveObject *ipa = (IOleInPlaceActiveObject *)QueryInterface(IID_IOleInPlaceActiveObject);
		if(ipa) {
			r = ipa->TranslateAccelerator(&msg) == S_OK;
			ipa->Release();
		}
	}
	return r;
}

void DHCtrlActiveX::Layout()
{
	DoResize();
}

HRESULT STDMETHODCALLTYPE AXStorage::QueryInterface(REFIID riid, void __RPC_FAR *__RPC_FAR *ppvObject) {
	throw Exc(t_("Function not implemented"));
}

ULONG STDMETHODCALLTYPE AXStorage::AddRef( void) {
	return AtomicInc(refcount);
}

ULONG STDMETHODCALLTYPE AXStorage::Release( void) {
	ULONG n = AtomicDec(refcount);
	if(n == 0)
		delete this;
	return n;
}

HRESULT STDMETHODCALLTYPE AXStorage::CreateStream(const OLECHAR *pwcsName, DWORD grfMode, DWORD reserved1, DWORD reserved2, IStream **ppstm) {
	throw Exc(t_("Function not implemented"));
}

HRESULT STDMETHODCALLTYPE AXStorage::OpenStream(const OLECHAR *pwcsName, void *reserved1, DWORD grfMode, DWORD reserved2, IStream **ppstm) {
	throw Exc(t_("Function not implemented"));
}

HRESULT STDMETHODCALLTYPE AXStorage::CreateStorage(const OLECHAR *pwcsName, DWORD grfMode, DWORD reserved1, DWORD reserved2, IStorage **ppstg) {
	throw Exc(t_("Function not implemented"));
}

HRESULT STDMETHODCALLTYPE AXStorage::OpenStorage(const OLECHAR *pwcsName, IStorage *pstgPriority, DWORD grfMode, SNB snbExclude, DWORD reserved, IStorage **ppstg) {
	throw Exc(t_("Function not implemented"));
}

HRESULT STDMETHODCALLTYPE AXStorage::CopyTo(DWORD ciidExclude, const IID *rgiidExclude, SNB snbExclude, IStorage *pstgDest) {
	throw Exc(t_("Function not implemented"));
}

HRESULT STDMETHODCALLTYPE AXStorage::MoveElementTo(const OLECHAR *pwcsName, IStorage *pstgDest, const OLECHAR *pwcsNewName, DWORD grfFlags) {
	throw Exc(t_("Function not implemented"));
}

HRESULT STDMETHODCALLTYPE AXStorage::Commit(DWORD grfCommitFlags) {
	throw Exc(t_("Function not implemented"));
}

HRESULT STDMETHODCALLTYPE AXStorage::Revert() {
	throw Exc(t_("Function not implemented"));
}

HRESULT STDMETHODCALLTYPE AXStorage::EnumElements(DWORD reserved1, void *reserved2, DWORD reserved3, IEnumSTATSTG **ppenum) {
	throw Exc(t_("Function not implemented"));
}

HRESULT STDMETHODCALLTYPE AXStorage::DestroyElement(const OLECHAR *pwcsName) {
	throw Exc(t_("Function not implemented"));
}

HRESULT STDMETHODCALLTYPE AXStorage::RenameElement(const OLECHAR *pwcsOldName, const OLECHAR *pwcsNewName) {
	throw Exc(t_("Function not implemented"));
}

HRESULT STDMETHODCALLTYPE AXStorage::SetElementTimes(const OLECHAR *pwcsName, const FILETIME *pctime, const FILETIME *patime, const FILETIME *pmtime) {
	throw Exc(t_("Function not implemented"));
}

HRESULT STDMETHODCALLTYPE AXStorage::SetClass(REFCLSID clsid) {
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE AXStorage::SetStateBits(DWORD grfStateBits, DWORD grfMask) {
	throw Exc(t_("Function not implemented"));
}

HRESULT STDMETHODCALLTYPE AXStorage::Stat(STATSTG *pstatstg, DWORD grfStatFlag) {
	throw Exc(t_("Function not implemented"));
}

HRESULT STDMETHODCALLTYPE AXClientSite::QueryInterface(REFIID riid, void __RPC_FAR *__RPC_FAR *ppvObject) {
	if (!memcmp(&riid, &IID_IUnknown, sizeof(GUID)))
		*ppvObject = reinterpret_cast<IUnknown *> (this);
	else if (!memcmp(&riid, &IID_IOleClientSite, sizeof(GUID)))
		*ppvObject = (IOleClientSite *)this;
	else if (!memcmp(&riid, &IID_IOleInPlaceSite, sizeof(GUID)))
		*ppvObject = (IOleInPlaceSite *)this;
	else {
		*ppvObject = 0;
		return(E_NOINTERFACE);
	}
	return S_OK;
}

ULONG STDMETHODCALLTYPE AXClientSite::AddRef() {
	return AtomicInc(refcount);
}

ULONG STDMETHODCALLTYPE AXClientSite::Release() {
	ULONG n = AtomicDec(refcount);
	if(n == 0)
		delete this;
	return n;
}

HRESULT STDMETHODCALLTYPE AXClientSite::SaveObject() {
	throw Exc(t_("Function not implemented"));
}

HRESULT STDMETHODCALLTYPE AXClientSite::GetMoniker(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk) {
	throw Exc(t_("Function not implemented"));
}

HRESULT STDMETHODCALLTYPE AXClientSite::GetContainer(IOleContainer **ppContainer) {
	*ppContainer = 0;
	return E_NOINTERFACE;
}

HRESULT STDMETHODCALLTYPE AXClientSite::ShowObject() {
	return NOERROR;
}

HRESULT STDMETHODCALLTYPE AXClientSite::OnShowWindow(BOOL fShow) {
	return NOERROR;
}

HRESULT STDMETHODCALLTYPE AXClientSite::RequestNewObjectLayout() {
	throw Exc(t_("Function not implemented"));
}


HRESULT STDMETHODCALLTYPE AXClientSite::GetWindow(HWND *phwnd) {
	*phwnd = hwnd;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE AXClientSite::ContextSensitiveHelp(BOOL fEnterMode) {
	throw Exc(t_("Function not implemented"));
}

HRESULT STDMETHODCALLTYPE AXClientSite::GetBorder(LPRECT lprectBorder) {
	throw Exc(t_("Function not implemented"));
}

HRESULT STDMETHODCALLTYPE AXClientSite::RequestBorderSpace(LPCBORDERWIDTHS pborderwidths) {
	throw Exc(t_("Function not implemented"));
}

HRESULT STDMETHODCALLTYPE AXClientSite::SetBorderSpace(LPCBORDERWIDTHS pborderwidths) {
	throw Exc(t_("Function not implemented"));
}

HRESULT STDMETHODCALLTYPE AXClientSite::SetActiveObject(IOleInPlaceActiveObject *pActiveObject, LPCOLESTR pszObjName) {
	return S_OK;
}

HRESULT STDMETHODCALLTYPE AXClientSite::InsertMenus(HMENU hmenuShared, LPOLEMENUGROUPWIDTHS lpMenuWidths) {
	throw Exc(t_("Function not implemented"));
}

HRESULT STDMETHODCALLTYPE AXClientSite::SetMenu(HMENU hmenuShared, HOLEMENU holemenu, HWND hwndActiveObject) {
	return S_OK;
}

HRESULT STDMETHODCALLTYPE AXClientSite::RemoveMenus(HMENU hmenuShared) {
	throw Exc(t_("Function not implemented"));
}

HRESULT STDMETHODCALLTYPE AXClientSite::SetStatusText(LPCOLESTR pszStatusText) {
	return S_OK;
}

HRESULT STDMETHODCALLTYPE AXClientSite::EnableModeless(BOOL fEnable) {
	return S_OK;
}

HRESULT STDMETHODCALLTYPE AXClientSite::TranslateAccelerator(LPMSG lpmsg, WORD wID) {
	throw Exc(t_("Function not implemented"));
}

HRESULT STDMETHODCALLTYPE AXClientSite::CanInPlaceActivate() {
	return S_OK;
}

HRESULT STDMETHODCALLTYPE AXClientSite::OnInPlaceActivate() {
	return S_OK;
}

HRESULT STDMETHODCALLTYPE AXClientSite::OnUIActivate() {
	return S_OK;
}

HRESULT STDMETHODCALLTYPE AXClientSite::GetWindowContext(IOleInPlaceFrame **ppFrame, IOleInPlaceUIWindow **ppDoc, LPRECT lprcPosRect, LPRECT lprcClipRect, LPOLEINPLACEFRAMEINFO lpFrameInfo) {
	*ppFrame = (IOleInPlaceFrame *)this;

	*ppDoc = 0;

	lpFrameInfo->fMDIApp = FALSE;
	lpFrameInfo->hwndFrame = hwnd;
	lpFrameInfo->haccel = 0;
	lpFrameInfo->cAccelEntries = 0;

	GetClientRect(lpFrameInfo->hwndFrame, lprcPosRect);
	GetClientRect(lpFrameInfo->hwndFrame, lprcClipRect);

	return S_OK;
}

HRESULT STDMETHODCALLTYPE AXClientSite::Scroll(SIZE scrollExtant) {
	throw Exc(t_("Function not implemented"));
}

HRESULT STDMETHODCALLTYPE AXClientSite::OnUIDeactivate(BOOL fUndoable) {
	return S_OK;
}

HRESULT STDMETHODCALLTYPE AXClientSite::OnInPlaceDeactivate() {
	return S_OK;
}

HRESULT STDMETHODCALLTYPE AXClientSite::DiscardUndoState() {
	throw Exc(t_("Function not implemented"));
}

HRESULT STDMETHODCALLTYPE AXClientSite::DeactivateAndUndo() {
	throw Exc(t_("Function not implemented"));
}

HRESULT STDMETHODCALLTYPE AXClientSite::OnPosRectChange(LPCRECT lprcPosRect) {
	return S_OK;
}

END_UPP_NAMESPACE

#endif
