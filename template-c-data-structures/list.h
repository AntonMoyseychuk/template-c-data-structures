#ifndef LIST_H
#define LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <memory.h>
#include <assert.h>
#include <stdlib.h>

#include <stdio.h>


#define _DEFINE_TYPED_LIST_NODE(type)                                                                                                   \
    typedef struct list_##type##_node {                                                                                                 \
        type _value;                                                                                                                    \
        struct list_##type##_node* _next;                                                                                               \
        struct list_##type##_node* _prev;                                                                                               \
    } list_##type##_node;  

#define _DEFINE_LIST_INIT_FUN(type)                                                                                                     \
    inline void _list_##type##_init(list_##type* obj) {                                                                                 \
        assert(obj != NULL && "_list_"#type"_init(list_"#type"* obj): obj is NULL");                                                    \
        obj->_size = 0;                                                                                                                 \
        obj->_head = NULL;                                                                                                              \
        obj->_tail = (list_##type##_node*)malloc(sizeof(list_##type##_node));                                                           \
        obj->_tail->_prev = obj->_head;                                                                                                 \
        obj->_tail->_next = NULL;                                                                                                       \
    }                                                                                                                                   \

#define _DEFINE_LIST_FREE_FUN(type)                                                                                                     \
    inline void _list_##type##_free(list_##type* obj) {                                                                                 \
        if (obj != NULL) {                                                                                                              \
            for (size_t i = 0; i < obj->_size; ++i) {                                                                                   \
                list_##type##_node* curr = obj->_head;                                                                                  \
                obj->_head = obj->_head->_next;                                                                                         \
                free(curr);                                                                                                             \
            }                                                                                                                           \
            free(obj->_tail);                                                                                                           \
            obj->_size = 0;                                                                                                             \
            obj->_head = obj->_tail = NULL;                                                                                             \
        }                                                                                                                               \
    }                                                                                                                                   \

// #define _DEFINE_LIST_PUSH_FRONT_FUN(type)                                                                                               \
//     inline void _list_##type##_push_front(list_##type* obj, type value) {                                                               \
//         assert(obj != NULL && "_list_"#type"_push_front(vector_"#type"* obj, type value): obj is NULL");                                \
//         ++obj->_size;                                                                                                                   \
//         if (obj->_head == NULL && obj->_tail == NULL) {                                                                                 \
//             obj->_head = (list_##type##_node*)malloc(sizeof(list_##type##_node));                                                       \
//             obj->_tail = (list_##type##_node*)malloc(sizeof(list_##type##_node));                                                       \
//             obj->_head->_value = value;                                                                                                 \
//             obj->_head->_prev = NULL;                                                                                                   \
//             obj->_head->_next = obj->_tail;                                                                                             \
//             obj->_tail->_prev = obj->_head;                                                                                             \
//             obj->_tail->_next = NULL;                                                                                                   \
//             memset(&obj->_tail->_value, 0, sizeof(obj->_tail->_value));                                                                 \
//         } else {                                                                                                                        \
//             list_##type##_node* temp = (list_##type##_node*)malloc(sizeof(list_##type##_node));                                         \
//             temp->_value = value;                                                                                                       \
//             temp->_prev = NULL;                                                                                                         \
//             temp->_next = obj->_head;                                                                                                   \
//             obj->_head = temp;                                                                                                          \
//         }                                                                                                                               \
//     }                                                                                                                                   \

// #define _DEFINE_LIST_PUSH_BACK_FUN(type)                                                                                                \
//     inline void _list_##type##_push_back(list_##type* obj, type value) {                                                                \
//         assert(obj != NULL && "_list_"#type"_push_back(vector_"#type"* obj, type value): obj is NULL");                                 \
//         ++obj->_size;                                                                                                                   \
//         if (obj->_size == 0) {                                                                                                          \
//             obj->_head = (list_##type##_node*)malloc(sizeof(list_##type##_node));                                                       \
//             obj->_tail = (list_##type##_node*)malloc(sizeof(list_##type##_node));                                                       \
//             obj->_head->_value = value;                                                                                                 \
//             obj->_head->_prev = NULL;                                                                                                   \
//             obj->_head->_next = obj->_tail;                                                                                             \
//             obj->_tail->_prev = obj->_head;                                                                                             \
//             obj->_tail->_next = NULL;                                                                                                   \
//             memset(&obj->_tail->_value, 0, sizeof(obj->_tail->_value));                                                                 \
//         } else {                                                                                                                        \
//             list_##type##_node* temp = (list_##type##_node*)malloc(sizeof(list_##type##_node));                                         \
//             temp->_value = value;                                                                                                       \
//             temp->_prev = obj->_tail->_prev;                                                                                            \
//             temp->_next = obj->_tail;                                                                                                   \
//             obj->_tail->_prev = temp;                                                                                                   \
//         }                                                                                                                               \
//     }                                                                                                                                   \

