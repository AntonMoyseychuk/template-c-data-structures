#ifndef LIST_H
#define LIST_H

#include <memory.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#include <stdio.h>

#include "util_macro.h"

#ifdef __cplusplus
extern "C" {
#endif

#pragma region list-node
#define _DEFINE_TYPED_LIST_NODE(type, is_ptr) \
    typedef struct list_##type##_p##is_ptr##_node { \
        _DEF_PTR(type, is_ptr) _value; \
        struct list_##type##_p##is_ptr##_node* _next; \
        struct list_##type##_p##is_ptr##_node* _prev; \
    } list_##type##_p##is_ptr##_node; 

#define _ALLOCATE_LIST_NODE(type, is_ptr, node_ptr, value, prev_ptr, next_ptr) { \
    node_ptr = (list_##type##_p##is_ptr##_node*)malloc(sizeof(list_##type##_p##is_ptr##_node)); \
    node_ptr->_value = value; \
    node_ptr->_prev = prev_ptr; \
    node_ptr->_next = next_ptr; \
}                                                                                                                                       
#pragma endregion list-node

#pragma region default-constructor
#define _DEFINE_LIST_true_DEFAULT_CONSTRUCTOR(type) \
    inline void list_##type##_ptrue_default_constr(list_##type##_ptrue* obj) { \
        assert(obj != NULL); \
        obj->_size = 0; \
        obj->_head = NULL; \
        _ALLOCATE_LIST_NODE(type, true, obj->_tail, (type)0, obj->_head, NULL); \
    }

#define _DEFINE_LIST_false_DEFAULT_CONSTRUCTOR(type) \
    inline void list_##type##_pfalse_default_constr(list_##type##_pfalse* obj) { \
        assert(obj != NULL); \
        obj->_size = 0; \
        obj->_head = NULL; \
        _ALLOCATE_LIST_NODE(type, false, obj->_tail, (type)0, obj->_head, NULL); \
    }

#define _DEFINE_LIST_DEFAULT_CONSTRUCTOR(type, is_ptr) \
    _DEFINE_LIST_##is_ptr##_DEFAULT_CONSTRUCTOR(type)
#pragma endregion default-constructor

#pragma region free-func
#define _DEFINE_LIST_true_FREE_FUN(type) \
    inline void list_##type##_ptrue_free(list_##type##_ptrue* obj) { \
        if (obj != NULL) { \
            for (size_t i = 0; i < obj->_size; ++i) { \
                list_##type##_ptrue_node* curr = obj->_head; \
                obj->_head = obj->_head->_next; \
                free(curr); \
            } \
            free(obj->_tail); \
            obj->_size = 0; \
            obj->_head = obj->_tail = NULL; \
        } \
    }

#define _DEFINE_LIST_false_FREE_FUN(type) \
    inline void list_##type##_pfalse_free(list_##type##_pfalse* obj) { \
        if (obj != NULL) { \
            for (size_t i = 0; i < obj->_size; ++i) { \
                list_##type##_pfalse_node* curr = obj->_head; \
                obj->_head = obj->_head->_next; \
                free(curr); \
            } \
            free(obj->_tail); \
            obj->_size = 0; \
            obj->_head = obj->_tail = NULL; \
        } \
    }

#define _DEFINE_LIST_FREE_FUN(type, is_ptr) \
    _DEFINE_LIST_##is_ptr##_FREE_FUN(type)
#pragma endregion free-func

#pragma region push_front-func
#define _DEFINE_LIST_true_PUSH_FRONT_FUN(type) \
    inline void list_##type##_ptrue_push_front(list_##type##_ptrue* obj, type* value) { \
        assert(obj != NULL); \
        if (obj->_size == 0) { \
            _ALLOCATE_LIST_NODE(type, true, obj->_head, value, NULL, obj->_tail); \
            obj->_tail->_prev = obj->_head; \
        } else { \
            list_##type##_ptrue_node* temp = NULL; \
            _ALLOCATE_LIST_NODE(type, true, temp, value, NULL, obj->_head); \
            obj->_head = temp; \
        } \
        ++obj->_size; \
    }

#define _DEFINE_LIST_false_PUSH_FRONT_FUN(type) \
    inline void list_##type##_pfalse_push_front(list_##type##_pfalse* obj, type value) { \
        assert(obj != NULL); \
        if (obj->_size == 0) { \
            _ALLOCATE_LIST_NODE(type, false, obj->_head, value, NULL, obj->_tail); \
            obj->_tail->_prev = obj->_head; \
        } else { \
            list_##type##_pfalse_node* temp = NULL; \
            _ALLOCATE_LIST_NODE(type, false, temp, value, NULL, obj->_head); \
            obj->_head = temp; \
        } \
        ++obj->_size; \
    }

#define _DEFINE_LIST_PUSH_FRONT_FUN(type, is_ptr) \
    _DEFINE_LIST_##is_ptr##_PUSH_FRONT_FUN(type)
#pragma endregion push_front-func

