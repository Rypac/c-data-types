/*
 * Generic vector type.
 */

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdlib.h>

/* Vector prototype definitions. */
#define VECTOR_PROTOTYPE(name, T)                                              \
                                                                               \
struct vector_##name {                                                         \
    size_t size;                                                               \
    size_t capacity;                                                           \
    T *elem;                                                                   \
};

#define vector_create(v, cap) {                                                \
    if (((v) = malloc(sizeof(*(v)))))                                          \
    {                                                                          \
        vector_init(v, cap);                                                   \
    }                                                                          \
}

#define vector_init(v, cap) {                                                  \
    (v)->elem = ((cap) > 0) ? calloc((cap), sizeof(*((v)->elem))) : NULL;      \
    (v)->capacity = (cap);                                                     \
    (v)->size = 0;                                                             \
}

#define vector_size(v)                                                         \
    (v)->size

#define vector_capacity(v)                                                     \
    (v)->capacity

#define vector_data(v)                                                         \
    (v)->elem

#define vector_at(v, index)                                                    \
    ((index) >= 0 && (index) < (v)->size) ? (v)->elem[(index)] : 0

#define vector_first(v)                                                        \
    ((v)->size > 0) ? vector_data(v)[0] : 0

#define vector_last(v)                                                         \
    ((v)->size > 0) ? vector_data(v)[(v)->size - 1] : 0

#define vector_clear(v) {                                                      \
    memset((v)->elem, 0, (v)->capacity * sizeof(*((v)->elem)));                \
}

#define vector_resize(v, new_cap) {                                            \
    (v)->elem = realloc((v)->elem, (new_cap) * sizeof(*((v)->elem)));          \
    (v)->capacity = (new_cap);                                                 \
}

#define vector_extend(v, new_cap) {                                            \
    if ((new_cap) > (v)->capacity)                                             \
    {                                                                          \
        vector_resize(v, new_cap);                                             \
    }                                                                          \
}

#define vector_shrink(v) {                                                     \
    if ((v)->size > 0)                                                         \
    {                                                                          \
        vector_resize(v, (v)->size);                                           \
    }                                                                          \
    else                                                                       \
    {                                                                          \
        vector_release(v);                                                     \
    }                                                                          \
}

#define vector_push_back(v, element) {                                         \
    if ((v)->size >= (v)->capacity)                                            \
    {                                                                          \
        vector_resize(v, (((v)->size > 0) ? (v)->size * 2 : 1));               \
    }                                                                          \
    (v)->elem[(v)->size++] = (element);                                        \
}

#define vector_pop_back(v)                                                     \
    ((v)->size > 0) ? (v)->elem[--(v)->size] : 0

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
        (v)->elem = 0;                                                         \
    }                                                                          \
    (v)->capacity = 0;                                                         \
    (v)->size = 0;                                                             \
}

#define vector_destroy(v) {                                                    \
    vector_release(v);                                                         \
    free(v);                                                                   \
    (v) = NULL;                                                                \
}

#define foreach_vector(T, e, v, function) {                                    \
    if (vector_size(v) > 0)                                                    \
    {                                                                          \
        T e = vector_first(v);                                                 \
        for (size_t _i_##e = 0; _i_##e < vector_size(v); ++_i_##e,             \
                e = vector_at(v, _i_##e))                                      \
            function                                                           \
    }                                                                          \
}

/* Define vector prototypes from the XMACRO definitions. */
#define TEMPLATE   VECTOR_PROTOTYPE
#include "vector.def"
#undef TEMPLATE

#endif
