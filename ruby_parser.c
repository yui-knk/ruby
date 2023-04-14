/* This is a wrapper for parse.y */

#include "internal.h"
#include "internal/array.h"
#include "internal/bignum.h"
#include "internal/compile.h"
#include "internal/complex.h"
#include "internal/encoding.h"
#include "internal/error.h"
#include "internal/hash.h"
#include "internal/io.h"
#include "internal/parse.h"
#include "internal/rational.h"
#include "internal/re.h"
#include "internal/ruby_parser.h"
#include "internal/string.h"
#include "internal/symbol.h"
#include "internal/thread.h"

#include "ruby/ruby.h"
#include "node.h"
#include "internal.h"
#include "ruby/ractor.h"
#include "vm_core.h"

struct ruby_parser {
    rb_parser_t *parser_params;
};


static void
parser_mark2(void *ptr)
{
    struct ruby_parser *parser = (struct ruby_parser*)ptr;
    rb_ruby_parser_mark(parser->parser_params);
}

static void
parser_free2(void *ptr)
{
    struct ruby_parser *parser = (struct ruby_parser*)ptr;
    rb_ruby_parser_free(parser->parser_params);
}

static size_t
parser_memsize2(const void *ptr)
{
    struct ruby_parser *parser = (struct ruby_parser*)ptr;
    return rb_ruby_parser_memsize(parser->parser_params);
}

static const rb_data_type_t ruby_parser_data_type = {
    "parser",
    {
        parser_mark2,
        parser_free2,
        parser_memsize2,
    },
    0, 0, RUBY_TYPED_FREE_IMMEDIATELY
};

static void
bignum_negate(VALUE b)
{
    BIGNUM_NEGATE(b);
}

static int
is_ascii_string2(VALUE str)
{
    return is_ascii_string(str);
}

static void
rational_set_num(VALUE r, VALUE n)
{
    RATIONAL_SET_NUM(r, n);
}

static VALUE
rational_get_num(VALUE obj)
{
    return RRATIONAL(obj)->num;
}

static void
rcomplex_set_real(VALUE cmp, VALUE r)
{
    RCOMPLEX_SET_REAL(cmp, r);
}

static void
rcomplex_set_imag(VALUE cmp, VALUE i)
{
    RCOMPLEX_SET_IMAG(cmp, i);
}

static VALUE
rcomplex_get_real(VALUE obj)
{
    return RCOMPLEX(obj)->real;
}

static VALUE
rcomplex_get_imag(VALUE obj)
{
    return RCOMPLEX(obj)->imag;
}

static VALUE
syntax_error_append(VALUE exc, VALUE file, int line, int column,
                       const void *enc, const char *fmt, va_list args)
{
    return rb_syntax_error_append(exc, file, line, column, (rb_encoding *)enc, fmt, args);
}

static int
vm_keep_script_lines(void)
{
    return ruby_vm_keep_script_lines;
}

static int
local_defined(ID id, const void *p)
{
    return rb_local_defined(id, (const rb_iseq_t *)p);
}

static int
dvar_defined(ID id, const void *p)
{
    return rb_dvar_defined(id, (const rb_iseq_t *)p);
}

static bool
hash_literal_key_p(VALUE k)
{
    switch (OBJ_BUILTIN_TYPE(k)) {
      case T_NODE:
        return false;
      default:
        return true;
    }
}

static int
literal_cmp(VALUE val, VALUE lit)
{
    if (val == lit) return 0;
    if (!hash_literal_key_p(val) || !hash_literal_key_p(lit)) return -1;
    return rb_iseq_cdhash_cmp(val, lit);
}

static st_index_t
literal_hash(VALUE a)
{
    if (!hash_literal_key_p(a)) return (st_index_t)a;
    return rb_iseq_cdhash_hash(a);
}

static int
is_usascii_enc(void *enc)
{
    return rb_is_usascii_enc((rb_encoding *)enc);
}

