#ifndef RUBY_NODE_H
#define RUBY_NODE_H 1
/**********************************************************************

  node.h -

  $Author$
  created at: Fri May 28 15:14:02 JST 1993

  Copyright (C) 1993-2007 Yukihiro Matsumoto

**********************************************************************/

#include "external/node.h"
#include "internal/compilers.h"

#if defined(__cplusplus)
extern "C" {
#if 0
} /* satisfy cc-mode */
#endif
#endif

static inline rb_code_location_t
code_loc_gen(const rb_code_location_t *loc1, const rb_code_location_t *loc2)
{
    rb_code_location_t loc;
    loc.beg_pos = loc1->beg_pos;
    loc.end_pos = loc2->end_pos;
    return loc;
}

#define RNODE(obj)  ((struct RNode *)(obj))


#define NODE_LSHIFT (NODE_TYPESHIFT+7)
#define NODE_LMASK  (((SIGNED_VALUE)1<<(sizeof(VALUE)*CHAR_BIT-NODE_LSHIFT))-1)
#define nd_line(n) (int)(((SIGNED_VALUE)(n)->flags)>>NODE_LSHIFT)
#define nd_set_line(n,l) \
    (n)->flags=(((n)->flags&~((VALUE)(-1)<<NODE_LSHIFT))|((VALUE)((l)&NODE_LMASK)<<NODE_LSHIFT))

#define nd_first_column(n) ((int)((n)->nd_loc.beg_pos.column))
#define nd_set_first_column(n, v) ((n)->nd_loc.beg_pos.column = (v))
#define nd_first_lineno(n) ((int)((n)->nd_loc.beg_pos.lineno))
#define nd_set_first_lineno(n, v) ((n)->nd_loc.beg_pos.lineno = (v))
#define nd_first_loc(n) ((n)->nd_loc.beg_pos)
#define nd_set_first_loc(n, v) (nd_first_loc(n) = (v))

#define nd_last_column(n) ((int)((n)->nd_loc.end_pos.column))
#define nd_set_last_column(n, v) ((n)->nd_loc.end_pos.column = (v))
#define nd_last_lineno(n) ((int)((n)->nd_loc.end_pos.lineno))
#define nd_set_last_lineno(n, v) ((n)->nd_loc.end_pos.lineno = (v))
#define nd_last_loc(n) ((n)->nd_loc.end_pos)
#define nd_set_last_loc(n, v) (nd_last_loc(n) = (v))
#define nd_node_id(n) ((n)->node_id)
#define nd_set_node_id(n,id) ((n)->node_id = (id))

#define NEW_NODE(t,a0,a1,a2,loc) rb_node_newnode((t),(VALUE)(a0),(VALUE)(a1),(VALUE)(a2),loc)
#define NEW_NODE_WITH_LOCALS(t,a1,a2,loc) node_newnode_with_locals(p, (t),(VALUE)(a1),(VALUE)(a2),loc)

