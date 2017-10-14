/**
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER within this package.
 */

#ifndef __DPAPI_H__
#define __DPAPI_H__

#ifndef DPAPI_IMP
#define DPAPI_IMP DECLSPEC_IMPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if WINAPI_FAMILY_PARTITION (WINAPI_PARTITION_DESKTOP)

#define CRYPTPROTECT_DEFAULT_PROVIDER { 0xdf9d8cd0, 0x1501, 0x11d1,{ 0x8c, 0x7a, 0x00, 0xc0, 0x4f, 0xc2, 0x97, 0xeb } }

#define szFORCE_KEY_PROTECTION "ForceKeyProtection"

#define dwFORCE_KEY_PROTECTION_DISABLED 0x0
#define dwFORCE_KEY_PROTECTION_USER_SELECT 0x1
#define dwFORCE_KEY_PROTECTION_HIGH 0x2

#define CRYPTPROTECT_PROMPT_ON_UNPROTECT 0x1
#define CRYPTPROTECT_PROMPT_ON_PROTECT 0x2
#define CRYPTPROTECT_PROMPT_RESERVED 0x04
#define CRYPTPROTECT_PROMPT_STRONG 0x08
#define CRYPTPROTECT_PROMPT_REQUIRE_STRONG 0x10

#define CRYPTPROTECT_UI_FORBIDDEN 0x1
#define CRYPTPROTECT_LOCAL_MACHINE 0x4
#define CRYPTPROTECT_CRED_SYNC 0x8
#define CRYPTPROTECT_AUDIT 0x10
#define CRYPTPROTECT_NO_RECOVERY 0x20
#define CRYPTPROTECT_VERIFY_PROTECTION 0x40
#define CRYPTPROTECT_CRED_REGENERATE 0x80

#define CRYPTPROTECT_FIRST_RESERVED_FLAGVAL 0x0fffffff
#define CRYPTPROTECT_LAST_RESERVED_FLAGVAL 0xffffffff

#define CRYPTPROTECTMEMORY_BLOCK_SIZE 16

#define CRYPTPROTECTMEMORY_SAME_PROCESS 0x0
#define CRYPTPROTECTMEMORY_CROSS_PROCESS 0x1
#define CRYPTPROTECTMEMORY_SAME_LOGON 0x2

#ifndef CRYPTO_BLOBS_DEFINED
#define CRYPTO_BLOBS_DEFINED
  typedef struct _CRYPTOAPI_BLOB {
    DWORD cbData;
    BYTE *pbData;
  } CRYPT_INTEGER_BLOB,*PCRYPT_INTEGER_BLOB;

  typedef CRYPT_INTEGER_BLOB CERT_BLOB,*PCERT_BLOB;
  typedef CRYPT_INTEGER_BLOB CERT_NAME_BLOB,*PCERT_NAME_BLOB;
  typedef CRYPT_INTEGER_BLOB CERT_RDN_VALUE_BLOB,*PCERT_RDN_VALUE_BLOB;
  typedef CRYPT_INTEGER_BLOB CRL_BLOB,*PCRL_BLOB;
  typedef CRYPT_INTEGER_BLOB CRYPT_ATTR_BLOB,*PCRYPT_ATTR_BLOB;
  typedef CRYPT_INTEGER_BLOB CRYPT_DATA_BLOB,*PCRYPT_DATA_BLOB;
  typedef CRYPT_INTEGER_BLOB CRYPT_DER_BLOB,*PCRYPT_DER_BLOB;
  typedef CRYPT_INTEGER_BLOB CRYPT_DIGEST_BLOB,*PCRYPT_DIGEST_BLOB;
  typedef CRYPT_INTEGER_BLOB CRYPT_HASH_BLOB,*PCRYPT_HASH_BLOB;
  typedef CRYPT_INTEGER_BLOB CRYPT_OBJID_BLOB,*PCRYPT_OBJID_BLOB;
  typedef CRYPT_INTEGER_BLOB CRYPT_UINT_BLOB,*PCRYPT_UINT_BLOB;
  typedef CRYPT_INTEGER_BLOB DATA_BLOB,*PDATA_BLOB;
#endif

  typedef struct _CRYPTPROTECT_PROMPTSTRUCT {
    DWORD cbSize;
    DWORD dwPromptFlags;
    HWND hwndApp;
    LPCWSTR szPrompt;
  } CRYPTPROTECT_PROMPTSTRUCT,*PCRYPTPROTECT_PROMPTSTRUCT;

  DPAPI_IMP WINBOOL WINAPI CryptProtectData (DATA_BLOB *pDataIn, LPCWSTR szDataDescr, DATA_BLOB *pOptionalEntropy, PVOID pvReserved, CRYPTPROTECT_PROMPTSTRUCT *pPromptStruct, DWORD dwFlags, DATA_BLOB *pDataOut);
  DPAPI_IMP WINBOOL WINAPI CryptUnprotectData (DATA_BLOB *pDataIn, LPWSTR *ppszDataDescr, DATA_BLOB *pOptionalEntropy, PVOID pvReserved, CRYPTPROTECT_PROMPTSTRUCT *pPromptStruct, DWORD dwFlags, DATA_BLOB *pDataOut);
  DPAPI_IMP WINBOOL WINAPI CryptProtectMemory (LPVOID pDataIn, DWORD cbDataIn, DWORD dwFlags);
  DPAPI_IMP WINBOOL WINAPI CryptUnprotectMemory (LPVOID pDataIn, DWORD cbDataIn, DWORD dwFlags);
#if NTDDI_VERSION >= 0x06020000
  WINBOOL WINAPI CryptProtectDataNoUI (DATA_BLOB *pDataIn, LPCWSTR szDataDescr, DATA_BLOB *pOptionalEntropy, PVOID pvReserved, CRYPTPROTECT_PROMPTSTRUCT *pPromptStruct, DWORD dwFlags, const BYTE *pbOptionalPassword, DWORD cbOptionalPassword, DATA_BLOB *pDataOut);
  WINBOOL WINAPI CryptUnprotectDataNoUI (DATA_BLOB *pDataIn, LPWSTR *ppszDataDescr, DATA_BLOB *pOptionalEntropy, PVOID pvReserved, CRYPTPROTECT_PROMPTSTRUCT *pPromptStruct, DWORD dwFlags, const BYTE *pbOptionalPassword, DWORD cbOptionalPassword, DATA_BLOB *pDataOut);
#endif
#if NTDDI_VERSION >= 0x06000000
  DPAPI_IMP WINBOOL WINAPI CryptUpdateProtectedState (PSID pOldSid, LPCWSTR pwszOldPassword, DWORD dwFlags, DWORD *pdwSuccessCount, DWORD *pdwFailureCount);
#endif

#endif

#ifdef __cplusplus
}
#endif

#endif
