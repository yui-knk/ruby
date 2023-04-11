#ifndef EXTERNAL_PARSE_H
#define EXTERNAL_PARSE_H

#include <sys/types.h>

// TODO: Expand
#include "ruby/internal/value.h"

typedef struct rb_parser_config_struct {
    void *(*malloc)(size_t size);
    void *(*calloc)(size_t number, size_t size);
    void (*free)(void *ptr);
} rb_parser_config_t;

typedef struct parser_params rb_parser_t;

#endif /* EXTERNAL_PARSE_H */
