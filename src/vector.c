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
struct vector_## name * vector_## name ##_new(int capacity)                    \
{                                                                              \
    struct vector_## name *vector = malloc(sizeof(struct vector_## name));     \
    if (vector)                                                                \
    {                                                                          \
        vector->elem = (capacity > 0) ? malloc(capacity * sizeof(type)) : NULL;\
        vector->capacity = capacity;                                           \
        vector->size = 0;                                                      \
    }                                                                          \
                                                                               \
    return vector;                                                             \
}                                                                              \
                                                                               \
inline int vector_## name ##_size(const struct vector_## name *vector)         \
{                                                                              \
    return vector->size;                                                       \
}                                                                              \
                                                                               \
inline int vector_## name ##_capacity(const struct vector_## name *vector)     \
{                                                                              \
    return vector->capacity;                                                   \
}                                                                              \
                                                                               \
inline type vector_## name ##_elem(                                            \
    const struct vector_## name *vector, int index)                            \
{                                                                              \
    return vector->elem[index];                                                \
}                                                                              \
                                                                               \
inline type vector_## name ##_first(const struct vector_## name *vector)       \
{                                                                              \
    return vector->elem[0];                                                    \
}                                                                              \
                                                                               \
inline type vector_## name ##_last(const struct vector_## name *vector)        \
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
    vector->capacity = new_size;                                               \
}                                                                              \
                                                                               \
inline void vector_## name ##_shrink(struct vector_## name *vector)            \
{                                                                              \
    vector_## name ##_resize(vector, vector->size);                            \
}                                                                              \
                                                                               \
void vector_## name ##_insert(                                                 \
    struct vector_## name *vector, type element, int index)                    \
{                                                                              \
    if (index >= vector->size)                                                 \
    {                                                                          \
        vector_## name ##_push_back(vector, element);                          \
    }                                                                          \
    else                                                                       \
    {                                                                          \
        vector->elem[index] = element;                                         \
    }                                                                          \
}                                                                              \
                                                                               \
void vector_## name ##_push_back(struct vector_## name *vector, type data)     \
{                                                                              \
    if (vector->size >= vector->capacity)                                      \
    {                                                                          \
        int new_capacity = (vector->size > 0) ? vector->size * 2 : 1;          \
        vector_## name ##_resize(vector, new_capacity);                        \
    }                                                                          \
    vector->elem[vector->size] = data;                                         \
    vector->size++;                                                            \
}                                                                              \
                                                                               \
type vector_## name ##_pop_back(struct vector_## name *vector)                 \
{                                                                              \
    type element = vector->elem[vector->size - 1];                             \
    vector->size--;                                                            \
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
