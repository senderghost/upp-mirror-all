/**
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER within this package.
 */

#ifndef _FTW_HXX
#define	_FTW_HXX

#include <sys/types.h>
#include <sys/stat.h>

#ifdef __cplusplus
extern "C" {
#endif

  struct FTW {
    int base;
    int level;
  };

  /* A regular file.  */
#define FTW_F 0
  /* A directory.  */
#define FTW_D 1
  /* An unreadable directory.  */
#define FTW_DNR	2
  /* An unstatable file.  */
#define FTW_NS 3
  /* A symbolic link (not supported).  */
#define FTW_SL 4
  /* A directory (all subdirs are visited). */
#define FTW_DP 5
  /* A symbolic link naming non-existing file (not supported).  */
#define FTW_SLN 6

  /* Do a physical walk (ignore symlinks).  */
#define FTW_PHYS 1
  /* Do report only files on same device as the argument (partial supported).  */
#define FTW_MOUNT 2
  /* Change to current directory while processing (unsupported).  */
#define FTW_CHDIR 4
  /* Do report files in directory before the directory itself.*/
#define FTW_DEPTH 8
  /* Tell callback to return FTW_* values instead of zero to continue and non-zero to terminate.  */
#define FTW_ACTIONRETVAL 16

  /* Continue with next sibling or with the first child-directory.  */
#define FTW_CONTINUE 0
  /* Return from ftw or nftw with FTW_STOP as return value.  */
#define FTW_STOP 1
  /* Valid only for FTW_D: Don't walk through the subtree. */
#define FTW_SKIP_SUBTREE 2
  /* Continue with FTW_DP callback for current directory (if FTW_DEPTH) and then its siblings.  */
#define FTW_SKIP_SIBLINGS 3

  int ftw (const char *, int (*) (const char *, const struct stat *, int), int);
  int ftw64 (const char *, int (*) (const char *, const struct stat64 *, int), int);

  int nftw (const char *, int (*) (const char *, const struct stat *, int , struct FTW *), int, int);
  int nftw64 (const char *, int (*) (const char *, const struct stat64 *, int , struct FTW *), int, int);

#ifdef __cplusplus
}
#endif

#endif
