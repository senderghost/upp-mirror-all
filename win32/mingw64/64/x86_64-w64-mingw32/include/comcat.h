/*** Autogenerated by WIDL 1.6 from include/comcat.idl - Do not edit ***/

#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include <rpc.h>
#include <rpcndr.h>

#ifndef COM_NO_WINDOWS_H
#include <windows.h>
#include <ole2.h>
#endif

#ifndef __comcat_h__
#define __comcat_h__

/* Forward declarations */

#ifndef __IEnumGUID_FWD_DEFINED__
#define __IEnumGUID_FWD_DEFINED__
typedef interface IEnumGUID IEnumGUID;
#endif

#ifndef __IEnumCATEGORYINFO_FWD_DEFINED__
#define __IEnumCATEGORYINFO_FWD_DEFINED__
typedef interface IEnumCATEGORYINFO IEnumCATEGORYINFO;
#endif

#ifndef __ICatRegister_FWD_DEFINED__
#define __ICatRegister_FWD_DEFINED__
typedef interface ICatRegister ICatRegister;
#endif

#ifndef __ICatInformation_FWD_DEFINED__
#define __ICatInformation_FWD_DEFINED__
typedef interface ICatInformation ICatInformation;
#endif

/* Headers for imported files */

#include <unknwn.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER within this package.
 */

#include <winapifamily.h>

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
#ifndef __IEnumGUID_FWD_DEFINED__
#define __IEnumGUID_FWD_DEFINED__
typedef interface IEnumGUID IEnumGUID;
#endif

#endif
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
#ifndef __IEnumCATEGORYINFO_FWD_DEFINED__
#define __IEnumCATEGORYINFO_FWD_DEFINED__
typedef interface IEnumCATEGORYINFO IEnumCATEGORYINFO;
#endif

#ifndef __ICatRegister_FWD_DEFINED__
#define __ICatRegister_FWD_DEFINED__
typedef interface ICatRegister ICatRegister;
#endif

#ifndef __ICatInformation_FWD_DEFINED__
#define __ICatInformation_FWD_DEFINED__
typedef interface ICatInformation ICatInformation;
#endif


EXTERN_C const CLSID CLSID_StdComponentCategoriesMgr;
#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
typedef GUID CATID;
typedef REFGUID REFCATID;
#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
#define IID_IEnumCLSID IID_IEnumGUID
#define IEnumCLSID IEnumGUID
#define LPENUMCLSID LPENUMGUID

#define CATID_NULL GUID_NULL
#define IsEqualCATID(rcatid1, rcatid2) IsEqualGUID(rcatid1, rcatid2)
#define IID_IEnumCATID IID_IEnumGUID
#define IEnumCATID IEnumGUID


EXTERN_C const CATID CATID_Insertable;
EXTERN_C const CATID CATID_Control;
EXTERN_C const CATID CATID_Programmable;
EXTERN_C const CATID CATID_IsShortcut;
EXTERN_C const CATID CATID_NeverShowExt;
EXTERN_C const CATID CATID_DocObject;
EXTERN_C const CATID CATID_Printable;
EXTERN_C const CATID CATID_RequiresDataPathHost;
EXTERN_C const CATID CATID_PersistsToMoniker;
EXTERN_C const CATID CATID_PersistsToStorage;
EXTERN_C const CATID CATID_PersistsToStreamInit;
EXTERN_C const CATID CATID_PersistsToStream;
EXTERN_C const CATID CATID_PersistsToMemory;
EXTERN_C const CATID CATID_PersistsToFile;
EXTERN_C const CATID CATID_PersistsToPropertyBag;
EXTERN_C const CATID CATID_InternetAware;
EXTERN_C const CATID CATID_DesignTimeUIActivatableControl;
#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
#ifndef _LPENUMGUID_DEFINED
#define _LPENUMGUID_DEFINED
/*****************************************************************************
 * IEnumGUID interface
 */
#ifndef __IEnumGUID_INTERFACE_DEFINED__
#define __IEnumGUID_INTERFACE_DEFINED__

