#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([sugi], [1.0], [http://igraph.org])
AC_CONFIG_SRCDIR([src/igraph_heap_pmt.h])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CC
AC_PROG_CC_C99

# Need c99 mode because of %llu in printf() and (long long int) datatype
# -fsanitize is for newer gcc and does memleak check
#CFLAGS="$CFLAGS -Wall -std=c99 -pedantic -fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined"
# -fverbose-asm generates documented asm output needs -S
CFLAGS="$CFLAGS -Wall -std=c99 -pedantic"

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([limits.h stddef.h stdint.h stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([floor])

#
# generates a line like this in config.h using configure:
# /* Keyword for thread local storage, or empty if not available */
# #define IGRAPH_THREAD_LOCAL __thread
#
# used in igraph_error.c like this:
# static IGRAPH_THREAD_LOCAL igraph_error_handler_t *igraph_i_error_handler=0;
#
tls_support=no
HAVE_TLS=0
#THREAD_LOCAL=
#AC_ARG_ENABLE(tls, AC_HELP_STRING([--enable-tls], [Compile with thread-local storage]))
#if test "x$enable_tls" != "xno"; then
#  keywords="__thread __declspec(thread)"
#  for kw in $keywords ; do
#      AC_TRY_COMPILE([int $kw test;], [], ac_cv_tls=$kw)
#      AC_TRY_COMPILE([int $kw test;], [], ac_cv_tls=$kw ; break ;)
#  done
#  AX_TLS([
#    AC_DEFINE([HAVE_TLS], [1], [Define to 1 if you want to use thread-local storage for global igraph structures])
#    tls_support=yes
#    HAVE_TLS=1
#    THREAD_LOCAL=$ac_cv_tls
#  ], [])
#fi

AC_SUBST(HAVE_TLS)
AC_DEFINE_UNQUOTED([IGRAPH_THREAD_LOCAL], $THREAD_LOCAL,
          [Keyword for thread local storage, or empty if not available])
AC_DEFINE_UNQUOTED([IGRAPH_F77_SAVE], [static IGRAPH_THREAD_LOCAL],
          [Keyword for thread local storage, or just static if not available])

# check openmp support available autoconf-2.62+
AC_OPENMP

# openmp is a compiler feature for parallel processing
AC_ARG_ENABLE(openmp,
        AS_HELP_STRING([--enable-openmp],[use OpenMP (default yes)]),
        [openmp=${enableval}],[openmp=yes])

#
if test "${openmp}" = "yes" ; then
	AC_LANG_PUSH([C])
	AX_OPENMP(have_openmp=yes,have_openmp=no)
	AC_LANG_POP
fi

# openmp adds interesting difficulties in the source
if test "$have_openmp" = "yes" ; then
HAVE_OPENMP=1
CFLAGS="$CFLAGS -fopenmp"
else
HAVE_OPENMP=0
fi

#
AC_DEFINE_UNQUOTED([HAVE_OPENMP], [$HAVE_OPENMP], [openmp support])

# default to gtk+-2.0 setting to 1
GTK_HAVE_API_VERSION_2=0
GTK_HAVE_API_VERSION_3=1

AC_ARG_ENABLE(gtk2,
[  --enable-gtk2           Use GTK 2.0 in preference to GTK 3.0 [[default=no]]],
[if test "$enableval" = "yes"
then
  prefer_gtk2=yes
else
  prefer_gtk2=no
fi])

AC_MSG_CHECKING([which gtk+ version to compile against])
AC_ARG_WITH([gtk],
  [AS_HELP_STRING([--with-gtk=2.0|3.0],[which gtk+ version to compile against (default: 3.0)])],
  [case "$with_gtk" in
     2.0|3.0) ;;
     *) AC_MSG_ERROR([invalid gtk version specified]) ;;
   esac],
  [with_gtk=3.0])
AC_MSG_RESULT([$with_gtk])

