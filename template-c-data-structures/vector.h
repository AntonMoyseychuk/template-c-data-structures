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


#define _DEFINE_VECTOR_INIT_FUN(type) \
    inline void _vector_##type##_init(vector_##type* obj) { \
        assert(obj != NULL); \
        obj->_buffer = NULL; \
        obj->_size = obj->_capacity = 0; \
    }

#define _DEFINE_VECTOR_INIT_SIZE_FUN(type) \
    inline void _vector_##type##_size_init(vector_##type* obj, size_t size) { \
        assert(obj != NULL); \
        obj->_size = obj->_capacity = size; \
        obj->_buffer = NULL; \
        if (obj->_capacity > 0) { \
            obj->_buffer = (type*)malloc(sizeof(type) * size); \
            memset(obj->_buffer, 0, obj->_capacity * sizeof(type)); \
        } \
    }

#define _DEFINE_VECTOR_INIT_SIZE_DEFUALT_VALUE_FUN(type) \
    inline void _vector_##type##_size_value_init(vector_##type* obj, size_t size, type value) { \
        assert(obj != NULL); \
        obj->_size = obj->_capacity = size; \
        obj->_buffer = size > 0 ? (type*)malloc(sizeof(type) * size) : NULL; \
        for (size_t i = 0; i < obj->_size; ++i) { \
            obj->_buffer[i] = value; \
        } \
    }

#define _DEFINE_VECTOR_FREE_FUN(type) \
    inline void _vector_##type##_free(const vector_##type* obj) { \
        if (obj != NULL) { \
            free(obj->_buffer); \
        } \
    }

#define _DEFINE_VECTOR_AT_FUN(type) \
    inline type* _vector_##type##_at(vector_##type* obj, size_t index) { \
        assert(obj != NULL); \
        assert(index < obj->_size); \
        return &(obj->_buffer[index]); \
    }

#define _DEFINE_VECTOR_SIZE_FUN(type) \
    inline size_t _vector_##type##_size(const vector_##type* obj) { \
        assert(obj != NULL); \
        return obj->_size; \
    }

#define _DEFINE_VECTOR_CAPACITY_FUN(type) \
    inline size_t _vector_##type##_capacity(const vector_##type* obj) { \
        assert(obj != NULL); \
        return obj->_capacity; \
    }

#define _DEFINE_VECTOR_PUSH_BACK_FUN(type) \
    inline void _vector_##type##_push_back(vector_##type* obj, type value) { \
        assert(obj != NULL); \
        if (obj->_size == obj->_capacity) { \
            const size_t old_capacity = obj->_capacity; \
            obj->_capacity = (old_capacity < 2) ? 2 : obj->_capacity * 1.5f; \
            obj->_buffer = (old_capacity > 0) ? (type*)realloc(obj->_buffer, obj->_capacity * sizeof(type)) : \
                (type*)malloc(obj->_capacity * sizeof(type)); \
        } \
        obj->_buffer[obj->_size++] = value; \
    }

#define _DEFINE_VECTOR_POP_BACK_FUN(type) \
    inline void _vector_##type##_pop_back(vector_##type* obj) { \
        assert(obj != NULL); \
        if (obj->_size > 0) { \
            --obj->_size; \
        } \
    }

#define _DEFINE_VECTOR_EMPTY_FUN(type) \
    inline int8_t _vector_##type##_empty(const vector_##type* obj) { \
        assert(obj != NULL); \
        return obj->_size == 0; \
    }

#define _DEFINE_VECTOR_ERASE_FUN(type) \
    inline void _vector_##type##_erase(vector_##type* obj, type* iter) { \
        assert(obj != NULL); \
        if (obj->_buffer != NULL && obj->_size > 0) { \
            if (iter >= obj->_buffer && iter < obj->_buffer + obj->_size) { \
                memmove_s(iter, obj->_capacity, iter + 1, obj->_buffer + obj->_size - iter - 1); \
                --obj->_size; \
            } \
        } \
    }

#define _DEFINE_VECTOR_ASSIGN_FUN(type) \
    inline void _vector_##type##_assign(vector_##type* dist, const vector_##type* src) { \
        assert(dist != NULL); \
        assert(src != NULL); \
        if (src->_buffer != NULL && src->_capacity > 0) { \
            dist->_size = src->_size; \
            dist->_capacity = src->_capacity; \
            free(dist->_buffer); \
            dist->_buffer = (type*)malloc(dist->_capacity * sizeof(type)); \
            memcpy_s(dist->_buffer, dist->_capacity * sizeof(type), \
                src->_buffer, src->_capacity * sizeof(type)); \
        } \
    }

#define _DEFINE_VECTOR_CLEAR_FUN(type) \
    inline void _vector_##type##_clear(vector_##type* obj) { \
        assert(obj != NULL); \
        obj->_size = 0; \
    }

