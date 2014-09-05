/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2012 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id: header 321634 2012-01-01 13:15:04Z felipe $ */

#ifndef PHP_BLOOM_FILTER_H
#define PHP_BLOOM_FILTER_H

extern zend_module_entry bloom_filter_module_entry;
#define phpext_bloom_filter_ptr &bloom_filter_module_entry

#ifdef PHP_WIN32
#	define PHP_BLOOM_FILTER_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_BLOOM_FILTER_API __attribute__ ((visibility("default")))
#else
#	define PHP_BLOOM_FILTER_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(bloom_filter);
PHP_MSHUTDOWN_FUNCTION(bloom_filter);
PHP_RINIT_FUNCTION(bloom_filter);
PHP_RSHUTDOWN_FUNCTION(bloom_filter);
PHP_MINFO_FUNCTION(bloom_filter);

PHP_FUNCTION(confirm_bloom_filter_compiled);	/* For testing, remove later. */
PHP_FUNCTION(bloom_filter_create);
PHP_FUNCTION(bloom_filter_add);
PHP_FUNCTION(bloom_filter_check);
PHP_FUNCTION(bloom_filter_destory);

/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     

ZEND_BEGIN_MODULE_GLOBALS(bloom_filter)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(bloom_filter)
*/

/* In every utility function you add that needs to use variables 
   in php_bloom_filter_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as BLOOM_FILTER_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define BLOOM_FILTER_G(v) TSRMG(bloom_filter_globals_id, zend_bloom_filter_globals *, v)
#else
#define BLOOM_FILTER_G(v) (bloom_filter_globals.v)
#endif

#endif	/* PHP_BLOOM_FILTER_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */