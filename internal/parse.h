#ifndef INTERNAL_PARSE_H                                 /*-*-C-*-vi:se ft=c:*/
#define INTERNAL_PARSE_H
/**
 * @author     Ruby developers <ruby-core@ruby-lang.org>
 * @copyright  This  file  is   a  part  of  the   programming  language  Ruby.
 *             Permission  is hereby  granted,  to  either redistribute  and/or
 *             modify this file, provided that  the conditions mentioned in the
 *             file COPYING are met.  Consult the file for details.
 * @brief      Internal header for the parser.
 */
#include "ruby/ruby.h"          /* for VALUE */
#include "external/parse.h"
#include "node.h"
struct rb_iseq_struct;          /* in vm_core.h */

/* parse.y */
void rb_ruby_parser_mark(void *ptr);
void rb_ruby_parser_free(void *ptr);
size_t rb_ruby_parser_memsize(const void *ptr);

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


#endif /* INTERNAL_PARSE_H */
