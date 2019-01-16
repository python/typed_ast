diff --git a/ast3/Parser/tokenizer.c b/ast3/Parser/tokenizer.c
index 617a744..667fb4a 100644
--- a/ast3/Parser/tokenizer.c
+++ b/ast3/Parser/tokenizer.c
@@ -105,10 +105,16 @@ const char *_Ta3Parser_TokenNames[] = {
     "OP",
     "AWAIT",
     "ASYNC",
+    "TYPE_IGNORE",
+    "TYPE_COMMENT",
     "<ERRORTOKEN>",
     "<N_TOKENS>"
 };
 
+/* Spaces in this constant are treated as "zero or more spaces or tabs" when
+   tokenizing. */
+static const char* type_comment_prefix = "# type: ";
+
 
 /* Create and initialize a new tok_state structure */
 
@@ -1493,10 +1499,56 @@ tok_get(struct tok_state *tok, char **p_start, char **p_end)
     /* Set start of current token */
     tok->start = tok->cur - 1;
 
-    /* Skip comment */
+    /* Skip comment, unless it's a type comment */
     if (c == '#') {
-        while (c != EOF && c != '\n') {
+        const char *prefix, *p, *type_start;
+
+        while (c != EOF && c != '\n')
             c = tok_nextc(tok);
+
+        p = tok->start;
+        prefix = type_comment_prefix;
+        while (*prefix && p < tok->cur) {
+            if (*prefix == ' ') {
+                while (*p == ' ' || *p == '\t')
+                    p++;
+            } else if (*prefix == *p) {
+                p++;
+            } else {
+                break;
+            }
+
+            prefix++;
+        }
+
+        /* This is a type comment if we matched all of type_comment_prefix. */
+        if (!*prefix) {
+            int is_type_ignore = 1;
+            tok_backup(tok, c);  /* don't eat the newline or EOF */
+
+            type_start = p;
+
+            is_type_ignore = tok->cur >= p + 6 && memcmp(p, "ignore", 6) == 0;
+            p += 6;
+            while (is_type_ignore && p < tok->cur) {
+              if (*p == '#')
+                  break;
+              is_type_ignore = is_type_ignore && (*p == ' ' || *p == '\t');
+              p++;
+            }
+
+            if (is_type_ignore) {
+                /* If this type ignore is the only thing on the line, consume the newline also. */
+                if (blankline) {
+                    tok_nextc(tok);
+                    tok->atbol = 1;
+                }
+                return TYPE_IGNORE;
+            } else {
+                *p_start = (char *) type_start;  /* after type_comment_prefix */
+                *p_end = tok->cur;
+                return TYPE_COMMENT;
+            }
         }
     }
 
