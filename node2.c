#include "external/node.h"
#include "external/parse.h"
#include "internal/parse.h"
#include "node2.h"

#define NODE_BUF_DEFAULT_LEN 16
#define T_NODE 0x1b

/* Setup NODE structure.
 * NODE is not an object managed by GC, but it imitates an object
 * so that it can work with `RB_TYPE_P(obj, T_NODE)`.
 * This dirty hack is needed because Ripper jumbles NODEs and other type
 * objects.
 */
void
rb_node_init(NODE *n, enum node_type type, VALUE a0, VALUE a1, VALUE a2)
{
    n->flags = T_NODE;
    nd_init_type(n, type);
    n->u1.value = a0;
    n->u2.value = a1;
    n->u3.value = a2;
    n->nd_loc.beg_pos.lineno = 0;
    n->nd_loc.beg_pos.column = 0;
    n->nd_loc.end_pos.lineno = 0;
    n->nd_loc.end_pos.column = 0;
    n->node_id = -1;
}

typedef struct node_buffer_elem_struct {
    struct node_buffer_elem_struct *next;
    long len;
    NODE buf[FLEX_ARY_LEN];
} node_buffer_elem_t;

typedef struct {
    long idx, len;
    node_buffer_elem_t *head;
    node_buffer_elem_t *last;
} node_buffer_list_t;

struct node_buffer_struct {
    node_buffer_list_t unmarkable;
    node_buffer_list_t markable;
    struct rb_ast_local_table_link *local_tables;
    VALUE mark_hash;
    // - id (sequence number)
    // - token_type
    // - text of token
    // - location info
    // Array, whose entry is array
    VALUE tokens;
    rb_parser_config_t *config;
};

#define ruby_xmalloc ast->node_buffer->config->malloc
#define rb_ident_hash_new ast->node_buffer->config->ident_hash_new
#define rb_xmalloc_mul_add ast->node_buffer->config->xmalloc_mul_add
#define rb_gc_mark ast->node_buffer->config->gc_mark
#define rb_gc_location ast->node_buffer->config->gc_location
#define rb_gc_mark_movable ast->node_buffer->config->gc_mark_movable
#define Qnil ast->node_buffer->config->qnil
#define Qtrue ast->node_buffer->config->qtrue
#define NIL_P ast->node_buffer->config->nil_p
#define rb_bug ast->node_buffer->config->bug
#define rb_hash_aset ast->node_buffer->config->hash_aset
#define RB_OBJ_WRITE(old, slot, young) ast->node_buffer->config->obj_write((VALUE)(old), (VALUE *)(slot), (VALUE)(young))

static void
init_node_buffer_list(node_buffer_list_t * nb, node_buffer_elem_t *head)
{
    nb->idx = 0;
    nb->len = NODE_BUF_DEFAULT_LEN;
    nb->head = nb->last = head;
    nb->head->len = nb->len;
    nb->head->next = NULL;
}

static node_buffer_t *
rb_node_buffer_new(rb_parser_config_t *config)
{
    const size_t bucket_size = offsetof(node_buffer_elem_t, buf) + NODE_BUF_DEFAULT_LEN * sizeof(NODE);
    const size_t alloc_size = sizeof(node_buffer_t) + (bucket_size * 2);
    STATIC_ASSERT(
        integer_overflow,
        offsetof(node_buffer_elem_t, buf) + NODE_BUF_DEFAULT_LEN * sizeof(NODE)
        > sizeof(node_buffer_t) + 2 * sizeof(node_buffer_elem_t));
    node_buffer_t *nb = config->malloc(alloc_size);
    init_node_buffer_list(&nb->unmarkable, (node_buffer_elem_t*)&nb[1]);
    init_node_buffer_list(&nb->markable, (node_buffer_elem_t*)((size_t)nb->unmarkable.head + bucket_size));
    nb->local_tables = 0;
    nb->mark_hash = config->qnil;
    nb->tokens = config->qnil;
    nb->config = config;
    return nb;
}

static void
node_buffer_list_free(node_buffer_list_t * nb)
{
    node_buffer_elem_t *nbe = nb->head;

    while (nbe != nb->last) {
        void *buf = nbe;
        nbe = nbe->next;
        xfree(buf);
    }
}

struct rb_ast_local_table_link {
    struct rb_ast_local_table_link *next;
    // struct rb_ast_id_table {
    int size;
    ID ids[FLEX_ARY_LEN];
    // }
};

