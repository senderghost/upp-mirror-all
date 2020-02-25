/*** Autogenerated by WIDL 4.12.1 from include/napcertrelyingparty.idl - Do not edit ***/

#ifdef _WIN32
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif
#include <rpc.h>
#include <rpcndr.h>
#endif

#ifndef COM_NO_WINDOWS_H
#include <windows.h>
#include <ole2.h>
#endif

#ifndef __napcertrelyingparty_h__
#define __napcertrelyingparty_h__

/* Forward declarations */

#ifndef __INapCertRelyingParty_FWD_DEFINED__
#define __INapCertRelyingParty_FWD_DEFINED__
typedef interface INapCertRelyingParty INapCertRelyingParty;
#ifdef __cplusplus
interface INapCertRelyingParty;
#endif /* __cplusplus */
#endif

/* Headers for imported files */

#include <naptypes.h>
#include <unknwn.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <winapifamily.h>

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

#include <wincrypt.h>

__MINGW_ATTRIB_UNUSED static const UINT32 NapAfwZonePropId = CERT_FIRST_USER_PROP_ID;
__MINGW_ATTRIB_UNUSED static const UINT32 NapAfwProtectionLevelPropId = CERT_FIRST_USER_PROP_ID + 1;

EXTERN_C const CLSID CLSID_NapCertRelyingParty;
/*****************************************************************************
 * INapCertRelyingParty interface
 */
#ifndef __INapCertRelyingParty_INTERFACE_DEFINED__
#define __INapCertRelyingParty_INTERFACE_DEFINED__

DEFINE_GUID(IID_INapCertRelyingParty, 0x62c02ffc, 0x4c77, 0x4158, 0x87,0x54, 0x78,0x2d,0x5b,0x4e,0xe6,0x6e);
#if defined(__cplusplus) && !defined(CINTERFACE)
MIDL_INTERFACE("62c02ffc-4c77-4158-8754-782d5b4ee66e")
INapCertRelyingParty : public IUnknown
{
    virtual HRESULT STDMETHODCALLTYPE SubscribeCertByGroup(
        EnforcementEntityId id,
        const BSTR subscriberName,
        const VARIANT *reserved,
        WINBOOL *certExists) = 0;

    virtual HRESULT STDMETHODCALLTYPE UnSubscribeCertByGroup(
        EnforcementEntityId id,
        const VARIANT *reserved) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetSubscribedRelyingParties(
        EnforcementEntityCount *count,
        EnforcementEntityId **relyingParties) = 0;

};
#ifdef __CRT_UUID_DECL
__CRT_UUID_DECL(INapCertRelyingParty, 0x62c02ffc, 0x4c77, 0x4158, 0x87,0x54, 0x78,0x2d,0x5b,0x4e,0xe6,0x6e)
#endif
#else
typedef struct INapCertRelyingPartyVtbl {
    BEGIN_INTERFACE

    /*** IUnknown methods ***/
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        INapCertRelyingParty *This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        INapCertRelyingParty *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        INapCertRelyingParty *This);

    /*** INapCertRelyingParty methods ***/
    HRESULT (STDMETHODCALLTYPE *SubscribeCertByGroup)(
        INapCertRelyingParty *This,
        EnforcementEntityId id,
        const BSTR subscriberName,
        const VARIANT *reserved,
        WINBOOL *certExists);

    HRESULT (STDMETHODCALLTYPE *UnSubscribeCertByGroup)(
        INapCertRelyingParty *This,
        EnforcementEntityId id,
        const VARIANT *reserved);

    HRESULT (STDMETHODCALLTYPE *GetSubscribedRelyingParties)(
        INapCertRelyingParty *This,
        EnforcementEntityCount *count,
        EnforcementEntityId **relyingParties);

    END_INTERFACE
} INapCertRelyingPartyVtbl;

interface INapCertRelyingParty {
    CONST_VTBL INapCertRelyingPartyVtbl* lpVtbl;
};

#ifdef COBJMACROS
#ifndef WIDL_C_INLINE_WRAPPERS
/*** IUnknown methods ***/
#define INapCertRelyingParty_QueryInterface(This,riid,ppvObject) (This)->lpVtbl->QueryInterface(This,riid,ppvObject)
#define INapCertRelyingParty_AddRef(This) (This)->lpVtbl->AddRef(This)
#define INapCertRelyingParty_Release(This) (This)->lpVtbl->Release(This)
/*** INapCertRelyingParty methods ***/
#define INapCertRelyingParty_SubscribeCertByGroup(This,id,subscriberName,reserved,certExists) (This)->lpVtbl->SubscribeCertByGroup(This,id,subscriberName,reserved,certExists)
#define INapCertRelyingParty_UnSubscribeCertByGroup(This,id,reserved) (This)->lpVtbl->UnSubscribeCertByGroup(This,id,reserved)
#define INapCertRelyingParty_GetSubscribedRelyingParties(This,count,relyingParties) (This)->lpVtbl->GetSubscribedRelyingParties(This,count,relyingParties)
#else
/*** IUnknown methods ***/
static FORCEINLINE HRESULT INapCertRelyingParty_QueryInterface(INapCertRelyingParty* This,REFIID riid,void **ppvObject) {
    return This->lpVtbl->QueryInterface(This,riid,ppvObject);
}
static FORCEINLINE ULONG INapCertRelyingParty_AddRef(INapCertRelyingParty* This) {
    return This->lpVtbl->AddRef(This);
}
static FORCEINLINE ULONG INapCertRelyingParty_Release(INapCertRelyingParty* This) {
    return This->lpVtbl->Release(This);
}
/*** INapCertRelyingParty methods ***/
static FORCEINLINE HRESULT INapCertRelyingParty_SubscribeCertByGroup(INapCertRelyingParty* This,EnforcementEntityId id,const BSTR subscriberName,const VARIANT *reserved,WINBOOL *certExists) {
    return This->lpVtbl->SubscribeCertByGroup(This,id,subscriberName,reserved,certExists);
}
static FORCEINLINE HRESULT INapCertRelyingParty_UnSubscribeCertByGroup(INapCertRelyingParty* This,EnforcementEntityId id,const VARIANT *reserved) {
    return This->lpVtbl->UnSubscribeCertByGroup(This,id,reserved);
}
static FORCEINLINE HRESULT INapCertRelyingParty_GetSubscribedRelyingParties(INapCertRelyingParty* This,EnforcementEntityCount *count,EnforcementEntityId **relyingParties) {
    return This->lpVtbl->GetSubscribedRelyingParties(This,count,relyingParties);
}
#endif
#endif

#endif


#endif  /* __INapCertRelyingParty_INTERFACE_DEFINED__ */

#endif
/* Begin additional prototypes for all interfaces */

ULONG           __RPC_USER BSTR_UserSize     (ULONG *, ULONG, BSTR *);
unsigned char * __RPC_USER BSTR_UserMarshal  (ULONG *, unsigned char *, BSTR *);
unsigned char * __RPC_USER BSTR_UserUnmarshal(ULONG *, unsigned char *, BSTR *);
void            __RPC_USER BSTR_UserFree     (ULONG *, BSTR *);
ULONG           __RPC_USER VARIANT_UserSize     (ULONG *, ULONG, VARIANT *);
unsigned char * __RPC_USER VARIANT_UserMarshal  (ULONG *, unsigned char *, VARIANT *);
unsigned char * __RPC_USER VARIANT_UserUnmarshal(ULONG *, unsigned char *, VARIANT *);
void            __RPC_USER VARIANT_UserFree     (ULONG *, VARIANT *);

/* End additional prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __napcertrelyingparty_h__ */
