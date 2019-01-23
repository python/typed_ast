--- /Users/guido/src/cpython37/Parser/asdl_c.py	2018-09-10 08:18:23.000000000 -0700
+++ ast3/Parser/asdl_c.py	2019-01-15 16:13:24.000000000 -0800
@@ -270,9 +270,9 @@
         margs = "a0"
         for i in range(1, len(args)+1):
             margs += ", a%d" % i
-        self.emit("#define %s(%s) _Py_%s(%s)" % (name, margs, name, margs), 0,
+        self.emit("#define %s(%s) _Ta3_%s(%s)" % (name, margs, name, margs), 0,
                 reflow=False)
-        self.emit("%s _Py_%s(%s);" % (ctype, name, argstr), False)
+        self.emit("%s _Ta3_%s(%s);" % (ctype, name, argstr), False)
 
     def visitProduct(self, prod, name):
         self.emit_function(name, get_c_type(name),
@@ -531,9 +531,9 @@
             self.emit("}", depth+1)
             self.emit("len = PyList_GET_SIZE(tmp);", depth+1)
             if self.isSimpleType(field):
-                self.emit("%s = _Py_asdl_int_seq_new(len, arena);" % field.name, depth+1)
+                self.emit("%s = _Ta3_asdl_int_seq_new(len, arena);" % field.name, depth+1)
             else:
-                self.emit("%s = _Py_asdl_seq_new(len, arena);" % field.name, depth+1)
+                self.emit("%s = _Ta3_asdl_seq_new(len, arena);" % field.name, depth+1)
             self.emit("if (%s == NULL) goto failed;" % field.name, depth+1)
             self.emit("for (i = 0; i < len; i++) {", depth+1)
             self.emit("%s val;" % ctype, depth+2)
@@ -729,8 +729,8 @@
 };
 
 static PyTypeObject AST_type = {
-    PyVarObject_HEAD_INIT(&PyType_Type, 0)
-    "_ast.AST",
+    PyVarObject_HEAD_INIT(NULL, 0)
+    "_ast3.AST",
     sizeof(AST_object),
     0,
     (destructor)ast_dealloc, /* tp_dealloc */
@@ -774,7 +774,7 @@
 static PyTypeObject* make_type(char *type, PyTypeObject* base, char**fields, int num_fields)
 {
     _Py_IDENTIFIER(__module__);
-    _Py_IDENTIFIER(_ast);
+    _Py_IDENTIFIER(_ast3);
     PyObject *fnames, *result;
     int i;
     fnames = PyTuple_New(num_fields);
@@ -791,7 +791,7 @@
                     type, base,
                     _PyUnicode_FromId(&PyId__fields), fnames,
                     _PyUnicode_FromId(&PyId___module__),
-                    _PyUnicode_FromId(&PyId__ast));
+                    _PyUnicode_FromId(&PyId__ast3));
     Py_DECREF(fnames);
     return (PyTypeObject*)result;
 }
@@ -1010,11 +1010,16 @@
 class ASTModuleVisitor(PickleVisitor):
 
     def visitModule(self, mod):
+        self.emit("PyObject *ast3_parse(PyObject *self, PyObject *args);", 0)
+        self.emit("static PyMethodDef ast3_methods[] = {", 0)
+        self.emit('    {"_parse",  ast3_parse, METH_VARARGS, "Parse string into typed AST."},', 0)
+        self.emit("    {NULL, NULL, 0, NULL}", 0)
+        self.emit("};", 0)
         self.emit("static struct PyModuleDef _astmodule = {", 0)
-        self.emit('  PyModuleDef_HEAD_INIT, "_ast"', 0)
+        self.emit('    PyModuleDef_HEAD_INIT, "_ast3", NULL, 0, ast3_methods', 0)
         self.emit("};", 0)
         self.emit("PyMODINIT_FUNC", 0)
-        self.emit("PyInit__ast(void)", 0)
+        self.emit("PyInit__ast3(void)", 0)
         self.emit("{", 0)
         self.emit("PyObject *m, *d;", 1)
         self.emit("if (!init_types()) return NULL;", 1)
@@ -1199,7 +1204,7 @@
 class PartingShots(StaticVisitor):
 
     CODE = """
-PyObject* PyAST_mod2obj(mod_ty t)
+PyObject* Ta3AST_mod2obj(mod_ty t)
 {
     if (!init_types())
         return NULL;
@@ -1207,7 +1212,7 @@
 }
 
 /* mode is 0 for "exec", 1 for "eval" and 2 for "single" input */
-mod_ty PyAST_obj2mod(PyObject* ast, PyArena* arena, int mode)
+mod_ty Ta3AST_obj2mod(PyObject* ast, PyArena* arena, int mode)
 {
     mod_ty res;
     PyObject *req_type[3];
@@ -1237,7 +1242,7 @@
         return res;
 }
 
-int PyAST_Check(PyObject* obj)
+int Ta3AST_Check(PyObject* obj)
 {
     if (!init_types())
         return -1;
@@ -1276,9 +1281,9 @@
                                 PrototypeVisitor(f),
                                 )
             c.visit(mod)
-            f.write("PyObject* PyAST_mod2obj(mod_ty t);\n")
-            f.write("mod_ty PyAST_obj2mod(PyObject* ast, PyArena* arena, int mode);\n")
-            f.write("int PyAST_Check(PyObject* obj);\n")
+            f.write("PyObject* Ta3AST_mod2obj(mod_ty t);\n")
+            f.write("mod_ty Ta3AST_obj2mod(PyObject* ast, PyArena* arena, int mode);\n")
+            f.write("int Ta3AST_Check(PyObject* obj);\n")
 
     if C_FILE:
         with open(C_FILE, "w") as f:
