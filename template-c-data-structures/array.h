#ifndef ARRAY_H
#define ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <memory.h>

#define _DEFINE_ARRAY_INIT_FUN(type, size)                                                                                      \
    inline void _array_##type##_##size##_init(array_##type##_##size* obj) {                                                     \
        assert(obj != NULL);                                                                                                    \
        obj->_size = (size);                                                                                                    \
        memset(obj->_buffer, (type)0, (size) * sizeof(type));                                                                   \
    }

#define _DEFINE_ARRAY_INIT_DEFAULT_VALUE_FUN(type, size)                                                                        \
    inline void _array_##type##_##size##_value_init(array_##type##_##size* obj, type value) {                                   \
        assert(obj != NULL);                                                                                                    \
        obj->_size = (size);                                                                                                    \
        for (size_t i = 0; i < obj->_size; ++i) {                                                                               \
            obj->_buffer[i] = value;                                                                                            \
        }                                                                                                                       \
    }

#define _DEFINE_ARRAY_AT_FUN(type, size)                                                                                        \
    inline type* _array_##type##_##size##_at(array_##type##_##size* obj, size_t index) {                                        \
        assert(obj != NULL);                                                                                                    \
        assert(index < obj->_size);                                                                                             \
        return &(obj->_buffer[index]);                                                                                          \
    }

#define _DEFINE_ARRAY_SIZE_FUN(type, size)                                                                                      \
    inline size_t _array_##type##_##size##_size(const array_##type##_##size* obj) {                                             \
        assert(obj != NULL);                                                                                                    \
        return obj->_size;                                                                                                      \
    }

#define _DEFINE_ARRAY_EMPTY_FUN(type, size)                                                                                     \
    inline int8_t _array_##type##_##size##_empty(const array_##type##_##size* obj) {                                            \
        assert(obj != NULL);                                                                                                    \
        return obj->_size == 0;                                                                                                 \
    }

#define _DEFINE_ARRAY_ASSIGN_FUN(type, size)                                                                                    \
    inline void _array_##type##_##size##_assign(array_##type##_##size* dist, const array_##type##_##size* src) {                \
        assert(dist != NULL);                                                                                                   \
        assert(src != NULL);                                                                                                    \
        memcpy_s(dist->_buffer, (size) * sizeof(type), src->_buffer, (size) * sizeof(type));                                    \
    }

#define _DEFINE_ARRAY_FILL_FUN(type, size)                                                                                      \
    inline void _array_##type##_##size##_fill(array_##type##_##size* obj, type value) {                                         \
        assert(obj != NULL);                                                                                                    \
        for (size_t i = 0; i < obj->_size; ++i) {                                                                               \
            obj->_buffer[i] = value;                                                                                            \
        }                                                                                                                       \
    }

#define _DEFINE_ARRAY_DATA_FUN(type, size)                                                                                      \
    inline type* _array_##type##_##size##_data(const array_##type##_##size* obj) {                                              \
        return obj != NULL ? obj->_buffer : NULL;                                                                               \
    }

#define _DEFINE_ARRAY_BEGIN_FUN(type, size)                                                                                     \
    inline const type* _array_##type##_##size##_begin(const array_##type##_##size* obj) {                                       \
        return obj != NULL ? obj->_buffer : NULL;                                                                               \
    }

#define _DEFINE_ARRAY_END_FUN(type, size)                                                                                       \
    inline const type* _array_##type##_##size##_end(const array_##type##_##size* obj) {                                         \
        return obj != NULL ? obj->_buffer + (size) : NULL;                                                                      \
    }

#define DEFINE_TYPED_ARRAY(type, size)                                                                                          \
    typedef struct array_##type##_##size {                                                                                      \
        type _buffer[(size)];                                                                                                   \
        size_t _size;                                                                                                           \
    } array_##type##_##size;                                                                                                    \
    \
    _DEFINE_ARRAY_INIT_FUN(type, size);                                                                                         \
    _DEFINE_ARRAY_INIT_DEFAULT_VALUE_FUN(type, size);                                                                           \
    _DEFINE_ARRAY_AT_FUN(type, size);                                                                                           \
    _DEFINE_ARRAY_SIZE_FUN(type, size);                                                                                         \
    _DEFINE_ARRAY_EMPTY_FUN(type, size);                                                                                        \
    _DEFINE_ARRAY_ASSIGN_FUN(type, size);                                                                                       \
    _DEFINE_ARRAY_FILL_FUN(type, size);                                                                                         \
    _DEFINE_ARRAY_DATA_FUN(type, size);                                                                                         \
    _DEFINE_ARRAY_BEGIN_FUN(type, size);                                                                                        \
    _DEFINE_ARRAY_END_FUN(type, size);                                                                                          \


#define ARRAY_DECLARE_INSTANCE(type, size, arr_name) array_##type##_##size arr_name
#define ARRAY_DEFAULT_CONSTRUCTOR(type, size, arr_ptr) _array_##type##_##size##_init(arr_ptr)
#define ARRAY_VALUE_CONSTRUCTOR(type, size, arr_ptr, value) _array_##type##_##size##_value_init(arr_ptr, value)
#define ARRAY_AT(type, size, arr_ptr, index) _array_##type##_##size##_at(arr_ptr, index)
#define ARRAY_SIZE(type, size, arr_ptr) _array_##type##_##size##_size(arr_ptr)
#define ARRAY_EMPTY(type, size, arr_ptr) _array_##type##_##size##_empty(arr_ptr)
#define ARRAY_ASSIGN(type, size, arr_ptr_left, arr_ptr_right) _array_##type##_##size##_assign(arr_ptr_left, arr_ptr_right)
#define ARRAY_FILL(type, size, arr_ptr, value) _array_##type##_##size##_fill(arr_ptr, value)
#define ARRAY_DATA(type, size, arr_ptr) _array_##type##_##size##_data(arr_ptr)
#define ARRAY_BEGIN(type, size, arr_ptr) _array_##type##_##size##_begin(arr_ptr)
#define ARRAY_END(type, size, arr_ptr) _array_##type##_##size##_end(arr_ptr)

#define ARRAY_CREATE_ITER(array_type, iter_name) array_type* iter_name
#define ARRAY_ITER_NEXT(iter) (iter + 1)
#define ARRAY_ITER_VALUE(iter) *iter

#ifdef __cplusplus
}
#endif

#endif