#ifndef Ta_AST_H
#define Ta_AST_H
#ifdef __cplusplus
extern "C" {
#endif

PyAPI_FUNC(int) TaAST_Validate(mod_ty);
PyAPI_FUNC(mod_ty) TaAST_FromNode(
    const node *n,
    PyCompilerFlags *flags,
    const char *filename,       /* decoded from the filesystem encoding */
    PyArena *arena);
PyAPI_FUNC(mod_ty) TaAST_FromNodeObject(
    const node *n,
    PyCompilerFlags *flags,
    PyObject *filename,
    PyArena *arena);

#ifdef __cplusplus
}
#endif
#endif /* !Ta_AST_H */
