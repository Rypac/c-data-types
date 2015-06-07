#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdlib.h>

#define Vector(T)                                                              \
struct {                                                                       \
    int size;                                                                  \
    int capacity;                                                              \
    T *elem;                                                                   \
}

#define VECTOR_PROTOTYPE(name, T)                                              \
typedef Vector(T) Vector_##name;

#define vector_create(v, cap) do {                                             \
    if (((v) = malloc(sizeof(*(v))))) {                                        \
        vector_init(v, cap);                                                   \
    }                                                                          \
} while (0)

#define vector_init(v, cap) do {                                               \
    (v)->elem = ((cap) > 0) ? calloc((cap), sizeof(*((v)->elem))) : NULL;      \
    (v)->size = 0;                                                             \
    (v)->capacity = (cap);                                                     \
} while (0)

#define vector_wrap(v, data, len, cap) do {                                    \
    (v)->elem = data;                                                          \
    (v)->size = len;                                                           \
    (v)->capacity = cap;                                                       \
} while (0)

#define vector_size(v)                                                         \
    (v)->size

#define vector_capacity(v)                                                     \
    (v)->capacity

#define vector_data(v)                                                         \
    (v)->elem

#define vector_at(v, index)                                                    \
    (v)->elem[(index)]

#define vector_first(v)                                                        \
    (v)->elem[0]

#define vector_last(v)                                                         \
    (v)->elem[(v)->size - 1]

#define vector_clear(v) do {                                                   \
    memset((v)->elem, 0, (v)->capacity * sizeof(*((v)->elem)));                \
} while (0)

#define vector_resize(v, new_cap) do {                                         \
    (v)->elem = realloc((v)->elem, (new_cap) * sizeof(*((v)->elem)));          \
    (v)->capacity = (new_cap);                                                 \
} while (0)

#define vector_extend(v, new_cap) do {                                         \
    if ((new_cap) > (v)->capacity) {                                           \
        vector_resize(v, new_cap);                                             \
    }                                                                          \
} while (0)

#define vector_shrink(v) do {                                                  \
    if ((v)->size > 0) {                                                       \
        vector_resize(v, (v)->size);                                           \
    } else {                                                                   \
        vector_release(v);                                                     \
    }                                                                          \
} while (0)

#define vector_push_back(v, element) do {                                      \
    if ((v)->size >= (v)->capacity) {                                          \
        vector_resize(v, (((v)->size > 0) ? (v)->size * 2 : 1));               \
    }                                                                          \
    (v)->elem[(v)->size++] = (element);                                        \
} while (0)

#define vector_pop_back(v)                                                     \
    (v)->elem[--(v)->size]

#define vector_insert(v, element, index) do {                                  \
    if (index < (v)->size) {                                                   \
        (v)->elem[(index)] = (element);                                        \
    } else {                                                                   \
        vector_push_back(v, element);                                          \
    }                                                                          \
} while (0)

#define vector_release(v) do {                                                 \
    if ((v)->elem) {                                                           \
        free((v)->elem);                                                       \
        (v)->elem = 0;                                                         \
    }                                                                          \
    (v)->capacity = 0;                                                         \
    (v)->size = 0;                                                             \
} while (0)

#define vector_destroy(v) do {                                                 \
    vector_release(v);                                                         \
    free(v);                                                                   \
    (v) = NULL;                                                                \
} while (0)

#define foreach_vector(T, e, v, loop_body) do {                                \
    if ((v)->size > 0) {                                                       \
        T e = vector_first(v);                                                 \
        for (int _i_##e = 0; _i_##e < (v)->size; e = (v)->elem[++_i_##e])      \
            loop_body                                                          \
    }                                                                          \
} while (0);

/* Define vector prototypes from the XMACRO definitions. */
#define TEMPLATE VECTOR_PROTOTYPE
#include "vector.def"
#undef TEMPLATE

#endif