#define NEW_DEFN(i,a,d,loc) NEW_NODE(NODE_DEFN,0,i,NEW_SCOPE(a,d,loc),loc)
#define NEW_DEFS(r,i,a,d,loc) NEW_NODE(NODE_DEFS,r,i,NEW_SCOPE(a,d,loc),loc)
#define NEW_SCOPE(a,b,loc) NEW_NODE_WITH_LOCALS(NODE_SCOPE,b,a,loc)
#define NEW_BLOCK(a,loc) NEW_NODE(NODE_BLOCK,a,0,0,loc)
#define NEW_IF(c,t,e,loc) NEW_NODE(NODE_IF,c,t,e,loc)
#define NEW_UNLESS(c,t,e,loc) NEW_NODE(NODE_UNLESS,c,t,e,loc)
#define NEW_CASE(h,b,loc) NEW_NODE(NODE_CASE,h,b,0,loc)
#define NEW_CASE2(b,loc) NEW_NODE(NODE_CASE2,0,b,0,loc)
#define NEW_CASE3(h,b,loc) NEW_NODE(NODE_CASE3,h,b,0,loc)
#define NEW_WHEN(c,t,e,loc) NEW_NODE(NODE_WHEN,c,t,e,loc)
#define NEW_IN(c,t,e,loc) NEW_NODE(NODE_IN,c,t,e,loc)
#define NEW_WHILE(c,b,n,loc) NEW_NODE(NODE_WHILE,c,b,n,loc)
#define NEW_UNTIL(c,b,n,loc) NEW_NODE(NODE_UNTIL,c,b,n,loc)
#define NEW_FOR(i,b,loc) NEW_NODE(NODE_FOR,0,b,i,loc)
#define NEW_FOR_MASGN(v,loc) NEW_NODE(NODE_FOR_MASGN,v,0,0,loc)
#define NEW_ITER(a,b,loc) NEW_NODE(NODE_ITER,0,NEW_SCOPE(a,b,loc),0,loc)
#define NEW_LAMBDA(a,b,loc) NEW_NODE(NODE_LAMBDA,0,NEW_SCOPE(a,b,loc),0,loc)
#define NEW_BREAK(s,loc) NEW_NODE(NODE_BREAK,s,0,0,loc)
#define NEW_NEXT(s,loc) NEW_NODE(NODE_NEXT,s,0,0,loc)
#define NEW_REDO(loc) NEW_NODE(NODE_REDO,0,0,0,loc)
#define NEW_RETRY(loc) NEW_NODE(NODE_RETRY,0,0,0,loc)
#define NEW_BEGIN(b,loc) NEW_NODE(NODE_BEGIN,0,b,0,loc)
#define NEW_RESCUE(b,res,e,loc) NEW_NODE(NODE_RESCUE,b,res,e,loc)
#define NEW_RESBODY(a,ex,n,loc) NEW_NODE(NODE_RESBODY,n,ex,a,loc)
#define NEW_ENSURE(b,en,loc) NEW_NODE(NODE_ENSURE,b,0,en,loc)
#define NEW_RETURN(s,loc) NEW_NODE(NODE_RETURN,s,0,0,loc)
#define NEW_YIELD(a,loc) NEW_NODE(NODE_YIELD,a,0,0,loc)
#define NEW_LIST(a,loc) NEW_NODE(NODE_LIST,a,1,0,loc)
#define NEW_ZLIST(loc) NEW_NODE(NODE_ZLIST,0,0,0,loc)
#define NEW_HASH(a,loc)  NEW_NODE(NODE_HASH,a,0,0,loc)
#define NEW_MASGN(l,r,loc)   NEW_NODE(NODE_MASGN,l,0,r,loc)
#define NEW_GASGN(v,val,loc) NEW_NODE(NODE_GASGN,v,val,v,loc)
#define NEW_LASGN(v,val,loc) NEW_NODE(NODE_LASGN,v,val,0,loc)
#define NEW_DASGN(v,val,loc) NEW_NODE(NODE_DASGN,v,val,0,loc)
#define NEW_IASGN(v,val,loc) NEW_NODE(NODE_IASGN,v,val,0,loc)
#define NEW_CDECL(v,val,path,loc) NEW_NODE(NODE_CDECL,v,val,path,loc)
#define NEW_CVASGN(v,val,loc) NEW_NODE(NODE_CVASGN,v,val,0,loc)
#define NEW_OP_ASGN1(p,id,a,loc) NEW_NODE(NODE_OP_ASGN1,p,id,a,loc)
#define NEW_OP_ASGN2(r,t,i,o,val,loc) NEW_NODE(NODE_OP_ASGN2,r,val,NEW_OP_ASGN22(i,o,t,loc),loc)
#define NEW_OP_ASGN22(i,o,t,loc) NEW_NODE(NODE_OP_ASGN2,i,o,t,loc)
#define NEW_OP_ASGN_OR(i,val,loc) NEW_NODE(NODE_OP_ASGN_OR,i,val,0,loc)
#define NEW_OP_ASGN_AND(i,val,loc) NEW_NODE(NODE_OP_ASGN_AND,i,val,0,loc)
#define NEW_OP_CDECL(v,op,val,loc) NEW_NODE(NODE_OP_CDECL,v,val,op,loc)
#define NEW_GVAR(v,loc) NEW_NODE(NODE_GVAR,v,0,v,loc)
#define NEW_LVAR(v,loc) NEW_NODE(NODE_LVAR,v,0,0,loc)
#define NEW_DVAR(v,loc) NEW_NODE(NODE_DVAR,v,0,0,loc)
#define NEW_IVAR(v,loc) NEW_NODE(NODE_IVAR,v,0,0,loc)
#define NEW_CONST(v,loc) NEW_NODE(NODE_CONST,v,0,0,loc)
#define NEW_CVAR(v,loc) NEW_NODE(NODE_CVAR,v,0,0,loc)
#define NEW_NTH_REF(n,loc)  NEW_NODE(NODE_NTH_REF,0,n,0,loc)
#define NEW_BACK_REF(n,loc) NEW_NODE(NODE_BACK_REF,0,n,0,loc)
#define NEW_MATCH(c,loc) NEW_NODE(NODE_MATCH,c,0,0,loc)
#define NEW_MATCH2(n1,n2,loc) NEW_NODE(NODE_MATCH2,n1,n2,0,loc)
#define NEW_MATCH3(r,n2,loc) NEW_NODE(NODE_MATCH3,r,n2,0,loc)
#define NEW_LIT(l,loc) NEW_NODE(NODE_LIT,l,0,0,loc)
#define NEW_STR(s,loc) NEW_NODE(NODE_STR,s,0,0,loc)
#define NEW_DSTR(s,loc) NEW_NODE(NODE_DSTR,s,1,0,loc)
#define NEW_XSTR(s,loc) NEW_NODE(NODE_XSTR,s,0,0,loc)
#define NEW_DXSTR(s,loc) NEW_NODE(NODE_DXSTR,s,0,0,loc)
#define NEW_DSYM(s,loc) NEW_NODE(NODE_DSYM,s,0,0,loc)
#define NEW_EVSTR(n,loc) NEW_NODE(NODE_EVSTR,0,(n),0,loc)
#define NEW_CALL(r,m,a,loc) NEW_NODE(NODE_CALL,r,m,a,loc)
#define NEW_OPCALL(r,m,a,loc) NEW_NODE(NODE_OPCALL,r,m,a,loc)
#define NEW_FCALL(m,a,loc) NEW_NODE(NODE_FCALL,0,m,a,loc)
#define NEW_VCALL(m,loc) NEW_NODE(NODE_VCALL,0,m,0,loc)
#define NEW_SUPER(a,loc) NEW_NODE(NODE_SUPER,0,0,a,loc)
#define NEW_ZSUPER(loc) NEW_NODE(NODE_ZSUPER,0,0,0,loc)
#define NEW_ARGS_AUX(r,b,loc) NEW_NODE(NODE_ARGS_AUX,r,b,0,loc)
#define NEW_OPT_ARG(i,v,loc) NEW_NODE(NODE_OPT_ARG,i,v,0,loc)
#define NEW_KW_ARG(i,v,loc) NEW_NODE(NODE_KW_ARG,i,v,0,loc)
#define NEW_POSTARG(i,v,loc) NEW_NODE(NODE_POSTARG,i,v,0,loc)
#define NEW_ARGSCAT(a,b,loc) NEW_NODE(NODE_ARGSCAT,a,b,0,loc)
#define NEW_ARGSPUSH(a,b,loc) NEW_NODE(NODE_ARGSPUSH,a,b,0,loc)
#define NEW_SPLAT(a,loc) NEW_NODE(NODE_SPLAT,a,0,0,loc)
#define NEW_BLOCK_PASS(b,loc) NEW_NODE(NODE_BLOCK_PASS,0,b,0,loc)
#define NEW_ALIAS(n,o,loc) NEW_NODE(NODE_ALIAS,n,o,0,loc)
#define NEW_VALIAS(n,o,loc) NEW_NODE(NODE_VALIAS,n,o,0,loc)
#define NEW_UNDEF(i,loc) NEW_NODE(NODE_UNDEF,0,i,0,loc)
#define NEW_CLASS(n,b,s,loc) NEW_NODE(NODE_CLASS,n,NEW_SCOPE(0,b,loc),(s),loc)
#define NEW_SCLASS(r,b,loc) NEW_NODE(NODE_SCLASS,r,NEW_SCOPE(0,b,loc),0,loc)
#define NEW_MODULE(n,b,loc) NEW_NODE(NODE_MODULE,n,NEW_SCOPE(0,b,loc),0,loc)
#define NEW_COLON2(c,i,loc) NEW_NODE(NODE_COLON2,c,i,0,loc)
#define NEW_COLON3(i,loc) NEW_NODE(NODE_COLON3,0,i,0,loc)
#define NEW_DOT2(b,e,loc) NEW_NODE(NODE_DOT2,b,e,0,loc)
#define NEW_DOT3(b,e,loc) NEW_NODE(NODE_DOT3,b,e,0,loc)
#define NEW_SELF(loc) NEW_NODE(NODE_SELF,0,0,1,loc)
#define NEW_NIL(loc) NEW_NODE(NODE_NIL,0,0,0,loc)
#define NEW_TRUE(loc) NEW_NODE(NODE_TRUE,0,0,0,loc)
#define NEW_FALSE(loc) NEW_NODE(NODE_FALSE,0,0,0,loc)
#define NEW_ERRINFO(loc) NEW_NODE(NODE_ERRINFO,0,0,0,loc)
#define NEW_DEFINED(e,loc) NEW_NODE(NODE_DEFINED,e,0,0,loc)
#define NEW_POSTEXE(b,loc) NEW_NODE(NODE_POSTEXE,0,b,0,loc)
#define NEW_ATTRASGN(r,m,a,loc) NEW_NODE(NODE_ATTRASGN,r,m,a,loc)
#define NEW_ERROR(loc) NEW_NODE(NODE_ERROR,0,0,0,loc)

