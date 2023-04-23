#ifndef VECTOR_H
#define VECTOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <memory.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include <stdio.h>



#define _DEFINE_VECTOR_INIT_FUN(type)                                                           \
    inline void _vector_##type##_init(vector_##type* obj, size_t size) {                         \
        if (obj != NULL) {                                                                      \
            obj->_buffer = (type*)malloc(sizeof(type) * (size > 0 ? size : 1));                 \
            obj->_size = obj->_capacity = size;                                              \
        }                                                                                       \
    }

#define _DEFINE_VECTOR_INIT_ARG_FUN(type)                                                       \
    inline void _vector_##type##_arg_init(vector_##type* obj, size_t size, type value) {         \
        obj->_buffer = (type*)malloc(sizeof(type) * (size > 0 ? size : 1));                  \
        for (size_t i = 0; i < size; ++i) {                                                     \
            obj->_buffer[i] = value;                                                       \
        }                                                                                       \
        obj->_size = obj->_capacity = size;                                             \
    }

#define _DEFINE_VECTOR_FREE_FUN(type)                                                           \
    inline void _vector_##type##_free(const vector_##type* obj) {                               \
        if (obj != NULL) {                                                      \
            free(obj->_buffer);                                                                         \
        }                                                                                       \
    }

#define _DEFINE_VECTOR_AT_FUN(type)                                                             \
    inline type* _vector_##type##_at(vector_##type* obj, size_t index) {                         \
        assert(index < obj->_size);                                                             \
        return &(obj->_buffer[index]);                                                          \
    }

#define _DEFINE_VECTOR_SIZE_FUN(type)                                                           \
    inline size_t _vector_##type##_size(const vector_##type* obj) {                              \
        return (obj != NULL ? obj->_size : 0);                                                  \
    }

#define _DEFINE_VECTOR_CAPACITY_FUN(type)                                                       \
    inline size_t _vector_##type##_capacity(const vector_##type* obj) {                          \
        return (obj != NULL ? obj->_capacity : 0);                                              \
    }

#define _DEFINE_VECTOR_PUSH_BACK_FUN(type)                                                      \
    inline void _vector_##type##_push_back(vector_##type* obj, type value) {                    \
        if (obj != NULL) {                                                                      \
            if (obj->_size >= obj->_capacity) {                                               \
                obj->_capacity = (obj->_capacity + 1) * 1.5f;                                 \
                obj->_buffer = realloc(obj->_buffer, obj->_capacity * sizeof(type));       \
            }                                                                                       \
            obj->_buffer[obj->_size++] = value;                                               \
        }                                                                                       \
    }

#define _DEFINE_VECTOR_POP_BACK_FUN(type)                                                       \
    inline void _vector_##type##_pop_back(vector_##type* obj) {                                  \
        if (obj != NULL && obj->_size > 0) {                                                                   \
            --obj->_size;                                                                       \
        }                                                                                       \
    }

#define _DEFINE_VECTOR_EMPTY_FUN(type)                                                          \
    inline int8_t _vector_##type##_empty(const vector_##type* obj) {                             \
        return (obj != NULL ? obj->_size == 0 : 1);                                                                 \
    }

#define _DEFINE_VECTOR_ERASE_FUN(type)                                                          \
    inline void _vector_##type##_erase(vector_##type* obj, size_t index) {                      \
        if (obj != NULL && obj->_buffer != NULL && obj->_size != 0) {                     \
            if (index < obj->_size) {                                                        \
                memmove_s(obj->_buffer + index, obj->_capacity,                           \
                    obj->_buffer + index + 1, obj->_size - index - 1);                    \
                --obj->_size;                                                                \
            }                                                                                   \
        }                                                                                       \
    }

#define _DEFINE_VECTOR_ASSIGN_FUN(type)                                                         \
    inline void _vector_##type##_assign(vector_##type* dist, const vector_##type* src) {        \
        if (src != NULL && src->_buffer != NULL && src->_capacity != 0) {                       \
            if (dist != NULL) {                                                                \
                free(dist->_buffer);                                                            \
                dist->_size = src->_size;                                                        \
                dist->_capacity = src->_capacity;                                                \
                dist->_buffer = (type*)malloc(dist->_capacity * sizeof(type));                \
                memcpy_s(dist->_buffer, dist->_capacity * sizeof(type),                       \
                    src->_buffer, src->_capacity * sizeof(type));                                                         \
            }                                                                                   \
        }                                                                                       \
    }

#define DEFINE_TYPED_VECTOR(type)                                                               \
    typedef struct vector_##type {                                                              \
        type* _buffer;                                                                          \
        size_t _size;                                                                           \
        size_t _capacity;                                                                       \
    } vector_##type;                                                                            \
    \
    _DEFINE_VECTOR_INIT_FUN(type);                                                              \
    _DEFINE_VECTOR_INIT_ARG_FUN(type);                                                          \
    _DEFINE_VECTOR_FREE_FUN(type);                                                              \
    _DEFINE_VECTOR_AT_FUN(type);                                                                \
    _DEFINE_VECTOR_SIZE_FUN(type);                                                              \
    _DEFINE_VECTOR_CAPACITY_FUN(type);                                                          \
    _DEFINE_VECTOR_PUSH_BACK_FUN(type);                                                         \
    _DEFINE_VECTOR_POP_BACK_FUN(type);                                                          \
    _DEFINE_VECTOR_EMPTY_FUN(type);                                                             \
    _DEFINE_VECTOR_ERASE_FUN(type);                                                             \
    _DEFINE_VECTOR_ASSIGN_FUN(type);                                                            \

#define VEC_CREATE_DEFAULT(type, vec_name, size) vector_##type vec_name; _vector_##type##_init(&vec_name, size)
#define VEC_CREATE(type, vec_name, size, value) vector_##type vec_name; _vector_##type##_arg_init(&vec_name, size, value)
#define VEC_FREE(type, vec_ptr) _vector_##type##_free(vec_ptr)

#define VEC_AT(type, vec_ptr, index) _vector_##type##_at(vec_ptr, index)

#define VEC_SIZE(type, vec_ptr) _vector_##type##_size(vec_ptr)
#define VEC_CAPACITY(type, vec_ptr) _vector_##type##_capacity(vec_ptr)

#define VEC_PUSH_BACK(type, vec_ptr, value) _vector_##type##_push_back(vec_ptr, value)
#define VEC_POP_BACK(type, vec_ptr) _vector_##type##_pop_back(vec_ptr)
#define VEC_ERASE(type, vec_ptr, index) _vector_##type##_erase(vec_ptr, index)
#define VEC_ASSIGN(type, dist_ptr, src_ptr) _vector_##type##_assign(dist_ptr, src_ptr)

#define VEC_EMPTY(type, vec_ptr) _vector_##type##_empty(vec_ptr)

#ifdef __cplusplus
}
#endif

#endif