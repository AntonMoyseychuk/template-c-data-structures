#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <memory.h>

#include "util_macro.h"

#ifdef __cplusplus
extern "C" {
#endif

#pragma region default-constructor
#define _DEFINE_ARRAY_true_DEFAULT_CONSTRUCTOR(type, size) \
    inline void array_##type##_ptrue##_##size##_default_constr(array_##type##_ptrue##_##size* obj) { \
        assert(obj != NULL); \
        obj->_size = (size); \
        memset(obj->_buffer, (type)0, (size) * sizeof(type)); \
    }

#define _DEFINE_ARRAY_false_DEFAULT_CONSTRUCTOR(type, size) \
    inline void array_##type##_pfalse##_##size##_default_constr(array_##type##_pfalse##_##size* obj) { \
        assert(obj != NULL); \
        obj->_size = (size); \
        memset(obj->_buffer, (type)0, (size) * sizeof(type)); \
    }

#define _DEFINE_ARRAY_DEFAULT_CONSTRUCTOR(type, is_ptr, size) \
    _DEFINE_ARRAY_##is_ptr##_DEFAULT_CONSTRUCTOR(type, size)
#pragma endregion default-constructor

#pragma region value-constructor
#define _DEFINE_ARRAY_true_VALUE_CONSTRUCTOR(type, size) \
    inline void array_##type##_ptrue##_##size##_value_constr(array_##type##_ptrue##_##size* obj, type* value) { \
        assert(obj != NULL); \
        obj->_size = (size); \
        for (size_t i = 0; i < obj->_size; ++i) { \
            obj->_buffer[i] = value; \
        } \
    }

#define _DEFINE_ARRAY_false_VALUE_CONSTRUCTOR(type, size) \
    inline void array_##type##_pfalse##_##size##_value_constr(array_##type##_pfalse##_##size* obj, type value) { \
        assert(obj != NULL); \
        obj->_size = (size); \
        for (size_t i = 0; i < obj->_size; ++i) { \
            obj->_buffer[i] = value; \
        } \
    }

#define _DEFINE_ARRAY_VALUE_CONSTRUCTOR(type, is_ptr, size) \
    _DEFINE_ARRAY_##is_ptr##_VALUE_CONSTRUCTOR(type, size)
#pragma endregion value-constructor

#pragma region at-func
#define _DEFINE_ARRAY_true_AT_FUN(type, size) \
    inline type** array_##type##_ptrue##_##size##_at(array_##type##_ptrue##_##size* obj, size_t index) { \
        assert(obj != NULL); \
        assert(index < obj->_size); \
        return &(obj->_buffer[index]); \
    }

#define _DEFINE_ARRAY_false_AT_FUN(type, size)   \
    inline type* array_##type##_pfalse##_##size##_at(array_##type##_pfalse##_##size* obj, size_t index) { \
        assert(obj != NULL); \
        assert(index < obj->_size); \
        return &(obj->_buffer[index]); \
    }

#define _DEFINE_ARRAY_AT_FUN(type, is_ptr, size) \
    _DEFINE_ARRAY_##is_ptr##_AT_FUN(type, size)
#pragma endregion at-func

#pragma region size-func
#define _DEFINE_ARRAY_true_SIZE_FUN(type, size) \
    inline size_t array_##type##_ptrue##_##size##_size(const array_##type##_ptrue##_##size* obj) { \
        assert(obj != NULL); \
        return obj->_size; \
    }

#define _DEFINE_ARRAY_false_SIZE_FUN(type, size) \
    inline size_t array_##type##_pfalse##_##size##_size(const array_##type##_pfalse##_##size* obj) { \
        assert(obj != NULL); \
        return obj->_size; \
    }

#define _DEFINE_ARRAY_SIZE_FUN(type, is_ptr, size) \
    _DEFINE_ARRAY_##is_ptr##_SIZE_FUN(type, size)
#pragma endregion size-func

#pragma region empty-func
#define _DEFINE_ARRAY_true_EMPTY_FUN(type, size) \
    inline int8_t array_##type##_ptrue##_##size##_empty(const array_##type##_ptrue##_##size* obj) { \
        assert(obj != NULL); \
        return obj->_size == 0; \
    }

#define _DEFINE_ARRAY_false_EMPTY_FUN(type, size) \
    inline int8_t array_##type##_pfalse##_##size##_empty(const array_##type##_pfalse##_##size* obj) { \
        assert(obj != NULL); \
        return obj->_size == 0; \
    }

#define _DEFINE_ARRAY_EMPTY_FUN(type, is_ptr, size) \
    _DEFINE_ARRAY_##is_ptr##_EMPTY_FUN(type, size)
#pragma endregion empty-func

#pragma region assign-func
#define _DEFINE_ARRAY_true_ASSIGN_FUN(type, size) \
    inline void array_##type##_ptrue##_##size##_assign(array_##type##_ptrue##_##size* dist, const array_##type##_ptrue##_##size* src) { \
        assert(dist != NULL); \
        assert(src != NULL); \
        memcpy_s(dist->_buffer, (size) * sizeof(type), src->_buffer, (size) * sizeof(type)); \
    }

