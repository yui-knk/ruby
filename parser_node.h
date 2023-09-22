#ifndef RUBY_PARSER_NODE_H
#define RUBY_PARSER_NODE_H 1
/*
 * This is a header file used by only "parse.y"
 */
#include "rubyparser.h"
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

#define NEW_NODE(t,s,a0,a1,a2,loc) rb_node_newnode((t),s,(VALUE)(a0),(VALUE)(a1),(VALUE)(a2),loc)
#define NEW_NODE_WITH_LOCALS(t,s,a1,a2,loc) node_newnode_with_locals(p,(t),sizeof(s),(VALUE)(a1),(VALUE)(a2),loc)


#define NEW_DEFN(i,a,d,loc) NEW_NODE(NODE_DEFN,rb_node_defn_t,0,i,NEW_SCOPE(a,d,loc),loc)
#define NEW_DEFS(r,i,a,d,loc) NEW_NODE(NODE_DEFS,rb_node_defs_t,r,i,NEW_SCOPE(a,d,loc),loc)
#define NEW_SCOPE(a,b,loc) NEW_NODE_WITH_LOCALS(NODE_SCOPE,rb_node_scope_t,b,a,loc)
#define NEW_BLOCK(a,loc) NEW_NODE(NODE_BLOCK,rb_node_block_t,a,0,0,loc)
#define NEW_IF(c,t,e,loc) NEW_NODE(NODE_IF,rb_node_if_t,c,t,e,loc)
#define NEW_UNLESS(c,t,e,loc) NEW_NODE(NODE_UNLESS,rb_node_unless_t,c,t,e,loc)
#define NEW_CASE(h,b,loc) NEW_NODE(NODE_CASE,rb_node_case_t,h,b,0,loc)
#define NEW_CASE2(b,loc) NEW_NODE(NODE_CASE2,rb_node_case2_t,0,b,0,loc)
#define NEW_CASE3(h,b,loc) NEW_NODE(NODE_CASE3,rb_node_case3_t,h,b,0,loc)
#define NEW_WHEN(c,t,e,loc) NEW_NODE(NODE_WHEN,rb_node_when_t,c,t,e,loc)
#define NEW_IN(c,t,e,loc) NEW_NODE(NODE_IN,rb_node_in_t,c,t,e,loc)
#define NEW_WHILE(c,b,n,loc) NEW_NODE(NODE_WHILE,rb_node_while_t,c,b,n,loc)
#define NEW_UNTIL(c,b,n,loc) NEW_NODE(NODE_UNTIL,rb_node_until_t,c,b,n,loc)
#define NEW_FOR(i,b,loc) NEW_NODE(NODE_FOR,rb_node_for_t,0,b,i,loc)
#define NEW_FOR_MASGN(v,loc) NEW_NODE(NODE_FOR_MASGN,rb_node_for_masgn_t,v,0,0,loc)
#define NEW_ITER(a,b,loc) NEW_NODE(NODE_ITER,rb_node_iter_t,0,NEW_SCOPE(a,b,loc),0,loc)
#define NEW_LAMBDA(a,b,loc) NEW_NODE(NODE_LAMBDA,rb_node_lambda_t,0,NEW_SCOPE(a,b,loc),0,loc)
#define NEW_BREAK(s,loc) NEW_NODE(NODE_BREAK,rb_node_break_t,s,0,0,loc)
#define NEW_NEXT(s,loc) NEW_NODE(NODE_NEXT,rb_node_next_t,s,0,0,loc)
#define NEW_REDO(loc) NEW_NODE(NODE_REDO,rb_node_redo_t,0,0,0,loc)
#define NEW_RETRY(loc) NEW_NODE(NODE_RETRY,rb_node_retry_t,0,0,0,loc)
#define NEW_BEGIN(b,loc) NEW_NODE(NODE_BEGIN,rb_node_begin_t,0,b,0,loc)
#define NEW_RESCUE(b,res,e,loc) NEW_NODE(NODE_RESCUE,rb_node_rescue_t,b,res,e,loc)
#define NEW_RESBODY(a,ex,n,loc) NEW_NODE(NODE_RESBODY,rb_node_resbody_t,n,ex,a,loc)
#define NEW_ENSURE(b,en,loc) NEW_NODE(NODE_ENSURE,rb_node_ensure_t,b,0,en,loc)
#define NEW_RETURN(s,loc) NEW_NODE(NODE_RETURN,rb_node_return_t,s,0,0,loc)
#define NEW_YIELD(a,loc) NEW_NODE(NODE_YIELD,rb_node_yield_t,a,0,0,loc)
#define NEW_LIST(a,loc) NEW_NODE(NODE_LIST,rb_node_list_t,a,1,0,loc)
#define NEW_ZLIST(loc) NEW_NODE(NODE_ZLIST,rb_node_zlist_t,0,0,0,loc)
#define NEW_HASH(a,loc)  NEW_NODE(NODE_HASH,rb_node_hash_t,a,0,0,loc)
#define NEW_MASGN(l,r,loc)   NEW_NODE(NODE_MASGN,rb_node_masgn_t,l,0,r,loc)
#define NEW_GASGN(v,val,loc) NEW_NODE(NODE_GASGN,rb_node_gasgn_t,v,val,0,loc)
#define NEW_LASGN(v,val,loc) NEW_NODE(NODE_LASGN,rb_node_lasgn_t,v,val,0,loc)
#define NEW_DASGN(v,val,loc) NEW_NODE(NODE_DASGN,rb_node_dasgn_t,v,val,0,loc)
#define NEW_IASGN(v,val,loc) NEW_NODE(NODE_IASGN,rb_node_iasgn_t,v,val,0,loc)
#define NEW_CDECL(v,val,path,loc) NEW_NODE(NODE_CDECL,rb_node_cdecl_t,v,val,path,loc)
#define NEW_CVASGN(v,val,loc) NEW_NODE(NODE_CVASGN,rb_node_cvasgn_t,v,val,0,loc)
#define NEW_OP_ASGN1(p,id,a,loc) NEW_NODE(NODE_OP_ASGN1,rb_node_op_asgn1_t,p,id,a,loc)
#define NEW_OP_ASGN2(r,t,i,o,val,loc) NEW_NODE(NODE_OP_ASGN2,rb_node_op_asgn2_t,r,val,NEW_OP_ASGN22(i,o,t,loc),loc)
#define NEW_OP_ASGN22(i,o,t,loc) NEW_NODE(NODE_OP_ASGN2,rb_node_op_asgn2_t,i,o,t,loc)
#define NEW_OP_ASGN_OR(i,val,loc) NEW_NODE(NODE_OP_ASGN_OR,rb_node_op_asgn_or_t,i,val,0,loc)
#define NEW_OP_ASGN_AND(i,val,loc) NEW_NODE(NODE_OP_ASGN_AND,rb_node_op_asgn_and_t,i,val,0,loc)
#define NEW_OP_CDECL(v,op,val,loc) NEW_NODE(NODE_OP_CDECL,rb_node_cdecl_t,v,val,op,loc)
#define NEW_GVAR(v,loc) NEW_NODE(NODE_GVAR,rb_node_gvar_t,v,0,0,loc)
#define NEW_LVAR(v,loc) NEW_NODE(NODE_LVAR,rb_node_lvar_t,v,0,0,loc)
#define NEW_DVAR(v,loc) NEW_NODE(NODE_DVAR,rb_node_dvar_t,v,0,0,loc)
#define NEW_IVAR(v,loc) NEW_NODE(NODE_IVAR,rb_node_ivar_t,v,0,0,loc)
#define NEW_CONST(v,loc) NEW_NODE(NODE_CONST,rb_node_const_t,v,0,0,loc)
#define NEW_CVAR(v,loc) NEW_NODE(NODE_CVAR,rb_node_cvar_t,v,0,0,loc)
#define NEW_NTH_REF(n,loc)  NEW_NODE(NODE_NTH_REF,rb_node_nth_ref_t,0,n,0,loc)
#define NEW_BACK_REF(n,loc) NEW_NODE(NODE_BACK_REF,rb_node_back_ref_t,0,n,0,loc)
#define NEW_MATCH(c,loc) NEW_NODE(NODE_MATCH,rb_node_match_t,c,0,0,loc)
#define NEW_MATCH2(n1,n2,loc) NEW_NODE(NODE_MATCH2,rb_node_match2_t,n1,n2,0,loc)
#define NEW_MATCH3(r,n2,loc) NEW_NODE(NODE_MATCH3,rb_node_match3_t,r,n2,0,loc)
#define NEW_LIT(l,loc) NEW_NODE(NODE_LIT,rb_node_lit_t,l,0,0,loc)
#define NEW_STR(s,loc) NEW_NODE(NODE_STR,rb_node_str_t,s,0,0,loc)
#define NEW_DSTR(s,loc) NEW_NODE(NODE_DSTR,rb_node_dstr_t,s,1,0,loc)
#define NEW_XSTR(s,loc) NEW_NODE(NODE_XSTR,rb_node_xstr_t,s,0,0,loc)
#define NEW_DXSTR(s,loc) NEW_NODE(NODE_DXSTR,rb_node_dxstr_t,s,0,0,loc)
#define NEW_DSYM(s,loc) NEW_NODE(NODE_DSYM,rb_node_dsym_t,s,0,0,loc)
#define NEW_EVSTR(n,loc) NEW_NODE(NODE_EVSTR,rb_node_evstr_t,0,(n),0,loc)
#define NEW_CALL(r,m,a,loc) NEW_NODE(NODE_CALL,rb_node_call_t,r,m,a,loc)
#define NEW_OPCALL(r,m,a,loc) NEW_NODE(NODE_OPCALL,rb_node_opcall_t,r,m,a,loc)
#define NEW_FCALL(m,a,loc) NEW_NODE(NODE_FCALL,rb_node_fcall_t,0,m,a,loc)
#define NEW_VCALL(m,loc) NEW_NODE(NODE_VCALL,rb_node_vcall_t,0,m,0,loc)
#define NEW_SUPER(a,loc) NEW_NODE(NODE_SUPER,rb_node_super_t,0,0,a,loc)
#define NEW_ZSUPER(loc) NEW_NODE(NODE_ZSUPER,rb_node_zsuper_t,0,0,0,loc)
#define NEW_ARGS_AUX(r,b,loc) NEW_NODE(NODE_ARGS_AUX,rb_node_args_aux_t,r,b,0,loc)
#define NEW_OPT_ARG(v,loc) NEW_NODE(NODE_OPT_ARG,rb_node_opt_arg_t,v,0,loc)
#define NEW_KW_ARG(v,loc) NEW_NODE(NODE_KW_ARG,rb_node_kw_arg_t,0,v,0,loc)
#define NEW_POSTARG(i,v,loc) NEW_NODE(NODE_POSTARG,rb_node_postarg_t,i,v,0,loc)
#define NEW_ARGSCAT(a,b,loc) NEW_NODE(NODE_ARGSCAT,rb_node_argscat_t,a,b,0,loc)
#define NEW_ARGSPUSH(a,b,loc) NEW_NODE(NODE_ARGSPUSH,rb_node_argspush_t,a,b,0,loc)
#define NEW_SPLAT(a,loc) NEW_NODE(NODE_SPLAT,rb_node_splat_t,a,0,0,loc)
#define NEW_BLOCK_PASS(b,loc) NEW_NODE(NODE_BLOCK_PASS,rb_node_block_pass_t,0,b,0,loc)
#define NEW_ALIAS(n,o,loc) NEW_NODE(NODE_ALIAS,rb_node_alias_t,n,o,0,loc)
#define NEW_VALIAS(n,o,loc) NEW_NODE(NODE_VALIAS,rb_node_valias_t,n,o,0,loc)
#define NEW_UNDEF(i,loc) NEW_NODE(NODE_UNDEF,rb_node_undef_t,0,i,0,loc)
#define NEW_CLASS(n,b,s,loc) NEW_NODE(NODE_CLASS,rb_node_class_t,n,NEW_SCOPE(0,b,loc),(s),loc)
#define NEW_SCLASS(r,b,loc) NEW_NODE(NODE_SCLASS,rb_node_sclass_t,r,NEW_SCOPE(0,b,loc),0,loc)
#define NEW_MODULE(n,b,loc) NEW_NODE(NODE_MODULE,rb_node_module_t,n,NEW_SCOPE(0,b,loc),0,loc)
#define NEW_COLON2(c,i,loc) NEW_NODE(NODE_COLON2,rb_node_colon2_t,c,i,0,loc)
#define NEW_COLON3(i,loc) NEW_NODE(NODE_COLON3,rb_node_colon3_t,0,i,0,loc)
#define NEW_DOT2(b,e,loc) NEW_NODE(NODE_DOT2,rb_node_dot2_t,b,e,0,loc)
#define NEW_DOT3(b,e,loc) NEW_NODE(NODE_DOT3,rb_node_dot3_t,b,e,0,loc)
#define NEW_SELF(loc) NEW_NODE(NODE_SELF,rb_node_self_t,0,0,1,loc)
#define NEW_NIL(loc) NEW_NODE(NODE_NIL,rb_node_nil_t,0,0,0,loc)
#define NEW_TRUE(loc) NEW_NODE(NODE_TRUE,rb_node_true_t,0,0,0,loc)
#define NEW_FALSE(loc) NEW_NODE(NODE_FALSE,rb_node_false_t,0,0,0,loc)
#define NEW_ERRINFO(loc) NEW_NODE(NODE_ERRINFO,rb_node_errinfo_t,0,0,0,loc)
#define NEW_DEFINED(e,loc) NEW_NODE(NODE_DEFINED,rb_node_defined_t,e,0,0,loc)
#define NEW_POSTEXE(b,loc) NEW_NODE(NODE_POSTEXE,rb_node_postexe_t,0,b,0,loc)
#define NEW_ATTRASGN(r,m,a,loc) NEW_NODE(NODE_ATTRASGN,rb_node_attrasgn_t,r,m,a,loc)
#define NEW_ERROR(loc) NEW_NODE(NODE_ERROR,rb_node_error_t,0,0,0,loc)


#if defined(__cplusplus)
#if 0
{ /* satisfy cc-mode */
#endif
}  /* extern "C" { */
#endif

#endif /* RUBY_PARSER_NODE_H */
