/*
 * Generic 2D matrix type.
 *
 * Author:  Ryan Davis
 * Date:    25/10/14
 */

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stdlib.h>

/*
 * Matrix protoype definition.
 * This should be defined once per type to avoid duplication of types.
 */
#define MATRIX_PROTOTYPE(type)                                                 \
                                                                               \
struct matrix_##type {                                                         \
    int cols;                                                                  \
    int rows;                                                                  \
    type **data;                                                               \
};

/*
 * Matrix function definitions.
 * These should be defined once in each file that they are used to avoid
 * duplicate function symbols over multiple files.
 */
#define MATRIX_FUNCTIONS(type)                                                 \
                                                                               \
static inline struct matrix_##type * matrix_##type##_new(int cols, int rows)   \
{                                                                              \
    struct matrix_##type *matrix = malloc(sizeof(struct matrix_##type));       \
                                                                               \
    if (matrix)                                                                \
    {                                                                          \
        matrix->cols = cols;                                                   \
        matrix->rows = rows;                                                   \
        matrix->data = malloc(rows * sizeof(type *));                          \
                                                                               \
        for (int i = 0; i < rows; i++)                                         \
        {                                                                      \
            matrix->data[i] = malloc(cols * sizeof(type));                     \
        }                                                                      \
    }                                                                          \
                                                                               \
    return matrix;                                                             \
}                                                                              \
                                                                               \
static inline void matrix_##type##_release(struct matrix_##type *matrix)       \
{                                                                              \
    if (matrix)                                                                \
    {                                                                          \
        for (int i = 0; i < matrix->rows; i++)                                 \
        {                                                                      \
            free(matrix->data[i]);                                             \
        }                                                                      \
                                                                               \
        free(matrix->data);                                                    \
        free(matrix);                                                          \
    }                                                                          \
}

/* Generic function accessors. */
#define matrix(type)                    struct matrix_##type
#define matrix_new(type, cols, rows)    matrix_##type##_new(cols, rows)
#define matrix_release(type, matrix)    matrix_##type##_release(matrix)

/* Definitions of commonly used matrix types. */
MATRIX_PROTOTYPE(int);
MATRIX_PROTOTYPE(float);
MATRIX_PROTOTYPE(double);

#endif
