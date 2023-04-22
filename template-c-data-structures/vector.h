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
    inline void vector_##type##_init(vector_##type** obj, size_t size) {                        \
        *obj = (vector_##type*)malloc(sizeof(vector_##type));                                   \
        (*obj)->_buffer = (type*)malloc(sizeof(type) * (size > 0 ? size : 1));                  \
        (*obj)->_size = (*obj)->_capacity = (size);                                             \
    }

#define _DEFINE_VECTOR_INIT_ARG_FUN(type)                                                       \
    inline void vector_##type##_arg_init(vector_##type** obj, size_t size, type value) {        \
        *obj = (vector_##type*)malloc(sizeof(vector_##type));                                   \
        (*obj)->_buffer = (type*)malloc(sizeof(type) * (size > 0 ? size : 1));                  \
        for (size_t i = 0; i < size; ++i) {                                                     \
            (*obj)->_buffer[i] = (value);                                                       \
        }                                                                                       \
        (*obj)->_size = (*obj)->_capacity = (size);                                             \
    }

#define _DEFINE_VECTOR_FREE_FUN(type)                                                           \
    inline void vector_##type##_free(const vector_##type** obj) {                               \
        if (obj != NULL && *obj != NULL) {                                                      \
            free((*obj)->_buffer);                                                              \
            free(*obj);                                                                         \
        }                                                                                       \
    }

#define _DEFINE_VECTOR_AT_FUN(type)                                                             \
    inline type* vector_##type##_at(vector_##type* obj, size_t index) {                         \
        assert(index < obj->_size);                                                             \
        return &(obj->_buffer[index]);                                                          \
    }

#define _DEFINE_VECTOR_SIZE_FUN(type)                                                           \
    inline size_t vector_##type##_size(const vector_##type* obj) {                              \
        return (obj != NULL ? obj->_size : 0);                                                  \
    }

#define _DEFINE_VECTOR_CAPACITY_FUN(type)                                                       \
    inline size_t vector_##type##_capacity(const vector_##type* obj) {                          \
        return (obj != NULL ? obj->_capacity : 0);                                              \
    }

#define _DEFINE_VECTOR_PUSH_BACK_FUN(type)                                                      \
    inline void vector_##type##_push_back(vector_##type** obj, type value) {                    \
        if ((*obj)->_size >= (*obj)->_capacity) {                                               \
            (*obj)->_capacity = ((*obj)->_capacity + 1) * 1.5f;                                 \
            (*obj)->_buffer = realloc((*obj)->_buffer, (*obj)->_capacity * sizeof(type));       \
        }                                                                                       \
        (*obj)->_buffer[(*obj)->_size++] = value;                                               \
    }

#define _DEFINE_VECTOR_POP_BACK_FUN(type)                                                       \
    inline void vector_##type##_pop_back(vector_##type* obj) {                                  \
        if (obj->_size > 0) {                                                                   \
            --obj->_size;                                                                       \
        }                                                                                       \
    }

#define _DEFINE_VECTOR_EMPTY_FUN(type)                                                          \
    inline int8_t vector_##type##_empty(const vector_##type* obj) {                             \
        return obj->_size == 0;                                                                 \
    }

#define _DEFINE_VECTOR_ERASE_FUN(type)                                                          \
    inline void vector_##type##_erase(vector_##type** obj, size_t index) {                      \
        if (obj != NULL && (*obj)->_buffer != NULL && (*obj)->_size != 0) {                     \
            if (index < (*obj)->_size) {                                                        \
                memmove_s((*obj)->_buffer + index, (*obj)->_capacity,                           \
                    (*obj)->_buffer + index + 1, (*obj)->_size - index - 1);                    \
                --(*obj)->_size;                                                                \
            }                                                                                   \
        }                                                                                       \
    }

#define _DEFINE_VECTOR_ASSIGN_FUN(type)                                                         \
    inline void vector_##type##_assign(vector_##type** dist, const vector_##type* src) {        \
        if (src != NULL && src->_buffer != NULL && src->_capacity != 0) {                       \
            if (*dist != NULL) {                                                                \
                free((*dist)->_buffer);                                                         \
            } else {                                                                            \
                *dist = (vector_##type*)malloc(sizeof(vector_##type));                          \
            }                                                                                   \
            (*dist)->_size = src->_size;                                                        \
            (*dist)->_capacity = src->_capacity;                                                \
            (*dist)->_buffer = (type*)malloc((*dist)->_capacity * sizeof(type));                \
            memcpy_s((*dist)->_buffer, (*dist)->_capacity * sizeof(type),                       \
                src->_buffer, src->_capacity * sizeof(type));                                   \
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

#ifdef __cplusplus
}
#endif

#endif