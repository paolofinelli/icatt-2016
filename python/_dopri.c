#define _CFFI_
#include <Python.h>
#ifdef __cplusplus
extern "C" {
#endif
#include <stddef.h>

/* This part is from file 'cffi/parse_c_type.h'.  It is copied at the
   beginning of C sources generated by CFFI's ffi.set_source(). */

typedef void *_cffi_opcode_t;

#define _CFFI_OP(opcode, arg)   (_cffi_opcode_t)(opcode | (((uintptr_t)(arg)) << 8))
#define _CFFI_GETOP(cffi_opcode)    ((unsigned char)(uintptr_t)cffi_opcode)
#define _CFFI_GETARG(cffi_opcode)   (((intptr_t)cffi_opcode) >> 8)

#define _CFFI_OP_PRIMITIVE       1
#define _CFFI_OP_POINTER         3
#define _CFFI_OP_ARRAY           5
#define _CFFI_OP_OPEN_ARRAY      7
#define _CFFI_OP_STRUCT_UNION    9
#define _CFFI_OP_ENUM           11
#define _CFFI_OP_FUNCTION       13
#define _CFFI_OP_FUNCTION_END   15
#define _CFFI_OP_NOOP           17
#define _CFFI_OP_BITFIELD       19
#define _CFFI_OP_TYPENAME       21
#define _CFFI_OP_CPYTHON_BLTN_V 23   // varargs
#define _CFFI_OP_CPYTHON_BLTN_N 25   // noargs
#define _CFFI_OP_CPYTHON_BLTN_O 27   // O  (i.e. a single arg)
#define _CFFI_OP_CONSTANT       29
#define _CFFI_OP_CONSTANT_INT   31
#define _CFFI_OP_GLOBAL_VAR     33
#define _CFFI_OP_DLOPEN_FUNC    35
#define _CFFI_OP_DLOPEN_CONST   37
#define _CFFI_OP_GLOBAL_VAR_F   39
#define _CFFI_OP_EXTERN_PYTHON  41

#define _CFFI_PRIM_VOID          0
#define _CFFI_PRIM_BOOL          1
#define _CFFI_PRIM_CHAR          2
#define _CFFI_PRIM_SCHAR         3
#define _CFFI_PRIM_UCHAR         4
#define _CFFI_PRIM_SHORT         5
#define _CFFI_PRIM_USHORT        6
#define _CFFI_PRIM_INT           7
#define _CFFI_PRIM_UINT          8
#define _CFFI_PRIM_LONG          9
#define _CFFI_PRIM_ULONG        10
#define _CFFI_PRIM_LONGLONG     11
#define _CFFI_PRIM_ULONGLONG    12
#define _CFFI_PRIM_FLOAT        13
#define _CFFI_PRIM_DOUBLE       14
#define _CFFI_PRIM_LONGDOUBLE   15

#define _CFFI_PRIM_WCHAR        16
#define _CFFI_PRIM_INT8         17
#define _CFFI_PRIM_UINT8        18
#define _CFFI_PRIM_INT16        19
#define _CFFI_PRIM_UINT16       20
#define _CFFI_PRIM_INT32        21
#define _CFFI_PRIM_UINT32       22
#define _CFFI_PRIM_INT64        23
#define _CFFI_PRIM_UINT64       24
#define _CFFI_PRIM_INTPTR       25
#define _CFFI_PRIM_UINTPTR      26
#define _CFFI_PRIM_PTRDIFF      27
#define _CFFI_PRIM_SIZE         28
#define _CFFI_PRIM_SSIZE        29
#define _CFFI_PRIM_INT_LEAST8   30
#define _CFFI_PRIM_UINT_LEAST8  31
#define _CFFI_PRIM_INT_LEAST16  32
#define _CFFI_PRIM_UINT_LEAST16 33
#define _CFFI_PRIM_INT_LEAST32  34
#define _CFFI_PRIM_UINT_LEAST32 35
#define _CFFI_PRIM_INT_LEAST64  36
#define _CFFI_PRIM_UINT_LEAST64 37
#define _CFFI_PRIM_INT_FAST8    38
#define _CFFI_PRIM_UINT_FAST8   39
#define _CFFI_PRIM_INT_FAST16   40
#define _CFFI_PRIM_UINT_FAST16  41
#define _CFFI_PRIM_INT_FAST32   42
#define _CFFI_PRIM_UINT_FAST32  43
#define _CFFI_PRIM_INT_FAST64   44
#define _CFFI_PRIM_UINT_FAST64  45
#define _CFFI_PRIM_INTMAX       46
#define _CFFI_PRIM_UINTMAX      47

#define _CFFI__NUM_PRIM         48
#define _CFFI__UNKNOWN_PRIM           (-1)
#define _CFFI__UNKNOWN_FLOAT_PRIM     (-2)
#define _CFFI__UNKNOWN_LONG_DOUBLE    (-3)

#define _CFFI__IO_FILE_STRUCT         (-1)


struct _cffi_global_s {
    const char *name;
    void *address;
    _cffi_opcode_t type_op;
    void *size_or_direct_fn;  // OP_GLOBAL_VAR: size, or 0 if unknown
                              // OP_CPYTHON_BLTN_*: addr of direct function
};

struct _cffi_getconst_s {
    unsigned long long value;
    const struct _cffi_type_context_s *ctx;
    int gindex;
};

struct _cffi_struct_union_s {
    const char *name;
    int type_index;          // -> _cffi_types, on a OP_STRUCT_UNION
    int flags;               // _CFFI_F_* flags below
    size_t size;
    int alignment;
    int first_field_index;   // -> _cffi_fields array
    int num_fields;
};
#define _CFFI_F_UNION         0x01   // is a union, not a struct
#define _CFFI_F_CHECK_FIELDS  0x02   // complain if fields are not in the
                                     // "standard layout" or if some are missing
#define _CFFI_F_PACKED        0x04   // for CHECK_FIELDS, assume a packed struct
#define _CFFI_F_EXTERNAL      0x08   // in some other ffi.include()
#define _CFFI_F_OPAQUE        0x10   // opaque

struct _cffi_field_s {
    const char *name;
    size_t field_offset;
    size_t field_size;
    _cffi_opcode_t field_type_op;
};

struct _cffi_enum_s {
    const char *name;
    int type_index;          // -> _cffi_types, on a OP_ENUM
    int type_prim;           // _CFFI_PRIM_xxx
    const char *enumerators; // comma-delimited string
};

struct _cffi_typename_s {
    const char *name;
    int type_index;   /* if opaque, points to a possibly artificial
                         OP_STRUCT which is itself opaque */
};

struct _cffi_type_context_s {
    _cffi_opcode_t *types;
    const struct _cffi_global_s *globals;
    const struct _cffi_field_s *fields;
    const struct _cffi_struct_union_s *struct_unions;
    const struct _cffi_enum_s *enums;
    const struct _cffi_typename_s *typenames;
    int num_globals;
    int num_struct_unions;
    int num_enums;
    int num_typenames;
    const char *const *includes;
    int num_types;
    int flags;      /* future extension */
};

struct _cffi_parse_info_s {
    const struct _cffi_type_context_s *ctx;
    _cffi_opcode_t *output;
    unsigned int output_size;
    size_t error_location;
    const char *error_message;
};

struct _cffi_externpy_s {
    const char *name;
    size_t size_of_result;
    void *reserved1, *reserved2;
};

#ifdef _CFFI_INTERNAL
static int parse_c_type(struct _cffi_parse_info_s *info, const char *input);
static int search_in_globals(const struct _cffi_type_context_s *ctx,
                             const char *search, size_t search_len);
static int search_in_struct_unions(const struct _cffi_type_context_s *ctx,
                                   const char *search, size_t search_len);
#endif

/* this block of #ifs should be kept exactly identical between
   c/_cffi_backend.c, cffi/vengine_cpy.py, cffi/vengine_gen.py
   and cffi/_cffi_include.h */
#if defined(_MSC_VER)
# include <malloc.h>   /* for alloca() */
# if _MSC_VER < 1600   /* MSVC < 2010 */
   typedef __int8 int8_t;
   typedef __int16 int16_t;
   typedef __int32 int32_t;
   typedef __int64 int64_t;
   typedef unsigned __int8 uint8_t;
   typedef unsigned __int16 uint16_t;
   typedef unsigned __int32 uint32_t;
   typedef unsigned __int64 uint64_t;
   typedef __int8 int_least8_t;
   typedef __int16 int_least16_t;
   typedef __int32 int_least32_t;
   typedef __int64 int_least64_t;
   typedef unsigned __int8 uint_least8_t;
   typedef unsigned __int16 uint_least16_t;
   typedef unsigned __int32 uint_least32_t;
   typedef unsigned __int64 uint_least64_t;
   typedef __int8 int_fast8_t;
   typedef __int16 int_fast16_t;
   typedef __int32 int_fast32_t;
   typedef __int64 int_fast64_t;
   typedef unsigned __int8 uint_fast8_t;
   typedef unsigned __int16 uint_fast16_t;
   typedef unsigned __int32 uint_fast32_t;
   typedef unsigned __int64 uint_fast64_t;
   typedef __int64 intmax_t;
   typedef unsigned __int64 uintmax_t;
# else
#  include <stdint.h>
# endif
# if _MSC_VER < 1800   /* MSVC < 2013 */
   typedef unsigned char _Bool;
# endif
#else
# include <stdint.h>
# if (defined (__SVR4) && defined (__sun)) || defined(_AIX) || defined(__hpux)
#  include <alloca.h>
# endif
#endif

#ifdef __GNUC__
# define _CFFI_UNUSED_FN  __attribute__((unused))
#else
# define _CFFI_UNUSED_FN  /* nothing */
#endif

#ifdef __cplusplus
# ifndef _Bool
#  define _Bool bool   /* semi-hackish: C++ has no _Bool; bool is builtin */
# endif
#endif

/**********  CPython-specific section  **********/
#ifndef PYPY_VERSION


#if PY_MAJOR_VERSION >= 3
# define PyInt_FromLong PyLong_FromLong
#endif

#define _cffi_from_c_double PyFloat_FromDouble
#define _cffi_from_c_float PyFloat_FromDouble
#define _cffi_from_c_long PyInt_FromLong
#define _cffi_from_c_ulong PyLong_FromUnsignedLong
#define _cffi_from_c_longlong PyLong_FromLongLong
#define _cffi_from_c_ulonglong PyLong_FromUnsignedLongLong

#define _cffi_to_c_double PyFloat_AsDouble
#define _cffi_to_c_float PyFloat_AsDouble

#define _cffi_from_c_int(x, type)                                        \
    (((type)-1) > 0 ? /* unsigned */                                     \
        (sizeof(type) < sizeof(long) ?                                   \
            PyInt_FromLong((long)x) :                                    \
         sizeof(type) == sizeof(long) ?                                  \
            PyLong_FromUnsignedLong((unsigned long)x) :                  \
            PyLong_FromUnsignedLongLong((unsigned long long)x)) :        \
        (sizeof(type) <= sizeof(long) ?                                  \
            PyInt_FromLong((long)x) :                                    \
            PyLong_FromLongLong((long long)x)))

#define _cffi_to_c_int(o, type)                                          \
    ((type)(                                                             \
     sizeof(type) == 1 ? (((type)-1) > 0 ? (type)_cffi_to_c_u8(o)        \
                                         : (type)_cffi_to_c_i8(o)) :     \
     sizeof(type) == 2 ? (((type)-1) > 0 ? (type)_cffi_to_c_u16(o)       \
                                         : (type)_cffi_to_c_i16(o)) :    \
     sizeof(type) == 4 ? (((type)-1) > 0 ? (type)_cffi_to_c_u32(o)       \
                                         : (type)_cffi_to_c_i32(o)) :    \
     sizeof(type) == 8 ? (((type)-1) > 0 ? (type)_cffi_to_c_u64(o)       \
                                         : (type)_cffi_to_c_i64(o)) :    \
     (Py_FatalError("unsupported size for type " #type), (type)0)))

#define _cffi_to_c_i8                                                    \
                 ((int(*)(PyObject *))_cffi_exports[1])
#define _cffi_to_c_u8                                                    \
                 ((int(*)(PyObject *))_cffi_exports[2])
#define _cffi_to_c_i16                                                   \
                 ((int(*)(PyObject *))_cffi_exports[3])
#define _cffi_to_c_u16                                                   \
                 ((int(*)(PyObject *))_cffi_exports[4])
#define _cffi_to_c_i32                                                   \
                 ((int(*)(PyObject *))_cffi_exports[5])
#define _cffi_to_c_u32                                                   \
                 ((unsigned int(*)(PyObject *))_cffi_exports[6])
#define _cffi_to_c_i64                                                   \
                 ((long long(*)(PyObject *))_cffi_exports[7])
#define _cffi_to_c_u64                                                   \
                 ((unsigned long long(*)(PyObject *))_cffi_exports[8])
#define _cffi_to_c_char                                                  \
                 ((int(*)(PyObject *))_cffi_exports[9])
#define _cffi_from_c_pointer                                             \
    ((PyObject *(*)(char *, CTypeDescrObject *))_cffi_exports[10])
#define _cffi_to_c_pointer                                               \
    ((char *(*)(PyObject *, CTypeDescrObject *))_cffi_exports[11])
#define _cffi_get_struct_layout                                          \
    not used any more
#define _cffi_restore_errno                                              \
    ((void(*)(void))_cffi_exports[13])
#define _cffi_save_errno                                                 \
    ((void(*)(void))_cffi_exports[14])
#define _cffi_from_c_char                                                \
    ((PyObject *(*)(char))_cffi_exports[15])
#define _cffi_from_c_deref                                               \
    ((PyObject *(*)(char *, CTypeDescrObject *))_cffi_exports[16])
#define _cffi_to_c                                                       \
    ((int(*)(char *, CTypeDescrObject *, PyObject *))_cffi_exports[17])
#define _cffi_from_c_struct                                              \
    ((PyObject *(*)(char *, CTypeDescrObject *))_cffi_exports[18])
#define _cffi_to_c_wchar_t                                               \
    ((wchar_t(*)(PyObject *))_cffi_exports[19])
#define _cffi_from_c_wchar_t                                             \
    ((PyObject *(*)(wchar_t))_cffi_exports[20])
#define _cffi_to_c_long_double                                           \
    ((long double(*)(PyObject *))_cffi_exports[21])
#define _cffi_to_c__Bool                                                 \
    ((_Bool(*)(PyObject *))_cffi_exports[22])
#define _cffi_prepare_pointer_call_argument                              \
    ((Py_ssize_t(*)(CTypeDescrObject *, PyObject *, char **))_cffi_exports[23])
#define _cffi_convert_array_from_object                                  \
    ((int(*)(char *, CTypeDescrObject *, PyObject *))_cffi_exports[24])
#define _CFFI_CPIDX  25
#define _cffi_call_python                                                \
    ((void(*)(struct _cffi_externpy_s *, char *))_cffi_exports[_CFFI_CPIDX])
#define _CFFI_NUM_EXPORTS 26

typedef struct _ctypedescr CTypeDescrObject;

static void *_cffi_exports[_CFFI_NUM_EXPORTS];

#define _cffi_type(index)   (                           \
    assert((((uintptr_t)_cffi_types[index]) & 1) == 0), \
    (CTypeDescrObject *)_cffi_types[index])

static PyObject *_cffi_init(const char *module_name, Py_ssize_t version,
                            const struct _cffi_type_context_s *ctx)
{
    PyObject *module, *o_arg, *new_module;
    void *raw[] = {
        (void *)module_name,
        (void *)version,
        (void *)_cffi_exports,
        (void *)ctx,
    };

    module = PyImport_ImportModule("_cffi_backend");
    if (module == NULL)
        goto failure;

    o_arg = PyLong_FromVoidPtr((void *)raw);
    if (o_arg == NULL)
        goto failure;

    new_module = PyObject_CallMethod(
        module, (char *)"_init_cffi_1_0_external_module", (char *)"O", o_arg);

    Py_DECREF(o_arg);
    Py_DECREF(module);
    return new_module;

  failure:
    Py_XDECREF(module);
    return NULL;
}

_CFFI_UNUSED_FN
static PyObject **_cffi_unpack_args(PyObject *args_tuple, Py_ssize_t expected,
                                    const char *fnname)
{
    if (PyTuple_GET_SIZE(args_tuple) != expected) {
        PyErr_Format(PyExc_TypeError,
                     "%.150s() takes exactly %zd arguments (%zd given)",
                     fnname, expected, PyTuple_GET_SIZE(args_tuple));
        return NULL;
    }
    return &PyTuple_GET_ITEM(args_tuple, 0);   /* pointer to the first item,
                                                  the others follow */
}

/**********  end CPython-specific section  **********/
#else
_CFFI_UNUSED_FN
static void (*_cffi_call_python_org)(struct _cffi_externpy_s *, char *);
# define _cffi_call_python  _cffi_call_python_org
#endif


#define _cffi_array_len(array)   (sizeof(array) / sizeof((array)[0]))

#define _cffi_prim_int(size, sign)                                      \
    ((size) == 1 ? ((sign) ? _CFFI_PRIM_INT8  : _CFFI_PRIM_UINT8)  :    \
     (size) == 2 ? ((sign) ? _CFFI_PRIM_INT16 : _CFFI_PRIM_UINT16) :    \
     (size) == 4 ? ((sign) ? _CFFI_PRIM_INT32 : _CFFI_PRIM_UINT32) :    \
     (size) == 8 ? ((sign) ? _CFFI_PRIM_INT64 : _CFFI_PRIM_UINT64) :    \
     _CFFI__UNKNOWN_PRIM)

#define _cffi_prim_float(size)                                          \
    ((size) == sizeof(float) ? _CFFI_PRIM_FLOAT :                       \
     (size) == sizeof(double) ? _CFFI_PRIM_DOUBLE :                     \
     (size) == sizeof(long double) ? _CFFI__UNKNOWN_LONG_DOUBLE :       \
     _CFFI__UNKNOWN_FLOAT_PRIM)

#define _cffi_check_int(got, got_nonpos, expected)      \
    ((got_nonpos) == (expected <= 0) &&                 \
     (got) == (unsigned long long)expected)

#ifdef MS_WIN32
# define _cffi_stdcall  __stdcall
#else
# define _cffi_stdcall  /* nothing */
#endif

#ifdef __cplusplus
}
#endif

/************************************************************/


    #include <math.h>
    #include "dopri.h"

    void c_gravity(int *n, double *x, double *y, double *f, double *rpar, int *ipar) {
        double r = sqrt(y[0] * y[0] + y[1] * y[1] + y[2] * y[2]);
        double r3 = r*r*r;
        f[0] = y[3];
        f[1] = y[4];
        f[2] = y[5];
        f[3] = -rpar[0] * y[0] / r3;
        f[4] = -rpar[0] * y[1] / r3;
        f[5] = -rpar[0] * y[2] / r3;
    }
    

/************************************************************/

static void *_cffi_types[] = {
/*  0 */ _CFFI_OP(_CFFI_OP_FUNCTION, 43), // void()(int *, double *, double *, double *, double *, int *)
/*  1 */ _CFFI_OP(_CFFI_OP_POINTER, 42), // int *
/*  2 */ _CFFI_OP(_CFFI_OP_POINTER, 41), // double *
/*  3 */ _CFFI_OP(_CFFI_OP_NOOP, 2),
/*  4 */ _CFFI_OP(_CFFI_OP_NOOP, 2),
/*  5 */ _CFFI_OP(_CFFI_OP_NOOP, 2),
/*  6 */ _CFFI_OP(_CFFI_OP_NOOP, 1),
/*  7 */ _CFFI_OP(_CFFI_OP_FUNCTION_END, 0),
/*  8 */ _CFFI_OP(_CFFI_OP_FUNCTION, 43), // void()(int *, double *, double *, double *, int *, double *, int *, int *, double *, int *, int *, double *)
/*  9 */ _CFFI_OP(_CFFI_OP_NOOP, 1),
/* 10 */ _CFFI_OP(_CFFI_OP_NOOP, 2),
/* 11 */ _CFFI_OP(_CFFI_OP_NOOP, 2),
/* 12 */ _CFFI_OP(_CFFI_OP_NOOP, 2),
/* 13 */ _CFFI_OP(_CFFI_OP_NOOP, 1),
/* 14 */ _CFFI_OP(_CFFI_OP_NOOP, 2),
/* 15 */ _CFFI_OP(_CFFI_OP_NOOP, 1),
/* 16 */ _CFFI_OP(_CFFI_OP_NOOP, 1),
/* 17 */ _CFFI_OP(_CFFI_OP_NOOP, 2),
/* 18 */ _CFFI_OP(_CFFI_OP_NOOP, 1),
/* 19 */ _CFFI_OP(_CFFI_OP_NOOP, 1),
/* 20 */ _CFFI_OP(_CFFI_OP_NOOP, 2),
/* 21 */ _CFFI_OP(_CFFI_OP_FUNCTION_END, 0),
/* 22 */ _CFFI_OP(_CFFI_OP_FUNCTION, 43), // void()(int *, void(*)(int *, double *, double *, double *, double *, int *), double *, double *, double *, double *, double *, int *, void(*)(int *, double *, double *, double *, int *, double *, int *, int *, double *, int *, int *, double *), int *, double *, int *, int *, int *, double *, int *, int *)
/* 23 */ _CFFI_OP(_CFFI_OP_NOOP, 1),
/* 24 */ _CFFI_OP(_CFFI_OP_POINTER, 0), // void(*)(int *, double *, double *, double *, double *, int *)
/* 25 */ _CFFI_OP(_CFFI_OP_NOOP, 2),
/* 26 */ _CFFI_OP(_CFFI_OP_NOOP, 2),
/* 27 */ _CFFI_OP(_CFFI_OP_NOOP, 2),
/* 28 */ _CFFI_OP(_CFFI_OP_NOOP, 2),
/* 29 */ _CFFI_OP(_CFFI_OP_NOOP, 2),
/* 30 */ _CFFI_OP(_CFFI_OP_NOOP, 1),
/* 31 */ _CFFI_OP(_CFFI_OP_POINTER, 8), // void(*)(int *, double *, double *, double *, int *, double *, int *, int *, double *, int *, int *, double *)
/* 32 */ _CFFI_OP(_CFFI_OP_NOOP, 1),
/* 33 */ _CFFI_OP(_CFFI_OP_NOOP, 2),
/* 34 */ _CFFI_OP(_CFFI_OP_NOOP, 1),
/* 35 */ _CFFI_OP(_CFFI_OP_NOOP, 1),
/* 36 */ _CFFI_OP(_CFFI_OP_NOOP, 1),
/* 37 */ _CFFI_OP(_CFFI_OP_NOOP, 2),
/* 38 */ _CFFI_OP(_CFFI_OP_NOOP, 1),
/* 39 */ _CFFI_OP(_CFFI_OP_NOOP, 1),
/* 40 */ _CFFI_OP(_CFFI_OP_FUNCTION_END, 0),
/* 41 */ _CFFI_OP(_CFFI_OP_PRIMITIVE, 14), // double
/* 42 */ _CFFI_OP(_CFFI_OP_PRIMITIVE, 7), // int
/* 43 */ _CFFI_OP(_CFFI_OP_PRIMITIVE, 0), // void
};

static struct _cffi_externpy_s _cffi_externpy__gravity =
  { "gravity", 0 };

static void gravity(int * a0, double * a1, double * a2, double * a3, double * a4, int * a5)
{
  char a[48];
  char *p = a;
  *(int * *)(p + 0) = a0;
  *(double * *)(p + 8) = a1;
  *(double * *)(p + 16) = a2;
  *(double * *)(p + 24) = a3;
  *(double * *)(p + 32) = a4;
  *(int * *)(p + 40) = a5;
  _cffi_call_python(&_cffi_externpy__gravity, p);
}

static struct _cffi_externpy_s _cffi_externpy__solout =
  { "solout", 0 };

static void solout(int * a0, double * a1, double * a2, double * a3, int * a4, double * a5, int * a6, int * a7, double * a8, int * a9, int * a10, double * a11)
{
  char a[96];
  char *p = a;
  *(int * *)(p + 0) = a0;
  *(double * *)(p + 8) = a1;
  *(double * *)(p + 16) = a2;
  *(double * *)(p + 24) = a3;
  *(int * *)(p + 32) = a4;
  *(double * *)(p + 40) = a5;
  *(int * *)(p + 48) = a6;
  *(int * *)(p + 56) = a7;
  *(double * *)(p + 64) = a8;
  *(int * *)(p + 72) = a9;
  *(int * *)(p + 80) = a10;
  *(double * *)(p + 88) = a11;
  _cffi_call_python(&_cffi_externpy__solout, p);
}

static void _cffi_d_c_dop853(int * x0, void(* x1)(int *, double *, double *, double *, double *, int *), double * x2, double * x3, double * x4, double * x5, double * x6, int * x7, void(* x8)(int *, double *, double *, double *, int *, double *, int *, int *, double *, int *, int *, double *), int * x9, double * x10, int * x11, int * x12, int * x13, double * x14, int * x15, int * x16)
{
  c_dop853(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16);
}
#ifndef PYPY_VERSION
static PyObject *
_cffi_f_c_dop853(PyObject *self, PyObject *args)
{
  int * x0;
  void(* x1)(int *, double *, double *, double *, double *, int *);
  double * x2;
  double * x3;
  double * x4;
  double * x5;
  double * x6;
  int * x7;
  void(* x8)(int *, double *, double *, double *, int *, double *, int *, int *, double *, int *, int *, double *);
  int * x9;
  double * x10;
  int * x11;
  int * x12;
  int * x13;
  double * x14;
  int * x15;
  int * x16;
  Py_ssize_t datasize;
  PyObject *arg0;
  PyObject *arg1;
  PyObject *arg2;
  PyObject *arg3;
  PyObject *arg4;
  PyObject *arg5;
  PyObject *arg6;
  PyObject *arg7;
  PyObject *arg8;
  PyObject *arg9;
  PyObject *arg10;
  PyObject *arg11;
  PyObject *arg12;
  PyObject *arg13;
  PyObject *arg14;
  PyObject *arg15;
  PyObject *arg16;
  PyObject **aa;

  aa = _cffi_unpack_args(args, 17, "c_dop853");
  if (aa == NULL)
    return NULL;
  arg0 = aa[0];
  arg1 = aa[1];
  arg2 = aa[2];
  arg3 = aa[3];
  arg4 = aa[4];
  arg5 = aa[5];
  arg6 = aa[6];
  arg7 = aa[7];
  arg8 = aa[8];
  arg9 = aa[9];
  arg10 = aa[10];
  arg11 = aa[11];
  arg12 = aa[12];
  arg13 = aa[13];
  arg14 = aa[14];
  arg15 = aa[15];
  arg16 = aa[16];

  datasize = _cffi_prepare_pointer_call_argument(
      _cffi_type(1), arg0, (char **)&x0);
  if (datasize != 0) {
    if (datasize < 0)
      return NULL;
    x0 = (int *)alloca((size_t)datasize);
    memset((void *)x0, 0, (size_t)datasize);
    if (_cffi_convert_array_from_object((char *)x0, _cffi_type(1), arg0) < 0)
      return NULL;
  }

  x1 = (void(*)(int *, double *, double *, double *, double *, int *))_cffi_to_c_pointer(arg1, _cffi_type(24));
  if (x1 == (void(*)(int *, double *, double *, double *, double *, int *))NULL && PyErr_Occurred())
    return NULL;

  datasize = _cffi_prepare_pointer_call_argument(
      _cffi_type(2), arg2, (char **)&x2);
  if (datasize != 0) {
    if (datasize < 0)
      return NULL;
    x2 = (double *)alloca((size_t)datasize);
    memset((void *)x2, 0, (size_t)datasize);
    if (_cffi_convert_array_from_object((char *)x2, _cffi_type(2), arg2) < 0)
      return NULL;
  }

  datasize = _cffi_prepare_pointer_call_argument(
      _cffi_type(2), arg3, (char **)&x3);
  if (datasize != 0) {
    if (datasize < 0)
      return NULL;
    x3 = (double *)alloca((size_t)datasize);
    memset((void *)x3, 0, (size_t)datasize);
    if (_cffi_convert_array_from_object((char *)x3, _cffi_type(2), arg3) < 0)
      return NULL;
  }

  datasize = _cffi_prepare_pointer_call_argument(
      _cffi_type(2), arg4, (char **)&x4);
  if (datasize != 0) {
    if (datasize < 0)
      return NULL;
    x4 = (double *)alloca((size_t)datasize);
    memset((void *)x4, 0, (size_t)datasize);
    if (_cffi_convert_array_from_object((char *)x4, _cffi_type(2), arg4) < 0)
      return NULL;
  }

  datasize = _cffi_prepare_pointer_call_argument(
      _cffi_type(2), arg5, (char **)&x5);
  if (datasize != 0) {
    if (datasize < 0)
      return NULL;
    x5 = (double *)alloca((size_t)datasize);
    memset((void *)x5, 0, (size_t)datasize);
    if (_cffi_convert_array_from_object((char *)x5, _cffi_type(2), arg5) < 0)
      return NULL;
  }

  datasize = _cffi_prepare_pointer_call_argument(
      _cffi_type(2), arg6, (char **)&x6);
  if (datasize != 0) {
    if (datasize < 0)
      return NULL;
    x6 = (double *)alloca((size_t)datasize);
    memset((void *)x6, 0, (size_t)datasize);
    if (_cffi_convert_array_from_object((char *)x6, _cffi_type(2), arg6) < 0)
      return NULL;
  }

  datasize = _cffi_prepare_pointer_call_argument(
      _cffi_type(1), arg7, (char **)&x7);
  if (datasize != 0) {
    if (datasize < 0)
      return NULL;
    x7 = (int *)alloca((size_t)datasize);
    memset((void *)x7, 0, (size_t)datasize);
    if (_cffi_convert_array_from_object((char *)x7, _cffi_type(1), arg7) < 0)
      return NULL;
  }

  x8 = (void(*)(int *, double *, double *, double *, int *, double *, int *, int *, double *, int *, int *, double *))_cffi_to_c_pointer(arg8, _cffi_type(31));
  if (x8 == (void(*)(int *, double *, double *, double *, int *, double *, int *, int *, double *, int *, int *, double *))NULL && PyErr_Occurred())
    return NULL;

  datasize = _cffi_prepare_pointer_call_argument(
      _cffi_type(1), arg9, (char **)&x9);
  if (datasize != 0) {
    if (datasize < 0)
      return NULL;
    x9 = (int *)alloca((size_t)datasize);
    memset((void *)x9, 0, (size_t)datasize);
    if (_cffi_convert_array_from_object((char *)x9, _cffi_type(1), arg9) < 0)
      return NULL;
  }

  datasize = _cffi_prepare_pointer_call_argument(
      _cffi_type(2), arg10, (char **)&x10);
  if (datasize != 0) {
    if (datasize < 0)
      return NULL;
    x10 = (double *)alloca((size_t)datasize);
    memset((void *)x10, 0, (size_t)datasize);
    if (_cffi_convert_array_from_object((char *)x10, _cffi_type(2), arg10) < 0)
      return NULL;
  }

  datasize = _cffi_prepare_pointer_call_argument(
      _cffi_type(1), arg11, (char **)&x11);
  if (datasize != 0) {
    if (datasize < 0)
      return NULL;
    x11 = (int *)alloca((size_t)datasize);
    memset((void *)x11, 0, (size_t)datasize);
    if (_cffi_convert_array_from_object((char *)x11, _cffi_type(1), arg11) < 0)
      return NULL;
  }

  datasize = _cffi_prepare_pointer_call_argument(
      _cffi_type(1), arg12, (char **)&x12);
  if (datasize != 0) {
    if (datasize < 0)
      return NULL;
    x12 = (int *)alloca((size_t)datasize);
    memset((void *)x12, 0, (size_t)datasize);
    if (_cffi_convert_array_from_object((char *)x12, _cffi_type(1), arg12) < 0)
      return NULL;
  }

  datasize = _cffi_prepare_pointer_call_argument(
      _cffi_type(1), arg13, (char **)&x13);
  if (datasize != 0) {
    if (datasize < 0)
      return NULL;
    x13 = (int *)alloca((size_t)datasize);
    memset((void *)x13, 0, (size_t)datasize);
    if (_cffi_convert_array_from_object((char *)x13, _cffi_type(1), arg13) < 0)
      return NULL;
  }

  datasize = _cffi_prepare_pointer_call_argument(
      _cffi_type(2), arg14, (char **)&x14);
  if (datasize != 0) {
    if (datasize < 0)
      return NULL;
    x14 = (double *)alloca((size_t)datasize);
    memset((void *)x14, 0, (size_t)datasize);
    if (_cffi_convert_array_from_object((char *)x14, _cffi_type(2), arg14) < 0)
      return NULL;
  }

  datasize = _cffi_prepare_pointer_call_argument(
      _cffi_type(1), arg15, (char **)&x15);
  if (datasize != 0) {
    if (datasize < 0)
      return NULL;
    x15 = (int *)alloca((size_t)datasize);
    memset((void *)x15, 0, (size_t)datasize);
    if (_cffi_convert_array_from_object((char *)x15, _cffi_type(1), arg15) < 0)
      return NULL;
  }

  datasize = _cffi_prepare_pointer_call_argument(
      _cffi_type(1), arg16, (char **)&x16);
  if (datasize != 0) {
    if (datasize < 0)
      return NULL;
    x16 = (int *)alloca((size_t)datasize);
    memset((void *)x16, 0, (size_t)datasize);
    if (_cffi_convert_array_from_object((char *)x16, _cffi_type(1), arg16) < 0)
      return NULL;
  }

  Py_BEGIN_ALLOW_THREADS
  _cffi_restore_errno();
  { c_dop853(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16); }
  _cffi_save_errno();
  Py_END_ALLOW_THREADS

  (void)self; /* unused */
  Py_INCREF(Py_None);
  return Py_None;
}
#else
#  define _cffi_f_c_dop853 _cffi_d_c_dop853
#endif

static void _cffi_d_c_gravity(int * x0, double * x1, double * x2, double * x3, double * x4, int * x5)
{
  c_gravity(x0, x1, x2, x3, x4, x5);
}
#ifndef PYPY_VERSION
static PyObject *
_cffi_f_c_gravity(PyObject *self, PyObject *args)
{
  int * x0;
  double * x1;
  double * x2;
  double * x3;
  double * x4;
  int * x5;
  Py_ssize_t datasize;
  PyObject *arg0;
  PyObject *arg1;
  PyObject *arg2;
  PyObject *arg3;
  PyObject *arg4;
  PyObject *arg5;
  PyObject **aa;

  aa = _cffi_unpack_args(args, 6, "c_gravity");
  if (aa == NULL)
    return NULL;
  arg0 = aa[0];
  arg1 = aa[1];
  arg2 = aa[2];
  arg3 = aa[3];
  arg4 = aa[4];
  arg5 = aa[5];

  datasize = _cffi_prepare_pointer_call_argument(
      _cffi_type(1), arg0, (char **)&x0);
  if (datasize != 0) {
    if (datasize < 0)
      return NULL;
    x0 = (int *)alloca((size_t)datasize);
    memset((void *)x0, 0, (size_t)datasize);
    if (_cffi_convert_array_from_object((char *)x0, _cffi_type(1), arg0) < 0)
      return NULL;
  }

  datasize = _cffi_prepare_pointer_call_argument(
      _cffi_type(2), arg1, (char **)&x1);
  if (datasize != 0) {
    if (datasize < 0)
      return NULL;
    x1 = (double *)alloca((size_t)datasize);
    memset((void *)x1, 0, (size_t)datasize);
    if (_cffi_convert_array_from_object((char *)x1, _cffi_type(2), arg1) < 0)
      return NULL;
  }

  datasize = _cffi_prepare_pointer_call_argument(
      _cffi_type(2), arg2, (char **)&x2);
  if (datasize != 0) {
    if (datasize < 0)
      return NULL;
    x2 = (double *)alloca((size_t)datasize);
    memset((void *)x2, 0, (size_t)datasize);
    if (_cffi_convert_array_from_object((char *)x2, _cffi_type(2), arg2) < 0)
      return NULL;
  }

  datasize = _cffi_prepare_pointer_call_argument(
      _cffi_type(2), arg3, (char **)&x3);
  if (datasize != 0) {
    if (datasize < 0)
      return NULL;
    x3 = (double *)alloca((size_t)datasize);
    memset((void *)x3, 0, (size_t)datasize);
    if (_cffi_convert_array_from_object((char *)x3, _cffi_type(2), arg3) < 0)
      return NULL;
  }

  datasize = _cffi_prepare_pointer_call_argument(
      _cffi_type(2), arg4, (char **)&x4);
  if (datasize != 0) {
    if (datasize < 0)
      return NULL;
    x4 = (double *)alloca((size_t)datasize);
    memset((void *)x4, 0, (size_t)datasize);
    if (_cffi_convert_array_from_object((char *)x4, _cffi_type(2), arg4) < 0)
      return NULL;
  }

  datasize = _cffi_prepare_pointer_call_argument(
      _cffi_type(1), arg5, (char **)&x5);
  if (datasize != 0) {
    if (datasize < 0)
      return NULL;
    x5 = (int *)alloca((size_t)datasize);
    memset((void *)x5, 0, (size_t)datasize);
    if (_cffi_convert_array_from_object((char *)x5, _cffi_type(1), arg5) < 0)
      return NULL;
  }

  Py_BEGIN_ALLOW_THREADS
  _cffi_restore_errno();
  { c_gravity(x0, x1, x2, x3, x4, x5); }
  _cffi_save_errno();
  Py_END_ALLOW_THREADS

  (void)self; /* unused */
  Py_INCREF(Py_None);
  return Py_None;
}
#else
#  define _cffi_f_c_gravity _cffi_d_c_gravity
#endif

static const struct _cffi_global_s _cffi_globals[] = {
  { "c_dop853", (void *)_cffi_f_c_dop853, _CFFI_OP(_CFFI_OP_CPYTHON_BLTN_V, 22), (void *)_cffi_d_c_dop853 },
  { "c_gravity", (void *)_cffi_f_c_gravity, _CFFI_OP(_CFFI_OP_CPYTHON_BLTN_V, 0), (void *)_cffi_d_c_gravity },
  { "gravity", (void *)&_cffi_externpy__gravity, _CFFI_OP(_CFFI_OP_EXTERN_PYTHON, 24), (void *)gravity },
  { "solout", (void *)&_cffi_externpy__solout, _CFFI_OP(_CFFI_OP_EXTERN_PYTHON, 31), (void *)solout },
};

static const struct _cffi_type_context_s _cffi_type_context = {
  _cffi_types,
  _cffi_globals,
  NULL,  /* no fields */
  NULL,  /* no struct_unions */
  NULL,  /* no enums */
  NULL,  /* no typenames */
  4,  /* num_globals */
  0,  /* num_struct_unions */
  0,  /* num_enums */
  0,  /* num_typenames */
  NULL,  /* no includes */
  44,  /* num_types */
  1,  /* flags */
};

#ifdef PYPY_VERSION
PyMODINIT_FUNC
_cffi_pypyinit__dopri(const void *p[])
{
    if (((intptr_t)p[0]) >= 0x0A03) {
        _cffi_call_python_org = (void(*)(struct _cffi_externpy_s *, char *))p[1];
    }
    p[0] = (const void *)0x2601;
    p[1] = &_cffi_type_context;
}
#  ifdef _MSC_VER
     PyMODINIT_FUNC
#  if PY_MAJOR_VERSION >= 3
     PyInit__dopri(void) { return NULL; }
#  else
     init_dopri(void) { }
#  endif
#  endif
#elif PY_MAJOR_VERSION >= 3
PyMODINIT_FUNC
PyInit__dopri(void)
{
  return _cffi_init("_dopri", 0x2601, &_cffi_type_context);
}
#else
PyMODINIT_FUNC
init_dopri(void)
{
  _cffi_init("_dopri", 0x2601, &_cffi_type_context);
}
#endif