typedef IEnumGUID *LPENUMGUID;
DEFINE_GUID(IID_IEnumGUID, 0x0002e000, 0x0000, 0x0000, 0xc0,0x00, 0x00,0x00,0x00,0x00,0x00,0x46);
#if defined(__cplusplus) && !defined(CINTERFACE)
MIDL_INTERFACE("0002e000-0000-0000-c000-000000000046")
IEnumGUID : public IUnknown
{
    virtual HRESULT STDMETHODCALLTYPE Next(
        ULONG celt,
        GUID *rgelt,
        ULONG *pceltFetched) = 0;

    virtual HRESULT STDMETHODCALLTYPE Skip(
        ULONG celt) = 0;

    virtual HRESULT STDMETHODCALLTYPE Reset(
        ) = 0;

    virtual HRESULT STDMETHODCALLTYPE Clone(
        IEnumGUID **ppenum) = 0;

};
#ifdef __CRT_UUID_DECL
__CRT_UUID_DECL(IEnumGUID, 0x0002e000, 0x0000, 0x0000, 0xc0,0x00, 0x00,0x00,0x00,0x00,0x00,0x46)
#endif
#else
typedef struct IEnumGUIDVtbl {
    BEGIN_INTERFACE

    /*** IUnknown methods ***/
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IEnumGUID* This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        IEnumGUID* This);

    ULONG (STDMETHODCALLTYPE *Release)(
        IEnumGUID* This);

    /*** IEnumGUID methods ***/
    HRESULT (STDMETHODCALLTYPE *Next)(
        IEnumGUID* This,
        ULONG celt,
        GUID *rgelt,
        ULONG *pceltFetched);

    HRESULT (STDMETHODCALLTYPE *Skip)(
        IEnumGUID* This,
        ULONG celt);

    HRESULT (STDMETHODCALLTYPE *Reset)(
        IEnumGUID* This);

    HRESULT (STDMETHODCALLTYPE *Clone)(
        IEnumGUID* This,
        IEnumGUID **ppenum);

    END_INTERFACE
} IEnumGUIDVtbl;
interface IEnumGUID {
    CONST_VTBL IEnumGUIDVtbl* lpVtbl;
};

#ifdef COBJMACROS
#ifndef WIDL_C_INLINE_WRAPPERS
/*** IUnknown methods ***/
#define IEnumGUID_QueryInterface(This,riid,ppvObject) (This)->lpVtbl->QueryInterface(This,riid,ppvObject)
#define IEnumGUID_AddRef(This) (This)->lpVtbl->AddRef(This)
#define IEnumGUID_Release(This) (This)->lpVtbl->Release(This)
/*** IEnumGUID methods ***/
#define IEnumGUID_Next(This,celt,rgelt,pceltFetched) (This)->lpVtbl->Next(This,celt,rgelt,pceltFetched)
#define IEnumGUID_Skip(This,celt) (This)->lpVtbl->Skip(This,celt)
#define IEnumGUID_Reset(This) (This)->lpVtbl->Reset(This)
#define IEnumGUID_Clone(This,ppenum) (This)->lpVtbl->Clone(This,ppenum)
#else
/*** IUnknown methods ***/
static FORCEINLINE HRESULT IEnumGUID_QueryInterface(IEnumGUID* This,REFIID riid,void **ppvObject) {
    return This->lpVtbl->QueryInterface(This,riid,ppvObject);
}
static FORCEINLINE ULONG IEnumGUID_AddRef(IEnumGUID* This) {
    return This->lpVtbl->AddRef(This);
}
static FORCEINLINE ULONG IEnumGUID_Release(IEnumGUID* This) {
    return This->lpVtbl->Release(This);
}
/*** IEnumGUID methods ***/
static FORCEINLINE HRESULT IEnumGUID_Next(IEnumGUID* This,ULONG celt,GUID *rgelt,ULONG *pceltFetched) {
    return This->lpVtbl->Next(This,celt,rgelt,pceltFetched);
}
static FORCEINLINE HRESULT IEnumGUID_Skip(IEnumGUID* This,ULONG celt) {
    return This->lpVtbl->Skip(This,celt);
}
static FORCEINLINE HRESULT IEnumGUID_Reset(IEnumGUID* This) {
    return This->lpVtbl->Reset(This);
}
static FORCEINLINE HRESULT IEnumGUID_Clone(IEnumGUID* This,IEnumGUID **ppenum) {
    return This->lpVtbl->Clone(This,ppenum);
}
#endif
#endif

#endif

HRESULT STDMETHODCALLTYPE IEnumGUID_RemoteNext_Proxy(
    IEnumGUID* This,
    ULONG celt,
    GUID *rgelt,
    ULONG *pceltFetched);
void __RPC_STUB IEnumGUID_RemoteNext_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE IEnumGUID_Skip_Proxy(
    IEnumGUID* This,
    ULONG celt);
void __RPC_STUB IEnumGUID_Skip_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE IEnumGUID_Reset_Proxy(
    IEnumGUID* This);
void __RPC_STUB IEnumGUID_Reset_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE IEnumGUID_Clone_Proxy(
    IEnumGUID* This,
    IEnumGUID **ppenum);
void __RPC_STUB IEnumGUID_Clone_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT CALLBACK IEnumGUID_Next_Proxy(
    IEnumGUID* This,
    ULONG celt,
    GUID *rgelt,
    ULONG *pceltFetched);
