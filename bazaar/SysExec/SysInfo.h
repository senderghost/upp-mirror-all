#ifndef _SysExec_SysInfo_h_
#define _SysExec_SysInfo_h_

#include <Core/Core.h>

NAMESPACE_UPP

#ifdef PLATFORM_WIN32

////////////////////////////////////////////////////////////////////////////////////
// utility functions to if running Vista or newer OSs
bool IsVistaOrLater(void);

////////////////////////////////////////////////////////////////////////////////////
// check if user is running in admin mode
bool IsUserAdministrator(void);

#endif

END_UPP_NAMESPACE

#endif
