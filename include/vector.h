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
    struct TYPE(vector, type) **vector,                                        \
    int size);                                                                 \
                                                                               \
type FUNCTION(vector, type, min)(const struct TYPE(vector, type) *vector);     \
                                                                               \
type FUNCTION(vector, type, max)(const struct TYPE(vector, type) *vector);     \
                                                                               \
void FUNCTION(vector, type, release)(struct TYPE(vector, type) **vector);

/* Generic vector function accessors. */
#define vector(type)                    TYPE(vector, type)
#define vector_new(type, size)          FUNCTION(vector, type, new)(size)
#define vector_copy(type, v)            FUNCTION(vector, type, copy)(v)
#define vector_resize(type, v, size)    FUNCTION(vector, type, resize)(&v, size)
#define vector_min(type, v)             FUNCTION(vector, type, min)(v)
#define vector_max(type, v)             FUNCTION(vector, type, max)(v)
#define vector_release(type, v)         FUNCTION(vector, type, release)(&v)

/* Define vector prototypes from the provided definitions. */
#define TEMPLATE   VECTOR_PROTOTYPE
#include <vector.def>
#undef TEMPLATE

#endif
