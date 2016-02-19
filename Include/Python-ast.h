/* File automatically generated by Parser/asdl_c.py. */

#include "asdl.h"

typedef struct _mod *mod_ty;

typedef struct _stmt *stmt_ty;

typedef struct _expr *expr_ty;

typedef enum _expr_context { Load=1, Store=2, Del=3, AugLoad=4, AugStore=5,
                             Param=6 } expr_context_ty;

typedef struct _slice *slice_ty;

typedef enum _boolop { And=1, Or=2 } boolop_ty;

typedef enum _operator { Add=1, Sub=2, Mult=3, MatMult=4, Div=5, Mod=6, Pow=7,
                         LShift=8, RShift=9, BitOr=10, BitXor=11, BitAnd=12,
                         FloorDiv=13 } operator_ty;

typedef enum _unaryop { Invert=1, Not=2, UAdd=3, USub=4 } unaryop_ty;

typedef enum _cmpop { Eq=1, NotEq=2, Lt=3, LtE=4, Gt=5, GtE=6, Is=7, IsNot=8,
                      In=9, NotIn=10 } cmpop_ty;

typedef struct _comprehension *comprehension_ty;

typedef struct _excepthandler *excepthandler_ty;

typedef struct _arguments *arguments_ty;

typedef struct _arg *arg_ty;

typedef struct _keyword *keyword_ty;

typedef struct _alias *alias_ty;

typedef struct _withitem *withitem_ty;

typedef struct _type_ignore *type_ignore_ty;


enum _mod_kind {Module_kind=1, Interactive_kind=2, Expression_kind=3,
                 FunctionType_kind=4, Suite_kind=5};
struct _mod {
    enum _mod_kind kind;
    union {
        struct {
            asdl_seq *body;
            asdl_seq *type_ignores;
        } Module;
        
        struct {
            asdl_seq *body;
        } Interactive;
        
        struct {
            expr_ty body;
        } Expression;
        
        struct {
            asdl_seq *argtypes;
            expr_ty returns;
        } FunctionType;
        
        struct {
            asdl_seq *body;
        } Suite;
        
    } v;
};

enum _stmt_kind {FunctionDef_kind=1, AsyncFunctionDef_kind=2, ClassDef_kind=3,
                  Return_kind=4, Delete_kind=5, Assign_kind=6,
                  AugAssign_kind=7, For_kind=8, AsyncFor_kind=9, While_kind=10,
                  If_kind=11, With_kind=12, AsyncWith_kind=13, Raise_kind=14,
                  Try_kind=15, Assert_kind=16, Import_kind=17,
                  ImportFrom_kind=18, Global_kind=19, Nonlocal_kind=20,
                  Expr_kind=21, Pass_kind=22, Break_kind=23, Continue_kind=24};
struct _stmt {
    enum _stmt_kind kind;
    union {
        struct {
            identifier name;
            arguments_ty args;
            asdl_seq *body;
            asdl_seq *decorator_list;
            expr_ty returns;
            string type_comment;
        } FunctionDef;
        
        struct {
            identifier name;
            arguments_ty args;
            asdl_seq *body;
            asdl_seq *decorator_list;
            expr_ty returns;
            string type_comment;
        } AsyncFunctionDef;
        
        struct {
            identifier name;
            asdl_seq *bases;
            asdl_seq *keywords;
            asdl_seq *body;
            asdl_seq *decorator_list;
        } ClassDef;
        
        struct {
            expr_ty value;
        } Return;
        
        struct {
            asdl_seq *targets;
        } Delete;
        
        struct {
            asdl_seq *targets;
            expr_ty value;
            string type_comment;
        } Assign;
        
        struct {
            expr_ty target;
            operator_ty op;
            expr_ty value;
        } AugAssign;
        
        struct {
            expr_ty target;
            expr_ty iter;
            asdl_seq *body;
            asdl_seq *orelse;
            string type_comment;
        } For;
        
        struct {
            expr_ty target;
            expr_ty iter;
            asdl_seq *body;
            asdl_seq *orelse;
        } AsyncFor;
        
        struct {
            expr_ty test;
            asdl_seq *body;
            asdl_seq *orelse;
        } While;
        
        struct {
            expr_ty test;
            asdl_seq *body;
            asdl_seq *orelse;
        } If;
        
        struct {
            asdl_seq *items;
            asdl_seq *body;
            string type_comment;
        } With;
        
        struct {
            asdl_seq *items;
            asdl_seq *body;
        } AsyncWith;
        
