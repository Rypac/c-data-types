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
static struct TYPE(vector, name) * FUNCTION(vector, name, new)(int size);      \
                                                                               \
static int FUNCTION(vector, name, size)(                                       \
    const struct TYPE(vector, name) *vector)                                   \
{                                                                              \
    return vector->internals.size;                                             \
}                                                                              \
                                                                               \
static type FUNCTION(vector, name, elem)(                                      \
    const struct TYPE(vector, name) *vector,                                   \
    int index)                                                                 \
{                                                                              \
    return vector->internals.elem[index];                                      \
}                                                                              \
                                                                               \
static type FUNCTION(vector, name, first)(                                     \
    const struct TYPE(vector, name) *vector)                                   \
{                                                                              \
    return vector->internals.elem[0];                                          \
}                                                                              \
                                                                               \
static type FUNCTION(vector, name, last)(                                      \
    const struct TYPE(vector, name) *vector)                                   \
{                                                                              \
    return vector->internals.elem[vector->internals.size - 1];                 \
}                                                                              \
                                                                               \
static void FUNCTION(vector, name, resize)(                                    \
    struct TYPE(vector, name) *vector,                                         \
    int new_size)                                                              \
{                                                                              \
    if (new_size > 0)                                                          \
    {                                                                          \
        vector->internals.elem =                                               \
            realloc(vector->internals.elem, new_size * sizeof(type));          \
    }                                                                          \
    else                                                                       \
    {                                                                          \
        if (vector->internals.elem)                                            \
        {                                                                      \
            free(vector->internals.elem);                                      \
        }                                                                      \
        vector->internals.elem = NULL;                                         \
    }                                                                          \
    vector->internals.size = new_size;                                         \
}                                                                              \
                                                                               \
static void FUNCTION(vector, name, insert)(                                    \
    struct TYPE(vector, name) *vector,                                         \
    type element,                                                              \
    int index)                                                                 \
{                                                                              \
    vector->internals.elem[index] = element;                                   \
}                                                                              \
                                                                               \
static void FUNCTION(vector, name, push_back)(                                 \
    struct TYPE(vector, name) *vector,                                         \
    type data)                                                                 \
{                                                                              \
    FUNCTION(vector, name, resize)(vector, vector->internals.size + 1);        \
    vector->internals.elem[vector->internals.size - 1] = data;                 \
}                                                                              \
                                                                               \
static type FUNCTION(vector, name, pop_back)(struct TYPE(vector, name) *vector)\
{                                                                              \
    type element = vector->internals.elem[vector->internals.size - 1];         \
    FUNCTION(vector, name, resize)(vector, vector->internals.size - 1);        \
    return element;                                                            \
}                                                                              \
                                                                               \
static struct TYPE(vector, name) * FUNCTION(vector, name, copy)(               \
    const struct TYPE(vector, name) *vector)                                   \
{                                                                              \
    struct TYPE(vector, name) *copy =                                          \
        FUNCTION(vector, name, new)(vector->internals.size);                   \
    if (copy)                                                                  \
    {                                                                          \
        for (int i = 0; i < copy->internals.size; i++)                         \
        {                                                                      \
            copy->internals.elem[i] = vector->internals.elem[i];               \
        }                                                                      \
    }                                                                          \
                                                                               \
    return copy;                                                               \
}                                                                              \
                                                                               \
static void FUNCTION(vector, name, release)(struct TYPE(vector, name) **vector)\
{                                                                              \
    if (vector && *vector)                                                     \
    {                                                                          \
        if ((*vector)->internals.elem)                                         \
        {                                                                      \
            free((*vector)->internals.elem);                                   \
        }                                                                      \
        free(*vector);                                                         \
        *vector = NULL;                                                        \
    }                                                                          \
}                                                                              \
                                                                               \
static struct TYPE(vector, name) * FUNCTION(vector, name, new)(int size)       \
{                                                                              \
    struct TYPE(vector, name) *vector =                                        \
        malloc(sizeof(struct TYPE(vector, name)));                             \
    if (vector)                                                                \
    {                                                                          \
        vector->internals.elem =                                               \
            (size > 0) ? malloc(size * sizeof(type)) : NULL;                   \
        vector->internals.size = size;                                         \
                                                                               \
        vector->size = &FUNCTION(vector, name, size);                          \
        vector->elem = &FUNCTION(vector, name, elem);                          \
        vector->first = &FUNCTION(vector, name, first);                        \
        vector->last = &FUNCTION(vector, name, last);                          \
        vector->insert = &FUNCTION(vector, name, insert);                      \
        vector->resize = &FUNCTION(vector, name, resize);                      \
        vector->push_back = &FUNCTION(vector, name, push_back);                \
        vector->pop_back = &FUNCTION(vector, name, pop_back);                  \
        vector->copy = &FUNCTION(vector, name, copy);                          \
        vector->release = &FUNCTION(vector, name, release);                    \
    }                                                                          \
                                                                               \
    return vector;                                                             \
}                                                                              \
                                                                               \
/* Class definition */                                                         \
const struct CLASS(vector, name, class) TYPE(vector, name) = {                 \
    .new = &FUNCTION(vector, name, new)                                        \
};

/* Define vector functions from the provided definitions. */
#define TEMPLATE   VECTOR_FUNCTIONS
#include <vector.def>
#undef TEMPLATE
