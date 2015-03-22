/*
 * Generic vector type.
 *
 * Author:  Ryan Davis
 * Date:    28/10/14
 */

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdlib.h>
#include "template.h"

/* Vector prototype definitions. */
#define VECTOR_PROTOTYPE(name, type)                                           \
                                                                               \
struct vector_## name {                                                        \
    int size;                                                                  \
    int capacity;                                                              \
    type *elem;                                                                \
};                                                                             \
                                                                               \
struct vector_## name * vector_## name ##_new(int capacity);                   \
int vector_## name ##_size(const struct vector_## name *v);                    \
int vector_## name ##_capacity(const struct vector_## name *v);                \
type vector_## name ##_elem(const struct vector_## name *v, int index);        \
type vector_## name ##_first(const struct vector_## name *v);                  \
type vector_## name ##_last(const struct vector_## name *v);                   \
void vector_## name ##_insert(struct vector_## name *v, type elem, int index); \
void vector_## name ##_resize(struct vector_## name *v, int new_size);         \
void vector_## name ##_push_back(struct vector_## name *v, type elem);         \
type vector_## name ##_pop_back(struct vector_## name *v);                     \
void vector_## name ##_release(struct vector_## name **vector);

#define vector_new(v, cap) {                                                   \
    v = malloc(sizeof(*v));                                                    \
    if (v)                                                                     \
    {                                                                          \
        (v)->elem = ((cap) > 0) ? malloc((cap) * sizeof((v)->elem)) : NULL;    \
        (v)->capacity = (cap);                                                 \
        (v)->size = 0;                                                         \
    }                                                                          \
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
        int new_capacity = ((v)->size > 0) ? (v)->size * 2 : 1;                \
        vector_resize(v, new_capacity);                                        \
    }                                                                          \
    (v)->elem[(v)->size] = (element);                                          \
    (v)->size++;                                                               \
}

#define vector_pop_back(v, element) {                                          \
    *element = (v)->elem[(v)->size - 1];                                       \
    (v)->size--;                                                               \
}

#define vector_insert(v, element, index) {                                     \
    if (index >= (v)->size)                                                    \
    {                                                                          \
        vector_push_back(v, element);                                          \
    }                                                                          \
    else                                                                       \
    {                                                                          \
        (v)->elem[(index)] = (element);                                        \
    }                                                                          \
}

#define vector_release(v) {                                                    \
    if (v)                                                                     \
    {                                                                          \
        if ((v)->elem)                                                         \
        {                                                                      \
            free((v)->elem);                                                   \
        }                                                                      \
        free(v);                                                               \
        v = NULL;                                                              \
    }                                                                          \
}

#define foreach_vector(T, e, v, function) {                                    \
    if (v && vector_size(v) > 0)                                               \
    {                                                                          \
        T e = vector_first(v);                                                 \
        for (int _i_ = 0; _i_ < vector_size(v); ++_i_, e = vector_elem(v, _i_))\
            function                                                           \
    }                                                                          \
}

/* Define vector prototypes from the provided definitions. */
#define TEMPLATE   VECTOR_PROTOTYPE
#include "vector.def"
#undef TEMPLATE

#endif
