/*
 * Generic vector type.
 */

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdlib.h>

/* Vector prototype definitions. */
#define VECTOR_PROTOTYPE(name, T)                                              \
                                                                               \
struct vector_## name {                                                        \
    size_t size;                                                               \
    size_t capacity;                                                           \
    T *elem;                                                                   \
};

#define vector_create(v, cap) {                                                \
    v = malloc(sizeof(*(v)));                                                  \
    vector_init(v, cap);                                                       \
}

#define vector_init(v, cap) {                                                  \
    (v)->elem = ((cap) > 0) ? malloc((cap) * sizeof((v)->elem)) : NULL;        \
    (v)->capacity = (cap);                                                     \
    (v)->size = 0;                                                             \
}

#define vector_size(v)                                                         \
    (v)->size

#define vector_capacity(v)                                                     \
    (v)->capacity

#define vector_elem(v, index)                                                  \
    (v)->elem[(index)]

#define vector_first(v)                                                        \
    (v)->elem[0]

#define vector_last(v)                                                         \
    (v)->elem[(v)->size - 1]

#define vector_resize(v, new_cap) {                                            \
    (v)->elem = realloc((v)->elem, (new_cap) * sizeof(*((v)->elem)));          \
    (v)->capacity = (new_cap);                                                 \
}

#define vector_shrink(v) {                                                     \
    vector_resize(v, (v)->size);                                               \
}

#define vector_push_back(v, element) {                                         \
    if ((v)->size >= (v)->capacity)                                            \
    {                                                                          \
        vector_resize(v, (((v)->size > 0) ? (v)->size * 2 : 1));               \
    }                                                                          \
    (v)->elem[(v)->size] = (element);                                          \
    (v)->size++;                                                               \
}

#define vector_pop_back(v, element) {                                          \
    *element = (v)->elem[(v)->size - 1];                                       \
    (v)->size--;                                                               \
}

#define vector_insert(v, element, index) {                                     \
    if (index < (v)->size)                                                     \
    {                                                                          \
        (v)->elem[(index)] = (element);                                        \
    }                                                                          \
    else                                                                       \
    {                                                                          \
        vector_push_back(v, element);                                          \
    }                                                                          \
}

#define vector_release(v) {                                                    \
    if ((v)->elem)                                                             \
    {                                                                          \
        free((v)->elem);                                                       \
    }                                                                          \
    (v)->capacity = 0;                                                         \
    (v)->size = 0;                                                             \
}

#define vector_destroy(v) {                                                    \
    vector_release(v);                                                         \
    free(v);                                                                   \
}

#define foreach_vector(T, e, v, function) {                                    \
    if (vector_size(v) > 0)                                                    \
    {                                                                          \
        T e = vector_first(v);                                                 \
        for (size_t _i_ = 0; _i_ < vector_size(v); ++_i_,                      \
                e = vector_elem(v, _i_))                                       \
            function                                                           \
    }                                                                          \
}

/* Define vector prototypes from the XMACRO definitions. */
#define TEMPLATE   VECTOR_PROTOTYPE
#include "vector.def"
#undef TEMPLATE

#endif
