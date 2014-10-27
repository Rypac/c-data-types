/*
 * Generic vector type.
 *
 * Author:  Ryan Davis
 * Date:    28/10/14
 */

#ifndef _VECTOR_H_
#define _VECTOR_H_

/* Definitions of any desired vector types. */
#define VECTOR_TEMPLATE                                                        \
    VECTOR_DEFINE(int)                                                         \
    VECTOR_DEFINE(float)                                                       \
    VECTOR_DEFINE(double)

/* Vector protoype definitions. */
#define VECTOR_PROTOTYPE(type)                                                 \
                                                                               \
struct vector_##type {                                                         \
    int size;                                                                  \
    type *data;                                                                \
};                                                                             \
                                                                               \
struct vector_##type * vector_##type##_new(int size);                          \
                                                                               \
struct vector_##type * vector_##type##_copy(                                   \
    const struct vector_##type *vector);                                       \
                                                                               \
type vector_##type##_min(const struct vector_##type *vector);                  \
                                                                               \
type vector_##type##_max(const struct vector_##type *vector);                  \
                                                                               \
void vector_##type##_release(struct vector_##type *vector);

/* Defining the vector prototypes from the initial definitions. */
#ifndef VECTOR_DEFINE
    #define VECTOR_DEFINE   VECTOR_PROTOTYPE
    VECTOR_TEMPLATE
    #undef VECTOR_DEFINE
#endif

/* Generic vector function accessors. */
#define vector(type)                    struct vector_##type
#define vector_new(type, size)          vector_##type##_new(size)
#define vector_copy(type, vector)       vector_##type##_copy(vector)
#define vector_min(type, vector)        vector_##type##_min(vector)
#define vector_max(type, vector)        vector_##type##_max(vector)
#define vector_release(type, vector)    vector_##type##_release(vector)

#endif
