#ifndef VECTOR_H
#define VECTOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <memory.h>
#include <stdlib.h>
#include <stdint.h>

#include <stdio.h>


#define _DEFINE_VECTOR_INIT_FUN(type) \
    inline void vector_##type##_init(vector_##type** obj, size_t size, type value) {\
        if ((size) > 0) {\
            *obj = (vector_##type*)malloc(sizeof(vector_##type)); \
            (*obj)->_buffer = (type*)malloc(sizeof(type) * (size));   \
            for (size_t i = 0; i < size; ++i) {\
                (*obj)->_buffer[i] = (value);\
            }\
            (*obj)->_size = (*obj)->_capacity = (size);  \
        } else {\
            *obj = NULL;\
        }\
    }

#define _DEFINE_VECTOR_FREE_FUN(type) \
    inline void vector_##type##_free(vector_##type* obj) {\
        if (obj != NULL) { \
            free(obj->_buffer);\
            free(obj);\
        } \
    }

#define _DEFINE_VECTOR_AT_FUN(type) \
    inline type* vector_##type##_at(vector_##type* obj, size_t index) {\
        return &(obj->_buffer[index]); \
    }

#define _DEFINE_VECTOR_SIZE_FUN(type) \
    inline size_t* vector_##type##_size(vector_##type* obj) {\
        return (obj != NULL ? &(obj->_size) : NULL); \
    }

#define _DEFINE_VECTOR_CAPACITY_FUN(type) \
    inline size_t* vector_##type##_capacity(vector_##type* obj) {\
        return (obj != NULL ? &(obj->_capacity) : NULL); \
    }

#define _DEFINE_VECTOR_PUSH_BACK_FUN(type) \
    inline void vector_##type##_push_back(vector_##type** obj, type value) { \
        if ((*obj)->_size >= (*obj)->_capacity) { \
            (*obj)->_capacity *= 1.5f; \
            (*obj)->_buffer = realloc((*obj)->_buffer, (*obj)->_capacity); \
        } \
        (*obj)->_buffer[(*obj)->_size++] = value; \
    }

#define _DEFINE_VECTOR_POP_BACK_FUN(type) \
    inline void vector_##type##_pop_back(vector_##type* obj) { \
        if (obj->_size > 0) { \
            --obj->_size; \
        } \
    }

#define _DEFINE_VECTOR_EMPTY_FUN(type) \
    inline int8_t vector_##type##_empty(vector_##type* obj) { \
        return obj->_size == 0; \
    }

#define DEFINE_TYPED_VECTOR(type)       \
    typedef struct vector_##type {      \
        type* _buffer;                   \
        size_t _size;                   \
        size_t _capacity;                   \
    } vector_##type; \
    \
    _DEFINE_VECTOR_INIT_FUN(type); \
    _DEFINE_VECTOR_FREE_FUN(type); \
    _DEFINE_VECTOR_AT_FUN(type); \
    _DEFINE_VECTOR_SIZE_FUN(type); \
    _DEFINE_VECTOR_CAPACITY_FUN(type); \
    _DEFINE_VECTOR_PUSH_BACK_FUN(type); \
    _DEFINE_VECTOR_POP_BACK_FUN(type); \
    _DEFINE_VECTOR_EMPTY_FUN(type); \

#ifdef __cplusplus
}
#endif

#endif