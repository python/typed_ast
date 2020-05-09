#include "../Include/pegen_interface.h"

#include "../tokenizer.h"
#include "pegen.h"

mod_ty
Ta3Pegen_ASTFromString(const char *str, const char *filename, int mode,
                      PegenCompilerFlags *flags, PyArena *arena)
{
    PyObject *filename_ob = PyUnicode_FromString(filename);
    if (filename_ob == NULL) {
        return NULL;
    }
    mod_ty result = Ta3Pegen_ASTFromStringObject(str, filename_ob, mode, flags, arena);
    Py_XDECREF(filename_ob);
    return result;
}

mod_ty
Ta3Pegen_ASTFromStringObject(const char *str, PyObject* filename, int mode,
                            PegenCompilerFlags *flags, PyArena *arena)
{
    mod_ty result = _Ta3Pegen_run_parser_from_string(str, mode, filename, flags, arena);
    return result;
}

mod_ty
Ta3Pegen_ASTFromFilename(const char *filename, int mode, PegenCompilerFlags *flags, PyArena *arena)
{
    PyObject *filename_ob = PyUnicode_FromString(filename);
    if (filename_ob == NULL) {
        return NULL;
    }

    mod_ty result = _Ta3Pegen_run_parser_from_file(filename, mode, filename_ob, flags, arena);
    Py_XDECREF(filename_ob);
    return result;
}

mod_ty
Ta3Pegen_ASTFromFileObject(FILE *fp, PyObject *filename_ob, int mode,
                          const char *enc, const char *ps1, const char* ps2,
                          PegenCompilerFlags *flags, int *errcode, PyArena *arena)
{
    return _Ta3Pegen_run_parser_from_file_pointer(fp, mode, filename_ob, enc, ps1, ps2,
                                        flags, errcode, arena);
}