#define _DEFINE_LIST_POP_BACK_FUN(type)                                                                                                 \
    inline void _list_##type##_pop_back(list_##type* obj) {                                                                             \
        assert(obj != NULL && "_list_"#type"_pop_back(vector_"#type"* obj): obj is NULL");                                              \
        if (obj->_size > 0) {                                                                                                           \
            list_##type##_node* temp = obj->_tail->_prev;                                                                               \
            if (obj->_size == 1) {                                                                                                      \
                obj->_head = NULL;                                                                                                      \
                obj->_tail->_prev = NULL;                                                                                               \
            } else {                                                                                                                    \
                temp->_prev->_next = obj->_tail;                                                                                        \
                obj->_tail->_prev = temp->_prev;                                                                                        \
            }                                                                                                                           \
            free(temp);                                                                                                                 \
            --obj->_size;                                                                                                               \
        }                                                                                                                               \
    }                                                                                                                                   \

#define _DEFINE_LIST_POP_FRONT_FUN(type)                                                                                                \
    inline void _list_##type##_pop_front(list_##type* obj) {                                                                            \
        assert(obj != NULL && "_list_"#type"_pop_front(vector_"#type"* obj): obj is NULL");                                             \
        if (obj->_size > 0) {                                                                                                           \
            list_##type##_node* temp = obj->_head;                                                                                      \
            if (obj->_size == 1) {                                                                                                      \
                obj->_head = NULL;                                                                                                      \
                obj->_tail->_prev = NULL;                                                                                               \
            } else {                                                                                                                    \
                obj->_head->_next->_prev = NULL;                                                                                              \
                obj->_head = obj->_head->_next;                                                                                               \
            }                                                                                                                           \
            free(temp);                                                                                                                 \
            --obj->_size;                                                                                                               \
        }                                                                                                                               \
    }                                                                                                                                   \

#define _DEFINE_LIST_SIZE_FUN(type)                                                                                                     \
    inline size_t _list_##type##_size(const list_##type* obj) {                                                                         \
        assert(obj != NULL && "_list_"#type"_size(vector_"#type"* obj): obj is NULL");                                                  \
        return obj->_size;                                                                                                              \
    }                                                                                                                                   \

#define DEFINE_TYPED_LIST(type)                                                                                                         \
    _DEFINE_TYPED_LIST_NODE(type);                                                                                                      \
    typedef struct list_##type {                                                                                                        \
        size_t _size;                                                                                                                   \
        list_##type##_node* _head;                                                                                                      \
        list_##type##_node* _tail;                                                                                                      \
    } list_##type;                                                                                                                      \
    \
    _DEFINE_LIST_INIT_FUN(type);                                                                                                        \
    _DEFINE_LIST_FREE_FUN(type);                                                                                                        \
    _DEFINE_LIST_SIZE_FUN(type);                                                                                                        \
    _DEFINE_LIST_POP_BACK_FUN(type);                                                                                                    \
    _DEFINE_LIST_POP_FRONT_FUN(type);                                                                                                   \
    // _DEFINE_LIST_PUSH_FRONT_FUN(type);                                                                                                  \
    // _DEFINE_LIST_PUSH_BACK_FUN(type);                                                                                                   \
    

#define LIST_CREATE(type, list_name) list_##type list_name; _list_##type##_init(&list_name)
#define LIST_FREE(type, list_ptr) _list_##type##_free(list_ptr)


#define LIST_SIZE(type, list_ptr) _list_##type##_size(list_ptr)


// #define LIST_PUSH_FRONT(type, list_ptr, value) _list_##type##_push_front(list_ptr, value)
// #define LIST_PUSH_BACK(type, list_ptr, value) _list_##type##_push_back(list_ptr, value)
#define LIST_POP_BACK(type, list_ptr) _list_##type##_pop_back(list_ptr)
#define LIST_POP_FRONT(type, list_ptr) _list_##type##_pop_front(list_ptr)


#ifdef __cplusplus
}
#endif

#endif