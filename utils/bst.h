#ifndef BST_H
#define BST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#define _DEFINE_TYPED_BST_NODE(type)                                                                                                    \
    typedef struct bst_##type##_node {                                                                                                  \
        type _value;                                                                                                                    \
        struct bst_##type##_node* _left;                                                                                                \
        struct bst_##type##_node* _right;                                                                                               \
    } bst_##type##_node;  

#define _ALLOCATE_BST_NODE(type, node_ptr, value, left_ptr, right_ptr) {                                                                \
    node_ptr = (list_##type##_node*)malloc(sizeof(list_##type##_node));                                                                 \
    node_ptr->_value = value;                                                                                                           \
    node_ptr->_prev = prev_ptr;                                                                                                         \
    node_ptr->_next = next_ptr;                                                                                                         \
}                                                                                                                                       \

// #define _DEFINE_BST_INIT_FUN(type)                                                                                                      \
//     inline void _bst_##type##_init(bst_##type* obj) {                                                                                   \
//         assert(obj != NULL && "_bst_"#type"_init(bst_"#type"* obj): obj is NULL");                                                      \
//         obj->_size = 0;                                                                                                                 \
//         obj->_root = NULL;                                                                                                              \
//         _ALLOCATE_LIST_NODE(type, obj->_tail, (type)0, obj->_head, NULL);                                                               \
//     }                                                                                                                                   \

#define _DEFINE_TYPED_BST(type)                                                                                                         \
    _DEFINE_TYPED_BST_NODE(type);                                                                                                       \
    typedef struct bst_##type {                                                                                                         \
        size_t _size;                                                                                                                   \
        bst_##type##_node* _root;                                                                                                       \
    } bst_##type;                                                                                                                       \
    \

#ifdef __cplusplus
}
#endif

#endif