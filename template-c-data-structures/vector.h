#ifndef VECTOR_H
#define VECTOR_H

#include <memory.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include <stdio.h>

#include "util_macro.h"

#ifdef __cplusplus
extern "C" {
#endif

#pragma region default-constructor
#define _DEFINE_VECTOR_true_DEFAULT_CONSTRUCTOR(type) \
    inline void vector_##type##_ptrue_default_constr(vector_##type##_ptrue* obj) { \
        assert(obj != NULL); \
        obj->_buffer = NULL; \
        obj->_size = obj->_capacity = 0; \
    }

#define _DEFINE_VECTOR_false_DEFAULT_CONSTRUCTOR(type) \
    inline void vector_##type##_pfalse_default_constr(vector_##type##_pfalse* obj) { \
        assert(obj != NULL); \
        obj->_buffer = NULL; \
        obj->_size = obj->_capacity = 0; \
    }

#define _DEFINE_VECTOR_DEFAULT_CONSTRUCTOR(type, is_ptr) \
    _DEFINE_VECTOR_##is_ptr##_DEFAULT_CONSTRUCTOR(type)
#pragma endregion default-constructor

#pragma region size-constructor
#define _DEFINE_VECTOR_true_SIZE_CONSTRUCTOR(type) \
    inline void vector_##type##_ptrue_size_constr(vector_##type##_ptrue* obj, size_t size) { \
        assert(obj != NULL); \
        obj->_size = obj->_capacity = size; \
        obj->_buffer = NULL; \
        if (obj->_capacity > 0) { \
            obj->_buffer = (type**)malloc(sizeof(type*) * size); \
            memset((void*)obj->_buffer, 0, obj->_capacity * sizeof(type*)); \
        } \
    }

#define _DEFINE_VECTOR_false_SIZE_CONSTRUCTOR(type) \
    inline void vector_##type##_pfalse_size_constr(vector_##type##_pfalse* obj, size_t size) { \
        assert(obj != NULL); \
        obj->_size = obj->_capacity = size; \
        obj->_buffer = NULL; \
        if (obj->_capacity > 0) { \
            obj->_buffer = (type*)malloc(sizeof(type) * size); \
            memset((void*)obj->_buffer, 0, obj->_capacity * sizeof(type)); \
        } \
    }

#define _DEFINE_VECTOR_SIZE_CONSTRUCTOR(type, is_ptr) \
    _DEFINE_VECTOR_##is_ptr##_SIZE_CONSTRUCTOR(type)
#pragma endregion size-constructor

#pragma region size-value-constructor
#define _DEFINE_VECTOR_true_SIZE_VALUE_CONSTRUCTOR(type) \
    inline void vector_##type##_ptrue_size_value_constr(vector_##type##_ptrue* obj, size_t size, type* value) { \
        assert(obj != NULL); \
        obj->_size = obj->_capacity = size; \
        obj->_buffer = size > 0 ? (type**)malloc(sizeof(type*) * size) : NULL; \
        for (size_t i = 0; i < obj->_size; ++i) { \
            obj->_buffer[i] = value; \
        } \
    }

#define _DEFINE_VECTOR_false_SIZE_VALUE_CONSTRUCTOR(type) \
    inline void vector_##type##_pfalse_size_value_constr(vector_##type##_pfalse* obj, size_t size, type value) { \
        assert(obj != NULL); \
        obj->_size = obj->_capacity = size; \
        obj->_buffer = size > 0 ? (type*)malloc(sizeof(type) * size) : NULL; \
        for (size_t i = 0; i < obj->_size; ++i) { \
            obj->_buffer[i] = value; \
        } \
    }

#define _DEFINE_VECTOR_SIZE_VALUE_CONSTRUCTOR(type, is_ptr) \
    _DEFINE_VECTOR_##is_ptr##_SIZE_VALUE_CONSTRUCTOR(type)
#pragma endregion size-value-constructor

#pragma region free-func
#define _DEFINE_VECTOR_true_FREE_FUN(type) \
    inline void vector_##type##_ptrue_free(const vector_##type##_ptrue* obj) { \
        if (obj != NULL) { \
            free(obj->_buffer); \
        } \
    }

#define _DEFINE_VECTOR_false_FREE_FUN(type) \
    inline void vector_##type##_pfalse_free(const vector_##type##_pfalse* obj) { \
        if (obj != NULL) { \
            free(obj->_buffer); \
        } \
    }

#define _DEFINE_VECTOR_FREE_FUN(type, is_ptr) \
    _DEFINE_VECTOR_##is_ptr##_FREE_FUN(type)
#pragma endregion free-func

#pragma region at-func
#define _DEFINE_VECTOR_true_AT_FUN(type) \
    inline type** vector_##type##_ptrue_at(vector_##type##_ptrue* obj, size_t index) { \
        assert(obj != NULL); \
        assert(index < obj->_size); \
        return &(obj->_buffer[index]); \
    }

