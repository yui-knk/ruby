#ifndef EXTERNAL_PARSE_H
#define EXTERNAL_PARSE_H

#include <sys/types.h>

// TODO: Expand
#include "ruby/internal/value.h"

typedef struct rb_parser_config_struct {
    /* Memory */
    void *(*malloc)(size_t size);
    void *(*calloc)(size_t number, size_t size);
    void (*free)(void *ptr);

    /* Array */
    VALUE (*ary_new)(void);
    VALUE (*ary_push)(VALUE ary, VALUE elem);
    VALUE (*ary_new_from_args)(long n, ...);
    VALUE (*ary_pop)(VALUE ary);
    VALUE (*ary_last)(int argc, const VALUE *argv, VALUE ary);
    VALUE (*ary_unshift)(VALUE ary, VALUE item);
    VALUE (*ary_new2)(long capa); // ary_new_capa
    VALUE (*ary_entry)(VALUE ary, long offset);
    VALUE (*ary_join)(VALUE ary, VALUE sep);
    VALUE (*ary_reverse)(VALUE ary);
    VALUE (*ary_clear)(VALUE ary);

    /* String */
    VALUE (*str_catf)(VALUE str, const char *format, ...);
    VALUE (*str_cat_cstr)(VALUE str, const char *ptr);
    VALUE (*str_subseq)(VALUE str, long beg, long len);
    VALUE (*str_dup)(VALUE str);
    VALUE (*str_new_frozen)(VALUE orig);
    VALUE (*str_buf_new)(long capa);
    VALUE (*str_buf_cat)(VALUE, const char*, long);
    void (*str_modify)(VALUE str);
    void (*str_set_len)(VALUE str, long len);
    VALUE (*str_cat)(VALUE str, const char *ptr, long len);
    VALUE (*str_resize)(VALUE str, long len);
    VALUE (*str_new)(const char *ptr, long len);
    VALUE (*str_new_cstr)(const char *ptr);

    /* Hash */
    VALUE (*hash_clear)(VALUE hash);
    VALUE (*hash_new)(void);
    VALUE (*hash_aset)(VALUE hash, VALUE key, VALUE val);
    VALUE (*hash_lookup)(VALUE hash, VALUE key);
    VALUE (*ident_hash_new)(void);

    /* Bignum */
    void (*bignum_negate)(VALUE b);

    /* Rational */
    void (*rational_set_num)(VALUE r, VALUE n);
    VALUE (*rational_get_num)(VALUE obj);


} rb_parser_config_t;

typedef struct parser_params rb_parser_t;

#endif /* EXTERNAL_PARSE_H */
