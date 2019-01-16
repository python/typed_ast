diff --git a/ast3/Grammar/Grammar b/ast3/Grammar/Grammar
index b139e9f..dfd730f 100644
--- a/ast3/Grammar/Grammar
+++ b/ast3/Grammar/Grammar
@@ -14,7 +14,10 @@
 #       single_input is a single interactive statement;
 #       file_input is a module or sequence of commands read from an input file;
 #       eval_input is the input for the eval() functions.
+#       func_type_input is a PEP 484 Python 2 function type comment
 # NB: compound_stmt in single_input is followed by extra NEWLINE!
+# NB: due to the way TYPE_COMMENT is tokenized it will always be followed by a
+#      NEWLINE
 single_input: NEWLINE | simple_stmt | compound_stmt NEWLINE
 file_input: (NEWLINE | stmt)* ENDMARKER
 eval_input: testlist NEWLINE* ENDMARKER
@@ -24,14 +27,14 @@ decorators: decorator+
 decorated: decorators (classdef | funcdef | async_funcdef)
 
 async_funcdef: ASYNC funcdef
-funcdef: 'def' NAME parameters ['->' test] ':' suite
+funcdef: 'def' NAME parameters ['->' test] ':' [TYPE_COMMENT] suite
 
 parameters: '(' [typedargslist] ')'
-typedargslist: (tfpdef ['=' test] (',' tfpdef ['=' test])* [',' [
-        '*' [tfpdef] (',' tfpdef ['=' test])* [',' ['**' tfpdef [',']]]
-      | '**' tfpdef [',']]]
-  | '*' [tfpdef] (',' tfpdef ['=' test])* [',' ['**' tfpdef [',']]]
-  | '**' tfpdef [','])
+typedargslist: (tfpdef ['=' test] (',' [TYPE_COMMENT] tfpdef ['=' test])* (TYPE_COMMENT | [',' [TYPE_COMMENT] [
+        '*' [tfpdef] (',' [TYPE_COMMENT] tfpdef ['=' test])* (TYPE_COMMENT | [',' [TYPE_COMMENT] ['**' tfpdef [','] [TYPE_COMMENT]]])
+      | '**' tfpdef [','] [TYPE_COMMENT]]])
+  | '*' [tfpdef] (',' [TYPE_COMMENT] tfpdef ['=' test])* (TYPE_COMMENT | [',' [TYPE_COMMENT] ['**' tfpdef [','] [TYPE_COMMENT]]])
+  | '**' tfpdef [','] [TYPE_COMMENT])
 tfpdef: NAME [':' test]
 varargslist: (vfpdef ['=' test] (',' vfpdef ['=' test])* [',' [
         '*' [vfpdef] (',' vfpdef ['=' test])* [',' ['**' vfpdef [',']]]
@@ -46,7 +49,7 @@ simple_stmt: small_stmt (';' small_stmt)* [';'] NEWLINE
 small_stmt: (expr_stmt | del_stmt | pass_stmt | flow_stmt |
              import_stmt | global_stmt | nonlocal_stmt | assert_stmt)
 expr_stmt: testlist_star_expr (annassign | augassign (yield_expr|testlist) |
-                     ('=' (yield_expr|testlist_star_expr))*)
+                     ('=' (yield_expr|testlist_star_expr))* [TYPE_COMMENT])
 annassign: ':' test ['=' test]
 testlist_star_expr: (test|star_expr) (',' (test|star_expr))* [',']
 augassign: ('+=' | '-=' | '*=' | '@=' | '/=' | '%=' | '&=' | '|=' | '^=' |
@@ -78,17 +81,18 @@ compound_stmt: if_stmt | while_stmt | for_stmt | try_stmt | with_stmt | funcdef
 async_stmt: ASYNC (funcdef | with_stmt | for_stmt)
 if_stmt: 'if' test ':' suite ('elif' test ':' suite)* ['else' ':' suite]
 while_stmt: 'while' test ':' suite ['else' ':' suite]
-for_stmt: 'for' exprlist 'in' testlist ':' suite ['else' ':' suite]
+for_stmt: 'for' exprlist 'in' testlist ':' [TYPE_COMMENT] suite ['else' ':' suite]
 try_stmt: ('try' ':' suite
            ((except_clause ':' suite)+
             ['else' ':' suite]
             ['finally' ':' suite] |
            'finally' ':' suite))
-with_stmt: 'with' with_item (',' with_item)*  ':' suite
+with_stmt: 'with' with_item (',' with_item)*  ':' [TYPE_COMMENT] suite
 with_item: test ['as' expr]
 # NB compile.c makes sure that the default except clause is last
 except_clause: 'except' [test ['as' NAME]]
-suite: simple_stmt | NEWLINE INDENT stmt+ DEDENT
+# the TYPE_COMMENT in suites is only parsed for funcdefs, but can't go elsewhere due to ambiguity
+suite: simple_stmt | NEWLINE [TYPE_COMMENT NEWLINE] INDENT stmt+ DEDENT
 
 test: or_test ['if' or_test 'else' test] | lambdef
 test_nocond: or_test | lambdef_nocond
@@ -154,3 +158,10 @@ encoding_decl: NAME
 
 yield_expr: 'yield' [yield_arg]
 yield_arg: 'from' test | testlist
+
+func_type_input: func_type NEWLINE* ENDMARKER
+func_type: '(' [typelist] ')' '->' test
+# typelist is a modified typedargslist (see above)
+typelist: (test (',' test)* [','
+       ['*' [test] (',' test)* [',' '**' test] | '**' test]]
+     |  '*' [test] (',' test)* [',' '**' test] | '**' test)