#define _DEFINE_VECTOR_false_AT_FUN(type) \
    inline type* vector_##type##_pfalse_at(vector_##type##_pfalse* obj, size_t index) { \
        assert(obj != NULL); \
        assert(index < obj->_size); \
        return &(obj->_buffer[index]); \
    }

#define _DEFINE_VECTOR_AT_FUN(type, is_ptr) \
    _DEFINE_VECTOR_##is_ptr##_AT_FUN(type)
#pragma endregion at-func

#pragma region size-func
#define _DEFINE_VECTOR_true_SIZE_FUN(type) \
    inline size_t vector_##type##_ptrue_size(const vector_##type##_ptrue* obj) { \
        assert(obj != NULL); \
        return obj->_size; \
    }

#define _DEFINE_VECTOR_false_SIZE_FUN(type) \
    inline size_t vector_##type##_pfalse_size(const vector_##type##_pfalse* obj) { \
        assert(obj != NULL); \
        return obj->_size; \
    }

#define _DEFINE_VECTOR_SIZE_FUN(type, is_ptr) \
    _DEFINE_VECTOR_##is_ptr##_SIZE_FUN(type)
#pragma endregion size-func

#pragma region capacity-func
#define _DEFINE_VECTOR_true_CAPACITY_FUN(type) \
    inline size_t vector_##type##_ptrue_capacity(const vector_##type##_ptrue* obj) { \
        assert(obj != NULL); \
        return obj->_capacity; \
    }

#define _DEFINE_VECTOR_false_CAPACITY_FUN(type) \
    inline size_t vector_##type##_pfalse_capacity(const vector_##type##_pfalse* obj) { \
        assert(obj != NULL); \
        return obj->_capacity; \
    }

#define _DEFINE_VECTOR_CAPACITY_FUN(type, is_ptr) \
    _DEFINE_VECTOR_##is_ptr##_CAPACITY_FUN(type)
#pragma endregion capacity-func

#pragma region push_back-func
#define _DEFINE_VECTOR_true_PUSH_BACK_FUN(type) \
    inline void vector_##type##_ptrue_push_back(vector_##type##_ptrue* obj, type* value) { \
        assert(obj != NULL); \
        if (obj->_size == obj->_capacity) { \
            const size_t old_capacity = obj->_capacity; \
            obj->_capacity = (old_capacity < 2) ? 2 : (size_t)(obj->_capacity * 1.5f); \
            obj->_buffer = (old_capacity > 0) ? (type*)realloc(obj->_buffer, obj->_capacity * sizeof(type)) : \
                (type*)malloc(obj->_capacity * sizeof(type)); \
        } \
        obj->_buffer[obj->_size++] = value; \
    }

#define _DEFINE_VECTOR_false_PUSH_BACK_FUN(type) \
    inline void vector_##type##_pfalse_push_back(vector_##type##_pfalse* obj, type value) { \
        assert(obj != NULL); \
        if (obj->_size == obj->_capacity) { \
            const size_t old_capacity = obj->_capacity; \
            obj->_capacity = (old_capacity < 2) ? 2 : (size_t)(obj->_capacity * 1.5f); \
            obj->_buffer = (old_capacity > 0) ? (type*)realloc(obj->_buffer, obj->_capacity * sizeof(type)) : \
                (type*)malloc(obj->_capacity * sizeof(type)); \
        } \
        obj->_buffer[obj->_size++] = value; \
    }

#define _DEFINE_VECTOR_PUSH_BACK_FUN(type, is_ptr) \
    _DEFINE_VECTOR_##is_ptr##_PUSH_BACK_FUN(type)
#pragma endregion push_back-func

#pragma region pop_back-func
#define _DEFINE_VECTOR_true_POP_BACK_FUN(type) \
    inline void vector_##type##_ptrue_pop_back(vector_##type##_ptrue* obj) { \
        assert(obj != NULL); \
        if (obj->_size > 0) { \
            --obj->_size; \
        } \
    }

#define _DEFINE_VECTOR_false_POP_BACK_FUN(type) \
    inline void vector_##type##_pfalse_pop_back(vector_##type##_pfalse* obj) { \
        assert(obj != NULL); \
        if (obj->_size > 0) { \
            --obj->_size; \
        } \
    }

#define _DEFINE_VECTOR_POP_BACK_FUN(type, is_ptr) \
    _DEFINE_VECTOR_##is_ptr##_POP_BACK_FUN(type)
#pragma endregion pop_back-func

#pragma region empty-func
#define _DEFINE_VECTOR_true_EMPTY_FUN(type) \
    inline int8_t vector_##type##_ptrue_empty(const vector_##type##_ptrue* obj) { \
        assert(obj != NULL); \
        return obj->_size == 0; \
    }

