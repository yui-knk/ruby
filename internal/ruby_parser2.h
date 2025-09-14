#ifndef INTERNAL_RUBY_PARSE2_H
#define INTERNAL_RUBY_PARSE2_H

#include "internal.h"
#include "internal/bignum.h"
#include "internal/compilers.h"
#include "internal/complex.h"
#include "internal/parse.h"
#include "internal/rational.h"
#include "internal/ruby_parser.h"
#include "rubyparser.h"
#include "vm.h"

RUBY_SYMBOL_EXPORT_BEGIN
#ifdef UNIVERSAL_PARSER
const rb_parser_config_t *rb_ruby_parser_config(void);
rb_parser_t *rb_parser2_params_new(void);
#endif
VALUE rb_parser2_set_context(VALUE, const struct rb_iseq_struct *, int);
VALUE rb_parser2_new(void);
VALUE rb_parser2_compile_string_path(VALUE vparser, VALUE fname, VALUE src, int line);
VALUE rb_str_new_parser2_string(rb_parser_string_t *str);
VALUE rb_str_new_mutable_parser2_string(rb_parser_string_t *str);
rb_parser_string_t *rb_parser2_lex_get_str(struct parser_params *p, struct lex_pointer_string *ptr_str);

// VALUE rb_node_str_string_val(const NODE *);
// VALUE rb_node_sym_string_val(const NODE *);
// VALUE rb_node_dstr_string_val(const NODE *);
// VALUE rb_node_regx_string_val(const NODE *);
// VALUE rb_node_dregx_string_val(const NODE *);
// VALUE rb_node_line_lineno_val(const NODE *);
// VALUE rb_node_file_path_val(const NODE *);
// VALUE rb_node_encoding_val(const NODE *);

// VALUE rb_node_integer_literal_val(const NODE *);
// VALUE rb_node_float_literal_val(const NODE *);
// VALUE rb_node_rational_literal_val(const NODE *);
// VALUE rb_node_imaginary_literal_val(const NODE *);
RUBY_SYMBOL_EXPORT_END

VALUE rb_parser2_end_seen_p(VALUE);
VALUE rb_parser2_encoding(VALUE);
VALUE rb_parser2_set_yydebug(VALUE, VALUE);
VALUE rb_parser2_build_script_lines_from(rb_parser_ary_t *script_lines);
void rb_parser2_set_options(VALUE, int, int, int, int);
VALUE rb_parser2_load_file(VALUE parser, VALUE name);
void rb_parser2_set_script_lines(VALUE vparser);
void rb_parser2_error_tolerant(VALUE vparser);
void rb_parser2_keep_tokens(VALUE vparser);

VALUE rb_parser2_compile_string(VALUE, const char*, VALUE, int);
VALUE rb_parser2_compile_file_path(VALUE vparser, VALUE fname, VALUE input, int line);
VALUE rb_parser2_compile_generic(VALUE vparser, rb_parser_lex_gets_func *lex_gets, VALUE fname, VALUE input, int line);
VALUE rb_parser2_compile_array(VALUE vparser, VALUE fname, VALUE array, int start);

VALUE rb_ruby_ast2_new(const NODE *const root);
rb_ast2_t *rb_ruby_ast2_data_get(VALUE ast_value);

#endif /* INTERNAL_RUBY_PARSE2_H */
