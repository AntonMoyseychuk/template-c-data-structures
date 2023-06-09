#ifndef BST_H
#define BST_H

#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define __ALLOCATE_BST_NODE(type, node_ptr, value, left_ptr, right_ptr) {                                                               \
    node_ptr = (_bst_##type##_node*)malloc(sizeof(_bst_##type##_node));                                                                 \
    node_ptr->_value = value;                                                                                                           \
    node_ptr->_left = left_ptr;                                                                                                         \
    node_ptr->_right = right_ptr;                                                                                                       \
} 
                                                                                                                                      

#define _DEFINE_TYPED_BST_NODE(type)                                                                                                    \
    typedef struct _bst_##type##_node {                                                                                                 \
        type _value;                                                                                                                    \
        struct _bst_##type##_node* _left;                                                                                               \
        struct _bst_##type##_node* _right;                                                                                              \
    } _bst_##type##_node;  

#define _DEFINE_BST_INIT_FUN(type)                                                                                                      \
    inline void _bst_##type##_init(bst_##type* obj) {                                                                                   \
        assert(obj != NULL);                                                                                                            \
        obj->_size = 0;                                                                                                                 \
        obj->_root = NULL;                                                                                                              \
    }                                                                                                                                   \

#define __DEFINE_BST_FREE_RECURSIVE_FUN(type)                                                                                           \
    inline void __bst_##type##_free_recursive(_bst_##type##_node* node) {                                                               \
        if (node == NULL) {                                                                                                             \
            return;                                                                                                                     \
        }                                                                                                                               \
        __bst_##type##_free_recursive(node->_left);                                                                                     \
        __bst_##type##_free_recursive(node->_right);                                                                                    \
        free(node);                                                                                                                     \
    }                                                                                                                                   \

#define _DEFINE_BST_FREE_FUN(type)                                                                                                      \
    inline void _bst_##type##_free(bst_##type* obj) {                                                                                   \
        assert(obj != NULL);                                                                                                            \
        obj->_size = 0;                                                                                                                 \
        __bst_##type##_free_recursive(obj->_root);                                                                                      \
    }                                                                                                                                   \

#define __DEFINE_BST_FIND_RECURSIVE_FUN(type)                                                                                           \
    inline _bst_##type##_node* __bst_##type##_find_recursive(const _bst_##type##_node* node, type value) {                              \
        if (node == NULL) {                                                                                                             \
            return NULL;                                                                                                                \
        }                                                                                                                               \
        if (value == node->_value) {                                                                                                    \
            return node;                                                                                                                \
        }                                                                                                                               \
        return __bst_##type##_find_recursive(value < node->_value ? node->_left : node->_right, value);                                 \
    }

#define _DEFINE_BST_FIND_FUN(type)                                                                                                      \
    inline _bst_##type##_node* _bst_##type##_find(const bst_##type* obj, type value) {                                                  \
        assert(obj != NULL);                                                                                                            \
        return __bst_##type##_find_recursive(obj->_root, value);                                                                        \
    }

#define __DEFINE_BST_INSERT_RECURSIVE_FUN(type)                                                                                         \
    inline _bst_##type##_node* __bst_##type##_insert_recursive(_bst_##type##_node* node, type value) {                                  \
        if (node == NULL) {                                                                                                             \
            __ALLOCATE_BST_NODE(type, node, value, NULL, NULL);                                                                         \
            return node;                                                                                                                \
        } else {                                                                                                                        \
            if (value < node->_value) {                                                                                                 \
                node->_left = __bst_##type##_insert_recursive(node->_left, value);                                                      \
            } else {                                                                                                                    \
                node->_right = __bst_##type##_insert_recursive(node->_right, value);                                                    \
            }                                                                                                                           \
            return node;                                                                                                                \
        }                                                                                                                               \
    }                                                                                                                                   \

#define _DEFINE_BST_INSERT_FUN(type)                                                                                                    \
    inline _bst_##type##_node* _bst_##type##_insert(bst_##type* obj, type value) {                                                      \
        assert(obj != NULL);                                                                                                            \
        _bst_##type##_node* is_exist = _bst_##type##_find(obj, value);                                                                  \
        if (is_exist) {                                                                                                                 \
            return NULL;                                                                                                                \
        }                                                                                                                               \
        obj->_root = __bst_##type##_insert_recursive(obj->_root, value);                                                                \
        ++obj->_size;                                                                                                                   \
        return obj->_root;                                                                                                              \
    }                                                                                                                                   \

