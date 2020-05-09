#define Py_PYTHON_AST_H
#include "Python.h"
#include "../Include/Python-ast.h"
#include "../Include/token.h"
#include "errcode.h"
#include "../Include/pegen_extra.h"
#include "../Include/pegen_interface.h"
#include "../Parser/pegen/pegen.h"

// from Python/pythonrun.c
const char *
_Pegen_SourceAsString(PyObject *cmd, const char *funcname, const char *what, PegenCompilerFlags *cf, PyObject **cmd_copy)
{
    const char *str;
    Py_ssize_t size;
    Py_buffer view;

    *cmd_copy = NULL;
    if (PyUnicode_Check(cmd)) {
        cf->cf_flags |= PyCF_IGNORE_COOKIE;
        str = PyUnicode_AsUTF8AndSize(cmd, &size);
        if (str == NULL)
            return NULL;
    }
    else if (PyBytes_Check(cmd)) {
        str = PyBytes_AS_STRING(cmd);
        size = PyBytes_GET_SIZE(cmd);
    }
    else if (PyByteArray_Check(cmd)) {
        str = PyByteArray_AS_STRING(cmd);
        size = PyByteArray_GET_SIZE(cmd);
    }
    else if (PyObject_GetBuffer(cmd, &view, PyBUF_SIMPLE) == 0) {
        /* Copy to NUL-terminated buffer. */
        *cmd_copy = PyBytes_FromStringAndSize(
            (const char *)view.buf, view.len);
        PyBuffer_Release(&view);
        if (*cmd_copy == NULL) {
            return NULL;
        }
        str = PyBytes_AS_STRING(*cmd_copy);
        size = PyBytes_GET_SIZE(*cmd_copy);
    }
    else {
        PyErr_Format(PyExc_TypeError,
            "%s() arg 1 must be a %s object",
            funcname, what);
        return NULL;
    }

    if (strlen(str) != (size_t)size) {
        PyErr_SetString(PyExc_ValueError,
            "source code string cannot contain null bytes");
        Py_CLEAR(*cmd_copy);
        return NULL;
    }
    return str;
}

// adapted from Py_CompileStringObject in Python/pythonrun.c
static PyObject *
string_object_to_py_ast(const char *str, PyObject *filename, int mode,
                       PegenCompilerFlags *flags)
{
    mod_ty mod;
    PyObject *result;
    PyArena *arena = PyArena_New();
    if (arena == NULL)
        return NULL;

    mod = Ta3Pegen_ASTFromStringObject(str, filename, mode, flags, arena);
    if (mod == NULL) {
        PyArena_Free(arena);
        return NULL;
    }

    result = Ta3AST_mod2obj(mod);
    PyArena_Free(arena);
    return result;
}

// adapted from builtin_compile_impl in Python/bltinmodule.c
static PyObject *
ast3_parse_impl(PyObject *source,
                PyObject *filename,
                const char *mode,
                int feature_version)
{
    PyObject *source_copy;
    const char *str;
    int compile_mode = -1;
    PegenCompilerFlags cf;
    //int start[] = {file_input, eval_input, single_input, func_type_input};
    PyObject *result;

    cf.cf_flags = PyCF_ONLY_AST | PyCF_SOURCE_IS_UTF8;
    cf.cf_feature_version = feature_version;

    if (strcmp(mode, "exec") == 0)
        compile_mode = 0;
    else if (strcmp(mode, "eval") == 0)
        compile_mode = 1;
    else if (strcmp(mode, "single") == 0)
        compile_mode = 2;
    else if (strcmp(mode, "func_type") == 0)
        compile_mode = 3;
    else {
        PyErr_SetString(PyExc_ValueError,
                        "parse() mode must be 'exec', 'eval', 'single', for 'func_type'");
        goto error;
    }

    str = _Pegen_SourceAsString(source, "parse", "string or bytes", &cf, &source_copy);
    if (str == NULL)
        goto error;

    result = string_object_to_py_ast(str, filename, compile_mode, &cf);
    Py_XDECREF(source_copy);
    goto finally;

error:
    result = NULL;
finally:
    Py_DECREF(filename);
    return result;
}

// adapted from old typed_ast based on builtin_compile in Python/clinic/bltinmodule.c.h
PyObject *
ast3_parse(PyObject *self, PyObject *args)
{
    PyObject *return_value = NULL;
    PyObject *source;
    PyObject *filename;
    const char *mode;
    int feature_version;

    if (PyArg_ParseTuple(args, "OO&si:parse", &source, PyUnicode_FSDecoder, &filename, &mode, &feature_version))
        return_value = ast3_parse_impl(source, filename, mode, feature_version);

    return return_value;
}