case "$with_gtk" in
  2.0) GTK_API_VERSION=2.0
       GTK_REQUIRED=2.0.0
       GTK_HAVE_API_VERSION_2=1
       GTK_HAVE_API_VERSION_3=0
       ;;
  3.0) GTK_API_VERSION=3.0
       GTK_REQUIRED=2.91.0
       GTK_HAVE_API_VERSION_2=0
       GTK_HAVE_API_VERSION_3=1
       ;;
esac

#
AC_SUBST([GTK_API_VERSION])
AC_SUBST([GTK_REQUIRED])

#
AM_CONDITIONAL([HAVE_GTK_2],[test "$with_gtk" = "2.0"])
AM_CONDITIONAL([HAVE_GTK_3],[test "$with_gtk" = "3.0"])

#
AC_DEFINE_UNQUOTED([GTK_HAVE_API_VERSION_2], [$GTK_HAVE_API_VERSION_2], [gtk version 2])
AC_DEFINE_UNQUOTED([GTK_HAVE_API_VERSION_3], [$GTK_HAVE_API_VERSION_3], [gtk version 3])

# Preliminary check for pkg-config
if test -z "$PKG_CONFIG"; then
   AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
fi
if test "$PKG_CONFIG" = "no" ; then
   echo "
Please install pkg-config and then reconfigure mooigraph.
pkg-config is available from http://www.freedesktop.org/
"
   exit 1
fi

# glib 2.0 (needed even if not building GUI; we need 2.14 for regexp functions)
PKG_CHECK_MODULES(GLIB, glib-2.0 >= 2.14.0, have_glib2="yes", have_glib2="no")
if test "${have_glib2}" = "no" ; then
   echo "
Please install glib-2.0 >= 2.14.0 and then reconfigure mooigraph.
glib-2.0 is available from http://www.gtk.org/
"
   exit 1
fi

# Initial check for GTK availability
if test "$prefer_gtk2" = "yes" ; then
    PKG_CHECK_MODULES(GTK2, gtk+-2.0 >= 2.14.0,
      GTK_CFLAGS=$GTK2_CFLAGS
      GTK_LIBS=$GTK2_LIBS
      CFLAGS="$CFLAGS $GTK_CFLAGS"
      LIBS="$LIBS $GTK_LIBS"
      gtk_version="2.0",
      echo "GTK 2 >= 2.14.0 not found"
    )
elif test "$prefer_gtk2" = "no" ; then
    PKG_CHECK_MODULES(GTK3, gtk+-3.0 >= 3.0.1,
      GTK_CFLAGS=$GTK3_CFLAGS
      GTK_LIBS=$GTK3_LIBS
      CFLAGS="$CFLAGS $GTK_CFLAGS"
      LIBS="$LIBS $GTK_LIBS"
      dnl AC_DEFINE(USE_GTK3)
      gtk_version="3.0"
      fake_gtkspinner="no",
      echo "GTK 3 >= 3.0.1 not found"
    )
fi

dnl GTK 2.0 fallback in case preference not given
if test "$prefer_gtk2" = "no" && test "$gtk_version" = "none" ; then
      PKG_CHECK_MODULES(GTK2, gtk+-2.0 >= 2.14.0,
        GTK_CFLAGS=$GTK2_CFLAGS
        GTK_LIBS=$GTK2_LIBS
        CFLAGS="$CFLAGS $GTK_CFLAGS"
        LIBS="$LIBS $GTK_LIBS"
        gtk_version="2.0",
        build_gui="no"
        echo "GTK 2 >= 2.14.0 not found"
    )
fi


#
PKG_CHECK_MODULES(GTK, gtk+-$GTK_API_VERSION >= $GTK_REQUIRED)
AC_SUBST(GTK_CFLAGS)
AC_SUBST(GTK_LIBS)

#
CFLAGS="$CFLAGS $GTK_CFLAGS"

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
