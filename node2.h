#ifndef RUBY_NODE2_H
#define RUBY_NODE2_H 1

#include "external/parse.h"

RUBY_SYMBOL_EXPORT_BEGIN

rb_ast_t *rb_ast_new(rb_parser_config_t *config);
void rb_ast_node_type_change(rb_ast_t *ast, NODE *n, enum node_type type);

RUBY_SYMBOL_EXPORT_END

static inline VALUE
rb_node_set_type(rb_ast_t *ast, NODE *n, enum node_type t)
{
#if RUBY_DEBUG
    rb_ast_node_type_change(ast, n, t);
#endif
    return nd_init_type(n, t);
}

#endif /* RUBY_NODE2_H */
