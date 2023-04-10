/* This is a wrapper for parse.y */

#include "external/parse.h"
#include "internal/ruby_parser.h"

#include "ruby/ruby.h"
#include "node.h"

static void
parser_mark(void *ptr)
{
//     struct parser_params *p = (struct parser_params*)ptr;

//     rb_gc_mark(p->lex.input);
//     rb_gc_mark(p->lex.lastline);
//     rb_gc_mark(p->lex.nextline);
//     rb_gc_mark(p->ruby_sourcefile_string);
//     rb_gc_mark((VALUE)p->lex.strterm);
//     rb_gc_mark((VALUE)p->ast);
//     rb_gc_mark(p->case_labels);
//     rb_gc_mark(p->delayed.token);
// #ifndef RIPPER
//     rb_gc_mark(p->debug_lines);
//     rb_gc_mark(p->compile_option);
//     rb_gc_mark(p->error_buffer);
//     rb_gc_mark(p->end_expect_token_locations);
//     rb_gc_mark(p->tokens);
// #else
//     rb_gc_mark(p->value);
//     rb_gc_mark(p->result);
//     rb_gc_mark(p->parsing_thread);
// #endif
//     rb_gc_mark(p->debug_buffer);
//     rb_gc_mark(p->debug_output);
// #ifdef YYMALLOC
//     rb_gc_mark((VALUE)p->heap);
// #endif
}

static void
parser_free(void *ptr)
{
    // struct parser_params *p = (struct parser_params*)ptr;
    // struct local_vars *local, *prev;

    // if (p->tokenbuf) {
    //     ruby_sized_xfree(p->tokenbuf, p->toksiz);
    // }
    // for (local = p->lvtbl; local; local = prev) {
    //     if (local->vars) xfree(local->vars);
    //     prev = local->prev;
    //     xfree(local);
    // }
    // {
    //     token_info *ptinfo;
    //     while ((ptinfo = p->token_info) != 0) {
    //         p->token_info = ptinfo->next;
    //         xfree(ptinfo);
    //     }
    // }
    // xfree(ptr);
}

static size_t
parser_memsize(const void *ptr)
{
    // struct parser_params *p = (struct parser_params*)ptr;
    // struct local_vars *local;
    // size_t size = sizeof(*p);

    // size += p->toksiz;
    // for (local = p->lvtbl; local; local = local->prev) {
    //     size += sizeof(*local);
    //     if (local->vars) size += local->vars->capa * sizeof(ID);
    // }
    // return size;
    return 0;
}

static const rb_data_type_t ruby_parser_data_type = {
    "parser",
    {
        parser_mark,
        parser_free,
        parser_memsize,
    },
    0, 0, RUBY_TYPED_FREE_IMMEDIATELY
};

struct ruby_parser {
    rb_parser_t *parser_params;
};

VALUE
rb_parser_new(void)
{
    struct ruby_parser *parser;
    rb_parser_config_t config;

    VALUE vparser = TypedData_Make_Struct(0, struct ruby_parser,
                                         &ruby_parser_data_type, parser);

    config.malloc = ruby_xmalloc;
    config.free = xfree;

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