void
rb_parser_config_initialize(rb_parser_config_t *config)
{
    config->malloc = ruby_xmalloc;
    config->calloc = ruby_xcalloc;
    config->free   = ruby_xfree;

    config->compile_callback  = rb_suppress_tracing;

    config->ary_new           = rb_ary_new;
    config->ary_push          = rb_ary_push;
    config->ary_new_from_args = rb_ary_new_from_args;
    config->ary_pop           = rb_ary_pop;
    config->ary_last          = rb_ary_last;
    config->ary_unshift       = rb_ary_unshift;
    config->ary_new2          = rb_ary_new2;
    config->ary_entry         = rb_ary_entry;
    config->ary_join          = rb_ary_join;
    config->ary_reverse       = rb_ary_reverse;
    config->ary_clear         = rb_ary_clear;

    config->sym_intern_ascii_cstr = rb_sym_intern_ascii_cstr;
    config->make_temporary_id     = rb_make_temporary_id;

    config->str_catf       = rb_str_catf;
    config->str_cat_cstr   = rb_str_cat_cstr;
    config->str_subseq     = rb_str_subseq;
    config->str_dup        = rb_str_dup;
    config->str_new_frozen = rb_str_new_frozen;
    config->str_buf_new    = rb_str_buf_new;
    config->str_buf_cat    = rb_str_buf_cat;
    config->str_modify     = rb_str_modify;
    config->str_set_len    = rb_str_set_len;
    config->str_cat        = rb_str_cat;
    config->str_resize     = rb_str_resize;
    config->str_new        = rb_str_new;
    config->str_new_cstr   = rb_str_new_cstr;
    config->fstring        = rb_fstring;
    config->is_ascii_string = is_ascii_string2;

    config->hash_clear     = rb_hash_clear;
    config->hash_new       = rb_hash_new;
    config->hash_aset      = rb_hash_aset;
    config->hash_lookup    = rb_hash_lookup;
    config->ident_hash_new = rb_ident_hash_new;

    config->bignum_negate = bignum_negate;

    config->rational_set_num = rational_set_num;
    config->rational_get_num = rational_get_num;

    config->rcomplex_set_real = rcomplex_set_real;
    config->rcomplex_set_imag = rcomplex_set_imag;
    config->rcomplex_get_real = rcomplex_get_real;
    config->rcomplex_get_imag = rcomplex_get_imag;

    config->stderr_tty_p    = rb_stderr_tty_p;
    config->write_error_str = rb_write_error_str;
    config->debug_output_stdout = rb_ractor_stdout;
    config->debug_output_stderr = rb_ractor_stderr;

    config->is_usascii_enc = is_usascii_enc;

    config->ractor_make_shareable = rb_ractor_make_shareable;

    config->vm_keep_script_lines = vm_keep_script_lines;
    config->local_defined        = local_defined;
    config->dvar_defined         = dvar_defined;

    config->literal_cmp  = literal_cmp;
    config->literal_hash = literal_hash;

    config->builtin_class_name = rb_builtin_class_name;
    config->syntax_error_append = syntax_error_append;

    config->reg_compile = rb_reg_compile;
    config->reg_check_preprocess = rb_reg_check_preprocess;
}

VALUE
rb_parser_new(void)
{
    struct ruby_parser *parser;
    rb_parser_config_t config;
    rb_parser_t *parser_params;

    rb_parser_config_initialize(&config);
    /*
     * Create parser_params ahead of vparser because
     * rb_ruby_parser_new can run GC so if create vparser
     * first, parser_mark2 tries to mark not initialized parser_params.
     */
    parser_params = rb_ruby_parser_new(config);
    VALUE vparser = TypedData_Make_Struct(0, struct ruby_parser,
                                         &ruby_parser_data_type, parser);
    parser->parser_params = parser_params;

    return vparser;
}

void
rb_parser_set_options(VALUE vparser, int print, int loop, int chomp, int split)
{
    struct ruby_parser *parser;

    TypedData_Get_Struct(vparser, struct ruby_parser, &ruby_parser_data_type, parser);
    rb_ruby_parser_set_options(parser->parser_params, print, loop, chomp, split);
}

