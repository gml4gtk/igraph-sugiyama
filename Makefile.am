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
#  */
#

#
ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

#
AM_MAKEFLAGS = --no-print-directory

#
AUTOMAKE_OPTIONS = foreign subdir-objects

# dirs with makefile.am
SUBDIRS = . src

#
NULL =

#
cleaner:
	$(RM) Makefile
	$(RM) Makefile.in
	$(RM) src/Makefile
	$(RM) src/Makefile.in
	$(RM) config.log
	$(RM) src/*.i
	$(RM) src/*.s
	$(RM) src/*.o
	$(RM) src/sugi
	$(RM) -r -f -v src/.deps
	$(RM) -r -f -v autom4te.cache
	$(RM) -r -f -v m4
	$(RM) *.in
	$(RM) *.in~
	$(RM) *.~
	$(RM) install-sh
	$(RM) ltmain.sh
	$(RM) missing
	$(RM) stamp-h1
	$(RM) depcomp
	$(RM) *.output
	$(RM) *.warnings
	$(RM) *.m4
	$(RM) *.status
	$(RM) compile
	$(RM) configure

# assembly mnemonics info
asminfo:
	objdump -d src/sugi | cut -f3 | grep -oE "^[a-z]+" | sort | uniq -c