#define _DEFINE_VECTOR_false_EMPTY_FUN(type) \
    inline int8_t vector_##type##_pfalse_empty(const vector_##type##_pfalse* obj) { \
        assert(obj != NULL); \
        return obj->_size == 0; \
    }

#define _DEFINE_VECTOR_EMPTY_FUN(type, is_ptr) \
    _DEFINE_VECTOR_##is_ptr##_EMPTY_FUN(type)
#pragma endregion empty-func

#pragma region erase-func
#define _DEFINE_VECTOR_true_ERASE_FUN(type) \
    inline void vector_##type##_ptrue_erase(vector_##type##_ptrue* obj, type** iter) { \
        assert(obj != NULL); \
        if (obj->_buffer != NULL && obj->_size > 0) { \
            if (iter >= obj->_buffer && iter < (obj->_buffer + obj->_size)) { \
                memmove_s((void*)iter, obj->_capacity, (void*)(iter + 1), (uintptr_t)obj->_buffer + obj->_size - (uintptr_t)iter - 1); \
                --obj->_size; \
            } \
        } \
    }

#define _DEFINE_VECTOR_false_ERASE_FUN(type) \
    inline void vector_##type##_pfalse_erase(vector_##type##_pfalse* obj, type* iter) { \
        assert(obj != NULL); \
        if (obj->_buffer != NULL && obj->_size > 0) { \
            if (iter >= obj->_buffer && iter < obj->_buffer + obj->_size) { \
                memmove_s((void*)iter, obj->_capacity, (void*)(iter + 1), obj->_buffer + obj->_size - iter - 1); \
                --obj->_size; \
            } \
        } \
    }

#define _DEFINE_VECTOR_ERASE_FUN(type, is_ptr) \
    _DEFINE_VECTOR_##is_ptr##_ERASE_FUN(type)
#pragma endregion erase-func

#pragma region assign-func
#define _DEFINE_VECTOR_true_ASSIGN_FUN(type) \
    inline void vector_##type##_ptrue_assign(vector_##type##_ptrue* dist, const vector_##type##_ptrue* src) { \
        assert(dist != NULL); \
        assert(src != NULL); \
        if (src->_buffer != NULL && src->_capacity > 0) { \
            dist->_size = src->_size; \
            dist->_capacity = src->_capacity; \
            free(dist->_buffer); \
            dist->_buffer = (type**)malloc(dist->_capacity * sizeof(type)); \
            memcpy_s((void*)dist->_buffer, dist->_capacity * sizeof(type), \
                (void*)src->_buffer, src->_capacity * sizeof(type)); \
        } \
    }

#define _DEFINE_VECTOR_false_ASSIGN_FUN(type) \
    inline void vector_##type##_pfalse_assign(vector_##type##_pfalse* dist, const vector_##type##_pfalse* src) { \
        assert(dist != NULL); \
        assert(src != NULL); \
        if (src->_buffer != NULL && src->_capacity > 0) { \
            dist->_size = src->_size; \
            dist->_capacity = src->_capacity; \
            free(dist->_buffer); \
            dist->_buffer = (type*)malloc(dist->_capacity * sizeof(type)); \
            memcpy_s((void*)dist->_buffer, dist->_capacity * sizeof(type), \
                (void*)src->_buffer, src->_capacity * sizeof(type)); \
        } \
    }

#define _DEFINE_VECTOR_ASSIGN_FUN(type, is_ptr) \
    _DEFINE_VECTOR_##is_ptr##_ASSIGN_FUN(type)
#pragma endregion assign-func

#pragma region clear-func
#define _DEFINE_VECTOR_true_CLEAR_FUN(type) \
    inline void vector_##type##_ptrue_clear(vector_##type##_ptrue* obj) { \
        assert(obj != NULL); \
        obj->_size = 0; \
    }

#define _DEFINE_VECTOR_false_CLEAR_FUN(type) \
    inline void vector_##type##_pfalse_clear(vector_##type##_pfalse* obj) { \
        assert(obj != NULL); \
        obj->_size = 0; \
    }

#define _DEFINE_VECTOR_CLEAR_FUN(type, is_ptr) \
    _DEFINE_VECTOR_##is_ptr##_CLEAR_FUN(type)
#pragma endregion clear-func

#pragma region resize-func
#define _DEFINE_VECTOR_true_RESIZE_FUN(type) \
    inline void vector_##type##_ptrue_resize(vector_##type##_ptrue* obj, size_t new_size) { \
        assert(obj != NULL); \
        if (new_size <= obj->_capacity) { \
            obj->_size = new_size; \
        } else { \
            if(obj->_buffer == NULL) { \
                obj->_buffer = (type**)malloc(new_size * sizeof(type*)); \
                memset(obj->_buffer, 0, new_size * sizeof(type*)); \
            } else { \
                obj->_buffer = (type**)realloc(obj->_buffer, new_size * sizeof(type*)); \
                memset(obj->_buffer + obj->_capacity, 0, (new_size - obj->_capacity) * sizeof(type*)); \
            } \
            obj->_size = obj->_capacity = new_size; \
        } \
    }