VALUE
rb_parser_set_context(VALUE vparser, const struct rb_iseq_struct *base, int main)
{
    struct ruby_parser *parser;

    TypedData_Get_Struct(vparser, struct ruby_parser, &ruby_parser_data_type, parser);
    rb_ruby_parser_set_context(parser->parser_params, base, main);
    return vparser;
}

void
rb_parser_keep_script_lines(VALUE vparser)
{
    struct ruby_parser *parser;

    TypedData_Get_Struct(vparser, struct ruby_parser, &ruby_parser_data_type, parser);
    rb_ruby_parser_keep_script_lines(parser->parser_params);
}

void
rb_parser_error_tolerant(VALUE vparser)
{
    struct ruby_parser *parser;

    TypedData_Get_Struct(vparser, struct ruby_parser, &ruby_parser_data_type, parser);
    rb_ruby_parser_error_tolerant(parser->parser_params);
}

rb_ast_t*
rb_parser_compile_file_path(VALUE vparser, VALUE fname, VALUE file, int start)
{
    struct ruby_parser *parser;
    rb_ast_t *ast;

    TypedData_Get_Struct(vparser, struct ruby_parser, &ruby_parser_data_type, parser);
    ast = rb_ruby_parser_compile_file_path(parser->parser_params, fname, file, start);
    RB_GC_GUARD(vparser);

    return ast;
}

void
rb_parser_keep_tokens(VALUE vparser)
{
    struct ruby_parser *parser;

    TypedData_Get_Struct(vparser, struct ruby_parser, &ruby_parser_data_type, parser);
    rb_ruby_parser_keep_tokens(parser->parser_params);
}

rb_ast_t*
rb_parser_compile_generic(VALUE vparser, VALUE (*lex_gets)(VALUE, int), VALUE fname, VALUE input, int start)
{
    struct ruby_parser *parser;
    rb_ast_t *ast;

    TypedData_Get_Struct(vparser, struct ruby_parser, &ruby_parser_data_type, parser);
    ast = rb_ruby_parser_compile_generic(parser->parser_params, lex_gets, fname, input, start);
    RB_GC_GUARD(vparser);

    return ast;
}

rb_ast_t*
rb_parser_compile_string(VALUE vparser, const char *f, VALUE s, int line)
{
    struct ruby_parser *parser;
    rb_ast_t *ast;

    TypedData_Get_Struct(vparser, struct ruby_parser, &ruby_parser_data_type, parser);
    ast = rb_ruby_parser_compile_string(parser->parser_params, f, s, line);
    RB_GC_GUARD(vparser);

    return ast;
}

rb_ast_t*
rb_parser_compile_string_path(VALUE vparser, VALUE f, VALUE s, int line)
{
    struct ruby_parser *parser;
    rb_ast_t *ast;

    TypedData_Get_Struct(vparser, struct ruby_parser, &ruby_parser_data_type, parser);
    ast = rb_ruby_parser_compile_string_path(parser->parser_params, f, s, line);
    RB_GC_GUARD(vparser);

    return ast;
}

VALUE
rb_parser_encoding(VALUE vparser)
{
    struct ruby_parser *parser;

    TypedData_Get_Struct(vparser, struct ruby_parser, &ruby_parser_data_type, parser);
    return rb_ruby_parser_encoding(parser->parser_params);
}

VALUE
rb_parser_end_seen_p(VALUE vparser)
{
    struct ruby_parser *parser;

    TypedData_Get_Struct(vparser, struct ruby_parser, &ruby_parser_data_type, parser);
    return RBOOL(rb_ruby_parser_end_seen_p(parser->parser_params));
}

VALUE
rb_parser_set_yydebug(VALUE vparser, VALUE flag)
{
    struct ruby_parser *parser;

    TypedData_Get_Struct(vparser, struct ruby_parser, &ruby_parser_data_type, parser);
    rb_ruby_parser_set_yydebug(parser->parser_params, RTEST(flag));
    return flag;
}
