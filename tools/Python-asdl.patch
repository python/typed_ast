diff --git a/ast3/Parser/Python.asdl b/ast3/Parser/Python.asdl
index f470ad1..7bde99c 100644
--- a/ast3/Parser/Python.asdl
+++ b/ast3/Parser/Python.asdl
@@ -6,17 +6,18 @@
 
 module Python
 {
-    mod = Module(stmt* body)
+    mod = Module(stmt* body, type_ignore *type_ignores)
         | Interactive(stmt* body)
         | Expression(expr body)
+        | FunctionType(expr* argtypes, expr returns)
 
         -- not really an actual node but useful in Jython's typesystem.
         | Suite(stmt* body)
 
     stmt = FunctionDef(identifier name, arguments args,
-                       stmt* body, expr* decorator_list, expr? returns)
+                       stmt* body, expr* decorator_list, expr? returns, string? type_comment)
           | AsyncFunctionDef(identifier name, arguments args,
-                             stmt* body, expr* decorator_list, expr? returns)
+                             stmt* body, expr* decorator_list, expr? returns, string? type_comment)
 
           | ClassDef(identifier name,
              expr* bases,
@@ -26,18 +27,18 @@ module Python
           | Return(expr? value)
 
           | Delete(expr* targets)
-          | Assign(expr* targets, expr value)
+          | Assign(expr* targets, expr value, string? type_comment)
           | AugAssign(expr target, operator op, expr value)
           -- 'simple' indicates that we annotate simple name without parens
           | AnnAssign(expr target, expr annotation, expr? value, int simple)
 
           -- use 'orelse' because else is a keyword in target languages
-          | For(expr target, expr iter, stmt* body, stmt* orelse)
-          | AsyncFor(expr target, expr iter, stmt* body, stmt* orelse)
+          | For(expr target, expr iter, stmt* body, stmt* orelse, string? type_comment)
+          | AsyncFor(expr target, expr iter, stmt* body, stmt* orelse, string? type_comment)
           | While(expr test, stmt* body, stmt* orelse)
           | If(expr test, stmt* body, stmt* orelse)
-          | With(withitem* items, stmt* body)
-          | AsyncWith(withitem* items, stmt* body)
+          | With(withitem* items, stmt* body, string? type_comment)
+          | AsyncWith(withitem* items, stmt* body, string? type_comment)
 
           | Raise(expr? exc, expr? cause)
           | Try(stmt* body, excepthandler* handlers, stmt* orelse, stmt* finalbody)
@@ -118,7 +119,7 @@ module Python
     arguments = (arg* args, arg? vararg, arg* kwonlyargs, expr* kw_defaults,
                  arg? kwarg, expr* defaults)
 
-    arg = (identifier arg, expr? annotation)
+    arg = (identifier arg, expr? annotation, string? type_comment)
            attributes (int lineno, int col_offset)
 
     -- keyword arguments supplied to call (NULL identifier for **kwargs)
@@ -128,5 +129,7 @@ module Python
     alias = (identifier name, identifier? asname)
 
     withitem = (expr context_expr, expr? optional_vars)
+
+    type_ignore = TypeIgnore(int lineno)
 }
 