HRESULT __RPC_STUB IEnumGUID_Next_Stub(
    IEnumGUID* This,
    ULONG celt,
    GUID *rgelt,
    ULONG *pceltFetched);

#endif  /* __IEnumGUID_INTERFACE_DEFINED__ */

#endif
#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
#ifndef _LPENUMCATEGORYINFO_DEFINED
#define _LPENUMCATEGORYINFO_DEFINED
/*****************************************************************************
 * IEnumCATEGORYINFO interface
 */
#ifndef __IEnumCATEGORYINFO_INTERFACE_DEFINED__
#define __IEnumCATEGORYINFO_INTERFACE_DEFINED__

typedef IEnumCATEGORYINFO *LPENUMCATEGORYINFO;

typedef struct tagCATEGORYINFO {
    CATID catid;
    LCID lcid;
    OLECHAR szDescription[128];
} CATEGORYINFO;
typedef struct tagCATEGORYINFO *LPCATEGORYINFO;

DEFINE_GUID(IID_IEnumCATEGORYINFO, 0x0002e011, 0x0000, 0x0000, 0xc0,0x00, 0x00,0x00,0x00,0x00,0x00,0x46);
#if defined(__cplusplus) && !defined(CINTERFACE)
MIDL_INTERFACE("0002e011-0000-0000-c000-000000000046")
IEnumCATEGORYINFO : public IUnknown
{
    virtual HRESULT STDMETHODCALLTYPE Next(
        ULONG celt,
        CATEGORYINFO *rgelt,
        ULONG *pceltFetched) = 0;

    virtual HRESULT STDMETHODCALLTYPE Skip(
        ULONG celt) = 0;

    virtual HRESULT STDMETHODCALLTYPE Reset(
        ) = 0;

    virtual HRESULT STDMETHODCALLTYPE Clone(
        IEnumCATEGORYINFO **ppenum) = 0;

};
#ifdef __CRT_UUID_DECL
__CRT_UUID_DECL(IEnumCATEGORYINFO, 0x0002e011, 0x0000, 0x0000, 0xc0,0x00, 0x00,0x00,0x00,0x00,0x00,0x46)
#endif
#else
typedef struct IEnumCATEGORYINFOVtbl {
    BEGIN_INTERFACE

    /*** IUnknown methods ***/
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IEnumCATEGORYINFO* This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        IEnumCATEGORYINFO* This);

    ULONG (STDMETHODCALLTYPE *Release)(
        IEnumCATEGORYINFO* This);

    /*** IEnumCATEGORYINFO methods ***/
    HRESULT (STDMETHODCALLTYPE *Next)(
        IEnumCATEGORYINFO* This,
        ULONG celt,
        CATEGORYINFO *rgelt,
        ULONG *pceltFetched);

    HRESULT (STDMETHODCALLTYPE *Skip)(
        IEnumCATEGORYINFO* This,
        ULONG celt);

    HRESULT (STDMETHODCALLTYPE *Reset)(
        IEnumCATEGORYINFO* This);

    HRESULT (STDMETHODCALLTYPE *Clone)(
        IEnumCATEGORYINFO* This,
        IEnumCATEGORYINFO **ppenum);

    END_INTERFACE
} IEnumCATEGORYINFOVtbl;
interface IEnumCATEGORYINFO {
    CONST_VTBL IEnumCATEGORYINFOVtbl* lpVtbl;
};

