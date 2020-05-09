#ifndef PEGEN_PEGEN_EXTRA_H
#define PEGEN_PEGEN_EXTRA_H

// Various workarounds to make the parser compatible with older 3.x
#include <Python.h>

// f-string input is new in 3.9
#if PY_MINOR_VERSION < 9
#define Py_fstring_input 800
#endif

// top level await new in 3.9
#if PY_MINOR_VERSION < 8
#define PyCF_ALLOW_TOP_LEVEL_AWAIT 0x2000
#endif

// typed_ast was merged into Python in 3.8
#if PY_MINOR_VERSION < 8
#define PyCF_TYPE_COMMENTS 0x1000
#endif

typedef struct {
    int cf_flags;  /* bitmask of CO_xxx flags relevant to future */
    int cf_feature_version;  /* minor Python version (PyCF_ONLY_AST) */
} PegenCompilerFlags;

#define _PegenCompilerFlags_INIT \
    (PegenCompilerFlags){.cf_flags = 0, .cf_feature_version = PY_MINOR_VERSION}


// Define 3.7+ input types
#if PY_MINOR_VERSION < 8
/* These definitions must match corresponding definitions in graminit.h. */
#define Py_single_input 256
#define Py_file_input 257
#define Py_eval_input 258
#define Py_func_type_input 345
#endif

// Py_UNREACHABLE was defined in 3.7
#if PY_MINOR_VERSION < 7
#if defined(RANDALL_WAS_HERE)
#  define Py_UNREACHABLE() \
    Py_FatalError( \
        "If you're seeing this, the code is in what I thought was\n" \
        "an unreachable state.\n\n" \
        "I could give you advice for what to do, but honestly, why\n" \
        "should you trust me?  I clearly screwed this up.  I'm writing\n" \
        "a message that should never appear, yet I know it will\n" \
        "probably appear someday.\n\n" \
        "On a deep level, I know I'm not up to this task.\n" \
        "I'm so sorry.\n" \
        "https://xkcd.com/2200")
#elif defined(Py_DEBUG)
#  define Py_UNREACHABLE() \
    Py_FatalError( \
        "We've reached an unreachable state. Anything is possible.\n" \
        "The limits were in our heads all along. Follow your dreams.\n" \
        "https://xkcd.com/2200")
#elif defined(__GNUC__) || defined(__clang__) || defined(__INTEL_COMPILER)
#  define Py_UNREACHABLE() __builtin_unreachable()
#elif defined(_MSC_VER)
#  define Py_UNREACHABLE() __assume(0)
#else
#  define Py_UNREACHABLE() \
    Py_FatalError("Unreachable C code path reached")
#endif
#endif

// 3.7 also introduced _Py_TypeName, which we provide an alternative for it here
const char * _Ta3Type_Name(PyTypeObject *);

int _Pegen_PyObject_LookupAttr(PyObject *, PyObject *, PyObject **);

const char *
_Pegen_SourceAsString(PyObject *cmd, const char *funcname, const char *what, PegenCompilerFlags *cf, PyObject **cmd_copy);


#endif /* !PEGEN_PYTHON_AST_H */