#ifndef UTIL_MACRO_H
#define UTIL_MACRO_H

#define _DEF_PTR_true(type) type*
#define _DEF_PTR_false(type) type
#define _DEF_PTR(type, is_ptr) _DEF_PTR_##is_ptr(type)

#endif