#define NODE_SPECIAL_REQUIRED_KEYWORD ((NODE *)-1)
#define NODE_REQUIRED_KEYWORD_P(node) ((node)->nd_value == NODE_SPECIAL_REQUIRED_KEYWORD)
#define NODE_SPECIAL_NO_NAME_REST     ((NODE *)-1)
#define NODE_NAMED_REST_P(node) ((node) != NODE_SPECIAL_NO_NAME_REST)
#define NODE_SPECIAL_EXCESSIVE_COMMA   ((ID)1)
#define NODE_SPECIAL_NO_REST_KEYWORD   ((NODE *)-1)

VALUE rb_node_case_when_optimizable_literal(const NODE *const node);

RUBY_SYMBOL_EXPORT_BEGIN

void rb_ast_mark(rb_ast_t*);
void rb_ast_update_references(rb_ast_t*);
void rb_ast_dispose(rb_ast_t*);
void rb_ast_free(rb_ast_t*);
size_t rb_ast_memsize(const rb_ast_t*);
void rb_ast_add_mark_object(rb_ast_t*, VALUE);
void rb_ast_set_tokens(rb_ast_t*, VALUE);
VALUE rb_ast_tokens(rb_ast_t *ast);
NODE *rb_ast_newnode(rb_ast_t*, enum node_type type);
void rb_ast_delete_node(rb_ast_t*, NODE *n);
rb_ast_id_table_t *rb_ast_new_local_table(rb_ast_t*, int);
rb_ast_id_table_t *rb_ast_resize_latest_local_table(rb_ast_t*, int);

VALUE rb_parser_dump_tree(const NODE *node, int comment);

void rb_node_init(NODE *n, enum node_type type, VALUE a0, VALUE a1, VALUE a2);
const char *ruby_node_name(int node);

const struct kwtable *rb_reserved_word(const char *, unsigned int);

struct parser_params;
void *rb_parser_malloc(struct parser_params *, size_t);
void *rb_parser_realloc(struct parser_params *, void *, size_t);
void *rb_parser_calloc(struct parser_params *, size_t, size_t);
void rb_parser_free(struct parser_params *, void *);
PRINTF_ARGS(void rb_parser_printf(struct parser_params *parser, const char *fmt, ...), 2, 3);

RUBY_SYMBOL_EXPORT_END

static inline bool
nd_type_p(const NODE *n, enum node_type t)
{
    return (enum node_type)nd_type(n) == t;
}
#if defined(__cplusplus)
#if 0
{ /* satisfy cc-mode */
#endif
}  /* extern "C" { */
#endif

#endif /* RUBY_NODE_H */
