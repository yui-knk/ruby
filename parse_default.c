#include <stdlib.h>

RUBY_SYMBOL_EXPORT_BEGIN
void rb_parser_config_default_initialize(rb_parser_config_t *config);
RUBY_SYMBOL_EXPORT_END

#define OnigCodePoint unsigned int

#define not_defined(t1, name, ...) \
static t1 \
not_defined_##name(__VA_ARGS__) \
{ \
    fprintf(stderr, #name" is not define.\n"); \
    exit(1); \
}

not_defined(void *, malloc, size_t size)
not_defined(void *, calloc, size_t number, size_t size)
not_defined(void *, realloc, void *ptr, size_t newsiz)
not_defined(void, free, void *ptr)
not_defined(void *, alloc_n, size_t nelems, size_t elemsiz)
not_defined(void *, alloc, size_t elemsiz)
not_defined(void *, realloc_n, void *ptr, size_t newelems, size_t newsiz)
not_defined(void *, zalloc, size_t elemsiz)
not_defined(void *, memmove, void *dest, const void *src, size_t t, size_t n)
not_defined(void *, nonempty_memcpy, void *dest, const void *src, size_t t, size_t n)
not_defined(void *, xmalloc_mul_add, size_t x, size_t y, size_t z)

not_defined(VALUE, new_strterm, VALUE v1, VALUE v2, VALUE v3, VALUE v0, int heredoc)
not_defined(int, strterm_is_heredoc, VALUE strterm)
not_defined(VALUE, tmpbuf_auto_free_pointer, void)
not_defined(void *, tmpbuf_set_ptr, VALUE v, void *ptr)
not_defined(rb_imemo_tmpbuf_t *, tmpbuf_parser_heap, void *buf, rb_imemo_tmpbuf_t *old_heap, size_t cnt)
not_defined(rb_ast_t *, ast_new, VALUE nb)

not_defined(VALUE, compile_callback, VALUE (*func)(VALUE), VALUE arg)
not_defined(NODE *, reg_named_capture_assign, struct parser_params* p, VALUE regexp, const rb_code_location_t *loc)
not_defined(int, script_lines_defined, void)
not_defined(VALUE, script_lines_get, void)

/* Object */
not_defined(VALUE, obj_freeze, VALUE obj)
not_defined(VALUE, obj_hide, VALUE obj)
not_defined(int, obj_frozen, VALUE obj)
not_defined(int, type_p, VALUE obj, int t)
not_defined(void, obj_freeze_raw, VALUE obj)

not_defined(int, fixnum_p, VALUE obj)
not_defined(int, symbol_p, VALUE obj)

/* Variable */
not_defined(VALUE, attr_get, VALUE obj, ID id)

/* Array */
not_defined(VALUE, ary_new, void)
not_defined(VALUE, ary_push, VALUE ary, VALUE elem)
not_defined(VALUE, ary_new_from_args, long n, ...)
not_defined(VALUE, ary_pop, VALUE ary)
not_defined(VALUE, ary_last, int argc, const VALUE *argv, VALUE ary)
not_defined(VALUE, ary_unshift, VALUE ary, VALUE item)
not_defined(VALUE, ary_new2, long capa); // ary_new_cap
not_defined(VALUE, ary_entry, VALUE ary, long offset)
not_defined(VALUE, ary_join, VALUE ary, VALUE sep)
not_defined(VALUE, ary_reverse, VALUE ary)
not_defined(VALUE, ary_clear, VALUE ary)
not_defined(long, array_len, VALUE a)
not_defined(VALUE, array_aref, VALUE v, long l)

/* Symbol */
not_defined(VALUE, sym_intern_ascii_cstr, const char *ptr)
not_defined(ID, make_temporary_id, size_t n)
not_defined(int, is_local_id, ID id)
not_defined(int, is_attrset_id, ID id)
not_defined(int, is_global_name_punct, const int c)
not_defined(int, id_type, ID id)
not_defined(ID, id_attrset, ID id)
not_defined(ID, intern, const char *name)
not_defined(ID, intern2, const char *name, long len)
not_defined(ID, intern3, const char *name, long len, rb_encoding *enc)
not_defined(ID, intern_str, VALUE str)
not_defined(int, is_notop_id, ID id)
not_defined(int, enc_symname_type, const char *name, long len, rb_encoding *enc, unsigned int allowed_attrset)
not_defined(VALUE, str_intern, VALUE str)
not_defined(const char *, id2name, ID id)
not_defined(VALUE, id2str, ID id)
not_defined(VALUE, id2sym, ID x)
not_defined(ID, sym2id, VALUE sym)

/* String */
not_defined(VALUE, str_catf, VALUE str, const char *format, ...)
not_defined(VALUE, str_cat_cstr, VALUE str, const char *ptr)
not_defined(VALUE, str_subseq, VALUE str, long beg, long len)
not_defined(VALUE, str_dup, VALUE str)
not_defined(VALUE, str_new_frozen, VALUE orig)
not_defined(VALUE, str_buf_new, long capa)
not_defined(VALUE, str_buf_cat, VALUE str, const char* ptr, long len)
not_defined(void, str_modify, VALUE str)
not_defined(void, str_set_len, VALUE str, long len)
not_defined(VALUE, str_cat, VALUE str, const char *ptr, long len)
not_defined(VALUE, str_resize, VALUE str, long len)
not_defined(VALUE, str_new, const char *ptr, long len)
not_defined(VALUE, str_new_cstr, const char *ptr)
not_defined(VALUE, fstring, VALUE str)
not_defined(int, is_ascii_string, VALUE str)
not_defined(VALUE, enc_str_new, const char *ptr, long len, rb_encoding *enc)
not_defined(VALUE, enc_str_buf_cat, VALUE str, const char *ptr, long len, rb_encoding *enc)
not_defined(VALUE, str_buf_append, VALUE str, VALUE str2)
not_defined(VALUE, str_vcatf, VALUE str, const char *fmt, va_list ap)
not_defined(char *, string_value_cstr, volatile VALUE *ptr)
not_defined(VALUE, rb_sprintf, const char *format, ...)
not_defined(char *, rstring_ptr, VALUE str)
not_defined(char *, rstring_end, VALUE str)
not_defined(long, rstring_len, VALUE str)
not_defined(VALUE, filesystem_str_new_cstr, const char *ptr)
not_defined(VALUE, obj_as_string, VALUE str)

/* Hash */
not_defined(VALUE, hash_clear, VALUE hash)
not_defined(VALUE, hash_new, void)
not_defined(VALUE, hash_aset, VALUE hash, VALUE key, VALUE val)
not_defined(VALUE, hash_lookup, VALUE hash, VALUE key)
not_defined(VALUE, ident_hash_new, void)

/* Fixnum */
not_defined(VALUE, int2fix, long i)

/* Bignum */
not_defined(void, bignum_negate, VALUE b)
not_defined(VALUE, big_norm, VALUE x)
not_defined(VALUE, int2big, intptr_t n)
not_defined(VALUE, cstr_to_inum, const char *str, int base, int badcheck)

/* Float */
not_defined(VALUE, float_new, double d)
not_defined(double, float_value, VALUE v)

/* Numeric */
not_defined(long, fix2int, VALUE val)
not_defined(int, num2int, VALUE val)
not_defined(VALUE, int_positive_pow, long x, unsigned long y)
not_defined(VALUE, int2num, int v)
not_defined(long, fix2long, VALUE val)

/* Rational */
not_defined(VALUE, rational_new, VALUE x, VALUE y)
not_defined(VALUE, rational_raw, VALUE x, VALUE y)
not_defined(VALUE, rational_raw1, VALUE x)
not_defined(void, rational_set_num, VALUE r, VALUE n)
not_defined(VALUE, rational_get_num, VALUE obj)

/* Complex */
not_defined(VALUE, complex_raw, VALUE x, VALUE y)
not_defined(void, rcomplex_set_real, VALUE cmp, VALUE r)
not_defined(void, rcomplex_set_imag, VALUE cmp, VALUE i)
not_defined(VALUE, rcomplex_get_real, VALUE obj)
not_defined(VALUE, rcomplex_get_imag, VALUE obj)

/* IO */
not_defined(int, stderr_tty_p, void)
not_defined(void, write_error_str, VALUE mesg)
not_defined(VALUE, default_rs, void)
not_defined(VALUE, io_write, VALUE io, VALUE str)
not_defined(VALUE, io_flush, VALUE io)
not_defined(VALUE, io_puts, int argc, const VALUE *argv, VALUE out)
not_defined(VALUE, io_gets_internal, VALUE io)

/* IO (Ractor) */
not_defined(VALUE, debug_output_stdout, void)
not_defined(VALUE, debug_output_stderr, void)

/* Encoding */
not_defined(int, is_usascii_enc, rb_encoding *enc)
not_defined(int, enc_isalnum, OnigCodePoint c, rb_encoding *enc)
not_defined(int, enc_precise_mbclen, const char *p, const char *e, rb_encoding *enc)
not_defined(int, mbclen_charfound_p, int len)
not_defined(const char *, enc_name, rb_encoding *enc)
not_defined(char *, enc_prev_char, const char *s, const char *p, const char *e, rb_encoding *enc)
not_defined(rb_encoding*, enc_get, VALUE obj)
not_defined(int, enc_asciicompat, rb_encoding *enc)
not_defined(rb_encoding *, utf8_encoding, void)
not_defined(VALUE, enc_associate, VALUE obj, rb_encoding *enc)
not_defined(rb_encoding *, ascii8bit_encoding, void)
not_defined(int, enc_codelen, int c, rb_encoding *enc)
not_defined(int, enc_mbcput, unsigned int c, void *buf, rb_encoding *enc)
not_defined(int, char_to_option_kcode, int c, int *option, int *kcode)
not_defined(int, ascii8bit_encindex, void)
not_defined(int, enc_find_index, const char *name)
not_defined(rb_encoding *, enc_from_index, int idx)
not_defined(VALUE, enc_associate_index, VALUE obj, int encindex)
not_defined(int, enc_isspace, OnigCodePoint c, rb_encoding *enc)
#define not_defined_ENC_CODERANGE_7BIT 0
#define not_defined_ENC_CODERANGE_UNKNOWN 0
not_defined(rb_encoding *, enc_compatible, VALUE str1, VALUE str2)
not_defined(VALUE, enc_from_encoding, rb_encoding *enc)
not_defined(int, encoding_get, VALUE obj)
not_defined(void, encoding_set, VALUE obj, int encindex)
not_defined(int, encoding_is_ascii8bit, VALUE obj)
not_defined(rb_encoding *, usascii_encoding, void)

/* Ractor */
not_defined(VALUE, ractor_make_shareable, VALUE obj)

/* Compile */
not_defined(int, vm_keep_script_lines, void)
// int rb_local_defined(ID id, const rb_iseq_t *iseq);
not_defined(int, local_defined, ID id, const void *p)
// int rb_dvar_defined(ID id, const rb_iseq_t *iseq);
not_defined(int, dvar_defined, ID id, const void *p)

/* Compile (parse.y) */
not_defined(int, literal_cmp, VALUE val, VALUE lit)
not_defined(st2_index_t, literal_hash, VALUE a)

/* Error (Exception) */
not_defined(const char *, builtin_class_name, VALUE x)
not_defined(VALUE, syntax_error_append, VALUE exc, VALUE file, int line, int column, void *enc, const char *fmt, va_list args)
not_defined(void, raise, VALUE exc, const char *fmt, ...)
not_defined(VALUE, syntax_error_new, void)

/* Eval */
not_defined(VALUE, errinfo, void)
not_defined(void, set_errinfo, VALUE err)
not_defined(void, exc_raise, VALUE mesg)
not_defined(VALUE, make_exception, int argc, const VALUE *argv)

/* GC */
not_defined(void, sized_xfree, void *x, size_t size)
not_defined(void *, sized_realloc_n, void *ptr, size_t new_count, size_t element_size, size_t old_count)
not_defined(VALUE, obj_write, VALUE old, VALUE *slot, VALUE young)
not_defined(VALUE, obj_written, VALUE old, VALUE slot, VALUE young)
not_defined(void, gc_register_mark_object, VALUE object)
not_defined(void, gc_guard, VALUE obj)
not_defined(void, gc_mark, VALUE obj)
not_defined(void, gc_mark_movable, VALUE ptr)
not_defined(VALUE, gc_location, VALUE value)

/* Re */
not_defined(VALUE, reg_compile, VALUE str, int options, const char *sourcefile, int sourceline)
not_defined(VALUE, reg_check_preprocess, VALUE str)
not_defined(int, memcicmp, const void *x, const void *y, long len)

/* Error */
not_defined(void, compile_warn, const char *file, int line, const char *fmt, ...)
not_defined(void, compile_warning, const char *file, int line, const char *fmt, ...)
not_defined(void, bug, const char *fmt, ...)
not_defined(void, fatal, const char *fmt, ...)
not_defined(VALUE, verbose, void)

/* VM */
not_defined(VALUE, make_backtrace, void)

/* Util */
not_defined(unsigned long, scan_hex, const char *start, size_t len, size_t *retlen)
not_defined(unsigned long, scan_oct, const char *start, size_t len, size_t *retlen)
not_defined(unsigned long, scan_digits, const char *str, ssize_t len, int base, size_t *retlen, int *overflow)
not_defined(double, strtod, const char *s00, char **se)

/* ctype */
not_defined(int, isspace, int c)
not_defined(int, isascii, int c)
not_defined(int, iscntrl, int c)
not_defined(int, isalpha, int c)
not_defined(int, isdigit, int c)
not_defined(int, isalnum, int c)
not_defined(int, isxdigit, int c)
not_defined(int, strcasecmp, const char *s1, const char *s2)
not_defined(int, strncasecmp, const char *s1, const char *s2, size_t n)

/* Misc */
not_defined(VALUE, rbool, VALUE v)
not_defined(int, undef_p, VALUE v)
not_defined(int, rtest, VALUE obj)
not_defined(int, nil_p, VALUE obj)
not_defined(int, flonum_p, VALUE obj)
#define not_defined_Qnil 0
#define not_defined_Qtrue 0
#define not_defined_Qfalse 0
#define not_defined_Qundef 0
#define not_defined_eArgError 0
#define not_defined_mRubyVMFrozenCore 0
not_defined(int, long2int, long l)
not_defined(int, special_const_p, VALUE v)
not_defined(int, builtin_type, VALUE v)

not_defined(VALUE, node_case_when_optimizable_literal, const NODE *const node)

void
rb_parser_config_default_initialize(rb_parser_config_t *config)
{
    config->counter = 0;

    config->st_functions.nonempty_memcpy = not_defined_nonempty_memcpy;

    config->malloc   = not_defined_malloc;
    config->calloc   = not_defined_calloc;
    config->realloc  = not_defined_realloc;
    config->free     = not_defined_free;
    config->alloc_n  = not_defined_alloc_n;
    config->alloc    = not_defined_alloc;
    config->realloc_n = not_defined_realloc_n;
    config->zalloc = not_defined_zalloc;
    config->rb_memmove = not_defined_memmove;
    config->nonempty_memcpy = not_defined_nonempty_memcpy;
    config->xmalloc_mul_add = not_defined_xmalloc_mul_add;

    config->new_strterm = not_defined_new_strterm;
    config->strterm_is_heredoc = not_defined_strterm_is_heredoc;
    config->tmpbuf_auto_free_pointer = not_defined_tmpbuf_auto_free_pointer;
    config->tmpbuf_set_ptr = not_defined_tmpbuf_set_ptr;
    config->tmpbuf_parser_heap = not_defined_tmpbuf_parser_heap;
    config->ast_new = not_defined_ast_new;

    config->compile_callback         = not_defined_compile_callback;
    config->reg_named_capture_assign = not_defined_reg_named_capture_assign;
    config->script_lines_defined     = not_defined_script_lines_defined;
    config->script_lines_get         = not_defined_script_lines_get;

    config->obj_freeze = not_defined_obj_freeze;
    config->obj_hide = not_defined_obj_hide;
    config->obj_frozen = not_defined_obj_frozen;
    config->type_p = not_defined_type_p;
    config->obj_freeze_raw = not_defined_obj_freeze_raw;

    config->fixnum_p = not_defined_fixnum_p;
    config->symbol_p = not_defined_symbol_p;

    config->attr_get = not_defined_attr_get;

    config->ary_new           = not_defined_ary_new;
    config->ary_push          = not_defined_ary_push;
    config->ary_new_from_args = not_defined_ary_new_from_args;
    config->ary_pop           = not_defined_ary_pop;
    config->ary_last          = not_defined_ary_last;
    config->ary_unshift       = not_defined_ary_unshift;
    config->ary_new2          = not_defined_ary_new2;
    config->ary_entry         = not_defined_ary_entry;
    config->ary_join          = not_defined_ary_join;
    config->ary_reverse       = not_defined_ary_reverse;
    config->ary_clear         = not_defined_ary_clear;
    config->array_len         = not_defined_array_len;
    config->array_aref        = not_defined_array_aref;

    config->sym_intern_ascii_cstr = not_defined_sym_intern_ascii_cstr;
    config->make_temporary_id     = not_defined_make_temporary_id;
    config->is_local_id           = not_defined_is_local_id;
    config->is_attrset_id         = not_defined_is_attrset_id;
    config->is_global_name_punct  = not_defined_is_global_name_punct;
    config->id_type               = not_defined_id_type;
    config->id_attrset            = not_defined_id_attrset;
    config->intern                = not_defined_intern;
    config->intern2               = not_defined_intern2;
    config->intern3               = not_defined_intern3;
    config->intern_str            = not_defined_intern_str;
    config->is_notop_id           = not_defined_is_notop_id;
    config->enc_symname_type      = not_defined_enc_symname_type;
    config->str_intern            = not_defined_str_intern;
    config->id2name               = not_defined_id2name;
    config->id2str                = not_defined_id2str;
    config->id2sym                = not_defined_id2sym;
    config->sym2id                = not_defined_sym2id;

    config->str_catf        = not_defined_str_catf;
    config->str_cat_cstr    = not_defined_str_cat_cstr;
    config->str_subseq      = not_defined_str_subseq;
    config->str_dup         = not_defined_str_dup;
    config->str_new_frozen  = not_defined_str_new_frozen;
    config->str_buf_new     = not_defined_str_buf_new;
    config->str_buf_cat     = not_defined_str_buf_cat;
    config->str_modify      = not_defined_str_modify;
    config->str_set_len     = not_defined_str_set_len;
    config->str_cat         = not_defined_str_cat;
    config->str_resize      = not_defined_str_resize;
    config->str_new         = not_defined_str_new;
    config->str_new_cstr    = not_defined_str_new_cstr;
    config->fstring         = not_defined_fstring;
    config->is_ascii_string = not_defined_is_ascii_string;
    config->enc_str_new     = not_defined_enc_str_new;
    config->enc_str_buf_cat = not_defined_enc_str_buf_cat;
    config->str_buf_append  = not_defined_str_buf_append;
    config->str_vcatf       = not_defined_str_vcatf;
    config->string_value_cstr = not_defined_string_value_cstr;
    config->rb_sprintf      = not_defined_rb_sprintf;
    config->rstring_ptr     = not_defined_rstring_ptr;
    config->rstring_end     = not_defined_rstring_end;
    config->rstring_len     = not_defined_rstring_len;
    config->filesystem_str_new_cstr = not_defined_filesystem_str_new_cstr;
    config->obj_as_string = not_defined_obj_as_string;

    config->hash_clear     = not_defined_hash_clear;
    config->hash_new       = not_defined_hash_new;
    config->hash_aset      = not_defined_hash_aset;
    config->hash_lookup    = not_defined_hash_lookup;
    config->ident_hash_new = not_defined_ident_hash_new;

    config->int2fix = not_defined_int2fix;

    config->bignum_negate = not_defined_bignum_negate;
    config->big_norm      = not_defined_big_norm;
    config->int2big       = not_defined_int2big;
    config->cstr_to_inum  = not_defined_cstr_to_inum;

    config->float_new   = not_defined_float_new;
    config->float_value = not_defined_float_value;

    config->fix2int          = not_defined_fix2int;
    config->num2int          = not_defined_num2int;
    config->int_positive_pow = not_defined_int_positive_pow;
    config->int2num          = not_defined_int2num;
    config->fix2long         = not_defined_fix2long;

    config->rational_new     = not_defined_rational_new;
    config->rational_raw     = not_defined_rational_raw;
    config->rational_raw1    = not_defined_rational_raw1;
    config->rational_set_num = not_defined_rational_set_num;
    config->rational_get_num = not_defined_rational_get_num;

    config->complex_raw       = not_defined_complex_raw;
    config->rcomplex_set_real = not_defined_rcomplex_set_real;
    config->rcomplex_set_imag = not_defined_rcomplex_set_imag;
    config->rcomplex_get_real = not_defined_rcomplex_get_real;
    config->rcomplex_get_imag = not_defined_rcomplex_get_imag;

    config->stderr_tty_p    = not_defined_stderr_tty_p;
    config->write_error_str = not_defined_write_error_str;
    config->default_rs = not_defined_default_rs;
    config->io_write = not_defined_io_write;
    config->io_flush = not_defined_io_flush;
    config->io_puts = not_defined_io_puts;
    config->io_gets_internal= not_defined_io_gets_internal;

    config->debug_output_stdout = not_defined_debug_output_stdout;
    config->debug_output_stderr = not_defined_debug_output_stderr;

    config->is_usascii_enc        = not_defined_is_usascii_enc;
    config->enc_isalnum           = not_defined_enc_isalnum;
    config->enc_precise_mbclen    = not_defined_enc_precise_mbclen;
    config->mbclen_charfound_p    = not_defined_mbclen_charfound_p;
    config->enc_name              = not_defined_enc_name;
    config->enc_prev_char         = not_defined_enc_prev_char;
    config->enc_get               = not_defined_enc_get;
    config->enc_asciicompat       = not_defined_enc_asciicompat;
    config->utf8_encoding         = not_defined_utf8_encoding;
    config->enc_associate         = not_defined_enc_associate;
    config->ascii8bit_encoding    = not_defined_ascii8bit_encoding;
    config->enc_codelen           = not_defined_enc_codelen;
    config->enc_mbcput            = not_defined_enc_mbcput;
    config->char_to_option_kcode  = not_defined_char_to_option_kcode;
    config->ascii8bit_encindex    = not_defined_ascii8bit_encindex;
    config->enc_find_index        = not_defined_enc_find_index;
    config->enc_from_index        = not_defined_enc_from_index;
    config->enc_associate_index   = not_defined_enc_associate_index;
    config->enc_isspace           = not_defined_enc_isspace;
    config->enc_coderange_7bit    = not_defined_ENC_CODERANGE_7BIT;
    config->enc_coderange_unknown = not_defined_ENC_CODERANGE_UNKNOWN;
    config->enc_compatible        = not_defined_enc_compatible;
    config->enc_from_encoding     = not_defined_enc_from_encoding;
    config->encoding_get          = not_defined_encoding_get;
    config->encoding_set          = not_defined_encoding_set;
    config->encoding_is_ascii8bit = not_defined_encoding_is_ascii8bit;
    config->usascii_encoding      = not_defined_usascii_encoding;

    config->ractor_make_shareable = not_defined_ractor_make_shareable;

    config->vm_keep_script_lines = not_defined_vm_keep_script_lines;
    config->local_defined        = not_defined_local_defined;
    config->dvar_defined         = not_defined_dvar_defined;

    config->literal_cmp  = not_defined_literal_cmp;
    config->literal_hash = not_defined_literal_hash;

    config->builtin_class_name = not_defined_builtin_class_name;
    config->syntax_error_append = not_defined_syntax_error_append;
    config->raise = not_defined_raise;
    config->syntax_error_new = not_defined_syntax_error_new;

    config->errinfo = not_defined_errinfo;
    config->set_errinfo = not_defined_set_errinfo;
    config->exc_raise = not_defined_exc_raise;
    config->make_exception = not_defined_make_exception;

    config->sized_xfree = not_defined_sized_xfree;
    config->sized_realloc_n = not_defined_sized_realloc_n;
    config->obj_write = not_defined_obj_write;
    config->obj_written = not_defined_obj_written;
    config->gc_register_mark_object = not_defined_gc_register_mark_object;
    config->gc_guard = not_defined_gc_guard;
    config->gc_mark = not_defined_gc_mark;
    config->gc_mark_movable = not_defined_gc_mark_movable;
    config->gc_location = not_defined_gc_location;

    config->reg_compile = not_defined_reg_compile;
    config->reg_check_preprocess = not_defined_reg_check_preprocess;
    config->memcicmp = not_defined_memcicmp;

    config->compile_warn    = not_defined_compile_warn;
    config->compile_warning = not_defined_compile_warning;
    config->bug             = not_defined_bug;
    config->fatal           = not_defined_fatal;
    config->verbose         = not_defined_verbose;

    config->make_backtrace = not_defined_make_backtrace;

    config->scan_hex    = not_defined_scan_hex;
    config->scan_oct    = not_defined_scan_oct;
    config->scan_digits = not_defined_scan_digits;
    config->strtod      = not_defined_strtod;

    config->isspace = not_defined_isspace;
    config->isascii = not_defined_isascii;
    config->iscntrl = not_defined_iscntrl;
    config->isalpha = not_defined_isalpha;
    config->isdigit = not_defined_isdigit;
    config->isalnum = not_defined_isalnum;
    config->isxdigit = not_defined_isxdigit;
    config->strcasecmp = not_defined_strcasecmp;
    config->strncasecmp = not_defined_strncasecmp;

    config->rbool = not_defined_rbool;
    config->undef_p = not_defined_undef_p;
    config->rtest = not_defined_rtest;
    config->nil_p = not_defined_nil_p;
    config->flonum_p = not_defined_flonum_p;
    config->qnil  = not_defined_Qnil;
    config->qtrue = not_defined_Qtrue;
    config->qfalse = not_defined_Qfalse;
    config->qundef = not_defined_Qundef;
    config->eArgError = not_defined_eArgError;
    config->mRubyVMFrozenCore = not_defined_mRubyVMFrozenCore;
    config->long2int = not_defined_long2int;
    config->special_const_p = not_defined_special_const_p;
    config->builtin_type = not_defined_builtin_type;

    config->node_case_when_optimizable_literal = not_defined_node_case_when_optimizable_literal;
}
