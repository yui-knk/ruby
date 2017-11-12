VALUE rb_cAST;

struct ASTNodeData {
    rb_ast_t *ast;
    NODE *node;
};

static void
node_gc_mark(void *ptr)
{
}

static const rb_data_type_t rb_node_type = {
    "AST/node",
    {node_gc_mark, RUBY_TYPED_DEFAULT_FREE, 0,},
    0, 0,
    RUBY_TYPED_FREE_IMMEDIATELY,
};

static VALUE rb_ast_s_alloc(VALUE klass);

static void
setup_node(VALUE obj, rb_ast_t *ast, NODE *node)
{
    struct ASTNodeData *data;

    TypedData_Get_Struct(obj, struct ASTNodeData, &rb_node_type, data);
    data->ast = ast;
    data->node = node;
}

static VALUE
ast_new_internal(VALUE klass, rb_ast_t *ast, NODE *node)
{
    VALUE obj;

    obj = rb_ast_s_alloc(klass);
    setup_node(obj, ast, node);

    return obj;
}

static VALUE
rb_ast_s_parse(VALUE klass, VALUE str)
{
    VALUE obj;
    rb_ast_t *ast = 0;

    const VALUE parser = rb_parser_new();

    str = rb_check_string_type(str);
    ast = rb_parser_compile_string_path(parser, rb_str_new_cstr("no file name"), str, 1);

    obj = ast_new_internal(klass, ast, ast->root);

    return obj;
}

static VALUE
rb_ast_s_alloc(VALUE klass)
{
    struct ASTNodeData *data;
    VALUE obj = TypedData_Make_Struct(klass, struct ASTNodeData, &rb_node_type, data);

    return obj;
}

static VALUE
node_type_to_str(NODE *node)
{
    return rb_str_new_cstr(ruby_node_name(nd_type(node)));
}

static VALUE
rb_ast_type(VALUE self)
{
    struct ASTNodeData *data;
    TypedData_Get_Struct(self, struct ASTNodeData, &rb_node_type, data);

    return node_type_to_str(data->node);
}

static VALUE
rb_ast_first_lineno(VALUE self)
{
    struct ASTNodeData *data;
    TypedData_Get_Struct(self, struct ASTNodeData, &rb_node_type, data);

    return INT2FIX(nd_lineno(data->node));
}

static VALUE
rb_ast_first_column(VALUE self)
{
    struct ASTNodeData *data;
    TypedData_Get_Struct(self, struct ASTNodeData, &rb_node_type, data);

    return INT2FIX(nd_column(data->node));
}

static VALUE
rb_ast_last_lineno(VALUE self)
{
    struct ASTNodeData *data;
    TypedData_Get_Struct(self, struct ASTNodeData, &rb_node_type, data);

    return INT2FIX(nd_last_lineno(data->node));
}

static VALUE
rb_ast_last_column(VALUE self)
{
    struct ASTNodeData *data;
    TypedData_Get_Struct(self, struct ASTNodeData, &rb_node_type, data);

    return INT2FIX(nd_last_column(data->node));
}
