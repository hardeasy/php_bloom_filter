dnl $Id$
dnl config.m4 for extension bloom_filter

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(bloom_filter, for bloom_filter support,
dnl Make sure that the comment is aligned:
dnl [  --with-bloom_filter             Include bloom_filter support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(bloom_filter, whether to enable bloom_filter support,
Make sure that the comment is aligned:
[  --enable-bloom_filter           Enable bloom_filter support])

if test "$PHP_BLOOM_FILTER" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-bloom_filter -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/bloom_filter.h"  # you most likely want to change this
  dnl if test -r $PHP_BLOOM_FILTER/$SEARCH_FOR; then # path given as parameter
  dnl   BLOOM_FILTER_DIR=$PHP_BLOOM_FILTER
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for bloom_filter files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       BLOOM_FILTER_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$BLOOM_FILTER_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the bloom_filter distribution])
  dnl fi

  dnl # --with-bloom_filter -> add include path
  dnl PHP_ADD_INCLUDE($BLOOM_FILTER_DIR/include)

  dnl # --with-bloom_filter -> check for lib and symbol presence
  dnl LIBNAME=bloom_filter # you may want to change this
  dnl LIBSYMBOL=bloom_filter # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $BLOOM_FILTER_DIR/lib, BLOOM_FILTER_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_BLOOM_FILTERLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong bloom_filter lib version or lib not found])
  dnl ],[
  dnl   -L$BLOOM_FILTER_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(BLOOM_FILTER_SHARED_LIBADD)

  PHP_NEW_EXTENSION(bloom_filter, bloom_filter.c, $ext_shared)
fi
