#ifndef ARRAY_H
#define ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>

#define _DEFINE_ARRAY_INIT_FUN(type, size)                                                                                      \
    inline void _array_##type##_init(array_##type##_type* obj) {                                                                \
        assert(obj != NULL && "_array_"#type"_init(vector_"#type"* obj): obj is NULL");                                         \
        obj->_buffer = (type*)malloc(2 * sizeof(type));                                                                         \
        obj->_size = obj->_capacity = 0;                                                                                        \
    }

#define DEFINE_TYPED_ARRAY(type, size)                                                                                          \
    static_assert(size > 0, "size must be greater than 0");                                                                     \
    typedef struct array_##type##_##size {                                                                                      \
        type _buffer[size];                                                                                                     \
        type _size;                                                                                                             \
    } array_##type##_##size;                                                                                                    \

#ifdef __cplusplus
}
#endif

#endif