#!/usr/bin/env sh

THISDIR="$(dirname $0)"
test "$THISDIR" = "." && THISDIR=${PWD}

RESULT=$("${THISDIR}"/python-config.sh "$@")

exec_prefix_win=$("${THISDIR}"/python-config.sh --exec-prefix)
exec_prefix_unix=/c/mingw520/i686-520-win32-dwarf-rt_v4-rev0/mingw32/opt
echo $(echo $RESULT | sed "s#${exec_prefix_win}#${exec_prefix_unix}#g")