#pragma region push_back-func
#define _DEFINE_LIST_true_PUSH_BACK_FUN(type) \
    inline void list_##type##_ptrue_push_back(list_##type##_ptrue* obj, type* value) { \
        assert(obj != NULL); \
        if (obj->_size == 0) { \
            _ALLOCATE_LIST_NODE(type, true, obj->_head, value, NULL, obj->_tail); \
            obj->_tail->_prev = obj->_head; \
        } else { \
            list_##type##_ptrue_node* temp = NULL; \
            _ALLOCATE_LIST_NODE(type, true, temp, value, obj->_tail->_prev, obj->_tail); \
            obj->_tail->_prev->_next = temp; \
            obj->_tail->_prev = temp; \
        } \
        ++obj->_size; \
    }

#define _DEFINE_LIST_false_PUSH_BACK_FUN(type) \
    inline void list_##type##_pfalse_push_back(list_##type##_pfalse* obj, type value) { \
        assert(obj != NULL); \
        if (obj->_size == 0) { \
            _ALLOCATE_LIST_NODE(type, false, obj->_head, value, NULL, obj->_tail); \
            obj->_tail->_prev = obj->_head; \
        } else { \
            list_##type##_pfalse_node* temp = NULL; \
            _ALLOCATE_LIST_NODE(type, false, temp, value, obj->_tail->_prev, obj->_tail); \
            obj->_tail->_prev->_next = temp; \
            obj->_tail->_prev = temp; \
        } \
        ++obj->_size; \
    }

#define _DEFINE_LIST_PUSH_BACK_FUN(type, is_ptr) \
    _DEFINE_LIST_##is_ptr##_PUSH_BACK_FUN(type)
#pragma endregion push_back-func

#pragma region pop_back-func
#define _DEFINE_LIST_true_POP_BACK_FUN(type) \
    inline void list_##type##_ptrue_pop_back(list_##type##_ptrue* obj) { \
        assert(obj != NULL); \
        if (obj->_size > 0) { \
            list_##type##_ptrue_node* temp = obj->_tail->_prev; \
            if (obj->_size == 1) { \
                obj->_head = NULL; \
                obj->_tail->_prev = NULL; \
            } else { \
                temp->_prev->_next = obj->_tail; \
                obj->_tail->_prev = temp->_prev; \
            } \
            free(temp); \
            --obj->_size; \
        } \
    }

#define _DEFINE_LIST_false_POP_BACK_FUN(type) \
    inline void list_##type##_pfalse_pop_back(list_##type##_pfalse* obj) { \
        assert(obj != NULL); \
        if (obj->_size > 0) { \
            list_##type##_pfalse_node* temp = obj->_tail->_prev; \
            if (obj->_size == 1) { \
                obj->_head = NULL; \
                obj->_tail->_prev = NULL; \
            } else { \
                temp->_prev->_next = obj->_tail; \
                obj->_tail->_prev = temp->_prev; \
            } \
            free(temp); \
            --obj->_size; \
        } \
    }

#define _DEFINE_LIST_POP_BACK_FUN(type, is_ptr) \
    _DEFINE_LIST_##is_ptr##_POP_BACK_FUN(type)
#pragma endregion pop_back-func

#pragma region pop_front-func
#define _DEFINE_LIST_true_POP_FRONT_FUN(type) \
    inline void list_##type##_ptrue_pop_front(list_##type##_ptrue* obj) { \
        assert(obj != NULL); \
        if (obj->_size > 0) { \
            list_##type##_ptrue_node* temp = obj->_head; \
            if (obj->_size == 1) { \
                obj->_head = NULL; \
                obj->_tail->_prev = NULL; \
            } else { \
                obj->_head->_next->_prev = NULL; \
                obj->_head = obj->_head->_next; \
            } \
            free(temp); \
            --obj->_size; \
        } \
    }

#define _DEFINE_LIST_false_POP_FRONT_FUN(type) \
    inline void list_##type##_pfalse_pop_front(list_##type##_pfalse* obj) { \
        assert(obj != NULL); \
        if (obj->_size > 0) { \
            list_##type##_pfalse_node* temp = obj->_head; \
            if (obj->_size == 1) { \
                obj->_head = NULL; \
                obj->_tail->_prev = NULL; \
            } else { \
                obj->_head->_next->_prev = NULL; \
                obj->_head = obj->_head->_next; \
            } \
            free(temp); \
            --obj->_size; \
        } \
    }

#define _DEFINE_LIST_POP_FRONT_FUN(type, is_ptr) \
    _DEFINE_LIST_##is_ptr##_POP_FRONT_FUN(type)
#pragma endregion pop_front-func

#pragma region size-func
#define _DEFINE_LIST_true_SIZE_FUN(type) \
    inline size_t list_##type##_ptrue_size(const list_##type##_ptrue* obj) { \
        assert(obj != NULL); \
        return obj->_size; \
    }

#define _DEFINE_LIST_false_SIZE_FUN(type) \
    inline size_t list_##type##_pfalse_size(const list_##type##_pfalse* obj) { \
        assert(obj != NULL); \
        return obj->_size; \
    }

#define _DEFINE_LIST_SIZE_FUN(type, is_ptr) \
    _DEFINE_LIST_##is_ptr##_SIZE_FUN(type)
