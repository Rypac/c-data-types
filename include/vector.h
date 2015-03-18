/*
 * Generic vector type.
 *
 * Author:  Ryan Davis
 * Date:    28/10/14
 */

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <template.h>

/* Vector prototype definitions. */
#define VECTOR_PROTOTYPE(type)                                                 \
                                                                               \
struct TYPE(vector, type) {                                                    \
    int size;                                                                  \
    type *data;                                                                \
};                                                                             \
                                                                               \
struct TYPE(vector, type) * FUNCTION(vector, type, new)(int size);             \
                                                                               \
struct TYPE(vector, type) * FUNCTION(vector, type, copy)(                      \
    const struct TYPE(vector, type) *vector);                                  \
                                                                               \
int FUNCTION(vector, type, resize)(                                            \
    struct TYPE(vector, type) *vector,                                         \
    int size);                                                                 \
                                                                               \
int FUNCTION(vector, type, extend)(                                            \
    struct TYPE(vector, type) *vector,                                         \
    int size);                                                                 \
                                                                               \
int FUNCTION(vector, type, push_back)(                                         \
    struct TYPE(vector, type) *vector,                                         \
    type data);                                                                \
                                                                               \
                                                                               \
void FUNCTION(vector, type, release)(struct TYPE(vector, type) **vector);

/* Generic vector function accessors. */
#define vector(type)                    TYPE(vector, type)
#define vector_new(type, size)          FUNCTION(vector, type, new)(size)
#define vector_copy(type, v)            FUNCTION(vector, type, copy)(v)
#define vector_resize(type, v, size)    FUNCTION(vector, type, resize)(v, size)
#define vector_extend(type, v, size)    FUNCTION(vector, type, extend)(v, size)
#define vector_push_back(type, v, data) FUNCTION(vector, type, push_back)(v, data)
#define vector_release(type, v)         FUNCTION(vector, type, release)(&v)

/* Vector iterator */
#define foreach_vector(element, vector)                                        \
    for (int i = 0; i < vector->count; ++i)                                    \
        if ((element = vector->data[i]))

/* Define vector prototypes from the provided definitions. */
#define TEMPLATE   VECTOR_PROTOTYPE
#include <vector.def>
#undef TEMPLATE

#endif