#ifdef COBJMACROS
#ifndef WIDL_C_INLINE_WRAPPERS
/*** IUnknown methods ***/
#define IEnumCATEGORYINFO_QueryInterface(This,riid,ppvObject) (This)->lpVtbl->QueryInterface(This,riid,ppvObject)
#define IEnumCATEGORYINFO_AddRef(This) (This)->lpVtbl->AddRef(This)
#define IEnumCATEGORYINFO_Release(This) (This)->lpVtbl->Release(This)
/*** IEnumCATEGORYINFO methods ***/
#define IEnumCATEGORYINFO_Next(This,celt,rgelt,pceltFetched) (This)->lpVtbl->Next(This,celt,rgelt,pceltFetched)
#define IEnumCATEGORYINFO_Skip(This,celt) (This)->lpVtbl->Skip(This,celt)
#define IEnumCATEGORYINFO_Reset(This) (This)->lpVtbl->Reset(This)
#define IEnumCATEGORYINFO_Clone(This,ppenum) (This)->lpVtbl->Clone(This,ppenum)
#else
/*** IUnknown methods ***/
static FORCEINLINE HRESULT IEnumCATEGORYINFO_QueryInterface(IEnumCATEGORYINFO* This,REFIID riid,void **ppvObject) {
    return This->lpVtbl->QueryInterface(This,riid,ppvObject);
}
static FORCEINLINE ULONG IEnumCATEGORYINFO_AddRef(IEnumCATEGORYINFO* This) {
    return This->lpVtbl->AddRef(This);
}
static FORCEINLINE ULONG IEnumCATEGORYINFO_Release(IEnumCATEGORYINFO* This) {
    return This->lpVtbl->Release(This);
}
/*** IEnumCATEGORYINFO methods ***/
static FORCEINLINE HRESULT IEnumCATEGORYINFO_Next(IEnumCATEGORYINFO* This,ULONG celt,CATEGORYINFO *rgelt,ULONG *pceltFetched) {
    return This->lpVtbl->Next(This,celt,rgelt,pceltFetched);
}
static FORCEINLINE HRESULT IEnumCATEGORYINFO_Skip(IEnumCATEGORYINFO* This,ULONG celt) {
    return This->lpVtbl->Skip(This,celt);
}
static FORCEINLINE HRESULT IEnumCATEGORYINFO_Reset(IEnumCATEGORYINFO* This) {
    return This->lpVtbl->Reset(This);
}
static FORCEINLINE HRESULT IEnumCATEGORYINFO_Clone(IEnumCATEGORYINFO* This,IEnumCATEGORYINFO **ppenum) {
    return This->lpVtbl->Clone(This,ppenum);
}
#endif
#endif

#endif

HRESULT STDMETHODCALLTYPE IEnumCATEGORYINFO_Next_Proxy(
    IEnumCATEGORYINFO* This,
    ULONG celt,
    CATEGORYINFO *rgelt,
    ULONG *pceltFetched);
void __RPC_STUB IEnumCATEGORYINFO_Next_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE IEnumCATEGORYINFO_Skip_Proxy(
    IEnumCATEGORYINFO* This,
    ULONG celt);
void __RPC_STUB IEnumCATEGORYINFO_Skip_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE IEnumCATEGORYINFO_Reset_Proxy(
    IEnumCATEGORYINFO* This);
void __RPC_STUB IEnumCATEGORYINFO_Reset_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE IEnumCATEGORYINFO_Clone_Proxy(
    IEnumCATEGORYINFO* This,
    IEnumCATEGORYINFO **ppenum);
void __RPC_STUB IEnumCATEGORYINFO_Clone_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);

#endif  /* __IEnumCATEGORYINFO_INTERFACE_DEFINED__ */

#endif

#ifndef _LPCATREGISTER_DEFINED
#define _LPCATREGISTER_DEFINED
/*****************************************************************************
 * ICatRegister interface
 */
#ifndef __ICatRegister_INTERFACE_DEFINED__
#define __ICatRegister_INTERFACE_DEFINED__

typedef ICatRegister *LPCATREGISTER;

DEFINE_GUID(IID_ICatRegister, 0x0002e012, 0x0000, 0x0000, 0xc0,0x00, 0x00,0x00,0x00,0x00,0x00,0x46);
#if defined(__cplusplus) && !defined(CINTERFACE)
MIDL_INTERFACE("0002e012-0000-0000-c000-000000000046")
ICatRegister : public IUnknown
{
    virtual HRESULT STDMETHODCALLTYPE RegisterCategories(
        ULONG cCategories,
        CATEGORYINFO rgCategoryInfo[]) = 0;

    virtual HRESULT STDMETHODCALLTYPE UnRegisterCategories(
        ULONG cCategories,
        CATID rgcatid[]) = 0;

    virtual HRESULT STDMETHODCALLTYPE RegisterClassImplCategories(
        REFCLSID rclsid,
        ULONG cCategories,
        CATID rgcatid[]) = 0;

    virtual HRESULT STDMETHODCALLTYPE UnRegisterClassImplCategories(
        REFCLSID rclsid,
        ULONG cCategories,
        CATID rgcatid[]) = 0;

    virtual HRESULT STDMETHODCALLTYPE RegisterClassReqCategories(
        REFCLSID rclsid,
        ULONG cCategories,
        CATID rgcatid[]) = 0;

    virtual HRESULT STDMETHODCALLTYPE UnRegisterClassReqCategories(
        REFCLSID rclsid,
        ULONG cCategories,
        CATID rgcatid[]) = 0;

};
#ifdef __CRT_UUID_DECL
__CRT_UUID_DECL(ICatRegister, 0x0002e012, 0x0000, 0x0000, 0xc0,0x00, 0x00,0x00,0x00,0x00,0x00,0x46)
#endif
#else
typedef struct ICatRegisterVtbl {
    BEGIN_INTERFACE

    /*** IUnknown methods ***/
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ICatRegister* This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        ICatRegister* This);

    ULONG (STDMETHODCALLTYPE *Release)(
        ICatRegister* This);

    /*** ICatRegister methods ***/
    HRESULT (STDMETHODCALLTYPE *RegisterCategories)(
        ICatRegister* This,
        ULONG cCategories,
        CATEGORYINFO rgCategoryInfo[]);

    HRESULT (STDMETHODCALLTYPE *UnRegisterCategories)(
        ICatRegister* This,
        ULONG cCategories,
        CATID rgcatid[]);

    HRESULT (STDMETHODCALLTYPE *RegisterClassImplCategories)(
        ICatRegister* This,
        REFCLSID rclsid,
        ULONG cCategories,
        CATID rgcatid[]);

    HRESULT (STDMETHODCALLTYPE *UnRegisterClassImplCategories)(
        ICatRegister* This,
        REFCLSID rclsid,
        ULONG cCategories,
        CATID rgcatid[]);

    HRESULT (STDMETHODCALLTYPE *RegisterClassReqCategories)(
        ICatRegister* This,
        REFCLSID rclsid,
        ULONG cCategories,
        CATID rgcatid[]);

    HRESULT (STDMETHODCALLTYPE *UnRegisterClassReqCategories)(
        ICatRegister* This,
        REFCLSID rclsid,
        ULONG cCategories,
        CATID rgcatid[]);

    END_INTERFACE
} ICatRegisterVtbl;
interface ICatRegister {
    CONST_VTBL ICatRegisterVtbl* lpVtbl;
};

