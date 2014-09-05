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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_bloom_filter.h"

#include <limits.h>

#define BIT_SET(a,n) (a[n/CHAR_BIT] |= (1<<(n%CHAR_BIT)))
#define BIT_CHECK(a,n) (a[n/CHAR_BIT] & (1<<(n%CHAR_BIT)))

#define PHP_BLOOM_FILTER_RES_NAME "bloom_filter"

int seed[7] = {3,5,7,11,13,31,37};

struct Bloom{
    unsigned long size;
    unsigned char *bits;
};
typedef struct Bloom *BloomPtr;
 
BloomPtr initBloom(unsigned long size){
    BloomPtr bl;
    bl = emalloc(sizeof(struct Bloom));
    bl->bits = (char *)calloc(size/CHAR_BIT+CHAR_BIT,sizeof(char));
    bl->size = size;
    return bl;
}
 
void destroyBloom(BloomPtr bl){
    efree(bl->bits);
    efree(bl);
}
 
unsigned long getValues(char *str,int n,unsigned long size){
    unsigned long hvalue = 0;
    char *p;
    p = str;
    while(*p!='\0'){
        hvalue = (hvalue * n) + *p++;
        if(hvalue > size)
            hvalue %= size;
 
    }
    return hvalue;
}
 
void addBloom(BloomPtr bl,char *str){
    int i;
    unsigned long hvalue;
    for(i=0;i<7;i++){
        hvalue = getValues(str,seed[i],bl->size);
        BIT_SET(bl->bits,hvalue);
    }
}
 
int checkBloom(BloomPtr bl,char *str){
    int i;
    unsigned long hvalue;
    for(i=0;i<7;i++){
        hvalue = getValues(str,seed[i],bl->size);
        if(!BIT_CHECK(bl->bits,hvalue))
            return 0;
    }
    return 1;
}


void bloom_filer_destroy_handler(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	destroyBloom( (BloomPtr)rsrc->ptr );
}

/* If you declare any globals in php_bloom_filter.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(bloom_filter)
*/

/* True global resources - no need for thread safety here */
static int le_bloom_filter;

/* {{{ bloom_filter_functions[]
 *
 * Every user visible function must have an entry in bloom_filter_functions[].
 */
const zend_function_entry bloom_filter_functions[] = {
	PHP_FE(confirm_bloom_filter_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(bloom_filter_create,	NULL)
	PHP_FE(bloom_filter_add,	NULL)
	PHP_FE(bloom_filter_check,	NULL)
	PHP_FE(bloom_filter_destory,	NULL)
	PHP_FE_END	/* Must be the last line in bloom_filter_functions[] */
};
/* }}} */

/* {{{ bloom_filter_module_entry
 */
zend_module_entry bloom_filter_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"bloom_filter",
	bloom_filter_functions,
	PHP_MINIT(bloom_filter),
	PHP_MSHUTDOWN(bloom_filter),
	PHP_RINIT(bloom_filter),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(bloom_filter),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(bloom_filter),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_BLOOM_FILTER
ZEND_GET_MODULE(bloom_filter)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("bloom_filter.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_bloom_filter_globals, bloom_filter_globals)
    STD_PHP_INI_ENTRY("bloom_filter.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_bloom_filter_globals, bloom_filter_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_bloom_filter_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_bloom_filter_init_globals(zend_bloom_filter_globals *bloom_filter_globals)
{
	bloom_filter_globals->global_value = 0;
	bloom_filter_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(bloom_filter)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	le_bloom_filter = zend_register_list_destructors_ex(NULL, NULL, PHP_BLOOM_FILTER_RES_NAME, module_number);
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(bloom_filter)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(bloom_filter)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(bloom_filter)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(bloom_filter)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "bloom_filter support", "enabled");
	php_info_print_table_row(2, "version", "1.0");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* Remove the following function when you have succesfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_bloom_filter_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_bloom_filter_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "bloom_filter", arg);
	RETURN_STRINGL(strg, len, 0);
}


PHP_FUNCTION(bloom_filter_create)
{
	zval *res; 
	int res_id;
	
	long bytelength;
	BloomPtr BL;
	if( zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"l",&bytelength) == FAILURE ){
		RETURN_NULL();
	}
	
	BL = initBloom(bytelength*8);
	
	res_id = ZEND_REGISTER_RESOURCE(res,BL,le_bloom_filter);
	
	RETURN_RESOURCE(res_id);
}

PHP_FUNCTION(bloom_filter_add)
{
	zval *zbl;
	char *buffer;
	int slen;
	BloomPtr BL;
	if( zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"rs",&zbl,&buffer,&slen) == FAILURE ){
		RETURN_NULL();
	}
	ZEND_FETCH_RESOURCE(BL, BloomPtr, &zbl, -1, PHP_BLOOM_FILTER_RES_NAME, le_bloom_filter);
	addBloom(BL,buffer);
	RETURN_TRUE;
}


PHP_FUNCTION(bloom_filter_check)
{
	zval *zbl;
	char *buffer;
	int slen;
	BloomPtr BL;
	if( zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"rs",&zbl,&buffer,&slen) == FAILURE ){
		RETURN_NULL();
	}
	ZEND_FETCH_RESOURCE(BL, BloomPtr, &zbl, -1, PHP_BLOOM_FILTER_RES_NAME, le_bloom_filter);
	
	if(checkBloom(BL,buffer)){
		RETURN_TRUE;
	}
	RETURN_FALSE;
}


PHP_FUNCTION(bloom_filter_destory)
{
	zval *zbl;
	BloomPtr BL;
	if( zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"r",&BL) == FAILURE ){
		RETURN_NULL();
	}
	ZEND_FETCH_RESOURCE(BL, BloomPtr, &zbl, -1, PHP_BLOOM_FILTER_RES_NAME, le_bloom_filter);
	destroyBloom(BL);
	RETURN_TRUE;
}


/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