#define _DEFINE_VECTOR_false_RESIZE_FUN(type) \
    inline void vector_##type##_pfalse_resize(vector_##type##_pfalse* obj, size_t new_size) { \
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

#define _DEFINE_VECTOR_RESIZE_FUN(type, is_ptr) \
    _DEFINE_VECTOR_##is_ptr##_RESIZE_FUN(type)
#pragma endregion resize-func

#pragma region data-func
#define _DEFINE_VECTOR_true_DATA_FUN(type) \
    inline type** vector_##type##_ptrue_data(const vector_##type##_ptrue* obj) { \
        return obj != NULL ? obj->_buffer : NULL; \
    }

#define _DEFINE_VECTOR_false_DATA_FUN(type) \
    inline type* vector_##type##_pfalse_data(const vector_##type##_pfalse* obj) { \
        return obj != NULL ? obj->_buffer : NULL; \
    }

#define _DEFINE_VECTOR_DATA_FUN(type, is_ptr) \
    _DEFINE_VECTOR_##is_ptr##_DATA_FUN(type)
#pragma endregion data-func

#pragma region begin-func
#define _DEFINE_VECTOR_true_BEGIN_FUN(type) \
    inline const type** vector_##type##_ptrue_begin(const vector_##type##_ptrue* obj) { \
        return obj != NULL ? obj->_buffer : NULL; \
    }

#define _DEFINE_VECTOR_false_BEGIN_FUN(type) \
    inline const type* vector_##type##_pfalse_begin(const vector_##type##_pfalse* obj) { \
        return obj != NULL ? obj->_buffer : NULL; \
    }

#define _DEFINE_VECTOR_BEGIN_FUN(type, is_ptr) \
    _DEFINE_VECTOR_##is_ptr##_BEGIN_FUN(type)
#pragma endregion begin-func

#pragma region end-func
#define _DEFINE_VECTOR_true_END_FUN(type) \
    inline const type** vector_##type##_ptrue_end(const vector_##type##_ptrue* obj) { \
        return obj != NULL ? obj->_buffer + obj->_size : NULL; \
    }

#define _DEFINE_VECTOR_false_END_FUN(type) \
    inline const type* vector_##type##_pfalse_end(const vector_##type##_pfalse* obj) { \
        return obj != NULL ? obj->_buffer + obj->_size : NULL; \
    }

#define _DEFINE_VECTOR_END_FUN(type, is_ptr) \
    _DEFINE_VECTOR_##is_ptr##_END_FUN(type)
#pragma endregion end-func

#define DEFINE_TYPED_VECTOR(type, is_ptr) \
    typedef struct vector_##type##_p##is_ptr { \
        _DEF_PTR(type, is_ptr)* _buffer; \
        size_t _size; \
        size_t _capacity; \
    } vector_##type##_p##is_ptr; \
    \
    _DEFINE_VECTOR_DEFAULT_CONSTRUCTOR(type, is_ptr); \
    _DEFINE_VECTOR_SIZE_CONSTRUCTOR(type, is_ptr); \
    _DEFINE_VECTOR_SIZE_VALUE_CONSTRUCTOR(type, is_ptr); \
    _DEFINE_VECTOR_FREE_FUN(type, is_ptr); \
    _DEFINE_VECTOR_AT_FUN(type, is_ptr); \
    _DEFINE_VECTOR_SIZE_FUN(type, is_ptr); \
    _DEFINE_VECTOR_CAPACITY_FUN(type, is_ptr); \
    _DEFINE_VECTOR_PUSH_BACK_FUN(type, is_ptr); \
    _DEFINE_VECTOR_POP_BACK_FUN(type, is_ptr); \
    _DEFINE_VECTOR_EMPTY_FUN(type, is_ptr); \
    _DEFINE_VECTOR_ERASE_FUN(type, is_ptr); \
    _DEFINE_VECTOR_ASSIGN_FUN(type, is_ptr); \
    _DEFINE_VECTOR_CLEAR_FUN(type, is_ptr); \
    _DEFINE_VECTOR_RESIZE_FUN(type, is_ptr); \
    _DEFINE_VECTOR_DATA_FUN(type, is_ptr); \
    _DEFINE_VECTOR_BEGIN_FUN(type, is_ptr); \
    _DEFINE_VECTOR_END_FUN(type, is_ptr); \

#ifdef __cplusplus
}
#endif

#endif