#ifdef COBJMACROS
#ifndef WIDL_C_INLINE_WRAPPERS
/*** IUnknown methods ***/
#define ICatRegister_QueryInterface(This,riid,ppvObject) (This)->lpVtbl->QueryInterface(This,riid,ppvObject)
#define ICatRegister_AddRef(This) (This)->lpVtbl->AddRef(This)
#define ICatRegister_Release(This) (This)->lpVtbl->Release(This)
/*** ICatRegister methods ***/
#define ICatRegister_RegisterCategories(This,cCategories,rgCategoryInfo) (This)->lpVtbl->RegisterCategories(This,cCategories,rgCategoryInfo)
#define ICatRegister_UnRegisterCategories(This,cCategories,rgcatid) (This)->lpVtbl->UnRegisterCategories(This,cCategories,rgcatid)
#define ICatRegister_RegisterClassImplCategories(This,rclsid,cCategories,rgcatid) (This)->lpVtbl->RegisterClassImplCategories(This,rclsid,cCategories,rgcatid)
#define ICatRegister_UnRegisterClassImplCategories(This,rclsid,cCategories,rgcatid) (This)->lpVtbl->UnRegisterClassImplCategories(This,rclsid,cCategories,rgcatid)
#define ICatRegister_RegisterClassReqCategories(This,rclsid,cCategories,rgcatid) (This)->lpVtbl->RegisterClassReqCategories(This,rclsid,cCategories,rgcatid)
#define ICatRegister_UnRegisterClassReqCategories(This,rclsid,cCategories,rgcatid) (This)->lpVtbl->UnRegisterClassReqCategories(This,rclsid,cCategories,rgcatid)
#else
/*** IUnknown methods ***/
static FORCEINLINE HRESULT ICatRegister_QueryInterface(ICatRegister* This,REFIID riid,void **ppvObject) {
    return This->lpVtbl->QueryInterface(This,riid,ppvObject);
}
static FORCEINLINE ULONG ICatRegister_AddRef(ICatRegister* This) {
    return This->lpVtbl->AddRef(This);
}
static FORCEINLINE ULONG ICatRegister_Release(ICatRegister* This) {
    return This->lpVtbl->Release(This);
}
/*** ICatRegister methods ***/
static FORCEINLINE HRESULT ICatRegister_RegisterCategories(ICatRegister* This,ULONG cCategories,CATEGORYINFO rgCategoryInfo[]) {
    return This->lpVtbl->RegisterCategories(This,cCategories,rgCategoryInfo);
}
static FORCEINLINE HRESULT ICatRegister_UnRegisterCategories(ICatRegister* This,ULONG cCategories,CATID rgcatid[]) {
    return This->lpVtbl->UnRegisterCategories(This,cCategories,rgcatid);
}
static FORCEINLINE HRESULT ICatRegister_RegisterClassImplCategories(ICatRegister* This,REFCLSID rclsid,ULONG cCategories,CATID rgcatid[]) {
    return This->lpVtbl->RegisterClassImplCategories(This,rclsid,cCategories,rgcatid);
}
static FORCEINLINE HRESULT ICatRegister_UnRegisterClassImplCategories(ICatRegister* This,REFCLSID rclsid,ULONG cCategories,CATID rgcatid[]) {
    return This->lpVtbl->UnRegisterClassImplCategories(This,rclsid,cCategories,rgcatid);
}
static FORCEINLINE HRESULT ICatRegister_RegisterClassReqCategories(ICatRegister* This,REFCLSID rclsid,ULONG cCategories,CATID rgcatid[]) {
    return This->lpVtbl->RegisterClassReqCategories(This,rclsid,cCategories,rgcatid);
}
static FORCEINLINE HRESULT ICatRegister_UnRegisterClassReqCategories(ICatRegister* This,REFCLSID rclsid,ULONG cCategories,CATID rgcatid[]) {
    return This->lpVtbl->UnRegisterClassReqCategories(This,rclsid,cCategories,rgcatid);
}
#endif
#endif

