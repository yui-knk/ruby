#ifndef RUBY_NODE2_H
#define RUBY_NODE2_H 1

#include "external/parse.h"

RUBY_SYMBOL_EXPORT_BEGIN

rb_ast_t *rb_ast_new(rb_parser_config_t *config);

RUBY_SYMBOL_EXPORT_END

#endif /* RUBY_NODE2_H */
