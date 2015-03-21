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
#define VECTOR_PROTOTYPE(name, type)                                           \
                                                                               \
struct TYPE(vector, name) {                                                    \
    int size;                                                                  \
    type *data;                                                                \
};                                                                             \
                                                                               \
/* Class definition */                                                         \
extern const struct CLASS(vector, name, class) {                               \
    struct TYPE(vector, name) * (*new)(int size);                              \
    struct TYPE(vector, name) * (*copy)(const struct TYPE(vector, name) *vec); \
    int (*resize)(struct TYPE(vector, name) *vec, int size);                   \
    int (*extend)(struct TYPE(vector, name) *vec, int size);                   \
    int (*push_back)(struct TYPE(vector, name) *vec, type data);               \
    void (*release)(struct TYPE(vector, name) **vec);                          \
} TYPE(vector, name);

/* Nicer looking type accessor. */
#define vector(type)    TYPE(vector, type)

/* Vector iterator */
#define foreach_vector(element, vector)                                        \
    for (int __it__ = 0; __it__ < vector->size; ++__it__)                      \
        if ((element = vector->data[__it__]))

/* Define vector prototypes from the provided definitions. */
#define TEMPLATE   VECTOR_PROTOTYPE
#include <vector.def>
#undef TEMPLATE

#endif
