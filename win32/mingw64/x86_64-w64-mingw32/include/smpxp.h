/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */
#define BASE_ID 0x6600

#define PR_SAMPLE_DISPLAY_NAME PROP_TAG (PT_TSTRING,(BASE_ID + 0x0001))
#define PR_SAMPLE_EMAIL_ADDR_TYPE PROP_TAG (PT_TSTRING,(BASE_ID + 0x0002))
#define PR_SAMPLE_EMAIL_ADDRESS PROP_TAG (PT_TSTRING,(BASE_ID + 0x0003))
#define PR_SAMPLE_INBOUND_DIR PROP_TAG (PT_TSTRING,(BASE_ID + 0x0004))
#define PR_SAMPLE_OUTBOUND_DIR PROP_TAG (PT_TSTRING,(BASE_ID + 0x0005))
#define PR_SAMPLE_FILENAME PROP_TAG (PT_TSTRING,(BASE_ID + 0x0006))
#define PR_SAMPLE_DIRECTORY PROP_TAG (PT_TSTRING,(BASE_ID + 0x0007))
#define PR_SAMPLE_FLAGS PROP_TAG (PT_LONG,(BASE_ID + 0x0008))
#define PR_SAMPLE_FLAG_PEER_TO_PEER ((ULONG) 0x00000001)
#define PR_SAMPLE_FLAG_UI_ALWAYS ((ULONG) 0x00000002)
#define PR_SAMPLE_FLAG_LOG_EVENTS ((ULONG) 0x00000004)
#define PR_SAMPLE_FLAG_SAVE_DATA ((ULONG) 0x00000008)
#define PR_SAMPLE_LOGFILE PROP_TAG (PT_TSTRING,(BASE_ID + 0x0009))
#define PR_SAMPLE_LOGHIGHWATER PROP_TAG (PT_LONG,(BASE_ID + 0x000A))
#define PR_SAMPLE_LOGLOWWATER PROP_TAG (PT_LONG,(BASE_ID + 0x000B))
