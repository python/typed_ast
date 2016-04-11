
#ifndef Py_COMPILE_H
#define Py_COMPILE_H

#include "code.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Public interface */
PyAPI_FUNC(PyFutureFeatures *) PyFuture_FromAST(struct _mod *, const char *);


#ifdef __cplusplus
}
#endif
#endif /* !Py_COMPILE_H */
