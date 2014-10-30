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
struct vector_##type * vector_##type##_new(int size)                           \
{                                                                              \
    struct vector_##type *vector = malloc(sizeof(struct vector_##type));       \
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
struct vector_##type * vector_##type##_copy(                                   \
    const struct vector_##type *vector)                                        \
{                                                                              \
    struct vector_##type *copy = vector_##type##_new(vector->size);            \
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
type vector_##type##_min(const struct vector_##type *vector)                   \
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
type vector_##type##_max(const struct vector_##type *vector)                   \
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
void vector_##type##_release(struct vector_##type **vector)                    \
{                                                                              \
    if (vector && *vector)                                                     \
    {                                                                          \
        free((*vector)->data);                                                 \
        free(*vector);                                                         \
        *vector = NULL;                                                        \
    }                                                                          \
}

/* Defining vector functions from the initial definitions. */
#define VECTOR_DEFINE   VECTOR_FUNCTIONS
VECTOR_TEMPLATE
#undef VECTOR_DEFINE
