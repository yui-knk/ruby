/* This is a wrapper for parse.y */

#include "external/parse.h"
#include "internal/ruby_parser.h"

#include "ruby/ruby.h"
#include "node.h"

struct ruby_parser {
    rb_parser_t *parser_params;
};


static void
parser_mark2(void *ptr)
{
    struct ruby_parser *parser = (struct ruby_parser*)ptr;
    parser_mark(parser->parser_params);
}

static void
parser_free2(void *ptr)
{
    struct ruby_parser *parser = (struct ruby_parser*)ptr;
    parser_free(parser->parser_params);
}

static size_t
parser_memsize2(const void *ptr)
{
    struct ruby_parser *parser = (struct ruby_parser*)ptr;
    return parser_memsize(parser->parser_params);
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

VALUE
rb_parser_new(void)
{
    struct ruby_parser *parser;
    rb_parser_config_t config;

    VALUE vparser = TypedData_Make_Struct(0, struct ruby_parser,
                                         &ruby_parser_data_type, parser);

    config.malloc = ruby_xmalloc;
    config.calloc = ruby_xcalloc;
    config.free = ruby_xfree;

    parser->parser_params = rb_ruby_parser_new(config);

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

    TypedData_Get_Struct(vparser, struct ruby_parser, &ruby_parser_data_type, parser);
    return rb_ruby_parser_compile_file_path(parser->parser_params, fname, file, start);
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

    TypedData_Get_Struct(vparser, struct ruby_parser, &ruby_parser_data_type, parser);
    return rb_ruby_parser_compile_generic(parser->parser_params, lex_gets, fname, input, start);
}

rb_ast_t*
rb_parser_compile_string(VALUE vparser, const char *f, VALUE s, int line)
{
    struct ruby_parser *parser;

    TypedData_Get_Struct(vparser, struct ruby_parser, &ruby_parser_data_type, parser);
    return rb_ruby_parser_compile_string(parser->parser_params, f, s, line);
}

rb_ast_t*
rb_parser_compile_string_path(VALUE vparser, VALUE f, VALUE s, int line)
{
    struct ruby_parser *parser;

    TypedData_Get_Struct(vparser, struct ruby_parser, &ruby_parser_data_type, parser);
    return rb_ruby_parser_compile_string_path(parser->parser_params, f, s, line);
}
