#!/bin/sh
# (or use sh -x to see what is going on)
#
# /*
#  *  This program is free software: you can redistribute it and/or modify
#  *  it under the terms of the GNU General Public License as published by
#  *  the Free Software Foundation, either version 3 of the License, or
#  *  (at your option) any later version.
#  *
#  *  This program is distributed in the hope that it will be useful,
#  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  *  GNU General Public License for more details.
#  *
#  *  You should have received a copy of the GNU General Public License
#  *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
#  *
#  */
#
# If environment variable DRYRUN is set, no configuring will be done -
# (e.g. in bash)  DRYRUN=1 ./autogen.sh
# will not do any configuring but will emit the programs that would be run.
#
# This is basically:
# aclocal -I m4
# autoheader
# autoconf
# automake --copy --add-missing --force-missing --include-deps --foreign
#
# or: autoreconf -fvim
#
# libtool version 2.2, 2.4 tested http://ftp.gnu.org/gnu/libtool

#
rm -fr autom4te.cache
rm -f ./configure
rm -f ./Makefile
rm -f ./Makefile.in
rm -fr src/.deps

#
locate_binary() {
  for f in $@
  do
    file=`which $f 2>/dev/null | grep -v '^no '`
    if test -n "$file" -a -x "$file"; then
      echo $file
      return 0
    fi
  done

  echo "" 
  return 1
}

# user set environment variable are possible this way
if test x$LIBTOOLIZE = x; then
  LIBTOOLIZE=`locate_binary libtoolize glibtoolize libtoolize-1.5`
  if test x$LIBTOOLIZE = x; then
    echo "./autogen.sh: no supported libtoolize"
  fi
fi

if test x$ACLOCAL = x; then
  ACLOCAL=`locate_binary aclocal aclocal-1.11 aclocal-1.10 aclocal-1.9 aclocal19`
  if test x$ACLOCAL = x; then
    echo "./autogen.sh: no supported aclocal"
  fi
fi

if test x$AUTOMAKE = x; then
  AUTOMAKE=`locate_binary automake automake-1.11 automake-1.10 automake-1.9 automake19`
  if test x$AUTOMAKE = x; then
    echo "./autogen.sh: no supported automake"
  fi
fi

if test x$AUTOCONF = x; then
  AUTOCONF=`locate_binary autoconf autoconf-2.59 autoconf259`
  if test x$AUTOCONF = x; then
    echo "./autogen.sh: no supported autoconf"
  fi
fi

if test x$AUTOHEADER = x; then
  AUTOHEADER=`locate_binary autoheader autoheader-2.59 autoheader259`
  if test x$AUTOHEADER = x; then
    echo "./autogen.sh: no supported autoheader"
  fi
fi

echo "./autogen.sh: libtoolize version ... (needs automake package installed)"
libtoolize --version 2>&1 > /dev/null
rc=$?
if test $rc -ne 0 ; then
    echo "./autogen.sh: no supported libtool on your machine"
    echo "./autogen.sh: libtool --version produced:"
    libtool --version
    exit 1
fi

#
lt_ver=`libtoolize --version | awk '{print $NF; exit}'`
lt_maj=`echo $lt_ver | sed 's;\..*;;g'`
lt_min=`echo $lt_ver | sed -e 's;^[0-9]*\.;;g'  -e 's;\..*$;;g'`
lt_teeny=`echo $lt_ver | sed -e 's;^[0-9]*\.[0-9]*\.;;g'`
echo "    $lt_ver"

case $lt_maj in
    0)
        echo "./autogen.sh: need libtool >= 1.4.0 but you seem to have $lt_ver"
        exit 1
        ;;

    1)
        if test $lt_min -lt 4 ; then
            echo "./autogen.sh: need libtool >= 1.4.0 but you seem to have $lt_ver"
            exit 1
        fi
        ;;

    *)
        echo "./autogen.sh: newer libtool then version 1.4.0 which is minimum needed."
        ;;
esac

#
echo "---"
echo "./autogen.sh: Using the following tools"
echo "  * `$LIBTOOLIZE --version | head -1`"
echo "  * `$ACLOCAL --version | head -1`"
echo "  * `$AUTOHEADER --version | head -1`"
echo "  * `$AUTOMAKE --version | head -1`"
echo "  * `$AUTOCONF --version | head -1`"
echo "---"


#
echo "./autogen.sh: Running libtoolize"
libtoolize --force --copy --automake


# aclocal
echo "./autogen.sh: Checking aclocal version...(needs automake package installed)"
acl_ver=`aclocal --version | awk '{print $NF; exit}'`
echo "    $acl_ver"


#
echo "./autogen.sh: Running aclocal"
aclocal --force -I .
echo "./autogen.sh: done with aclocal"


# autoheader generates config.h.in with a problem when incluced multiple times
echo "./autogen.sh: Checking autoheader version"
ah_ver=`autoheader --version | awk '{print $NF; exit}'`
echo "    $ah_ver"


#
echo "./autogen.sh: Running autoheader"
autoheader
echo "./autogen.sh: done with autoheader"


# automake
echo "Checking automake version..."
am_ver=`automake --version | awk '{print $NF; exit}'`
echo "    $am_ver"

# http://www.gnu.org/software/womb/gnits/Preface.html
# http://www.gnu.org/software/hello/manual/automake/Gnits.html
# https://secure.wikimedia.org/wikipedia/en/wiki/Gnits_Standards
# --gnu does checks on files like NEWS etc. according to GNU standards
# --gnits does few more GNU standards checks and wants to THANK YOU insiting on a THANKS file.
# --add-missing creates the INSTALL file
echo "./autogen.sh: Running automake"
automake --force --copy --add-missing --gnu
echo "./autogen.sh: done with automake"

# autoconf

echo "./autogen.sh: Checking autoconf version"
ac_ver=`autoconf --version | awk '{print $NF; exit}'`
echo "    $ac_ver"

#
echo "./autogen.sh:Running autoconf"
autoconf
echo "./autogen.sh: done with autoconf"

# optional
./configure CC=gcc

# now run make, for example:
# make
# make install DESTDIR=./bin
# or make package with fpm tool for example:
# fpm -s dir -t deb -n mooigraph -v 4.0 -C ./bin etc.

# end.