static void
rb_node_buffer_free(node_buffer_t *nb)
{
    node_buffer_list_free(&nb->unmarkable);
    node_buffer_list_free(&nb->markable);
    struct rb_ast_local_table_link *local_table = nb->local_tables;
    while (local_table) {
        struct rb_ast_local_table_link *next_table = local_table->next;
        xfree(local_table);
        local_table = next_table;
    }
    xfree(nb);
}

static NODE *
ast_newnode_in_bucket(rb_ast_t *ast, node_buffer_list_t *nb)
{
    if (nb->idx >= nb->len) {
        long n = nb->len * 2;
        node_buffer_elem_t *nbe;
        nbe = rb_xmalloc_mul_add(n, sizeof(NODE), offsetof(node_buffer_elem_t, buf));
        nbe->len = n;
        nb->idx = 0;
        nb->len = n;
        nbe->next = nb->head;
        nb->head = nbe;
    }
    return &nb->head->buf[nb->idx++];
}

RBIMPL_ATTR_PURE()
static bool
nodetype_markable_p(enum node_type type)
{
    switch (type) {
      case NODE_MATCH:
      case NODE_LIT:
      case NODE_STR:
      case NODE_XSTR:
      case NODE_DSTR:
      case NODE_DXSTR:
      case NODE_DREGX:
      case NODE_DSYM:
      case NODE_ARGS:
      case NODE_ARYPTN:
      case NODE_FNDPTN:
        return true;
      default:
        return false;
    }
}

const char *
ruby_node_name(rb_ast_t *ast, int node)
{
    switch (node) {
#include "node_name.inc"
      default:
        rb_bug("unknown node: %d", node);
        return 0;
    }
}

NODE *
rb_ast_newnode(rb_ast_t *ast, enum node_type type)
{
    node_buffer_t *nb = ast->node_buffer;
    node_buffer_list_t *bucket =
        (nodetype_markable_p(type) ? &nb->markable : &nb->unmarkable);
    return ast_newnode_in_bucket(ast, bucket);
}

void
rb_ast_node_type_change(rb_ast_t *ast, NODE *n, enum node_type type)
{
    enum node_type old_type = nd_type(n);
    if (nodetype_markable_p(old_type) != nodetype_markable_p(type)) {
        rb_bug("node type changed: %s -> %s",
               ruby_node_name(ast, old_type), ruby_node_name(ast, type));
    }
}

rb_ast_id_table_t *
rb_ast_new_local_table(rb_ast_t *ast, int size)
{
    size_t alloc_size = sizeof(struct rb_ast_local_table_link) + size * sizeof(ID);
    struct rb_ast_local_table_link *link = ruby_xmalloc(alloc_size);
    link->next = ast->node_buffer->local_tables;
    ast->node_buffer->local_tables = link;
    link->size = size;

    return (rb_ast_id_table_t *) &link->size;
}

rb_ast_id_table_t *
rb_ast_resize_latest_local_table(rb_ast_t *ast, int size)
{
    struct rb_ast_local_table_link *link = ast->node_buffer->local_tables;
    size_t alloc_size = sizeof(struct rb_ast_local_table_link) + size * sizeof(ID);
    link = ruby_xrealloc(link, alloc_size);
    ast->node_buffer->local_tables = link;
    link->size = size;

    return (rb_ast_id_table_t *) &link->size;
}

void
rb_ast_delete_node(rb_ast_t *ast, NODE *n)
{
    (void)ast;
    (void)n;
    /* should we implement freelist? */
}

rb_ast_t *
rb_ast_new(rb_parser_config_t *config)
{
    node_buffer_t *nb = rb_node_buffer_new(config);
    return config->ast_new((VALUE)nb);
}

typedef void node_itr_t(rb_ast_t *ast, void *ctx, NODE * node);

static void
iterate_buffer_elements(rb_ast_t *ast, node_buffer_elem_t *nbe, long len, node_itr_t *func, void *ctx)
{
    long cursor;
    for (cursor = 0; cursor < len; cursor++) {
        func(ast, ctx, &nbe->buf[cursor]);
    }
}

static void
iterate_node_values(rb_ast_t *ast, node_buffer_list_t *nb, node_itr_t * func, void *ctx)
{
    node_buffer_elem_t *nbe = nb->head;

    /* iterate over the head first because it's not full */
    iterate_buffer_elements(ast, nbe, nb->idx, func, ctx);

    nbe = nbe->next;
    while (nbe) {
        iterate_buffer_elements(ast, nbe, nbe->len, func, ctx);
        nbe = nbe->next;
    }
}

