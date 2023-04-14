#ifndef EXTERNAL_PARSE_H
#define EXTERNAL_PARSE_H

#include <sys/types.h>

// TODO: Expand
#include "ruby/internal/value.h"
#include "ruby/st.h"

typedef struct rb_parser_config_struct {
    /* Memory */
    void *(*malloc)(size_t size);
    void *(*calloc)(size_t number, size_t size);
    void (*free)(void *ptr);

    // VALUE rb_suppress_tracing(VALUE (*func)(VALUE), VALUE arg);
    VALUE (*compile_callback)(VALUE (*func)(VALUE), VALUE arg);

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

    /* Symbol */
    VALUE (*sym_intern_ascii_cstr)(const char *ptr);
    ID (*make_temporary_id)(size_t n);

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
    VALUE (*fstring)(VALUE);
    int (*is_ascii_string)(VALUE str);

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

    /* Complex */
    void (*rcomplex_set_real)(VALUE cmp, VALUE r);
    void (*rcomplex_set_imag)(VALUE cmp, VALUE i);
    VALUE (*rcomplex_get_real)(VALUE obj);
    VALUE (*rcomplex_get_imag)(VALUE obj);

    /* IO */
    int (*stderr_tty_p)(void);
    void (*write_error_str)(VALUE mesg);
    /* IO (Ractor) */
    VALUE (*debug_output_stdout)(void);
    VALUE (*debug_output_stderr)(void);

    /* Ractor */
    VALUE (*ractor_make_shareable)(VALUE obj);

    /* Compile */
    int (*vm_keep_script_lines)(void);
    // int rb_local_defined(ID id, const rb_iseq_t *iseq);
    int (*local_defined)(ID, const void*);
    // int rb_dvar_defined(ID id, const rb_iseq_t *iseq);
    int (*dvar_defined)(ID, const void*);

    /* Compile (parse.y) */
    int (*literal_cmp)(VALUE val, VALUE lit);
    st_index_t (*literal_hash)(VALUE a);

    /* Error */
    const char *(*builtin_class_name)(VALUE x);
    // VALUE rb_syntax_error_append(VALUE, VALUE, int, int, rb_encoding*, const char*, va_list);
    VALUE (*syntax_error_append)(VALUE, VALUE, int, int, const void*, const char*, va_list);

    /* Re */
    VALUE (*reg_compile)(VALUE str, int options, const char *sourcefile, int sourceline);
    VALUE (*reg_check_preprocess)(VALUE str);

} rb_parser_config_t;

typedef struct parser_params rb_parser_t;

#endif /* EXTERNAL_PARSE_H */