        struct {
            expr_ty exc;
            expr_ty cause;
        } Raise;
        
        struct {
            asdl_seq *body;
            asdl_seq *handlers;
            asdl_seq *orelse;
            asdl_seq *finalbody;
        } Try;
        
        struct {
            expr_ty test;
            expr_ty msg;
        } Assert;
        
        struct {
            asdl_seq *names;
        } Import;
        
        struct {
            identifier module;
            asdl_seq *names;
            int level;
        } ImportFrom;
        
        struct {
            asdl_seq *names;
        } Global;
        
        struct {
            asdl_seq *names;
        } Nonlocal;
        
        struct {
            expr_ty value;
        } Expr;
        
    } v;
    int lineno;
    int col_offset;
};

enum _expr_kind {BoolOp_kind=1, BinOp_kind=2, UnaryOp_kind=3, Lambda_kind=4,
                  IfExp_kind=5, Dict_kind=6, Set_kind=7, ListComp_kind=8,
                  SetComp_kind=9, DictComp_kind=10, GeneratorExp_kind=11,
                  Await_kind=12, Yield_kind=13, YieldFrom_kind=14,
                  Compare_kind=15, Call_kind=16, Num_kind=17, Str_kind=18,
                  Bytes_kind=19, NameConstant_kind=20, Ellipsis_kind=21,
                  Attribute_kind=22, Subscript_kind=23, Starred_kind=24,
                  Name_kind=25, List_kind=26, Tuple_kind=27};
struct _expr {
    enum _expr_kind kind;
    union {
        struct {
            boolop_ty op;
            asdl_seq *values;
        } BoolOp;
        
        struct {
            expr_ty left;
            operator_ty op;
            expr_ty right;
        } BinOp;
        
        struct {
            unaryop_ty op;
            expr_ty operand;
        } UnaryOp;
        
        struct {
            arguments_ty args;
            expr_ty body;
        } Lambda;
        
        struct {
            expr_ty test;
            expr_ty body;
            expr_ty orelse;
        } IfExp;
        
        struct {
            asdl_seq *keys;
            asdl_seq *values;
        } Dict;
        
        struct {
            asdl_seq *elts;
        } Set;
        
        struct {
            expr_ty elt;
            asdl_seq *generators;
        } ListComp;
        
        struct {
            expr_ty elt;
            asdl_seq *generators;
        } SetComp;
        
        struct {
            expr_ty key;
            expr_ty value;
            asdl_seq *generators;
        } DictComp;
        
        struct {
            expr_ty elt;
            asdl_seq *generators;
        } GeneratorExp;
        
        struct {
            expr_ty value;
        } Await;
        
        struct {
            expr_ty value;
        } Yield;
        
        struct {
            expr_ty value;
        } YieldFrom;
        
        struct {
            expr_ty left;
            asdl_int_seq *ops;
            asdl_seq *comparators;
        } Compare;
        
        struct {
            expr_ty func;
            asdl_seq *args;
            asdl_seq *keywords;
        } Call;
        
        struct {
            object n;
        } Num;
        
        struct {
            string s;
        } Str;
        
        struct {
            bytes s;
        } Bytes;
        
        struct {
            singleton value;
        } NameConstant;
        
        struct {
            expr_ty value;
            identifier attr;
            expr_context_ty ctx;
        } Attribute;
        
        struct {
            expr_ty value;
            slice_ty slice;
            expr_context_ty ctx;
        } Subscript;
        
        struct {
            expr_ty value;
            expr_context_ty ctx;
        } Starred;
        
        struct {
            identifier id;
            expr_context_ty ctx;
        } Name;
        
        struct {
            asdl_seq *elts;
            expr_context_ty ctx;
        } List;
        
        struct {
            asdl_seq *elts;
            expr_context_ty ctx;
        } Tuple;
        
    } v;
    int lineno;
    int col_offset;
};

enum _slice_kind {Slice_kind=1, ExtSlice_kind=2, Index_kind=3};
struct _slice {
    enum _slice_kind kind;
    union {
        struct {
            expr_ty lower;
            expr_ty upper;
            expr_ty step;
        } Slice;
        
        struct {
            asdl_seq *dims;
        } ExtSlice;
        
        struct {
            expr_ty value;
        } Index;
        
    } v;
};

struct _comprehension {
    expr_ty target;
    expr_ty iter;
    asdl_seq *ifs;
};

