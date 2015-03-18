/*
 * Generic vector type.
 *
 * Author:  Ryan Davis
 * Date:    28/10/14
 */

#include <stdlib.h>
#include <vector.h>

/* Vector function definitions. */
#define VECTOR_FUNCTIONS(type)                                                 \
                                                                               \
struct TYPE(vector, type) * FUNCTION(vector, type, new)(int size)              \
{                                                                              \
    struct TYPE(vector, type) *vector =                                        \
        malloc(sizeof(struct TYPE(vector, type)));                             \
    if (!vector)                                                               \
    {                                                                          \
        return NULL;                                                           \
    }                                                                          \
                                                                               \
    vector->size = size;                                                       \
    vector->data = (size > 0) ? malloc(size * sizeof(type)) : NULL;            \
                                                                               \
    return vector;                                                             \
}                                                                              \
                                                                               \
struct TYPE(vector, type) * FUNCTION(vector, type, copy)(                      \
    const struct TYPE(vector, type) *vector)                                   \
{                                                                              \
    struct TYPE(vector, type) *copy =                                          \
        FUNCTION(vector, type, new)(vector->size);                             \
    if (!copy)                                                                 \
    {                                                                          \
        return NULL;                                                           \
    }                                                                          \
                                                                               \
    for (int i = 0; i < copy->size; i++)                                       \
    {                                                                          \
        copy->data[i] = vector->data[i];                                       \
    }                                                                          \
                                                                               \
    return copy;                                                               \
}                                                                              \
                                                                               \
int FUNCTION(vector, type, resize)(                                            \
    struct TYPE(vector, type) *vector,                                         \
    int size)                                                                  \
{                                                                              \
    type resized_vector =  realloc(vector->data, size * sizeof(type));         \
    if (!resized_vector)                                                       \
    {                                                                          \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    vector->data = resized_vector;                                             \
    vector->size = size;                                                       \
    return 0;                                                                  \
}                                                                              \
                                                                               \
int FUNCTION(vector, type, extend)(                                            \
    struct TYPE(vector, type) *vector,                                         \
    int size)                                                                  \
{                                                                              \
    return FUNCTION(vector, type, resize)(vector, vector->count + size);       \
}                                                                              \
                                                                               \
int FUNCTION(vector, type, push_back)(                                         \
    struct TYPE(vector, type) *vector,                                         \
    type data)                                                                 \
{                                                                              \
    if (FUNCTION(vector, type, extend)(vector, 1) < 0)                         \
    {                                                                          \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    vector->data[vector->count - 1] = data;                                    \
    return 0;                                                                  \
}                                                                              \
                                                                               \
void FUNCTION(vector, type, release)(struct TYPE(vector, type) **vector)       \
{                                                                              \
    if (vector && *vector)                                                     \
    {                                                                          \
        if (*(vector)->data)                                                   \
        {                                                                      \
            free((*vector)->data);                                             \
        }                                                                      \
        free(*vector);                                                         \
        *vector = NULL;                                                        \
    }                                                                          \
}

/* Define vector functions from the provided definitions. */
#define TEMPLATE   VECTOR_FUNCTIONS
#include <vector.def>
#undef TEMPLATE