static void
mark_ast_value(rb_ast_t *ast, void *ctx, NODE * node)
{
    switch (nd_type(node)) {
      case NODE_ARGS:
        {
            struct rb_args_info *args = node->nd_ainfo;
            rb_gc_mark_movable(args->imemo);
            break;
        }
      case NODE_MATCH:
      case NODE_LIT:
      case NODE_STR:
      case NODE_XSTR:
      case NODE_DSTR:
      case NODE_DXSTR:
      case NODE_DREGX:
      case NODE_DSYM:
        rb_gc_mark_movable(node->nd_lit);
        break;
      case NODE_ARYPTN:
      case NODE_FNDPTN:
        rb_gc_mark_movable(node->nd_rval);
        break;
      default:
        rb_bug("unreachable node %s", ruby_node_name(ast, nd_type(node)));
    }
}

static void
update_ast_value(rb_ast_t *ast, void *ctx, NODE * node)
{
    switch (nd_type(node)) {
      case NODE_ARGS:
        {
            struct rb_args_info *args = node->nd_ainfo;
            args->imemo = rb_gc_location(args->imemo);
            break;
        }
      case NODE_MATCH:
      case NODE_LIT:
      case NODE_STR:
      case NODE_XSTR:
      case NODE_DSTR:
      case NODE_DXSTR:
      case NODE_DREGX:
      case NODE_DSYM:
        node->nd_lit = rb_gc_location(node->nd_lit);
        break;
      case NODE_ARYPTN:
      case NODE_FNDPTN:
        node->nd_rval = rb_gc_location(node->nd_rval);
        break;
      default:
        rb_bug("unreachable");
    }
}

void
rb_ast_update_references(rb_ast_t *ast)
{
    if (ast->node_buffer) {
        node_buffer_t *nb = ast->node_buffer;

        iterate_node_values(ast, &nb->markable, update_ast_value, NULL);
    }
}

void
rb_ast_mark(rb_ast_t *ast)
{
    if (ast->node_buffer) {
        rb_gc_mark(ast->node_buffer->mark_hash);
        rb_gc_mark(ast->node_buffer->tokens);
    }
    if (ast->body.compile_option) rb_gc_mark(ast->body.compile_option);
    if (ast->node_buffer) {
        node_buffer_t *nb = ast->node_buffer;

        iterate_node_values(ast, &nb->markable, mark_ast_value, NULL);
    }
    if (ast->body.script_lines) rb_gc_mark(ast->body.script_lines);
}

void
rb_ast_free(rb_ast_t *ast)
{
    if (ast->node_buffer) {
        rb_node_buffer_free(ast->node_buffer);
        ast->node_buffer = 0;
    }
}

static size_t
buffer_list_size(node_buffer_list_t *nb)
{
    size_t size = 0;
    node_buffer_elem_t *nbe = nb->head;
    while (nbe != nb->last) {
        nbe = nbe->next;
        size += offsetof(node_buffer_elem_t, buf) + nb->len * sizeof(NODE);
    }
    return size;
}

size_t
rb_ast_memsize(const rb_ast_t *ast)
{
    size_t size = 0;
    node_buffer_t *nb = ast->node_buffer;

    if (nb) {
        size += sizeof(node_buffer_t) + offsetof(node_buffer_elem_t, buf) + NODE_BUF_DEFAULT_LEN * sizeof(NODE);
        size += buffer_list_size(&nb->unmarkable);
        size += buffer_list_size(&nb->markable);
    }
    return size;
}

void
rb_ast_dispose(rb_ast_t *ast)
{
    // rb_ast_free(ast);
}

void
rb_ast_add_mark_object(rb_ast_t *ast, VALUE obj)
{
    if (NIL_P(ast->node_buffer->mark_hash)) {
        RB_OBJ_WRITE(ast, &ast->node_buffer->mark_hash, rb_ident_hash_new());
    }
    rb_hash_aset(ast->node_buffer->mark_hash, obj, Qtrue);
}

VALUE
rb_ast_tokens(rb_ast_t *ast)
{
    return ast->node_buffer->tokens;
}

void
rb_ast_set_tokens(rb_ast_t *ast, VALUE tokens)
{
    RB_OBJ_WRITE(ast, &ast->node_buffer->tokens, tokens);
}
