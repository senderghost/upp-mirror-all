/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */
#ifndef __SENS_H__
#define __SENS_H__

#define CONNECTION_LAN 0x00000001
#define CONNECTION_WAN 0x00000002
#define CONNECTION_AOL 0x00000004

DEFINE_GUID(SENSGUID_PUBLISHER,0x5fee1bd6,0x5b9b,0x11d1,0x8d,0xd2,0x00,0xaa,0x00,0x4a,0xbd,0x5e);
DEFINE_GUID(SENSGUID_SUBSCRIBER_LCE,0xd3938ab0,0x5b9d,0x11d1,0x8d,0xd2,0x00,0xaa,0x00,0x4a,0xbd,0x5e);
DEFINE_GUID(SENSGUID_SUBSCRIBER_WININET,0xd3938ab5,0x5b9d,0x11d1,0x8d,0xd2,0x00,0xaa,0x00,0x4a,0xbd,0x5e);
DEFINE_GUID(SENSGUID_EVENTCLASS_NETWORK,0xd5978620,0x5b9f,0x11d1,0x8d,0xd2,0x00,0xaa,0x00,0x4a,0xbd,0x5e);
DEFINE_GUID(SENSGUID_EVENTCLASS_LOGON,0xd5978630,0x5b9f,0x11d1,0x8d,0xd2,0x00,0xaa,0x00,0x4a,0xbd,0x5e);
DEFINE_GUID(SENSGUID_EVENTCLASS_ONNOW,0xd5978640,0x5b9f,0x11d1,0x8d,0xd2,0x00,0xaa,0x00,0x4a,0xbd,0x5e);
DEFINE_GUID(SENSGUID_EVENTCLASS_LOGON2,0xd5978650,0x5b9f,0x11d1,0x8d,0xd2,0x00,0xaa,0x00,0x4a,0xbd,0x5e);

#endif
