#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


#include "libfr.h"


#ifndef _FR_VEC_H
#define _FR_VEC_H


#define VEC_MIN_SIZE 16

#define Vec(type)                                                              \
struct                                                                         \
{                                                                              \
    size_t _next_el;                                                           \
    size_t _capacity;                                                          \
    type *_buf;                                                                \
}


#define Vec_new(T)                                                             \
    malloc(sizeof(Vec(T)))


#define Vec_destroy(vec_ptr)                                                   \
    free(vec_ptr)


#define Vec_size(vec_ptr)                                                      \
    (vec_ptr->_next_el - 1)


#define Vec_capacity(vec_ptr)                                                  \
    (vec_ptr->_capacity)


#define Vec_get(vec_ptr, i)                                                    \
    (vec_ptr->_buf[i])


#define Vec_set(vec_ptr, i, val)                                               \
    vec_ptr->_buf[i] = val;


#define Vec_init(T, vec_ptr, len)                                              \
    vec_ptr->_next_el = 0;                                                     \
    vec_ptr->_capacity = max(2 * len, VEC_MIN_SIZE);                           \
    vec_ptr->_buf = _Vec_init_buf(T, len);


#define Vec_resize(T, vec_ptr, len)                                            \
    vec_ptr->_capcity = len;                                                   \
    vec_ptr->_next_el = min(vec_ptr->_next_el, vec_ptr->_capcity);             \
    T *__new_buf = _Vec_init_buf(T, vec_ptr->_capacity);                       \
    _Vec_copy_buf(vec_ptr->_buf, __new_buf, vec_ptr->_capacity);               \
    free(vec_ptr->_buf);                                                       \
    vec_ptr->_buf = __new_buf;                                                 \

#define Vec_push(T, vec_ptr, el)                                               \
    vec_ptr->_buf[vec_ptr->_next_el] = el;                                     \
    vec_ptr->_next_el++;                                                       \
    _Vec_grow(T, vec_ptr);


#define Vec_pop(T, vec_ptr, el) ({                                             \
    vec_ptr->_next_el--;                                                       \
    el = vec_ptr->_buf[vec_ptr->_next_el];                                     \
    _Vec_shrink(T, vec_ptr);                                                   \
})


#define Vec_foreach(vec_ptr, el)                                               \
    for (int i = 0;                                                            \
         i < vec_ptr->_next_el && ((el = vec_ptr->_buf[i]) || true);           \
         i++)                                                                  \


#define _Vec_init_buf(T, len) \
    malloc(sizeof(T) * len);


#define _Vec_copy_buf(old_buf, new_buf, len)                                   \
    for (size_t i = 0; i < len; i++) {                                         \
        new_buf[i] = old_buf[i];                                               \
    }


#define _Vec_grow(T, vec_ptr)                                                  \
    if (vec_ptr->_next_el >= vec_ptr->_capacity) {                             \
        vec_ptr->_capacity *= 2;                                               \
        T *__new_buf = _Vec_init_buf(T, vec_ptr->_capacity);                   \
        _Vec_copy_buf(vec_ptr->_buf, __new_buf, vec_ptr->_capacity);           \
        free(vec_ptr->_buf);                                                   \
        vec_ptr->_buf = __new_buf;                                             \
    }


#define _Vec_shrink(T, vec_ptr)                                                \
    if (                                                                       \
        vec_ptr->_capacity >= 2 * VEC_MIN_SIZE                                 \
        && vec_ptr->_next_el <= vec_ptr->_capacity / 4                         \
        && vec_ptr->_next_el                                                   \
    ) {                                                                        \
        vec_ptr->_capacity /= 2;                                               \
        T *__new_buf = _Vec_init_buf(T, vec_ptr->_capacity);                   \
        _Vec_copy_buf(vec_ptr->_buf, __new_buf, vec_ptr->_capacity);           \
        free(vec_ptr->_buf);                                                   \
        vec_ptr->_buf = __new_buf;                                             \
    }


#endif
