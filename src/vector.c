/*
 * Generic vector type.
 *
 * Author:  Ryan Davis
 * Date:    28/10/14
 */

#include <stdlib.h>
#include "vector.h"

/* Vector function definitions. */
#define VECTOR_FUNCTIONS(name, type)                                           \
                                                                               \
struct vector_## name * vector_## name ##_new(int size)                        \
{                                                                              \
    struct vector_## name *vector = malloc(sizeof(struct vector_## name));     \
    if (vector)                                                                \
    {                                                                          \
        vector->elem = (size > 0) ? malloc(size * sizeof(type)) : NULL;        \
        vector->size = size;                                                   \
    }                                                                          \
                                                                               \
    return vector;                                                             \
}                                                                              \
                                                                               \
int vector_## name ##_size(const struct vector_## name *vector)                \
{                                                                              \
    return vector->size;                                                       \
}                                                                              \
                                                                               \
type vector_## name ##_elem(const struct vector_## name *vector, int index)    \
{                                                                              \
    return vector->elem[index];                                                \
}                                                                              \
                                                                               \
type vector_## name ##_first(const struct vector_## name *vector)              \
{                                                                              \
    return vector->elem[0];                                                    \
}                                                                              \
                                                                               \
type vector_## name ##_last(const struct vector_## name *vector)               \
{                                                                              \
    return vector->elem[vector->size - 1];                                     \
}                                                                              \
                                                                               \
void vector_## name ##_resize(struct vector_## name *vector, int new_size)     \
{                                                                              \
    if (new_size > 0)                                                          \
    {                                                                          \
        vector->elem = realloc(vector->elem, new_size * sizeof(type));         \
    }                                                                          \
    else                                                                       \
    {                                                                          \
        if (vector->elem)                                                      \
        {                                                                      \
            free(vector->elem);                                                \
        }                                                                      \
        vector->elem = NULL;                                                   \
    }                                                                          \
    vector->size = new_size;                                                   \
}                                                                              \
                                                                               \
void vector_## name ##_insert(struct vector_## name *v, type elem, int index)  \
{                                                                              \
    v->elem[index] = elem;                                                     \
}                                                                              \
                                                                               \
void vector_## name ##_push_back(struct vector_## name *vector, type data)     \
{                                                                              \
    vector_## name ##_resize(vector, vector->size + 1);                        \
    vector->elem[vector->size - 1] = data;                                     \
}                                                                              \
                                                                               \
type vector_## name ##_pop_back(struct vector_## name *vector)                 \
{                                                                              \
    type element = vector->elem[vector->size - 1];                             \
    vector_## name ##_resize(vector, vector->size - 1);                        \
    return element;                                                            \
}                                                                              \
                                                                               \
struct vector_## name * vector_## name ##_copy(                                \
    const struct vector_## name *vector)                                       \
{                                                                              \
    struct vector_## name *copy = vector_## name ##_new(vector->size);         \
    if (copy)                                                                  \
    {                                                                          \
        for (int i = 0; i < copy->size; i++)                                   \
        {                                                                      \
            copy->elem[i] = vector->elem[i];                                   \
        }                                                                      \
    }                                                                          \
                                                                               \
    return copy;                                                               \
}                                                                              \
                                                                               \
void vector_## name ##_release(struct vector_## name **vector)                 \
{                                                                              \
    if (vector && *vector)                                                     \
    {                                                                          \
        if ((*vector)->elem)                                                   \
        {                                                                      \
            free((*vector)->elem);                                             \
        }                                                                      \
        free(*vector);                                                         \
        *vector = NULL;                                                        \
    }                                                                          \
}

/* Define vector functions from the provided definitions. */
#define TEMPLATE   VECTOR_FUNCTIONS
#include "vector.def"
#undef TEMPLATE