#define _DEFINE_ARRAY_false_ASSIGN_FUN(type, size) \
    inline void array_##type##_pfalse##_##size##_assign(array_##type##_pfalse##_##size* dist, const array_##type##_pfalse##_##size* src) { \
        assert(dist != NULL); \
        assert(src != NULL); \
        memcpy_s(dist->_buffer, (size) * sizeof(type), src->_buffer, (size) * sizeof(type)); \
    }

#define _DEFINE_ARRAY_ASSIGN_FUN(type, is_ptr, size) \
    _DEFINE_ARRAY_##is_ptr##_ASSIGN_FUN(type, size)
#pragma endregion assign-func

#pragma region fill-func
#define _DEFINE_ARRAY_true_FILL_FUN(type, size) \
    inline void array_##type##_ptrue##_##size##_fill(array_##type##_ptrue##_##size* obj, type* value) { \
        assert(obj != NULL); \
        for (size_t i = 0; i < obj->_size; ++i) { \
            obj->_buffer[i] = value; \
        } \
    }

#define _DEFINE_ARRAY_false_FILL_FUN(type, size) \
    inline void array_##type##_pfalse##_##size##_fill(array_##type##_pfalse##_##size* obj, type value) { \
        assert(obj != NULL); \
        for (size_t i = 0; i < obj->_size; ++i) { \
            obj->_buffer[i] = value; \
        } \
    }

#define _DEFINE_ARRAY_FILL_FUN(type, is_ptr, size) \
    _DEFINE_ARRAY_##is_ptr##_FILL_FUN(type, size)
#pragma endregion fill-func

#pragma region data-func
#define _DEFINE_ARRAY_true_DATA_FUN(type, size) \
    inline type** array_##type##_ptrue##_##size##_data(const array_##type##_ptrue##_##size* obj) { \
        return (obj != NULL ? obj->_buffer : NULL); \
    }

#define _DEFINE_ARRAY_false_DATA_FUN(type, size) \
    inline type* array_##type##_pfalse##_##size##_data(const array_##type##_pfalse##_##size* obj) { \
        return (obj != NULL ? obj->_buffer : NULL); \
    }

#define _DEFINE_ARRAY_DATA_FUN(type, is_ptr, size) \
    _DEFINE_ARRAY_##is_ptr##_DATA_FUN(type, size)
#pragma endregion data-func

#pragma region begin-func
#define _DEFINE_ARRAY_true_BEGIN_FUN(type, size) \
    inline const type** array_##type##_ptrue##_##size##_begin(const array_##type##_ptrue##_##size* obj) { \
        return (obj != NULL ? obj->_buffer : NULL); \
    }

#define _DEFINE_ARRAY_false_BEGIN_FUN(type, size) \
    inline const type* array_##type##_pfalse##_##size##_begin(const array_##type##_pfalse##_##size* obj) { \
        return (obj != NULL ? obj->_buffer : NULL); \
    }

#define _DEFINE_ARRAY_BEGIN_FUN(type, is_ptr, size) \
    _DEFINE_ARRAY_##is_ptr##_BEGIN_FUN(type, size)
#pragma endregion begin-func

#pragma region end-func
#define _DEFINE_ARRAY_true_END_FUN(type, size) \
    inline const type** array_##type##_ptrue##_##size##_end(const array_##type##_ptrue##_##size* obj) { \
        return (obj != NULL ? obj->_buffer + (size) : NULL); \
    }

#define _DEFINE_ARRAY_false_END_FUN(type, size) \
    inline const type* array_##type##_pfalse##_##size##_end(const array_##type##_pfalse##_##size* obj) { \
        return (obj != NULL ? obj->_buffer + (size) : NULL); \
    }

#define _DEFINE_ARRAY_END_FUN(type, is_ptr, size) \
    _DEFINE_ARRAY_##is_ptr##_END_FUN(type, size)
#pragma endregion end-func

#define DEFINE_TYPED_ARRAY(type, is_ptr, size) \
    typedef struct array_##type##_p##is_ptr##_##size { \
        _DEF_PTR(type, is_ptr) _buffer[(size)]; \
        size_t _size; \
    } array_##type##_p##is_ptr##_##size; \
    \
    _DEFINE_ARRAY_DEFAULT_CONSTRUCTOR(type, is_ptr, size); \
    _DEFINE_ARRAY_VALUE_CONSTRUCTOR(type, is_ptr, size); \
    _DEFINE_ARRAY_AT_FUN(type, is_ptr, size); \
    _DEFINE_ARRAY_SIZE_FUN(type, is_ptr, size); \
    _DEFINE_ARRAY_EMPTY_FUN(type, is_ptr, size); \
    _DEFINE_ARRAY_ASSIGN_FUN(type, is_ptr, size); \
    _DEFINE_ARRAY_FILL_FUN(type, is_ptr, size); \
    _DEFINE_ARRAY_DATA_FUN(type, is_ptr, size); \
    _DEFINE_ARRAY_BEGIN_FUN(type, is_ptr, size); \
    _DEFINE_ARRAY_END_FUN(type, is_ptr, size); \


#ifdef __cplusplus
}
#endif

#endif