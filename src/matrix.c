/*
 * Generic 2D matrix type.
 *
 * Author:  Ryan Davis
 * Date:    25/10/14
 */

#include <stdlib.h>
#include <matrix.h>

/* Matrix function definitions. */
#define MATRIX_FUNCTIONS(type)                                                 \
                                                                               \
struct matrix_##type * matrix_##type##_new(int cols, int rows)                 \
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
void matrix_##type##_release(struct matrix_##type *matrix)                     \
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

/* Defining matrix functions from the initial definitions. */
#define MATRIX_DEFINE   MATRIX_FUNCTIONS
MATRIX_TEMPLATE
#undef MATRIX_DEFINE
