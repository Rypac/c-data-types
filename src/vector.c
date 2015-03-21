/*
 * Generic vector type.
 *
 * Author:  Ryan Davis
 * Date:    28/10/14
 */

#include <stdlib.h>
#include <vector.h>

/* Vector function definitions. */
#define VECTOR_FUNCTIONS(name, type)                                           \
                                                                               \
static struct TYPE(vector, name) * FUNCTION(vector, name, new)(int size)       \
{                                                                              \
    struct TYPE(vector, name) *vector =                                        \
        malloc(sizeof(struct TYPE(vector, name)));                             \
    if (vector)                                                                \
    {                                                                          \
        vector->elem = (size > 0) ? malloc(size * sizeof(type)) : NULL;        \
        vector->size = size;                                                   \
    }                                                                          \
                                                                               \
    return vector;                                                             \
}                                                                              \
                                                                               \
static struct TYPE(vector, name) * FUNCTION(vector, name, copy)(               \
    const struct TYPE(vector, name) *vector)                                   \
{                                                                              \
    struct TYPE(vector, name) *copy =                                          \
        FUNCTION(vector, name, new)(vector->size);                             \
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
static void FUNCTION(vector, name, resize)(                                    \
    struct TYPE(vector, name) *vector,                                         \
    int new_size)                                                              \
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
static void FUNCTION(vector, name, push_back)(                                 \
    struct TYPE(vector, name) *vector,                                         \
    type data)                                                                 \
{                                                                              \
    FUNCTION(vector, name, resize)(vector, vector->size + 1);                  \
    vector->elem[vector->size - 1] = data;                                     \
}                                                                              \
                                                                               \
static type FUNCTION(vector, name, pop_back)(struct TYPE(vector, name) *vector)\
{                                                                              \
    type element = vector->elem[vector->size - 1];                             \
    FUNCTION(vector, name, resize)(vector, vector->size - 1);                  \
    return element;                                                            \
}                                                                              \
                                                                               \
static void FUNCTION(vector, name, release)(struct TYPE(vector, name) **vector)\
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
}                                                                              \
                                                                               \
/* Class definition */                                                         \
const struct CLASS(vector, name, class) TYPE(vector, name) = {                 \
    .new = &FUNCTION(vector, name, new),                                       \
    .copy = &FUNCTION(vector, name, copy),                                     \
    .resize = &FUNCTION(vector, name, resize),                                 \
    .push_back = &FUNCTION(vector, name, push_back),                           \
    .pop_back = &FUNCTION(vector, name, pop_back),                             \
    .release = &FUNCTION(vector, name, release)                                \
};

/* Define vector functions from the provided definitions. */
#define TEMPLATE   VECTOR_FUNCTIONS
#include <vector.def>
#undef TEMPLATE
