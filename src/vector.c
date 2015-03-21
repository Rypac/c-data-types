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
static struct TYPE(vector, name) * FUNCTION(vector, name, copy)(               \
    const struct TYPE(vector, name) *vector)                                   \
{                                                                              \
    struct TYPE(vector, name) *copy =                                          \
        FUNCTION(vector, name, new)(vector->size);                             \
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
static int FUNCTION(vector, name, resize)(                                     \
    struct TYPE(vector, name) *vector,                                         \
    int size)                                                                  \
{                                                                              \
    type *resized_vector =  realloc(vector->data, size * sizeof(type));        \
    if (!resized_vector)                                                       \
    {                                                                          \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    vector->data = resized_vector;                                             \
    vector->size = size;                                                       \
                                                                               \
    return 0;                                                                  \
}                                                                              \
                                                                               \
static int FUNCTION(vector, name, extend)(                                     \
    struct TYPE(vector, name) *vector,                                         \
    int size)                                                                  \
{                                                                              \
    return FUNCTION(vector, name, resize)(vector, vector->size + size);        \
}                                                                              \
                                                                               \
static int FUNCTION(vector, name, push_back)(                                  \
    struct TYPE(vector, name) *vector,                                         \
    type data)                                                                 \
{                                                                              \
    if (FUNCTION(vector, name, extend)(vector, 1) < 0)                         \
    {                                                                          \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    vector->data[vector->size - 1] = data;                                     \
                                                                               \
    return 0;                                                                  \
}                                                                              \
                                                                               \
static void FUNCTION(vector, name, release)(struct TYPE(vector, name) **vector)\
{                                                                              \
    if (vector && *vector)                                                     \
    {                                                                          \
        if ((*vector)->data)                                                   \
        {                                                                      \
            free((*vector)->data);                                             \
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
    .extend = &FUNCTION(vector, name, extend),                                 \
    .push_back = &FUNCTION(vector, name, push_back),                           \
    .release = &FUNCTION(vector, name, release)                                \
};

/* Define vector functions from the provided definitions. */
#define TEMPLATE   VECTOR_FUNCTIONS
#include <vector.def>
#undef TEMPLATE
