#ifndef Ta3_PEGENINTERFACE
#define Ta3_PEGENINTERFACE
#ifdef __cplusplus
extern "C" {
#endif

#include "Python.h"
#include "../Include/Python-ast.h"

mod_ty Ta3Pegen_ASTFromString(
    const char *str,
    const char *filename,
    int mode,
    PegenCompilerFlags *flags,
    PyArena *arena);
mod_ty Ta3Pegen_ASTFromStringObject(
    const char *str,
    PyObject* filename,
    int mode,
    PegenCompilerFlags *flags,
    PyArena *arena);
mod_ty Ta3Pegen_ASTFromFileObject(
    FILE *fp,
    PyObject *filename_ob,
    int mode,
    const char *enc,
    const char *ps1,
    const char *ps2,
    PegenCompilerFlags *flags,
    int *errcode,
    PyArena *arena);
mod_ty Ta3Pegen_ASTFromFilename(
    const char *filename,
    int mode,
    PegenCompilerFlags *flags,
    PyArena *arena);


#ifdef __cplusplus
}
#endif
#endif /* !Ta3_PEGENINTERFACE*/