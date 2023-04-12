#ifndef INTERNAL_RUBY_PARSE_H
#define INTERNAL_RUBY_PARSE_H

#include "external/parse.h"
#include "vm.h"
#include "node.h"

rb_parser_t *rb_ruby_parser_new(rb_parser_config_t config);
void rb_ruby_parser_set_options(rb_parser_t *p, int print, int loop, int chomp, int split);
void rb_ruby_parser_set_options(rb_parser_t *p, int print, int loop, int chomp, int split);
rb_parser_t *rb_ruby_parser_set_context(rb_parser_t *p, const struct rb_iseq_struct *base, int main);
void rb_ruby_parser_keep_script_lines(rb_parser_t *p);
void rb_ruby_parser_error_tolerant(rb_parser_t *p);
rb_ast_t* rb_ruby_parser_compile_file_path(rb_parser_t *p, VALUE fname, VALUE file, int start);
void rb_ruby_parser_keep_tokens(rb_parser_t *p);
rb_ast_t* rb_ruby_parser_compile_generic(rb_parser_t *p, VALUE (*lex_gets)(VALUE, int), VALUE fname, VALUE input, int start);
rb_ast_t* rb_ruby_parser_compile_string(rb_parser_t *p, const char *f, VALUE s, int line);
rb_ast_t* rb_ruby_parser_compile_string_path(rb_parser_t *p, VALUE f, VALUE s, int line);
VALUE rb_ruby_parser_encoding(rb_parser_t *p);
int rb_ruby_parser_end_seen_p(rb_parser_t *p);
int rb_ruby_parser_set_yydebug(rb_parser_t *p, int flag);

#endif /* INTERNAL_RUBY_PARSE_H */