#define _DEFINE_VECTOR_RESIZE_FUN(type) \
    inline void _vector_##type##_resize(vector_##type* obj, size_t new_size) { \
        assert(obj != NULL); \
        if (new_size <= obj->_capacity) { \
            obj->_size = new_size; \
        } else { \
            if(obj->_buffer == NULL) { \
                obj->_buffer = (type*)malloc(new_size * sizeof(type)); \
                memset(obj->_buffer, 0, new_size * sizeof(type)); \
            } else { \
                obj->_buffer = (type*)realloc(obj->_buffer, new_size * sizeof(type)); \
                memset(obj->_buffer + obj->_capacity, 0, (new_size - obj->_capacity) * sizeof(type)); \
            } \
            obj->_size = obj->_capacity = new_size; \
        } \
    }

#define _DEFINE_VECTOR_DATA_FUN(type) \
    inline type* _vector_##type##_data(const vector_##type* obj) { \
        return obj != NULL ? obj->_buffer : NULL; \
    }

#define _DEFINE_VECTOR_BEGIN_FUN(type) \
    inline type* _vector_##type##_begin(const vector_##type* obj) { \
        return obj != NULL ? obj->_buffer : NULL; \
    }

#define _DEFINE_VECTOR_END_FUN(type) \
    inline type* _vector_##type##_end(const vector_##type* obj) { \
        return obj != NULL ? obj->_buffer + obj->_size : NULL; \
    }

#define DEFINE_TYPED_VECTOR(type) \
    typedef struct vector_##type { \
        type* _buffer; \
        size_t _size; \
        size_t _capacity; \
    } vector_##type; \
    \
    _DEFINE_VECTOR_INIT_FUN(type); \
    _DEFINE_VECTOR_INIT_SIZE_FUN(type); \
    _DEFINE_VECTOR_INIT_SIZE_DEFUALT_VALUE_FUN(type); \
    _DEFINE_VECTOR_FREE_FUN(type); \
    _DEFINE_VECTOR_AT_FUN(type); \
    _DEFINE_VECTOR_SIZE_FUN(type); \
    _DEFINE_VECTOR_CAPACITY_FUN(type); \
    _DEFINE_VECTOR_PUSH_BACK_FUN(type); \
    _DEFINE_VECTOR_POP_BACK_FUN(type); \
    _DEFINE_VECTOR_EMPTY_FUN(type); \
    _DEFINE_VECTOR_ERASE_FUN(type); \
    _DEFINE_VECTOR_ASSIGN_FUN(type); \
    _DEFINE_VECTOR_CLEAR_FUN(type); \
    _DEFINE_VECTOR_RESIZE_FUN(type); \
    _DEFINE_VECTOR_DATA_FUN(type); \
    _DEFINE_VECTOR_BEGIN_FUN(type); \
    _DEFINE_VECTOR_END_FUN(type); \


// #define VEC_DECLARE_INSTANCE(type, vec_name) vector_##type vec_name
// #define VEC_DEFAULT_CONSTRUCTOR(type, vec_ptr) _vector_##type##_init(vec_ptr)
// #define VEC_SIZED_CONSTRUCTOR(type, vec_ptr, size) _vector_##type##_size_init(vec_ptr, size)
// #define VEC_SIZED_VALUE_CONSTRUCTOR(type, vec_ptr, size, value) _vector_##type##_size_value_init(vec_ptr, size, value)
//
// #define VEC_FREE(type, vec_ptr) _vector_##type##_free(vec_ptr)
//
// #define VEC_AT(type, vec_ptr, index) _vector_##type##_at(vec_ptr, index)
// #define VEC_BEGIN(type, vec_ptr) _vector_##type##_begin(vec_ptr)
// #define VEC_END(type, vec_ptr) _vector_##type##_end(vec_ptr)
//
// #define VEC_SIZE(type, vec_ptr) _vector_##type##_size(vec_ptr)
// #define VEC_CAPACITY(type, vec_ptr) _vector_##type##_capacity(vec_ptr)
// #define VEC_DATA(type, vec_ptr) _vector_##type##_data(vec_ptr)
//
// #define VEC_PUSH_BACK(type, vec_ptr, value) _vector_##type##_push_back(vec_ptr, value)
// #define VEC_POP_BACK(type, vec_ptr) _vector_##type##_pop_back(vec_ptr)
// #define VEC_ERASE(type, vec_ptr, iter) _vector_##type##_erase(vec_ptr, iter)
// #define VEC_ASSIGN(type, dist_ptr, src_ptr) _vector_##type##_assign(dist_ptr, src_ptr)
//
// #define VEC_EMPTY(type, vec_ptr) _vector_##type##_empty(vec_ptr)
// #define VEC_CLEAR(type, vec_ptr) _vector_##type##_clear(vec_ptr)
//
// #define VEC_RESIZE(type, vec_ptr, size) _vector_##type##_resize(vec_ptr, size)
//
// #define VEC_CREATE_ITER(vec_type, iter_name) vec_type* iter_name
// #define VEC_ITER_NEXT(iter) (iter + 1)
// #define VEC_ITER_VALUE(iter) *iter

#ifdef __cplusplus
}
#endif

#endif