#ifndef INTERNAL_RUBY_PARSE_H
#define INTERNAL_RUBY_PARSE_H

#include "vm.h"
#include "node.h"
#include "external/parse.h"

VALUE rb_parser_new(void);
VALUE rb_parser_end_seen_p(VALUE);
VALUE rb_parser_encoding(VALUE);
VALUE rb_parser_set_yydebug(VALUE, VALUE);
VALUE rb_parser_dump_tree(const NODE *node, int comment);
void rb_parser_set_options(VALUE, int, int, int, int);
void *rb_parser_load_file(VALUE parser, VALUE name);
void rb_parser_keep_script_lines(VALUE vparser);
void rb_parser_error_tolerant(VALUE vparser);
void rb_parser_keep_tokens(VALUE vparser);

RUBY_SYMBOL_EXPORT_BEGIN
VALUE rb_parser_set_context(VALUE, const struct rb_iseq_struct *, int);
RUBY_SYMBOL_EXPORT_END

rb_ast_t *rb_parser_compile_string(VALUE, const char*, VALUE, int);
rb_ast_t *rb_parser_compile_string_path(VALUE vparser, VALUE fname, VALUE src, int line);
rb_ast_t *rb_parser_compile_file_path(VALUE vparser, VALUE fname, VALUE input, int line);
rb_ast_t *rb_parser_compile_generic(VALUE vparser, VALUE (*lex_gets)(VALUE, int), VALUE fname, VALUE input, int line);

#endif /* INTERNAL_RUBY_PARSE_H */
