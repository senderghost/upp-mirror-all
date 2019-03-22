# tdbcConfig.sh --
#
# This shell script (for sh) is generated automatically by TDBC's configure
# script. It will create shell variables for most of the configuration options
# discovered by the configure script. This script is intended to be included
# by the configure scripts for TDBC extensions so that they don't have to
# figure this all out for themselves.
#
# The information in this file is specific to a single platform.
#
# RCS: @(#) $Id$

# TDBC's version number
tdbc_VERSION=1.0.6
TDBC_VERSION=1.0.6

# Name of the TDBC library - may be either a static or shared library
tdbc_LIB_FILE=tdbc106.dll
TDBC_LIB_FILE=tdbc106.dll

# String to pass to the linker to pick up the TDBC library from its build dir
tdbc_BUILD_LIB_SPEC="-LC:/mingw810/i686-810-win32-dwarf-rt_v6-rev0/build/tcl8.6.8/win/pkgs/tdbc1.0.6 -ltdbc106"
TDBC_BUILD_LIB_SPEC="-LC:/mingw810/i686-810-win32-dwarf-rt_v6-rev0/build/tcl8.6.8/win/pkgs/tdbc1.0.6 -ltdbc106"

# String to pass to the linker to pick up the TDBC library from its installed
# dir.
tdbc_LIB_SPEC="-LC:/mingw810/i686-810-win32-dwarf-rt_v6-rev0/mingw32/opt/lib/tdbc1.0.6 -ltdbc106"
TDBC_LIB_SPEC="-LC:/mingw810/i686-810-win32-dwarf-rt_v6-rev0/mingw32/opt/lib/tdbc1.0.6 -ltdbc106"

# Name of the TBDC stub library
tdbc_STUB_LIB_FILE="libtdbcstub106.a"
TDBC_STUB_LIB_FILE="libtdbcstub106.a"

# String to pass to the linker to pick up the TDBC stub library from its
# build directory
tdbc_BUILD_STUB_LIB_SPEC="-LC:/mingw810/i686-810-win32-dwarf-rt_v6-rev0/build/tcl8.6.8/win/pkgs/tdbc1.0.6 -ltdbcstub106"
TDBC_BUILD_STUB_LIB_SPEC="-LC:/mingw810/i686-810-win32-dwarf-rt_v6-rev0/build/tcl8.6.8/win/pkgs/tdbc1.0.6 -ltdbcstub106"

# String to pass to the linker to pick up the TDBC stub library from its
# installed directory
tdbc_STUB_LIB_SPEC="-LC:/mingw810/i686-810-win32-dwarf-rt_v6-rev0/mingw32/opt/lib/tdbc1.0.6 -ltdbcstub106"
TDBC_STUB_LIB_SPEC="-LC:/mingw810/i686-810-win32-dwarf-rt_v6-rev0/mingw32/opt/lib/tdbc1.0.6 -ltdbcstub106"

# Path name of the TDBC stub library in its build directory
tdbc_BUILD_STUB_LIB_PATH="C:/mingw810/i686-810-win32-dwarf-rt_v6-rev0/build/tcl8.6.8/win/pkgs/tdbc1.0.6/libtdbcstub106.a"
TDBC_BUILD_STUB_LIB_PATH="C:/mingw810/i686-810-win32-dwarf-rt_v6-rev0/build/tcl8.6.8/win/pkgs/tdbc1.0.6/libtdbcstub106.a"

# Path name of the TDBC stub library in its installed directory
tdbc_STUB_LIB_PATH="C:/mingw810/i686-810-win32-dwarf-rt_v6-rev0/mingw32/opt/lib/tdbc1.0.6/libtdbcstub106.a"
TDBC_STUB_LIB_PATH="C:/mingw810/i686-810-win32-dwarf-rt_v6-rev0/mingw32/opt/lib/tdbc1.0.6/libtdbcstub106.a"

# Location of the top-level source directories from which TDBC was built.
# This is the directory that contains doc/, generic/ and so on.  If TDBC
# was compiled in a directory other than the source directory, this still
# points to the location of the sources, not the location where TDBC was
# compiled.
tdbc_SRC_DIR="C:/mingw810/src/tcl8.6.8/pkgs/tdbc1.0.6"
TDBC_SRC_DIR="C:/mingw810/src/tcl8.6.8/pkgs/tdbc1.0.6"

# String to pass to the compiler so that an extension can find installed TDBC
# headers
tdbc_INCLUDE_SPEC="-I/c/mingw810/i686-810-win32-dwarf-rt_v6-rev0/mingw32/opt/include"
TDBC_INCLUDE_SPEC="-I/c/mingw810/i686-810-win32-dwarf-rt_v6-rev0/mingw32/opt/include"

# String to pass to the compiler so that an extension can find TDBC headers
# in the source directory
tdbc_BUILD_INCLUDE_SPEC="-IC:/mingw810/src/tcl8.6.8/pkgs/tdbc1.0.6/generic"
TDBC_BUILD_INCLUDE_SPEC="-IC:/mingw810/src/tcl8.6.8/pkgs/tdbc1.0.6/generic"

# Path name where .tcl files in the tdbc package appear at run time.
tdbc_LIBRARY_PATH="/c/mingw810/i686-810-win32-dwarf-rt_v6-rev0/mingw32/opt/lib/tdbc1.0.6"
TDBC_LIBRARY_PATH="/c/mingw810/i686-810-win32-dwarf-rt_v6-rev0/mingw32/opt/lib/tdbc1.0.6"

# Path name where .tcl files in the tdbc package appear at build time.
tdbc_BUILD_LIBRARY_PATH="C:/mingw810/src/tcl8.6.8/pkgs/tdbc1.0.6/library"
TDBC_BUILD_LIBRARY_PATH="C:/mingw810/src/tcl8.6.8/pkgs/tdbc1.0.6/library"

# Additional flags that must be passed to the C compiler to use tdbc
tdbc_CFLAGS=
TDBC_CFLAGS=

