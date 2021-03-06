CONFIG_ARGS="$*" 
AC_INIT(zzcat.c)
AC_PREREQ(2.49)
AC_COPYRIGHT([Guido Draheim <guido@gmx.de> for ZZipLib.SF.net])
AC_REVISION()
ln -s . uses # _AC_CONFIG_AUX_DIR(uses)
# =======================================================================
AC_SUBST(CONFIG_ARGS)
AC_CANONICAL_SYSTEM
AC_SET_DEFAULT_PATHS_SYSTEM
# -----------------------------------------------------------------------
AC_ARG_ENABLE(thread-safe,AC_HELP_STRING([--disable-thread-safe],
	[disable thread-safe libtool option]),, with_thread_safe="yes")
THREAD_SAFE=""
test "$with_thread_safe" = "yes" && THREAD_SAFE="-thread-safe"
test "$with_thread_safe" = "$host_os" && THREAD_SAFE="-thread-safe"
AC_SUBST(THREAD_SAFE)
if test -n "$THREAD_SAFE" ; then
  AC_MSG_RESULT(...using thread-safe linkage)
else
  AC_MSG_RESULT(disabled thread-safe linkage)
fi
# ----------------------------------------------------------------
AC_MSG_CHECKING(zlib install prefix)
AC_ARG_WITH(zlib, AC_HELP_STRING([--with-zlib],
	[zlib prefix (e.g. '$HOME/software')]),  , [with_zlib="no"])
if test "${with_zlib}" = yes ; then # choose --prefix paths
   if test "${prefix}" = NONE ; then
      AC_MSG_RESULT(oops, but only itself...)
      AC_MSG_ERROR(--with-zlib requires a path argument or a --prefix path set)
   fi
   with_zlib="$prefix"
fi

if test ".$with_zlib" = ".no" ; then
   AC_MSG_RESULT(none)
elif test ".$with_zlib" = "./usr" ; then
   AC_MSG_RESULT([oops, ignored (may try --with-zlib=/usr/.)])
else
   if test ! -d "$with_zlib/include" ; then
      AC_MSG_RESULT(oops, given but...)
      AC_MSG_ERROR("$with_zlib/include" is not a directory)
   fi
   if test ! -d "$with_zlib/lib" ; then
      AC_MSG_RESULT(oops, given but...)
      AC_MSG_ERROR("$with_zlib/lib" is not a directory)
   fi
   CPPFLAGS="$CPPFLAGS -I$with_zlib/include"
   LDFLAGS="$LDFLAGS -L$with_zlib/lib"
   AC_MSG_RESULT($with_zlib)
   AC_MSG_RESULT(..adding CPPFLAGS -I$with_zlib/include)
   AC_MSG_RESULT(..adding LDFLAGS -L$with_zlib/include)
fi
# -----------------------------------------------------------------------
AC_SPEC_PACKAGE_VERSION(zziplib.spec)
AM_INIT_AUTOMAKE($PACKAGE,$VERSION)

AC_PROG_CC
AC_PROG_INSTALL
AC_LIBTOOL_WIN32_DLL
AM_PROG_LIBTOOL
AC_SET_RELEASEINFO_VERSIONINFO

# -----------------------------------------------------------------------
AC_MSG_RESULT([creating zzip-msvc.in via zzip-msvc.sed of config.h.in])
sed -f zzip-msvc.sed config.h.in >zzip-msvc.in
AM_CONFIG_HEADER(config.h)
AX_PREFIX_CONFIG_H([zzip-config.h],[zzip])
AX_PREFIX_CONFIG_H([zzip-msvc.h],[zzip],[zzip-msvc.in])
AM_MAINTAINER_MODE

AC_PATH_PROGS(PERL, perl5 perl, echo no perl found for)
AC_PATH_PROGS(PHP,  php-standalone php, echo no php found for)
AC_PATH_PROGS(MKZIP, zip pkzip, :)
AC_PATH_PROGS(XMLTO, xmlto, :)

AC_C_INLINE
AC_C_CONST
AC_STDC_HEADERS
AC_HEADER_DIRENT
AC_CHECK_HEADERS(stdint.h unistd.h windows.h winnt.h zlib.h sys/int_types.h) 
AC_CHECK_HEADERS(sys/types.h sys/mman.h sys/stat.h sys/param.h) dnl posix'ish