enum _excepthandler_kind {ExceptHandler_kind=1};
struct _excepthandler {
    enum _excepthandler_kind kind;
    union {
        struct {
            expr_ty type;
            identifier name;
            asdl_seq *body;
        } ExceptHandler;
        
    } v;
    int lineno;
    int col_offset;
};

struct _arguments {
    asdl_seq *args;
    arg_ty vararg;
    asdl_seq *kwonlyargs;
    asdl_seq *kw_defaults;
    arg_ty kwarg;
    asdl_seq *defaults;
};

struct _arg {
    identifier arg;
    expr_ty annotation;
    int lineno;
    int col_offset;
};

struct _keyword {
    identifier arg;
    expr_ty value;
};

struct _alias {
    identifier name;
    identifier asname;
};

struct _withitem {
    expr_ty context_expr;
    expr_ty optional_vars;
};

enum _type_ignore_kind {TypeIgnore_kind=1};
struct _type_ignore {
    enum _type_ignore_kind kind;
    union {
        struct {
            int lineno;
        } TypeIgnore;
        
    } v;
};


#define Module(a0, a1, a2) _Ta_Module(a0, a1, a2)
mod_ty _Ta_Module(asdl_seq * body, asdl_seq * type_ignores, PyArena *arena);
#define Interactive(a0, a1) _Ta_Interactive(a0, a1)
mod_ty _Ta_Interactive(asdl_seq * body, PyArena *arena);
#define Expression(a0, a1) _Ta_Expression(a0, a1)
mod_ty _Ta_Expression(expr_ty body, PyArena *arena);
#define FunctionType(a0, a1, a2) _Ta_FunctionType(a0, a1, a2)
mod_ty _Ta_FunctionType(asdl_seq * argtypes, expr_ty returns, PyArena *arena);
#define Suite(a0, a1) _Ta_Suite(a0, a1)
mod_ty _Ta_Suite(asdl_seq * body, PyArena *arena);
#define FunctionDef(a0, a1, a2, a3, a4, a5, a6, a7, a8) _Ta_FunctionDef(a0, a1, a2, a3, a4, a5, a6, a7, a8)
stmt_ty _Ta_FunctionDef(identifier name, arguments_ty args, asdl_seq * body,
                        asdl_seq * decorator_list, expr_ty returns, string
                        type_comment, int lineno, int col_offset, PyArena
                        *arena);
#define AsyncFunctionDef(a0, a1, a2, a3, a4, a5, a6, a7, a8) _Ta_AsyncFunctionDef(a0, a1, a2, a3, a4, a5, a6, a7, a8)
stmt_ty _Ta_AsyncFunctionDef(identifier name, arguments_ty args, asdl_seq *
                             body, asdl_seq * decorator_list, expr_ty returns,
                             string type_comment, int lineno, int col_offset,
                             PyArena *arena);
#define ClassDef(a0, a1, a2, a3, a4, a5, a6, a7) _Ta_ClassDef(a0, a1, a2, a3, a4, a5, a6, a7)
stmt_ty _Ta_ClassDef(identifier name, asdl_seq * bases, asdl_seq * keywords,
                     asdl_seq * body, asdl_seq * decorator_list, int lineno,
                     int col_offset, PyArena *arena);
#define Return(a0, a1, a2, a3) _Ta_Return(a0, a1, a2, a3)
stmt_ty _Ta_Return(expr_ty value, int lineno, int col_offset, PyArena *arena);
#define Delete(a0, a1, a2, a3) _Ta_Delete(a0, a1, a2, a3)
stmt_ty _Ta_Delete(asdl_seq * targets, int lineno, int col_offset, PyArena
                   *arena);
#define Assign(a0, a1, a2, a3, a4, a5) _Ta_Assign(a0, a1, a2, a3, a4, a5)
stmt_ty _Ta_Assign(asdl_seq * targets, expr_ty value, string type_comment, int
                   lineno, int col_offset, PyArena *arena);
#define AugAssign(a0, a1, a2, a3, a4, a5) _Ta_AugAssign(a0, a1, a2, a3, a4, a5)
stmt_ty _Ta_AugAssign(expr_ty target, operator_ty op, expr_ty value, int
                      lineno, int col_offset, PyArena *arena);
#define For(a0, a1, a2, a3, a4, a5, a6, a7) _Ta_For(a0, a1, a2, a3, a4, a5, a6, a7)
stmt_ty _Ta_For(expr_ty target, expr_ty iter, asdl_seq * body, asdl_seq *
                orelse, string type_comment, int lineno, int col_offset,
                PyArena *arena);
