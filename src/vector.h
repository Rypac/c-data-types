/*
 * Generic vector type.
 *
 * Author:  Ryan Davis
 * Date:    25/10/14
 */

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdlib.h>

/*
 * Vector protoype definition.
 * This should be defined once per type to avoid duplication of types.
 */
#define VECTOR_PROTOTYPE(type)                                                 \
                                                                               \
struct vector_##type {                                                         \
    int size;                                                                  \
    type *data;                                                                \
};

/*
 * Vector function definitions.
 * These should be defined once in each file that they are used to avoid
 * duplicate function symbols over multiple files.
 */
#define VECTOR_FUNCTIONS(type)                                                 \
                                                                               \
static inline struct vector_##type * vector_##type##_new(int size)             \
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
static inline struct vector_##type * vector_##type##_copy(                     \
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
static inline type vector_##type##_min(const struct vector_##type *vector)     \
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
static inline type vector_##type##_max(const struct vector_##type *vector)     \
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
static inline void vector_##type##_release(struct vector_##type *vector)       \
{                                                                              \
    if (vector)                                                                \
    {                                                                          \
        free(vector->data);                                                    \
        free(vector);                                                          \
    }                                                                          \
}

/* Generic function accessors. */
#define vector(type)                    struct vector_##type
#define vector_new(type, size)          vector_##type##_new(size)
#define vector_copy(type, vector)       vector_##type##_copy(vector)
#define vector_min(type, vector)        vector_##type##_min(vector)
#define vector_max(type, vector)        vector_##type##_max(vector)
#define vector_release(type, vector)    vector_##type##_release(vector)

/* Definitions of commonly used vector types. */
VECTOR_PROTOTYPE(int);
VECTOR_PROTOTYPE(float);
VECTOR_PROTOTYPE(double);

#endif
