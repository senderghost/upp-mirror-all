/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */
#ifdef __cplusplus
extern "C"{
#endif

#ifndef __IID_DEFINED__
#define __IID_DEFINED__
  typedef struct _IID {
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char c[8];
  } IID;
#endif

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
  typedef IID CLSID;
#endif

  const IID IID_ICatalog = {0x6eb22870,0x8a19,0x11d0,{0x81,0xb6,0x00,0xa0,0xc9,0x23,0x1c,0x29}};
  const IID IID_IComponentUtil = {0x6eb22873,0x8a19,0x11d0,{0x81,0xb6,0x00,0xa0,0xc9,0x23,0x1c,0x29}};
  const IID IID_IPackageUtil = {0x6eb22874,0x8a19,0x11d0,{0x81,0xb6,0x00,0xa0,0xc9,0x23,0x1c,0x29}};
  const IID IID_IRemoteComponentUtil = {0x6eb22875,0x8a19,0x11d0,{0x81,0xb6,0x00,0xa0,0xc9,0x23,0x1c,0x29}};
  const IID IID_IRoleAssociationUtil = {0x6eb22876,0x8a19,0x11d0,{0x81,0xb6,0x00,0xa0,0xc9,0x23,0x1c,0x29}};
  const IID LIBID_MTSAdmin = {0x6eb22880,0x8a19,0x11d0,{0x81,0xb6,0x00,0xa0,0xc9,0x23,0x1c,0x29}};
  const CLSID CLSID_Catalog = {0x6eb22881,0x8a19,0x11d0,{0x81,0xb6,0x00,0xa0,0xc9,0x23,0x1c,0x29}};
  const CLSID CLSID_CatalogObject = {0x6eb22882,0x8a19,0x11d0,{0x81,0xb6,0x00,0xa0,0xc9,0x23,0x1c,0x29}};
  const CLSID CLSID_CatalogCollection = {0x6eb22883,0x8a19,0x11d0,{0x81,0xb6,0x00,0xa0,0xc9,0x23,0x1c,0x29}};
  const CLSID CLSID_ComponentUtil = {0x6eb22884,0x8a19,0x11d0,{0x81,0xb6,0x00,0xa0,0xc9,0x23,0x1c,0x29}};
  const CLSID CLSID_PackageUtil = {0x6eb22885,0x8a19,0x11d0,{0x81,0xb6,0x00,0xa0,0xc9,0x23,0x1c,0x29}};
  const CLSID CLSID_RemoteComponentUtil = {0x6eb22886,0x8a19,0x11d0,{0x81,0xb6,0x00,0xa0,0xc9,0x23,0x1c,0x29}};
  const CLSID CLSID_RoleAssociationUtil = {0x6eb22887,0x8a19,0x11d0,{0x81,0xb6,0x00,0xa0,0xc9,0x23,0x1c,0x29}};

#ifdef __cplusplus
}
#endif