AC_TYPE_OFF_T
AC_COMPILE_CHECK_SIZEOF(short)
AC_COMPILE_CHECK_SIZEOF(int)
AC_COMPILE_CHECK_SIZEOF(long)
AC_COMPILE_CHECK_SIZEOF(size_t)
dnl -------------------------------------------------------------
AC_MSG_CHECKING(for zlib being found)
if test "_$ac_cv_header_zlib_h" != "_yes" ; then
  AC_MSG_RESULT(dnl
...oops: zlib.h not found - try adding some CPPFLAGS to configure call)
         AC_MSG_RESULT(dnl
...note: and when linkage fails you might also need to set some LDFLAGS)
  case "$prefix" in
    NONE|/usr) 
            AC_MSG_RESULT(dnl
...note: both can be set by specifying the install prefix of the zlib library)
            AC_MSG_RESULT(dnl
...note: via --with-zlib=path ... it will test for -Ipath/include -Lpath/lib)
    ;;
    *) if test -d $prefix/include ; then
         AC_MSG_RESULT(dnl
...note: -I$prefix/include is not added to CPPFLAGS automatically and)
         AC_MSG_RESULT(dnl
...note: neither is -L$prefix/lib for LDFLAGS .. both will be if you specify)
         AC_MSG_RESULT(dnl
...note: --with-zlib to configure call, or use --with-zlib=installprefix)
       fi
     ;;
  esac
  AC_MSG_ERROR(zlib.h not found: "zlib" is required to build "$PACKAGE")
  exit 1
fi
AC_MSG_RESULT(yes)
# ----------------------------------------------------------------
AC_MSG_CHECKING(docdir default)
AC_ARG_WITH(docdir, AC_HELP_STRING([--with-docdir],
	[docdir prefix (prefix/share/doc)]),  , [with_docdir="no"])