#endif

HRESULT STDMETHODCALLTYPE ICatRegister_RegisterCategories_Proxy(
    ICatRegister* This,
    ULONG cCategories,
    CATEGORYINFO rgCategoryInfo[]);
void __RPC_STUB ICatRegister_RegisterCategories_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE ICatRegister_UnRegisterCategories_Proxy(
    ICatRegister* This,
    ULONG cCategories,
    CATID rgcatid[]);
void __RPC_STUB ICatRegister_UnRegisterCategories_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE ICatRegister_RegisterClassImplCategories_Proxy(
    ICatRegister* This,
    REFCLSID rclsid,
    ULONG cCategories,
    CATID rgcatid[]);
void __RPC_STUB ICatRegister_RegisterClassImplCategories_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE ICatRegister_UnRegisterClassImplCategories_Proxy(
    ICatRegister* This,
    REFCLSID rclsid,
    ULONG cCategories,
    CATID rgcatid[]);
void __RPC_STUB ICatRegister_UnRegisterClassImplCategories_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE ICatRegister_RegisterClassReqCategories_Proxy(
    ICatRegister* This,
    REFCLSID rclsid,
    ULONG cCategories,
    CATID rgcatid[]);
void __RPC_STUB ICatRegister_RegisterClassReqCategories_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE ICatRegister_UnRegisterClassReqCategories_Proxy(
    ICatRegister* This,
    REFCLSID rclsid,
    ULONG cCategories,
    CATID rgcatid[]);
void __RPC_STUB ICatRegister_UnRegisterClassReqCategories_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);

#endif  /* __ICatRegister_INTERFACE_DEFINED__ */

#endif

#ifndef _LPCATINFORMATION_DEFINED
#define _LPCATINFORMATION_DEFINED
/*****************************************************************************
 * ICatInformation interface
 */
#ifndef __ICatInformation_INTERFACE_DEFINED__
#define __ICatInformation_INTERFACE_DEFINED__

typedef ICatInformation *LPCATINFORMATION;

