/*
 * The Python Imaging Library
 *
 * a tiny module to get builds compatible to the running CPU
 *
 * Copyright (c) 2017 Shunsuke Shimizu
 *
 * See the README file for information on usage and redistribution.
 */

#include "Python.h"
#include "py3.h"

#if defined(__x86_64__)
static void
cpuid(int* eax, int* ebx, int* ecx, int* edx)
{
    __asm__(
        "movl %0, %%eax\n\t"
        "movl %2, %%ecx\n\t"
        "cpuid\n\t"
        "movl %%eax, %0\n\t"
        "movl %%ebx, %1\n\t"
        "movl %%ecx, %2\n\t"
        "movl %%edx, %3\n\t"
    : "+rm" (*eax), "=rm" (*ebx), "+rm" (*ecx), "=rm" (*edx)
    :
    : "%eax", "%ebx", "%ecx", "%edx"
    );
}
#endif

static PyObject*
get_available_builds(PyObject* self, PyObject* args)
{
    PyObject* list = PyList_New(0);
#if defined(__x86_64__)
    int eax, ebx, ecx, edx, max_set;
    /* check feature sets available */
    eax = 0;
    cpuid(&eax, &ebx, &ecx, &edx);
    max_set = eax;
    /* get basic feature set */
    eax = 1;
    if (eax > max_set) goto ret;
    cpuid(&eax, &ebx, &ecx, &edx);
    /* check sse4.1 and sse4.2 */
    if (!(ecx & (1 << 19) && ecx & (1 << 20))) goto ret;
    PyList_Insert(list, 0, PyUnicode_FromString("SSE4"));
    /* get extended feature set */
    eax = 7;
    ecx = 0;
    if (eax > max_set) goto ret;
    cpuid(&eax, &ebx, &ecx, &edx);
    /* check avx2 */
    if (!(ebx & (1 << 5))) goto ret;
    PyList_Insert(list, 0, PyUnicode_FromString("AVX2"));
#endif
ret:
    (void) self, (void) args;
    PyList_Append(list, PyUnicode_FromString("GENERIC"));
    return list;
}

static PyMethodDef _functions[] = {
    {"get_available_builds", (PyCFunction) get_available_builds, METH_NOARGS},
    {NULL, NULL}
};

#if PY_VERSION_HEX >= 0x03000000
PyMODINIT_FUNC
PyInit__imagingbuilds(void) {
    static PyModuleDef module_def = {
        PyModuleDef_HEAD_INIT,
        "_imagingbuilds",   /* m_name */
        NULL,               /* m_doc */
        -1,                 /* m_size */
        _functions,         /* m_methods */
    };

    return PyModule_Create(&module_def);
}
#else
PyMODINIT_FUNC
init_imagingbuilds(void)
{
    Py_InitModule("_imagingbuilds", _functions);
}
#endif
