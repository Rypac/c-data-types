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
                                                                               \
    if (vector)                                                                \
    {                                                                          \
        vector->size = size;                                                   \
        vector->data = malloc(size * sizeof(type));                            \
    }                                                                          \
                                                                               \
    return vector;                                                             \
}                                                                              \
                                                                               \
struct TYPE(vector, type) * FUNCTION(vector, type, copy)(                      \
    const struct TYPE(vector, type) *vector)                                   \
{                                                                              \
    struct TYPE(vector, type) *copy =                                          \
        FUNCTION(vector, type, new)(vector->size);                             \
                                                                               \
    if (copy)                                                                  \
    {                                                                          \
        for (int i = 0; i < copy->size; i++)                                   \
        {                                                                      \
            copy->data[i] = vector->data[i];                                   \
        }                                                                      \
    }                                                                          \
                                                                               \
    return copy;                                                               \
}                                                                              \
                                                                               \
int FUNCTION(vector, type, resize)(                                            \
    struct TYPE(vector, type) **vector,                                        \
    int size)                                                                  \
{                                                                              \
    struct TYPE(vector, type) *new_vector =                                    \
        realloc(*vector, size * sizeof(struct TYPE(vector, type)));            \
                                                                               \
    if (new_vector)                                                            \
    {                                                                          \
        *vector = new_vector;                                                  \
        (*vector)->size = size;                                                \
        return 0;                                                              \
    }                                                                          \
    else                                                                       \
    {                                                                          \
        return -1;                                                             \
    }                                                                          \
}                                                                              \
                                                                               \
type FUNCTION(vector, type, min)(const struct TYPE(vector, type) *vector)      \
{                                                                              \
    type min = vector->data[0];                                                \
                                                                               \
    for (int i = 0; i < vector->size; i++)                                     \
    {                                                                          \
        min = (vector->data[i] < min) ? vector->data[i] : min;                 \
    }                                                                          \
                                                                               \
    return min;                                                                \
}                                                                              \
                                                                               \
type FUNCTION(vector, type, max)(const struct TYPE(vector, type) *vector)      \
{                                                                              \
    type max = vector->data[0];                                                \
                                                                               \
    for (int i = 0; i < vector->size; i++)                                     \
    {                                                                          \
        max = (vector->data[i] > max) ? vector->data[i] : max;                 \
    }                                                                          \
                                                                               \
    return max;                                                                \
}                                                                              \
                                                                               \
void FUNCTION(vector, type, release)(struct TYPE(vector, type) **vector)       \
{                                                                              \
    if (vector && *vector)                                                     \
    {                                                                          \
        free((*vector)->data);                                                 \
        free(*vector);                                                         \
        *vector = NULL;                                                        \
    }                                                                          \
}

/* Define vector functions from the provided definitions. */
#define TEMPLATE   VECTOR_FUNCTIONS
#include <vector.def>
#undef TEMPLATE