#define AsyncFor(a0, a1, a2, a3, a4, a5, a6) _Ta_AsyncFor(a0, a1, a2, a3, a4, a5, a6)
stmt_ty _Ta_AsyncFor(expr_ty target, expr_ty iter, asdl_seq * body, asdl_seq *
                     orelse, int lineno, int col_offset, PyArena *arena);
#define While(a0, a1, a2, a3, a4, a5) _Ta_While(a0, a1, a2, a3, a4, a5)
stmt_ty _Ta_While(expr_ty test, asdl_seq * body, asdl_seq * orelse, int lineno,
                  int col_offset, PyArena *arena);
#define If(a0, a1, a2, a3, a4, a5) _Ta_If(a0, a1, a2, a3, a4, a5)
stmt_ty _Ta_If(expr_ty test, asdl_seq * body, asdl_seq * orelse, int lineno,
               int col_offset, PyArena *arena);
#define With(a0, a1, a2, a3, a4, a5) _Ta_With(a0, a1, a2, a3, a4, a5)
stmt_ty _Ta_With(asdl_seq * items, asdl_seq * body, string type_comment, int
                 lineno, int col_offset, PyArena *arena);
#define AsyncWith(a0, a1, a2, a3, a4) _Ta_AsyncWith(a0, a1, a2, a3, a4)
stmt_ty _Ta_AsyncWith(asdl_seq * items, asdl_seq * body, int lineno, int
                      col_offset, PyArena *arena);
#define Raise(a0, a1, a2, a3, a4) _Ta_Raise(a0, a1, a2, a3, a4)
stmt_ty _Ta_Raise(expr_ty exc, expr_ty cause, int lineno, int col_offset,
                  PyArena *arena);
#define Try(a0, a1, a2, a3, a4, a5, a6) _Ta_Try(a0, a1, a2, a3, a4, a5, a6)
stmt_ty _Ta_Try(asdl_seq * body, asdl_seq * handlers, asdl_seq * orelse,
                asdl_seq * finalbody, int lineno, int col_offset, PyArena
                *arena);
#define Assert(a0, a1, a2, a3, a4) _Ta_Assert(a0, a1, a2, a3, a4)
stmt_ty _Ta_Assert(expr_ty test, expr_ty msg, int lineno, int col_offset,
                   PyArena *arena);
#define Import(a0, a1, a2, a3) _Ta_Import(a0, a1, a2, a3)
stmt_ty _Ta_Import(asdl_seq * names, int lineno, int col_offset, PyArena
                   *arena);
#define ImportFrom(a0, a1, a2, a3, a4, a5) _Ta_ImportFrom(a0, a1, a2, a3, a4, a5)
stmt_ty _Ta_ImportFrom(identifier module, asdl_seq * names, int level, int
                       lineno, int col_offset, PyArena *arena);
#define Global(a0, a1, a2, a3) _Ta_Global(a0, a1, a2, a3)
stmt_ty _Ta_Global(asdl_seq * names, int lineno, int col_offset, PyArena
                   *arena);
#define Nonlocal(a0, a1, a2, a3) _Ta_Nonlocal(a0, a1, a2, a3)
stmt_ty _Ta_Nonlocal(asdl_seq * names, int lineno, int col_offset, PyArena
                     *arena);
#define Expr(a0, a1, a2, a3) _Ta_Expr(a0, a1, a2, a3)
stmt_ty _Ta_Expr(expr_ty value, int lineno, int col_offset, PyArena *arena);
#define Pass(a0, a1, a2) _Ta_Pass(a0, a1, a2)
stmt_ty _Ta_Pass(int lineno, int col_offset, PyArena *arena);
#define Break(a0, a1, a2) _Ta_Break(a0, a1, a2)
stmt_ty _Ta_Break(int lineno, int col_offset, PyArena *arena);
#define Continue(a0, a1, a2) _Ta_Continue(a0, a1, a2)
stmt_ty _Ta_Continue(int lineno, int col_offset, PyArena *arena);
#define BoolOp(a0, a1, a2, a3, a4) _Ta_BoolOp(a0, a1, a2, a3, a4)
expr_ty _Ta_BoolOp(boolop_ty op, asdl_seq * values, int lineno, int col_offset,
                   PyArena *arena);
#define BinOp(a0, a1, a2, a3, a4, a5) _Ta_BinOp(a0, a1, a2, a3, a4, a5)
expr_ty _Ta_BinOp(expr_ty left, operator_ty op, expr_ty right, int lineno, int
                  col_offset, PyArena *arena);