case "${with_docdir}" in
 prefix/*)  docdir=` echo "$withval" | sed 's/^prefix/${prefix}'` ;;
 datadir/*) docdir=` echo "$withval" | sed 's/^datadir/${datadir}'` ;;
 yes) docdir='${prefix}/doc' ;;
 no)  docdir='${datadir}/doc' ;;
 /*|\\*|[a-zA-Z]:*) docdir="$with_docdir"  ;;
 *) AC_MSG_RESULT(oops)
    AC_MSG_ERROR(bad value ${withval} for --with-docdir) 
 ;;
esac
AC_SUBST(docdir)
AC_MSG_RESULT($docdir)
# ----------------------------------------------------------------
AC_MSG_CHECKING(whether io-wrap needs to wrap system calls)
AC_ARG_WITH(wrapwrap, AC_HELP_STRING([--with-wrapwrap],
        [io-wrap needs to wrap systemcalls (no)]), , [with_wrapwrap="auto"])
case "$with_wrapwrap" in
  yes|no) WRAPWRAP="$with_wrapwrap"  ;;
  auto)
     if test "$ac_cv_sizeof_size_t" != "$ac_cv_sizeof_int" 
     then WRAPWRAP="yes" ; else WRAPWRAP="no" ; fi ;;
  *) AC_MSG_RESULT(oops)
     AC_MSG_ERROR(bad value $with_wrapwrap for --with-wrapwrap) ;;
esac
if test "$WRAPWRAP" = "yes" ; then
  AC_DEFINE(WRAPWRAP, 1, [io-wrap needs to wrap systemcalls])
fi
AC_MSG_RESULT($WRAPWRAP)
# ----------------------------------------------------------------
AC_MSG_CHECKING(whether using debugging messages in libraries)
AC_ARG_WITH(debug, AC_HELP_STRING([--with-debug],
	[debug messages in library]),
	[case "${withval}" in
		yes|no) with_debug="$withval" ;;
		*) AC_MSG_RESULT(oops)
                   AC_MSG_ERROR(bad value ${withval} for --with-debug) ;;
	esac], [with_debug="no"])
test "$with_debug" != "yes" && with_debug="no" # yes or no
test "$with_debug" = "yes" && export CFLAGS="$CFLAGS -DDEBUG" 
result="$with_debug" ; test "$result" = "yes" && result="yes, added -DDEBUG"
AC_MSG_RESULT($result)
if test "$with_debug" = "yes" ; then if test -n "$RELEASEINFO" ; then
   RELEASEINFO="$RELEASEINFO-dbg"
   AC_MSG_RESULT(modified release, $RELEASEINFO)
fi fi
# ----------------------------------------------------------------
AC_MSG_CHECKING(whether thread stack is too small for bufsiz buffers)
 # many embedded platforms, superthreaded systems and kernel usage
 # will severely limit the stackspace for its threads. Use _LOWSTK
 # compile-define on those platforms.
AC_ARG_WITH(lowstk, AC_HELP_STRING([--with-lowstk],
	[limited thread stack]),
	[case "${withval}" in
		yes|no|auto) with_lowstk="$withval" ;;
		*) AC_MSG_ERROR(bad value ${withval} for --with-lowstk) ;;
	esac], [with_lowstk="auto"])
if test "$with_lowstk" = "auto"; then
  case $target in
	*-palmos-*) $with_lowstk="yes" ;;
  esac
fi
test "$with_lowstk" != "yes" && with_lowstk="no" # yes or no
test "$with_lowstk" = "yes" && CFLAGS="$CFLAGS -D_LOWSTK" 
result="$with_lowstk" ; test "$result" = "yes" && result="yes, added -D_LOWSTK"
AC_MSG_RESULT($with_lowstk)
# ---------------------------------------------------------------
AC_MSG_CHECKING(whether can use mmap for file scanning)
 # system with mmap are probably better performing an searching
 # and parsing - atleast memory consumption is far better
AC_ARG_ENABLE(mmap, AC_HELP_STRING([--disable-mmap],
	[disable mmap usage]),
	[case "${enableval}" in
		yes|no|auto) enable_mmap="${enableval}" ;;
		*) AC_MSG_RESULT(oops)
                   AC_MSG_ERROR(bad value ${enableval} for --disable-mmap) ;;
	esac], [enable_mmap="auto"])
if test "$enable_mmap" = "auto"
then
    test "$ac_cv_header_winbase_h"  && enable_mmap="yes, winbase.h"
    test "$ac_cv_header_sys_mman_h" && enable_mmap="yes, sys/mman.h"
fi
case "$enable_mmap" in
   yes|yes,*) CFLAGS="$CFLAGS -D_USE_MMAP"
      AC_MSG_RESULT($enable_mmap, added -D_USE_MMAP) ;;
   *) enable_mmap="no"
      AC_MSG_RESULT(no (just a bit slower)) ;;
esac
# ---------------------------------------------------------------
AC_MSG_CHECKING(running extra tests on make check)
if test "MKZIP" != ":" ; then
  AC_MSG_RESULT(yes)
  ZIPTESTS=""
else
  AC_MSG_RESULT(no)
  ZIPTESTS="#"
fi
AC_SUBST(ZIPTESTS)
# ---------------------------------------------------------------
test "$GCC" = "yes" && CFLAGS="$CFLAGS -Wall"
export CFLAGS
# ---------------------------------------------------------------
AC_MSG_CHECKING(link options)
case "$host_os" in
  mingw*) 
    ZZIPLIB_LDFLAGS="-no-undefined -export-all-symbols -mconsole"
    RESOLVES=' '
  ;;
  *)
    ZZIPLIB_LDFLAGS="--export-dynamic"
    RESOLVES=' # '
  ;;
esac
AC_MSG_RESULT([$ZZIPLIB_LDFLAGS $RESOLVES])
AC_SUBST([ZZIPLIB_LDFLAGS])
AC_SUBST([RESOLVES])
# ---------------------------------------------------------------
AC_MSG_CHECKING(maintainer mode)
if test "$USE_MAINTAINER_MODE" = "no" ; then 
 LIBTOOL="$LIBTOOL --silent"
 test -z "$TIMEOUT" && TIMEOUT="99"
 T="sleep $TIMEOUT"
 AUTOHEADER="$T ; true ERROR: CALL TO AUTOHEADER BUT NO MAINTAINER-MODE"
 AUTOMAKE="$T ; true ERROR: CALL TO AUTOMAKE BUT NO MAINTAINER-MODE"
 AUTOCONF="$T ; true ERROR: CALL TO AUTOCONF BUT NO MAINTAINER-MODE"
 result="libtool-silent, autotools-sleep-$TIMEOUT"
else
 result="no"
fi
AC_MSG_RESULT([$result])
# ---------------------------------------------------------------
AX_CFLAGS_WARN_ALL
AX_CFLAGS_NO_WRITABLE_STRINGS
AX_CFLAGS_STRICT_PROTOTYPES
# ---------------------------------------------------------------
AC_SUBST([CONFIG_FILES])
AC_OUTPUT([Makefile zzip-config])
dnl -------------------------------------------------------------
PATCH_LIBTOOL_ON_DARWIN_ZSH_OVERQUOTING
PATCH_LIBTOOL_SYS_LIB_SEARCH_PATH_SPEC
PATCH_LIBTOOL_TO_ADD_HOST_CC
# ---------------------------------------------------------------
echo '-----' $PACKAGE $VERSION $prefix
$SHELL libtool --features || true
test "$enable_mmap" != "no" && echo "enable  mmap   ($enable_mmap)"
test "$enable_mmap"  = "no" && echo "disable mmap   ($enable_mmap)"
test "$with_lowstk" != "no" && echo "with    lowstk ($with_lowstk)"
test "$with_lowstk"  = "no" && echo "without lowstk ($with_lowstk)"
test "$with_debug"  != "no" && echo "with    debug  ($with_debug)"
test "$with_debug"   = "no" && echo "without debug  ($with_debug)"
echo '# make  && make check  && make install'
