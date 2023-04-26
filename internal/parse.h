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
#include <limits.h>
#include "external/parse.h"
#include "external/node.h"
#include "internal/static_assert.h"

#define rb_encoding void

struct rb_iseq_struct;          /* in vm_core.h */

#define STRTERM_HEREDOC IMEMO_FL_USER0

/* structs for managing terminator of string literal and heredocment */
typedef struct rb_strterm_literal_struct {
    union {
        VALUE dummy;
        long nest;
    } u0;
    union {
        VALUE dummy;
        long func;	    /* STR_FUNC_* (e.g., STR_FUNC_ESCAPE and STR_FUNC_EXPAND) */
    } u1;
    union {
        VALUE dummy;
        long paren;	    /* '(' of `%q(...)` */
    } u2;
    union {
        VALUE dummy;
        long term;	    /* ')' of `%q(...)` */
    } u3;
} rb_strterm_literal_t;

#define HERETERM_LENGTH_BITS ((SIZEOF_VALUE - 1) * CHAR_BIT - 1)

typedef struct rb_strterm_heredoc_struct {
    VALUE lastline;	/* the string of line that contains `<<"END"` */
    long offset;	/* the column of END in `<<"END"` */
    int sourceline;	/* lineno of the line that contains `<<"END"` */
    unsigned length	/* the length of END in `<<"END"` */
#if HERETERM_LENGTH_BITS < SIZEOF_INT * CHAR_BIT
    : HERETERM_LENGTH_BITS
# define HERETERM_LENGTH_MAX ((1U << HERETERM_LENGTH_BITS) - 1)
#else
# define HERETERM_LENGTH_MAX UINT_MAX
#endif
    ;
#if HERETERM_LENGTH_BITS < SIZEOF_INT * CHAR_BIT
    unsigned quote: 1;
    unsigned func: 8;
#else
    uint8_t quote;
    uint8_t func;
#endif
} rb_strterm_heredoc_t;
STATIC_ASSERT(rb_strterm_heredoc_t, sizeof(rb_strterm_heredoc_t) <= 4 * SIZEOF_VALUE);

typedef struct rb_strterm_struct {
    VALUE flags;
    union {
        rb_strterm_literal_t literal;
        rb_strterm_heredoc_t heredoc;
    } u;
} rb_strterm_t;

/* parse.y */
void rb_ruby_parser_mark(void *ptr);
size_t rb_ruby_parser_memsize(const void *ptr);

void rb_ruby_parser_set_options(rb_parser_t *p, int print, int loop, int chomp, int split);
void rb_ruby_parser_set_options(rb_parser_t *p, int print, int loop, int chomp, int split);
rb_parser_t *rb_ruby_parser_set_context(rb_parser_t *p, const struct rb_iseq_struct *base, int main);
void rb_ruby_parser_keep_script_lines(rb_parser_t *p);
void rb_ruby_parser_error_tolerant(rb_parser_t *p);
rb_ast_t* rb_ruby_parser_compile_file_path(rb_parser_t *p, VALUE fname, VALUE file, int start);
void rb_ruby_parser_keep_tokens(rb_parser_t *p);
rb_ast_t* rb_ruby_parser_compile_generic(rb_parser_t *p, VALUE (*lex_gets)(VALUE, int), VALUE fname, VALUE input, int start);
rb_ast_t* rb_ruby_parser_compile_string_path(rb_parser_t *p, VALUE f, VALUE s, int line);
VALUE rb_ruby_parser_encoding(rb_parser_t *p);
int rb_ruby_parser_end_seen_p(rb_parser_t *p);
int rb_ruby_parser_set_yydebug(rb_parser_t *p, int flag);

int rb_reg_named_capture_assign_iter_impl(struct parser_params *p, const char *s, long len, void *enc, NODE **succ_block, const rb_code_location_t *loc);


#undef rb_encoding

#endif /* INTERNAL_PARSE_H */
