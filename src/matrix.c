/*
 * Generic 2D matrix type.
 *
 * Author:  Ryan Davis
 * Date:    25/10/14
 */

#include <stdlib.h>
#include "matrix.h"

/* Matrix function definitions. */
#define MATRIX_FUNCTIONS(type)                                                 \
                                                                               \
struct TYPE(matrix, type) * FUNCTION(matrix, type, new)(int cols, int rows)    \
{                                                                              \
    struct TYPE(matrix, type) *matrix =                                        \
        malloc(sizeof(struct TYPE(matrix, type)));                             \
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
void FUNCTION(matrix, type, release)(struct TYPE(matrix, type) **matrix)       \
{                                                                              \
    if (matrix && *matrix)                                                     \
    {                                                                          \
        for (int i = 0; i < (*matrix)->rows; i++)                              \
        {                                                                      \
            free((*matrix)->data[i]);                                          \
        }                                                                      \
                                                                               \
        free((*matrix)->data);                                                 \
        free(*matrix);                                                         \
                                                                               \
        *matrix = NULL;                                                        \
    }                                                                          \
}

/* Define matrix functions from the provided definitions. */
#define TEMPLATE  MATRIX_FUNCTIONS
#include <matrix.def>
#undef TEMPLATE
