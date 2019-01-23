diff --git a/ast3/Python/ast.c b/ast3/Python/ast.c
index e12f8e6..1fa762d 100644
--- a/ast3/Python/ast.c
+++ b/ast3/Python/ast.c
@@ -665,6 +665,13 @@ new_identifier(const char *n, struct compiling *c)
 
 #define NEW_IDENTIFIER(n) new_identifier(STR(n), c)
 
+static string
+new_type_comment(const char *s, struct compiling *c)
+{
+  return PyUnicode_DecodeUTF8(s, strlen(s), NULL);
+}
+#define NEW_TYPE_COMMENT(n) new_type_comment(STR(n), c)
+
 static int
 ast_error(struct compiling *c, const node *n, const char *errmsg)
 {
@@ -734,11 +741,15 @@ num_stmts(const node *n)
         case simple_stmt:
             return NCH(n) / 2; /* Divide by 2 to remove count of semi-colons */
         case suite:
+            /* suite: simple_stmt | NEWLINE [TYPE_COMMENT NEWLINE] INDENT stmt+ DEDENT */
             if (NCH(n) == 1)
                 return num_stmts(CHILD(n, 0));
             else {
+                i = 2;
                 l = 0;
-                for (i = 2; i < (NCH(n) - 1); i++)
+                if (TYPE(CHILD(n, 1)) == TYPE_COMMENT)
+                    i += 2;
+                for (; i < (NCH(n) - 1); i++)
                     l += num_stmts(CHILD(n, i));
                 return l;
             }
@@ -763,10 +774,13 @@ Ta3AST_FromNodeObject(const node *n, PyCompilerFlags *flags,
 {
     int i, j, k, num;
     asdl_seq *stmts = NULL;
+    asdl_seq *type_ignores = NULL;
     stmt_ty s;
     node *ch;
     struct compiling c;
     mod_ty res = NULL;
+    asdl_seq *argtypes = NULL;
+    expr_ty ret, arg;
 
     c.c_arena = arena;
     /* borrowed reference */
@@ -806,7 +820,23 @@ Ta3AST_FromNodeObject(const node *n, PyCompilerFlags *flags,
                     }
                 }
             }
-            res = Module(stmts, arena);
+
+            /* Type ignores are stored under the ENDMARKER in file_input. */
+            ch = CHILD(n, NCH(n) - 1);
+            REQ(ch, ENDMARKER);
+            num = NCH(ch);
+            type_ignores = _Ta3_asdl_seq_new(num, arena);
+            if (!type_ignores)
+                goto out;
+
+            for (i = 0; i < num; i++) {
+                type_ignore_ty ti = TypeIgnore(LINENO(CHILD(ch, i)), arena);
+                if (!ti)
+                    goto out;
+                asdl_seq_SET(type_ignores, i, ti);
+            }
+
+            res = Module(stmts, type_ignores, arena);
             break;
         case eval_input: {
             expr_ty testlist_ast;
@@ -857,6 +887,40 @@ Ta3AST_FromNodeObject(const node *n, PyCompilerFlags *flags,
                 res = Interactive(stmts, arena);
             }
             break;
+        case func_type_input:
+            n = CHILD(n, 0);
+            REQ(n, func_type);
+
+            if (TYPE(CHILD(n, 1)) == typelist) {
+                ch = CHILD(n, 1);
+                /* this is overly permissive -- we don't pay any attention to
+                 * stars on the args -- just parse them into an ordered list */
+                num = 0;
+                for (i = 0; i < NCH(ch); i++) {
+                    if (TYPE(CHILD(ch, i)) == test)
+                        num++;
+                }
+
+                argtypes = _Ta3_asdl_seq_new(num, arena);
+
+                j = 0;
+                for (i = 0; i < NCH(ch); i++) {
+                    if (TYPE(CHILD(ch, i)) == test) {
+                        arg = ast_for_expr(&c, CHILD(ch, i));
+                        if (!arg)
+                            goto out;
+                        asdl_seq_SET(argtypes, j++, arg);
+                    }
+                }
+            }
+            else
+                argtypes = _Ta3_asdl_seq_new(0, arena);
+
+            ret = ast_for_expr(&c, CHILD(n, NCH(n) - 1));
+            if (!ret)
+                goto out;
+            res = FunctionType(argtypes, ret, arena);
+            break;
         default:
             PyErr_Format(PyExc_SystemError,
                          "invalid node %d for Ta3AST_FromNode", TYPE(n));
@@ -1250,7 +1314,7 @@ ast_for_arg(struct compiling *c, const node *n)
             return NULL;
     }
 
-    ret = arg(name, annotation, LINENO(n), n->n_col_offset, c->c_arena);
+    ret = arg(name, annotation, NULL, LINENO(n), n->n_col_offset, c->c_arena);
     if (!ret)
         return NULL;
     return ret;
@@ -1308,12 +1372,19 @@ handle_keywordonly_args(struct compiling *c, const node *n, int start,
                     goto error;
                 if (forbidden_name(c, argname, ch, 0))
                     goto error;
-                arg = arg(argname, annotation, LINENO(ch), ch->n_col_offset,
+                arg = arg(argname, annotation, NULL, LINENO(ch), ch->n_col_offset,
                           c->c_arena);
                 if (!arg)
                     goto error;
                 asdl_seq_SET(kwonlyargs, j++, arg);
-                i += 2; /* the name and the comma */
+                i += 1; /* the name */
+                if (TYPE(CHILD(n, i)) == COMMA)
+                    i += 1; /* the comma, if present */
+                break;
+            case TYPE_COMMENT:
+                /* arg will be equal to the last argument processed */
+                arg->type_comment = NEW_TYPE_COMMENT(ch);
+                i += 1;
                 break;
             case DOUBLESTAR:
                 return i;
@@ -1448,11 +1519,14 @@ ast_for_arguments(struct compiling *c, const node *n)
                 if (!arg)
                     return NULL;
                 asdl_seq_SET(posargs, k++, arg);
-                i += 2; /* the name and the comma */
+                i += 1; /* the name */
+                if (TYPE(CHILD(n, i)) == COMMA)
+                    i += 1; /* the comma, if present */
                 break;
             case STAR:
                 if (i+1 >= NCH(n) ||
-                    (i+2 == NCH(n) && TYPE(CHILD(n, i+1)) == COMMA)) {
+                    (i+2 == NCH(n) && (TYPE(CHILD(n, i+1)) == COMMA
+                                       || TYPE(CHILD(n, i+1)) == TYPE_COMMENT))) {
                     ast_error(c, CHILD(n, i),
                         "named arguments must follow bare *");
                     return NULL;
@@ -1461,6 +1535,13 @@ ast_for_arguments(struct compiling *c, const node *n)
                 if (TYPE(ch) == COMMA) {
                     int res = 0;
                     i += 2; /* now follows keyword only arguments */
+
+                    if (TYPE(CHILD(n, i)) == TYPE_COMMENT) {
+                        ast_error(c, CHILD(n, i),
+                                "bare * has associated type comment");
+                        return NULL;
+                    }
+
                     res = handle_keywordonly_args(c, n, i,
                                                   kwonlyargs, kwdefaults);
                     if (res == -1) return NULL;
@@ -1471,7 +1552,15 @@ ast_for_arguments(struct compiling *c, const node *n)
                     if (!vararg)
                         return NULL;
 
-                    i += 3;
+                i += 2; /* the star and the name */
+                if (TYPE(CHILD(n, i)) == COMMA)
+                    i += 1; /* the comma, if present */
+
+                    if (TYPE(CHILD(n, i)) == TYPE_COMMENT) {
+                        vararg->type_comment = NEW_TYPE_COMMENT(CHILD(n, i));
+                        i += 1;
+                    }
+
                     if (i < NCH(n) && (TYPE(CHILD(n, i)) == tfpdef
                                     || TYPE(CHILD(n, i)) == vfpdef)) {
                         int res = 0;
@@ -1488,7 +1577,19 @@ ast_for_arguments(struct compiling *c, const node *n)
                 kwarg = ast_for_arg(c, ch);
                 if (!kwarg)
                     return NULL;
-                i += 3;
+                i += 2; /* the double star and the name */
+                if (TYPE(CHILD(n, i)) == COMMA)
+                    i += 1; /* the comma, if present */
+                break;
+            case TYPE_COMMENT:
+                assert(i);
+
+                if (kwarg)
+                    arg = kwarg;
+
+                /* arg will be equal to the last argument processed */
+                arg->type_comment = NEW_TYPE_COMMENT(ch);
+                i += 1;
                 break;
             default:
                 PyErr_Format(PyExc_SystemError,
@@ -1593,12 +1694,14 @@ static stmt_ty
 ast_for_funcdef_impl(struct compiling *c, const node *n,
                      asdl_seq *decorator_seq, int is_async)
 {
-    /* funcdef: 'def' NAME parameters ['->' test] ':' suite */
+    /* funcdef: 'def' NAME parameters ['->' test] ':' [TYPE_COMMENT] suite */
     identifier name;
     arguments_ty args;
     asdl_seq *body;
     expr_ty returns = NULL;
     int name_i = 1;
+    node *tc;
+    string type_comment = NULL;
 
     REQ(n, funcdef);
 
@@ -1616,17 +1719,30 @@ ast_for_funcdef_impl(struct compiling *c, const node *n,
             return NULL;
         name_i += 2;
     }
+    if (TYPE(CHILD(n, name_i + 3)) == TYPE_COMMENT) {
+        type_comment = NEW_TYPE_COMMENT(CHILD(n, name_i + 3));
+        name_i += 1;
+    }
     body = ast_for_suite(c, CHILD(n, name_i + 3));
     if (!body)
         return NULL;
 
+    if (!type_comment && NCH(CHILD(n, name_i + 3)) > 1) {
+        /* If the function doesn't have a type comment on the same line, check
+         * if the suite has a type comment in it. */
+        tc = CHILD(CHILD(n, name_i + 3), 1);
+
+        if (TYPE(tc) == TYPE_COMMENT)
+            type_comment = NEW_TYPE_COMMENT(tc);
+    }
+
     if (is_async)
         return AsyncFunctionDef(name, args, body, decorator_seq, returns,
-                                LINENO(n),
+                                type_comment, LINENO(n),
                                 n->n_col_offset, c->c_arena);
     else
         return FunctionDef(name, args, body, decorator_seq, returns,
-                           LINENO(n),
+                           type_comment, LINENO(n),
                            n->n_col_offset, c->c_arena);
 }
 
@@ -2896,15 +3012,16 @@ ast_for_expr_stmt(struct compiling *c, const node *n)
 {
     REQ(n, expr_stmt);
     /* expr_stmt: testlist_star_expr (annassign | augassign (yield_expr|testlist) |
-                            ('=' (yield_expr|testlist_star_expr))*)
+                           ('=' (yield_expr|testlist_star_expr))* [TYPE_COMMENT])
        annassign: ':' test ['=' test]
        testlist_star_expr: (test|star_expr) (',' test|star_expr)* [',']
        augassign: '+=' | '-=' | '*=' | '@=' | '/=' | '%=' | '&=' | '|=' | '^='
                 | '<<=' | '>>=' | '**=' | '//='
        test: ... here starts the operator precedence dance
      */
+    int num = NCH(n);
 
-    if (NCH(n) == 1) {
+    if (num == 1 || (num == 2 && TYPE(CHILD(n, 1)) == TYPE_COMMENT)) {
         expr_ty e = ast_for_testlist(c, CHILD(n, 0));
         if (!e)
             return NULL;
@@ -3020,17 +3137,22 @@ ast_for_expr_stmt(struct compiling *c, const node *n)
         }
     }
     else {
-        int i;
+        int i, nch_minus_type, has_type_comment;
         asdl_seq *targets;
         node *value;
         expr_ty expression;
+        string type_comment;
 
         /* a normal assignment */
         REQ(CHILD(n, 1), EQUAL);
-        targets = _Ta3_asdl_seq_new(NCH(n) / 2, c->c_arena);
+
+        has_type_comment = TYPE(CHILD(n, num - 1)) == TYPE_COMMENT;
+        nch_minus_type = num - has_type_comment;
+
+        targets = _Ta3_asdl_seq_new(nch_minus_type / 2, c->c_arena);
         if (!targets)
             return NULL;
-        for (i = 0; i < NCH(n) - 2; i += 2) {
+        for (i = 0; i < nch_minus_type - 2; i += 2) {
             expr_ty e;
             node *ch = CHILD(n, i);
             if (TYPE(ch) == yield_expr) {
@@ -3047,14 +3169,18 @@ ast_for_expr_stmt(struct compiling *c, const node *n)
 
             asdl_seq_SET(targets, i / 2, e);
         }
-        value = CHILD(n, NCH(n) - 1);
+        value = CHILD(n, nch_minus_type - 1);
         if (TYPE(value) == testlist_star_expr)
             expression = ast_for_testlist(c, value);
         else
             expression = ast_for_expr(c, value);
         if (!expression)
             return NULL;
-        return Assign(targets, expression, LINENO(n), n->n_col_offset, c->c_arena);
+        if (has_type_comment)
+            type_comment = NEW_TYPE_COMMENT(CHILD(n, nch_minus_type));
+        else
+            type_comment = NULL;
+        return Assign(targets, expression, type_comment, LINENO(n), n->n_col_offset, c->c_arena);
     }
 }
 
@@ -3461,7 +3587,7 @@ ast_for_assert_stmt(struct compiling *c, const node *n)
 static asdl_seq *
 ast_for_suite(struct compiling *c, const node *n)
 {
-    /* suite: simple_stmt | NEWLINE INDENT stmt+ DEDENT */
+    /* suite: simple_stmt | NEWLINE [TYPE_COMMENT NEWLINE] INDENT stmt+ DEDENT */
     asdl_seq *seq;
     stmt_ty s;
     int i, total, num, end, pos = 0;
@@ -3491,7 +3617,11 @@ ast_for_suite(struct compiling *c, const node *n)
         }
     }
     else {
-        for (i = 2; i < (NCH(n) - 1); i++) {
+        i = 2;
+        if (TYPE(CHILD(n, 1)) == TYPE_COMMENT)
+            i += 2;
+
+        for (; i < (NCH(n) - 1); i++) {
             ch = CHILD(n, i);
             REQ(ch, stmt);
             num = num_stmts(ch);
@@ -3692,11 +3822,15 @@ ast_for_for_stmt(struct compiling *c, const node *n, int is_async)
     expr_ty expression;
     expr_ty target, first;
     const node *node_target;
-    /* for_stmt: 'for' exprlist 'in' testlist ':' suite ['else' ':' suite] */
+    int has_type_comment;
+    string type_comment;
+    /* for_stmt: 'for' exprlist 'in' testlist ':' [TYPE_COMMENT] suite ['else' ':' suite] */
     REQ(n, for_stmt);
 
-    if (NCH(n) == 9) {
-        seq = ast_for_suite(c, CHILD(n, 8));
+    has_type_comment = TYPE(CHILD(n, 5)) == TYPE_COMMENT;
+
+    if (NCH(n) == 9 + has_type_comment) {
+        seq = ast_for_suite(c, CHILD(n, 8 + has_type_comment));
         if (!seq)
             return NULL;
     }
@@ -3716,17 +3850,22 @@ ast_for_for_stmt(struct compiling *c, const node *n, int is_async)
     expression = ast_for_testlist(c, CHILD(n, 3));
     if (!expression)
         return NULL;
-    suite_seq = ast_for_suite(c, CHILD(n, 5));
+    suite_seq = ast_for_suite(c, CHILD(n, 5 + has_type_comment));
     if (!suite_seq)
         return NULL;
 
+    if (has_type_comment)
+        type_comment = NEW_TYPE_COMMENT(CHILD(n, 5));
+    else
+        type_comment = NULL;
+
     if (is_async)
         return AsyncFor(target, expression, suite_seq, seq,
-                        LINENO(n), n->n_col_offset,
+                        type_comment, LINENO(n), n->n_col_offset,
                         c->c_arena);
     else
         return For(target, expression, suite_seq, seq,
-                   LINENO(n), n->n_col_offset,
+                   type_comment, LINENO(n), n->n_col_offset,
                    c->c_arena);
 }
 
@@ -3872,20 +4011,24 @@ ast_for_with_item(struct compiling *c, const node *n)
     return withitem(context_expr, optional_vars, c->c_arena);
 }
 
-/* with_stmt: 'with' with_item (',' with_item)* ':' suite */
+/* with_stmt: 'with' with_item (',' with_item)*  ':' [TYPE_COMMENT] suite */
 static stmt_ty
 ast_for_with_stmt(struct compiling *c, const node *n, int is_async)
 {
-    int i, n_items;
+    int i, n_items, nch_minus_type, has_type_comment;
     asdl_seq *items, *body;
+    string type_comment;
 
     REQ(n, with_stmt);
 
-    n_items = (NCH(n) - 2) / 2;
+    has_type_comment = TYPE(CHILD(n, NCH(n) - 2)) == TYPE_COMMENT;
+    nch_minus_type = NCH(n) - has_type_comment;
+
+    n_items = (nch_minus_type - 2) / 2;
     items = _Ta3_asdl_seq_new(n_items, c->c_arena);
     if (!items)
         return NULL;
-    for (i = 1; i < NCH(n) - 2; i += 2) {
+    for (i = 1; i < nch_minus_type - 2; i += 2) {
         withitem_ty item = ast_for_with_item(c, CHILD(n, i));
         if (!item)
             return NULL;
@@ -3896,10 +4039,15 @@ ast_for_with_stmt(struct compiling *c, const node *n, int is_async)
     if (!body)
         return NULL;
 
+    if (has_type_comment)
+        type_comment = NEW_TYPE_COMMENT(CHILD(n, NCH(n) - 2));
+    else
+        type_comment = NULL;
+
     if (is_async)
-        return AsyncWith(items, body, LINENO(n), n->n_col_offset, c->c_arena);
+        return AsyncWith(items, body, type_comment, LINENO(n), n->n_col_offset, c->c_arena);
     else
-        return With(items, body, LINENO(n), n->n_col_offset, c->c_arena);
+        return With(items, body, type_comment, LINENO(n), n->n_col_offset, c->c_arena);
 }
 
 static stmt_ty