DEFINE_GUID(IID_ICatInformation, 0x0002e013, 0x0000, 0x0000, 0xc0,0x00, 0x00,0x00,0x00,0x00,0x00,0x46);
#if defined(__cplusplus) && !defined(CINTERFACE)
MIDL_INTERFACE("0002e013-0000-0000-c000-000000000046")
ICatInformation : public IUnknown
{
    virtual HRESULT STDMETHODCALLTYPE EnumCategories(
        LCID lcid,
        IEnumCATEGORYINFO **ppenumCategoryInfo) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetCategoryDesc(
        REFCATID rcatid,
        LCID lcid,
        LPWSTR *pszDesc) = 0;

    virtual HRESULT STDMETHODCALLTYPE EnumClassesOfCategories(
        ULONG cImplemented,
        const CATID rgcatidImpl[],
        ULONG cRequired,
        const CATID rgcatidReq[],
        IEnumGUID **ppenumClsid) = 0;

    virtual HRESULT STDMETHODCALLTYPE IsClassOfCategories(
        REFCLSID rclsid,
        ULONG cImplemented,
        const CATID rgcatidImpl[],
        ULONG cRequired,
        const CATID rgcatidReq[]) = 0;

    virtual HRESULT STDMETHODCALLTYPE EnumImplCategoriesOfClass(
        REFCLSID rclsid,
        IEnumGUID **ppenumCatid) = 0;

    virtual HRESULT STDMETHODCALLTYPE EnumReqCategoriesOfClass(
        REFCLSID rclsid,
        IEnumGUID **ppenumCatid) = 0;

};
#ifdef __CRT_UUID_DECL
__CRT_UUID_DECL(ICatInformation, 0x0002e013, 0x0000, 0x0000, 0xc0,0x00, 0x00,0x00,0x00,0x00,0x00,0x46)
#endif
#else
typedef struct ICatInformationVtbl {
    BEGIN_INTERFACE

    /*** IUnknown methods ***/
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ICatInformation* This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        ICatInformation* This);

    ULONG (STDMETHODCALLTYPE *Release)(
        ICatInformation* This);

    /*** ICatInformation methods ***/
    HRESULT (STDMETHODCALLTYPE *EnumCategories)(
        ICatInformation* This,
        LCID lcid,
        IEnumCATEGORYINFO **ppenumCategoryInfo);

    HRESULT (STDMETHODCALLTYPE *GetCategoryDesc)(
        ICatInformation* This,
        REFCATID rcatid,
        LCID lcid,
        LPWSTR *pszDesc);

    HRESULT (STDMETHODCALLTYPE *EnumClassesOfCategories)(
        ICatInformation* This,
        ULONG cImplemented,
        const CATID rgcatidImpl[],
        ULONG cRequired,
        const CATID rgcatidReq[],
        IEnumGUID **ppenumClsid);

    HRESULT (STDMETHODCALLTYPE *IsClassOfCategories)(
        ICatInformation* This,
        REFCLSID rclsid,
        ULONG cImplemented,
        const CATID rgcatidImpl[],
        ULONG cRequired,
        const CATID rgcatidReq[]);

    HRESULT (STDMETHODCALLTYPE *EnumImplCategoriesOfClass)(
        ICatInformation* This,
        REFCLSID rclsid,
        IEnumGUID **ppenumCatid);

    HRESULT (STDMETHODCALLTYPE *EnumReqCategoriesOfClass)(
        ICatInformation* This,
        REFCLSID rclsid,
        IEnumGUID **ppenumCatid);

    END_INTERFACE
} ICatInformationVtbl;
interface ICatInformation {
    CONST_VTBL ICatInformationVtbl* lpVtbl;
};

#ifdef COBJMACROS
#ifndef WIDL_C_INLINE_WRAPPERS
/*** IUnknown methods ***/
#define ICatInformation_QueryInterface(This,riid,ppvObject) (This)->lpVtbl->QueryInterface(This,riid,ppvObject)
#define ICatInformation_AddRef(This) (This)->lpVtbl->AddRef(This)
#define ICatInformation_Release(This) (This)->lpVtbl->Release(This)
/*** ICatInformation methods ***/
#define ICatInformation_EnumCategories(This,lcid,ppenumCategoryInfo) (This)->lpVtbl->EnumCategories(This,lcid,ppenumCategoryInfo)
#define ICatInformation_GetCategoryDesc(This,rcatid,lcid,pszDesc) (This)->lpVtbl->GetCategoryDesc(This,rcatid,lcid,pszDesc)
#define ICatInformation_EnumClassesOfCategories(This,cImplemented,rgcatidImpl,cRequired,rgcatidReq,ppenumClsid) (This)->lpVtbl->EnumClassesOfCategories(This,cImplemented,rgcatidImpl,cRequired,rgcatidReq,ppenumClsid)
#define ICatInformation_IsClassOfCategories(This,rclsid,cImplemented,rgcatidImpl,cRequired,rgcatidReq) (This)->lpVtbl->IsClassOfCategories(This,rclsid,cImplemented,rgcatidImpl,cRequired,rgcatidReq)
#define ICatInformation_EnumImplCategoriesOfClass(This,rclsid,ppenumCatid) (This)->lpVtbl->EnumImplCategoriesOfClass(This,rclsid,ppenumCatid)
#define ICatInformation_EnumReqCategoriesOfClass(This,rclsid,ppenumCatid) (This)->lpVtbl->EnumReqCategoriesOfClass(This,rclsid,ppenumCatid)
#else
/*** IUnknown methods ***/
static FORCEINLINE HRESULT ICatInformation_QueryInterface(ICatInformation* This,REFIID riid,void **ppvObject) {
    return This->lpVtbl->QueryInterface(This,riid,ppvObject);
}
static FORCEINLINE ULONG ICatInformation_AddRef(ICatInformation* This) {
    return This->lpVtbl->AddRef(This);
}
static FORCEINLINE ULONG ICatInformation_Release(ICatInformation* This) {
    return This->lpVtbl->Release(This);
}
/*** ICatInformation methods ***/
static FORCEINLINE HRESULT ICatInformation_EnumCategories(ICatInformation* This,LCID lcid,IEnumCATEGORYINFO **ppenumCategoryInfo) {
    return This->lpVtbl->EnumCategories(This,lcid,ppenumCategoryInfo);
}
static FORCEINLINE HRESULT ICatInformation_GetCategoryDesc(ICatInformation* This,REFCATID rcatid,LCID lcid,LPWSTR *pszDesc) {
    return This->lpVtbl->GetCategoryDesc(This,rcatid,lcid,pszDesc);
}
static FORCEINLINE HRESULT ICatInformation_EnumClassesOfCategories(ICatInformation* This,ULONG cImplemented,const CATID rgcatidImpl[],ULONG cRequired,const CATID rgcatidReq[],IEnumGUID **ppenumClsid) {
    return This->lpVtbl->EnumClassesOfCategories(This,cImplemented,rgcatidImpl,cRequired,rgcatidReq,ppenumClsid);
}
static FORCEINLINE HRESULT ICatInformation_IsClassOfCategories(ICatInformation* This,REFCLSID rclsid,ULONG cImplemented,const CATID rgcatidImpl[],ULONG cRequired,const CATID rgcatidReq[]) {
    return This->lpVtbl->IsClassOfCategories(This,rclsid,cImplemented,rgcatidImpl,cRequired,rgcatidReq);
}
static FORCEINLINE HRESULT ICatInformation_EnumImplCategoriesOfClass(ICatInformation* This,REFCLSID rclsid,IEnumGUID **ppenumCatid) {
    return This->lpVtbl->EnumImplCategoriesOfClass(This,rclsid,ppenumCatid);
}
static FORCEINLINE HRESULT ICatInformation_EnumReqCategoriesOfClass(ICatInformation* This,REFCLSID rclsid,IEnumGUID **ppenumCatid) {
    return This->lpVtbl->EnumReqCategoriesOfClass(This,rclsid,ppenumCatid);
}
#endif
#endif