#pragma endregion size-func

#pragma region empty-func
#define _DEFINE_LIST_true_EMPTY_FUN(type) \
    inline int8_t list_##type##_ptrue_empty(const list_##type##_ptrue* obj) { \
        assert(obj != NULL); \
        return obj->_size == 0; \
    }

#define _DEFINE_LIST_false_EMPTY_FUN(type) \
    inline int8_t list_##type##_pfalse_empty(const list_##type##_pfalse* obj) { \
        assert(obj != NULL); \
        return obj->_size == 0; \
    }

#define _DEFINE_LIST_EMPTY_FUN(type, is_ptr) \
    _DEFINE_LIST_##is_ptr##_EMPTY_FUN(type)
#pragma endregion empty-func

#pragma region front-func
#define _DEFINE_LIST_true_FRONT_FUN(type) \
    inline type** list_##type##_ptrue_front(list_##type##_ptrue* obj) { \
        assert(obj != NULL); \
        return obj->_head != NULL ? &obj->_head->_value : NULL; \
    }

#define _DEFINE_LIST_false_FRONT_FUN(type) \
    inline type* list_##type##_pfalse_front(list_##type##_pfalse* obj) { \
        assert(obj != NULL); \
        return obj->_head != NULL ? &obj->_head->_value : NULL; \
    }

#define _DEFINE_LIST_FRONT_FUN(type, is_ptr) \
    _DEFINE_LIST_##is_ptr##_FRONT_FUN(type)
#pragma endregion front-func

#pragma region back-func
#define _DEFINE_LIST_true_BACK_FUN(type) \
    inline type** list_##type##_ptrue_back(list_##type##_ptrue* obj) { \
        assert(obj != NULL); \
        return obj->_tail->_prev != NULL ? &obj->_tail->_prev->_value : NULL; \
    }

#define _DEFINE_LIST_false_BACK_FUN(type) \
    inline type* list_##type##_pfalse_back(list_##type##_pfalse* obj) { \
        assert(obj != NULL); \
        return obj->_tail->_prev != NULL ? &obj->_tail->_prev->_value : NULL; \
    }

#define _DEFINE_LIST_BACK_FUN(type, is_ptr) \
    _DEFINE_LIST_##is_ptr##_BACK_FUN(type)
#pragma endregion back-func

#pragma region begin-func
#define _DEFINE_LIST_true_BEGIN_FUN(type) \
    inline list_##type##_ptrue_node* list_##type##_ptrue_begin(list_##type##_ptrue* obj) { \
        assert(obj != NULL); \
        return obj->_head; \
    }

#define _DEFINE_LIST_false_BEGIN_FUN(type) \
    inline list_##type##_pfalse_node* list_##type##_pfalse_begin(list_##type##_pfalse* obj) { \
        assert(obj != NULL); \
        return obj->_head; \
    }

#define _DEFINE_LIST_BEGIN_FUN(type, is_ptr) \
    _DEFINE_LIST_##is_ptr##_BEGIN_FUN(type)
#pragma endregion begin-func

#pragma region end-func
#define _DEFINE_LIST_END_FUN(type) \
    inline list_##type##_ptrue_node* list_##type##_ptrue_end(list_##type##_ptrue* obj) { \
        assert(obj != NULL); \
        return obj->_tail; \
    }

#define _DEFINE_LIST_END_FUN(type) \
    inline list_##type##_pfalse_node* list_##type##_pfalse_end(list_##type##_pfalse* obj) { \
        assert(obj != NULL); \
        return obj->_tail; \
    }

#define _DEFINE_LIST_END_FUN(type, is_ptr) \
    _DEFINE_LIST_##is_ptr##_END_FUN(type)
#pragma endregion end-func

#define DEFINE_TYPED_LIST(type, is_ptr) \
    _DEFINE_TYPED_LIST_NODE(type, is_ptr); \
    typedef struct list_##type##_p##is_ptr { \
        size_t _size; \
        list_##type##_p##is_ptr##_node* _head; \
        list_##type##_p##is_ptr##_node* _tail; \
    } list_##type##_p##is_ptr; \
    \
    _DEFINE_LIST_DEFAULT_CONSTRUCTOR(type, is_ptr); \
    _DEFINE_LIST_FREE_FUN(type, is_ptr); \
    _DEFINE_LIST_SIZE_FUN(type, is_ptr); \
    _DEFINE_LIST_EMPTY_FUN(type, is_ptr); \
    _DEFINE_LIST_POP_BACK_FUN(type, is_ptr); \
    _DEFINE_LIST_POP_FRONT_FUN(type, is_ptr); \
    _DEFINE_LIST_PUSH_BACK_FUN(type, is_ptr); \
    _DEFINE_LIST_PUSH_FRONT_FUN(type, is_ptr); \
    _DEFINE_LIST_FRONT_FUN(type, is_ptr); \
    _DEFINE_LIST_BACK_FUN(type, is_ptr); \
    _DEFINE_LIST_BEGIN_FUN(type, is_ptr); \
    _DEFINE_LIST_END_FUN(type, is_ptr) \

#ifdef __cplusplus
}
#endif

#endif