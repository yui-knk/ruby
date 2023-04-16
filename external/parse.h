#ifndef EXTERNAL_PARSE_H
#define EXTERNAL_PARSE_H

#include <sys/types.h>
#include "external/value.h"
#include "external/node.h"
// TODO: Expand
#include "ruby/st.h"

#define rb_encoding void
#define OnigCodePoint unsigned int

typedef struct parser_params rb_parser_t;

typedef struct rb_parser_config_struct {
    /* Memory */
    void *(*malloc)(size_t size);
    void *(*calloc)(size_t number, size_t size);
    void (*free)(void *ptr);

    // VALUE rb_suppress_tracing(VALUE (*func)(VALUE), VALUE arg);
    VALUE (*compile_callback)(VALUE (*func)(VALUE), VALUE arg);
    NODE *(*reg_named_capture_assign)(struct parser_params* p, VALUE regexp, const rb_code_location_t *loc);

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
    int (*is_local_id)(ID);
    int (*is_attrset_id)(ID);
    int (*is_global_name_punct)(const int c);
    int (*id_type)(ID id);
    ID (*intern3)(const char *name, long len, rb_encoding *enc);
    int (*is_notop_id)(ID);
    int (*enc_symname_type)(const char *name, long len, rb_encoding *enc, unsigned int allowed_attrset);

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
    VALUE (*enc_str_new)(const char *ptr, long len, rb_encoding *enc);
    VALUE (*enc_str_buf_cat)(VALUE str, const char *ptr, long len, rb_encoding *enc);

    /* Hash */
    VALUE (*hash_clear)(VALUE hash);
    VALUE (*hash_new)(void);
    VALUE (*hash_aset)(VALUE hash, VALUE key, VALUE val);
    VALUE (*hash_lookup)(VALUE hash, VALUE key);
    VALUE (*ident_hash_new)(void);

    /* Bignum */
    void (*bignum_negate)(VALUE b);

    /* Rational */
    VALUE (*rational_new)(VALUE x, VALUE y);
    VALUE (*rational_raw)(VALUE x, VALUE y);
    void (*rational_set_num)(VALUE r, VALUE n);
    VALUE (*rational_get_num)(VALUE obj);

    /* Complex */
    VALUE (*complex_raw)(VALUE x, VALUE y);
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

    /* Encoding */
    int (*is_usascii_enc)(rb_encoding *enc);
    int (*enc_isalnum)(OnigCodePoint c, rb_encoding *enc);
    int (*enc_precise_mbclen)(const char *p, const char *e, rb_encoding *enc);
    int (*mbclen_charfound_p)(int len);
    const char *(*enc_name)(rb_encoding *enc);
    char *(*enc_prev_char)(const char *s, const char *p, const char *e, rb_encoding *enc);
    rb_encoding* (*enc_get)(VALUE obj);
    int (*enc_asciicompat)(rb_encoding *enc);
    rb_encoding *(*utf8_encoding)(void);
    VALUE (*enc_associate)(VALUE obj, rb_encoding *enc);
    rb_encoding *(*ascii8bit_encoding)(void);
    int (*enc_codelen)(int c, rb_encoding *enc);
    int (*enc_mbcput)(unsigned int c, void *buf, rb_encoding *enc);
    int (*char_to_option_kcode)(int c, int *option, int *kcode);
    int (*ascii8bit_encindex)(void);
    int (*enc_find_index)(const char *name);
    rb_encoding *(*enc_from_index)(int idx);
    VALUE (*enc_associate_index)(VALUE obj, int encindex);
    int (*enc_isspace)(OnigCodePoint c, rb_encoding *enc);
    int enc_coderange_7bit;
    int enc_coderange_unknown;
    rb_encoding *(*enc_compatible)(VALUE str1, VALUE str2);
    VALUE (*enc_from_encoding)(rb_encoding *enc);
    int (*encoding_get)(VALUE obj);
    void (*encoding_set)(VALUE obj, int encindex);
    int (*encoding_is_ascii8bit)(VALUE obj);
    rb_encoding *(*usascii_encoding)(void);

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
    VALUE (*syntax_error_append)(VALUE, VALUE, int, int, rb_encoding*, const char*, va_list);

    /* Re */
    VALUE (*reg_compile)(VALUE str, int options, const char *sourcefile, int sourceline);
    VALUE (*reg_check_preprocess)(VALUE str);

    /* Error */
    void (*compile_warn)(const char *file, int line, const char *fmt, ...);
    void (*compile_warning)(const char *file, int line, const char *fmt, ...);
    void (*bug)(const char *fmt, ...);
    void (*fatal)(const char *fmt, ...);

    /* Util */
    unsigned long (*scan_hex)(const char *start, size_t len, size_t *retlen);
    unsigned long (*scan_oct)(const char *start, size_t len, size_t *retlen);
    unsigned long (*scan_digits)(const char *str, ssize_t len, int base, size_t *retlen, int *overflow);

} rb_parser_config_t;

#undef rb_encoding
#undef OnigCodePoint

#endif /* EXTERNAL_PARSE_H */