#define UnaryOp(a0, a1, a2, a3, a4) _Ta_UnaryOp(a0, a1, a2, a3, a4)
expr_ty _Ta_UnaryOp(unaryop_ty op, expr_ty operand, int lineno, int col_offset,
                    PyArena *arena);
#define Lambda(a0, a1, a2, a3, a4) _Ta_Lambda(a0, a1, a2, a3, a4)
expr_ty _Ta_Lambda(arguments_ty args, expr_ty body, int lineno, int col_offset,
                   PyArena *arena);
#define IfExp(a0, a1, a2, a3, a4, a5) _Ta_IfExp(a0, a1, a2, a3, a4, a5)
expr_ty _Ta_IfExp(expr_ty test, expr_ty body, expr_ty orelse, int lineno, int
                  col_offset, PyArena *arena);
#define Dict(a0, a1, a2, a3, a4) _Ta_Dict(a0, a1, a2, a3, a4)
expr_ty _Ta_Dict(asdl_seq * keys, asdl_seq * values, int lineno, int
                 col_offset, PyArena *arena);
#define Set(a0, a1, a2, a3) _Ta_Set(a0, a1, a2, a3)
expr_ty _Ta_Set(asdl_seq * elts, int lineno, int col_offset, PyArena *arena);
#define ListComp(a0, a1, a2, a3, a4) _Ta_ListComp(a0, a1, a2, a3, a4)
expr_ty _Ta_ListComp(expr_ty elt, asdl_seq * generators, int lineno, int
                     col_offset, PyArena *arena);
#define SetComp(a0, a1, a2, a3, a4) _Ta_SetComp(a0, a1, a2, a3, a4)
expr_ty _Ta_SetComp(expr_ty elt, asdl_seq * generators, int lineno, int
                    col_offset, PyArena *arena);
#define DictComp(a0, a1, a2, a3, a4, a5) _Ta_DictComp(a0, a1, a2, a3, a4, a5)
expr_ty _Ta_DictComp(expr_ty key, expr_ty value, asdl_seq * generators, int
                     lineno, int col_offset, PyArena *arena);
#define GeneratorExp(a0, a1, a2, a3, a4) _Ta_GeneratorExp(a0, a1, a2, a3, a4)
expr_ty _Ta_GeneratorExp(expr_ty elt, asdl_seq * generators, int lineno, int
                         col_offset, PyArena *arena);
#define Await(a0, a1, a2, a3) _Ta_Await(a0, a1, a2, a3)
expr_ty _Ta_Await(expr_ty value, int lineno, int col_offset, PyArena *arena);
#define Yield(a0, a1, a2, a3) _Ta_Yield(a0, a1, a2, a3)
expr_ty _Ta_Yield(expr_ty value, int lineno, int col_offset, PyArena *arena);
#define YieldFrom(a0, a1, a2, a3) _Ta_YieldFrom(a0, a1, a2, a3)
expr_ty _Ta_YieldFrom(expr_ty value, int lineno, int col_offset, PyArena
                      *arena);
#define Compare(a0, a1, a2, a3, a4, a5) _Ta_Compare(a0, a1, a2, a3, a4, a5)
expr_ty _Ta_Compare(expr_ty left, asdl_int_seq * ops, asdl_seq * comparators,
                    int lineno, int col_offset, PyArena *arena);
#define Call(a0, a1, a2, a3, a4, a5) _Ta_Call(a0, a1, a2, a3, a4, a5)
expr_ty _Ta_Call(expr_ty func, asdl_seq * args, asdl_seq * keywords, int
                 lineno, int col_offset, PyArena *arena);
#define Num(a0, a1, a2, a3) _Ta_Num(a0, a1, a2, a3)
expr_ty _Ta_Num(object n, int lineno, int col_offset, PyArena *arena);
#define Str(a0, a1, a2, a3) _Ta_Str(a0, a1, a2, a3)
expr_ty _Ta_Str(string s, int lineno, int col_offset, PyArena *arena);
#define Bytes(a0, a1, a2, a3) _Ta_Bytes(a0, a1, a2, a3)
expr_ty _Ta_Bytes(bytes s, int lineno, int col_offset, PyArena *arena);
#define NameConstant(a0, a1, a2, a3) _Ta_NameConstant(a0, a1, a2, a3)
expr_ty _Ta_NameConstant(singleton value, int lineno, int col_offset, PyArena
                         *arena);