#define __DEFINE_BST_ERASE_RECURSIVE_FUN(type)                                                                                          \
    inline _bst_##type##_node* __bst_##type##_erase_recursive(_bst_##type##_node* node, type value) {                                   \
        if (node == NULL) {                                                                                                             \
            return NULL;                                                                                                                \
        }                                                                                                                               \
        \
        if (value < node->_value) {                                                                                                     \
            node->_left = __bst_##type##_erase_recursive(node->_left, value);                                                           \
        } else if (value > node->_value) {                                                                                              \
            node->_right = __bst_##type##_erase_recursive(node->_right, value);                                                         \
        } else {                                                                                                                        \
            if (node->_left == NULL) {                                                                                                  \
                _bst_##type##_node* temp = node->_right;                                                                                \
                free(node);                                                                                                             \
                return temp;                                                                                                            \
            } else if (node->_right == NULL) {                                                                                          \
                _bst_##type##_node* temp = node->_left;                                                                                 \
                free(node);                                                                                                             \
                return temp;                                                                                                            \
            }                                                                                                                           \
            \
            _bst_##type##_node* most_left_node = node->_right;                                                                          \
            while(most_left_node != NULL && most_left_node->_left != NULL) {                                                            \
                most_left_node = most_left_node->_left;                                                                                 \
            }                                                                                                                           \
            node->_value = most_left_node->_value;                                                                                      \
            node->_right = __bst_##type##_erase_recursive(node->_right, most_left_node->_value);                                        \
        }                                                                                                                               \
        return node;                                                                                                                    \
    }                                                                                                                                   \

#define _DEFINE_BST_ERASE_FUN(type)                                                                                                     \
    inline void _bst_##type##_erase(bst_##type* obj, type value) {                                                                      \
        assert(obj != NULL);                                                                                                            \
        _bst_##type##_node* is_exist = _bst_##type##_find(obj, value);                                                                  \
        if (is_exist) {                                                                                                                 \
            __bst_##type##_erase_recursive(obj->_root, value);                                                                          \
            --obj->_size;                                                                                                               \
        }                                                                                                                               \
    }                                                                                                                                   \

#define DEFINE_TYPED_BST(type)                                                                                                          \
    _DEFINE_TYPED_BST_NODE(type);                                                                                                       \
    typedef struct _bst_##type {                                                                                                        \
        size_t _size;                                                                                                                   \
        _bst_##type##_node* _root;                                                                                                      \
    } bst_##type;                                                                                                                       \
    \
    _DEFINE_BST_INIT_FUN(type);                                                                                                         \
    __DEFINE_BST_FIND_RECURSIVE_FUN(type);                                                                                              \
    _DEFINE_BST_FIND_FUN(type);                                                                                                         \
    __DEFINE_BST_INSERT_RECURSIVE_FUN(type);                                                                                            \
    _DEFINE_BST_INSERT_FUN(type);                                                                                                       \
    __DEFINE_BST_FREE_RECURSIVE_FUN(type);                                                                                              \
    _DEFINE_BST_FREE_FUN(type);                                                                                                         \
    __DEFINE_BST_ERASE_RECURSIVE_FUN(type);                                                                                             \
    _DEFINE_BST_ERASE_FUN(type);                                                                                                        \


#define BST_DECLARE_INSTANCE(type, bst_name) bst_##type bst_name
#define BST_DEFAULT_CONSTRUCTOR(type, bst_ptr) _bst_##type##_init(bst_ptr)
#define BST_FREE(type, bst_ptr) _bst_##type##_free(bst_ptr)

#define BST_FIND(type, bst_ptr, value) _bst_##type##_find(bst_ptr, value)

#define BST_INSERT(type, bst_ptr, value) _bst_##type##_insert(bst_ptr, value)
#define BST_ERASE(type, bst_ptr, value) _bst_##type##_erase(bst_ptr, value)


#ifdef __cplusplus
}
#endif

#endif