#endif

HRESULT STDMETHODCALLTYPE ICatInformation_EnumCategories_Proxy(
    ICatInformation* This,
    LCID lcid,
    IEnumCATEGORYINFO **ppenumCategoryInfo);
void __RPC_STUB ICatInformation_EnumCategories_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE ICatInformation_GetCategoryDesc_Proxy(
    ICatInformation* This,
    REFCATID rcatid,
    LCID lcid,
    LPWSTR *pszDesc);
void __RPC_STUB ICatInformation_GetCategoryDesc_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE ICatInformation_RemoteEnumClassesOfCategories_Proxy(
    ICatInformation* This,
    ULONG cImplemented,
    const CATID rgcatidImpl[],
    ULONG cRequired,
    const CATID rgcatidReq[],
    IEnumGUID **ppenumClsid);
void __RPC_STUB ICatInformation_RemoteEnumClassesOfCategories_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE ICatInformation_RemoteIsClassOfCategories_Proxy(
    ICatInformation* This,
    REFCLSID rclsid,
    ULONG cImplemented,
    const CATID rgcatidImpl[],
    ULONG cRequired,
    const CATID rgcatidReq[]);
void __RPC_STUB ICatInformation_RemoteIsClassOfCategories_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE ICatInformation_EnumImplCategoriesOfClass_Proxy(
    ICatInformation* This,
    REFCLSID rclsid,
    IEnumGUID **ppenumCatid);
void __RPC_STUB ICatInformation_EnumImplCategoriesOfClass_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE ICatInformation_EnumReqCategoriesOfClass_Proxy(
    ICatInformation* This,
    REFCLSID rclsid,
    IEnumGUID **ppenumCatid);
void __RPC_STUB ICatInformation_EnumReqCategoriesOfClass_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT CALLBACK ICatInformation_EnumClassesOfCategories_Proxy(
    ICatInformation* This,
    ULONG cImplemented,
    const CATID rgcatidImpl[],
    ULONG cRequired,
    const CATID rgcatidReq[],
    IEnumGUID **ppenumClsid);
HRESULT __RPC_STUB ICatInformation_EnumClassesOfCategories_Stub(
    ICatInformation* This,
    ULONG cImplemented,
    const CATID rgcatidImpl[],
    ULONG cRequired,
    const CATID rgcatidReq[],
    IEnumGUID **ppenumClsid);
HRESULT CALLBACK ICatInformation_IsClassOfCategories_Proxy(
    ICatInformation* This,
    REFCLSID rclsid,
    ULONG cImplemented,
    const CATID rgcatidImpl[],
    ULONG cRequired,
    const CATID rgcatidReq[]);
HRESULT __RPC_STUB ICatInformation_IsClassOfCategories_Stub(
    ICatInformation* This,
    REFCLSID rclsid,
    ULONG cImplemented,
    const CATID rgcatidImpl[],
    ULONG cRequired,
    const CATID rgcatidReq[]);

#endif  /* __ICatInformation_INTERFACE_DEFINED__ */

#endif
#endif
/* Begin additional prototypes for all interfaces */


/* End additional prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __comcat_h__ */