#define Ellipsis(a0, a1, a2) _Ta_Ellipsis(a0, a1, a2)
expr_ty _Ta_Ellipsis(int lineno, int col_offset, PyArena *arena);
#define Attribute(a0, a1, a2, a3, a4, a5) _Ta_Attribute(a0, a1, a2, a3, a4, a5)
expr_ty _Ta_Attribute(expr_ty value, identifier attr, expr_context_ty ctx, int
                      lineno, int col_offset, PyArena *arena);
#define Subscript(a0, a1, a2, a3, a4, a5) _Ta_Subscript(a0, a1, a2, a3, a4, a5)
expr_ty _Ta_Subscript(expr_ty value, slice_ty slice, expr_context_ty ctx, int
                      lineno, int col_offset, PyArena *arena);
#define Starred(a0, a1, a2, a3, a4) _Ta_Starred(a0, a1, a2, a3, a4)
expr_ty _Ta_Starred(expr_ty value, expr_context_ty ctx, int lineno, int
                    col_offset, PyArena *arena);
#define Name(a0, a1, a2, a3, a4) _Ta_Name(a0, a1, a2, a3, a4)
expr_ty _Ta_Name(identifier id, expr_context_ty ctx, int lineno, int
                 col_offset, PyArena *arena);
#define List(a0, a1, a2, a3, a4) _Ta_List(a0, a1, a2, a3, a4)
expr_ty _Ta_List(asdl_seq * elts, expr_context_ty ctx, int lineno, int
                 col_offset, PyArena *arena);
#define Tuple(a0, a1, a2, a3, a4) _Ta_Tuple(a0, a1, a2, a3, a4)
expr_ty _Ta_Tuple(asdl_seq * elts, expr_context_ty ctx, int lineno, int
                  col_offset, PyArena *arena);
#define Slice(a0, a1, a2, a3) _Ta_Slice(a0, a1, a2, a3)
slice_ty _Ta_Slice(expr_ty lower, expr_ty upper, expr_ty step, PyArena *arena);
#define ExtSlice(a0, a1) _Ta_ExtSlice(a0, a1)
slice_ty _Ta_ExtSlice(asdl_seq * dims, PyArena *arena);
#define Index(a0, a1) _Ta_Index(a0, a1)
slice_ty _Ta_Index(expr_ty value, PyArena *arena);
#define comprehension(a0, a1, a2, a3) _Ta_comprehension(a0, a1, a2, a3)
comprehension_ty _Ta_comprehension(expr_ty target, expr_ty iter, asdl_seq *
                                   ifs, PyArena *arena);
#define ExceptHandler(a0, a1, a2, a3, a4, a5) _Ta_ExceptHandler(a0, a1, a2, a3, a4, a5)
excepthandler_ty _Ta_ExceptHandler(expr_ty type, identifier name, asdl_seq *
                                   body, int lineno, int col_offset, PyArena
                                   *arena);
#define arguments(a0, a1, a2, a3, a4, a5, a6) _Ta_arguments(a0, a1, a2, a3, a4, a5, a6)
arguments_ty _Ta_arguments(asdl_seq * args, arg_ty vararg, asdl_seq *
                           kwonlyargs, asdl_seq * kw_defaults, arg_ty kwarg,
                           asdl_seq * defaults, PyArena *arena);
#define arg(a0, a1, a2, a3, a4) _Ta_arg(a0, a1, a2, a3, a4)
arg_ty _Ta_arg(identifier arg, expr_ty annotation, int lineno, int col_offset,
               PyArena *arena);
#define keyword(a0, a1, a2) _Ta_keyword(a0, a1, a2)
keyword_ty _Ta_keyword(identifier arg, expr_ty value, PyArena *arena);
#define alias(a0, a1, a2) _Ta_alias(a0, a1, a2)
alias_ty _Ta_alias(identifier name, identifier asname, PyArena *arena);
#define withitem(a0, a1, a2) _Ta_withitem(a0, a1, a2)
withitem_ty _Ta_withitem(expr_ty context_expr, expr_ty optional_vars, PyArena
                         *arena);
#define TypeIgnore(a0, a1) _Ta_TypeIgnore(a0, a1)
type_ignore_ty _Ta_TypeIgnore(int lineno, PyArena *arena);

PyObject* TaAST_mod2obj(mod_ty t);
mod_ty TaAST_obj2mod(PyObject* ast, PyArena* arena, int mode);
int TaAST_Check(PyObject* obj);
