diff --git a/ast3/Parser/parsetok.c b/ast3/Parser/parsetok.c
index 9f01a0d..5529feb 100644
--- a/ast3/Parser/parsetok.c
+++ b/ast3/Parser/parsetok.c
@@ -177,6 +177,38 @@ warn(const char *msg, const char *filename, int lineno)
 #endif
 #endif
 
+typedef struct {
+    int *items;
+    size_t size;
+    size_t num_items;
+} growable_int_array;
+
+int growable_int_array_init(growable_int_array *arr, size_t initial_size) {
+    assert(initial_size > 0);
+    arr->items = malloc(initial_size * sizeof(*arr->items));
+    arr->size = initial_size;
+    arr->num_items = 0;
+
+    return arr->items != NULL;
+}
+
+int growable_int_array_add(growable_int_array *arr, int item) {
+    if (arr->num_items >= arr->size) {
+        arr->size *= 2;
+        arr->items = realloc(arr->items, arr->size * sizeof(*arr->items));
+        if (!arr->items)
+            return 0;
+    }
+
+    arr->items[arr->num_items] = item;
+    arr->num_items++;
+    return 1;
+}
+
+void growable_int_array_deallocate(growable_int_array *arr) {
+    free(arr->items);
+}
+
 /* Parse input coming from the given tokenizer structure.
    Return error code. */
 
@@ -188,6 +220,13 @@ parsetok(struct tok_state *tok, grammar *g, int start, perrdetail *err_ret,
     node *n;
     int started = 0;
 
+    growable_int_array type_ignores;
+    if (!growable_int_array_init(&type_ignores, 10)) {
+        err_ret->error = E_NOMEM;
+        Ta3Tokenizer_Free(tok);
+        return NULL;
+    }
+
     if ((ps = Ta3Parser_New(g, start)) == NULL) {
         err_ret->error = E_NOMEM;
         Ta3Tokenizer_Free(tok);
@@ -259,6 +298,14 @@ parsetok(struct tok_state *tok, grammar *g, int start, perrdetail *err_ret,
         else
             col_offset = -1;
 
+        if (type == TYPE_IGNORE) {
+            if (!growable_int_array_add(&type_ignores, tok->lineno)) {
+                err_ret->error = E_NOMEM;
+                break;
+            }
+            continue;
+        }
+
         if ((err_ret->error =
              Ta3Parser_AddToken(ps, (int)type, str,
                                tok->lineno, col_offset,
@@ -275,6 +322,22 @@ parsetok(struct tok_state *tok, grammar *g, int start, perrdetail *err_ret,
         n = ps->p_tree;
         ps->p_tree = NULL;
 
+        if (n->n_type == file_input) {
+            /* Put type_ignore nodes in the ENDMARKER of file_input. */
+            int num;
+            node *ch;
+            size_t i;
+
+            num = NCH(n);
+            ch = CHILD(n, num - 1);
+            REQ(ch, ENDMARKER);
+
+            for (i = 0; i < type_ignores.num_items; i++) {
+                Ta3Node_AddChild(ch, TYPE_IGNORE, NULL, type_ignores.items[i], 0);
+            }
+        }
+        growable_int_array_deallocate(&type_ignores);
+
 #ifndef PGEN
         /* Check that the source for a single input statement really
            is a single statement by looking at what is left in the
