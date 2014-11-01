/*
 * Generic 2D matrix type.
 *
 * Author:  Ryan Davis
 * Date:    25/10/14
 */

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <template.h>

/* Matrix prototype definitions. */
#define MATRIX_PROTOTYPE(type)                                                 \
                                                                               \
struct TYPE(matrix, type) {                                                    \
    int cols;                                                                  \
    int rows;                                                                  \
    type **data;                                                               \
};                                                                             \
                                                                               \
struct TYPE(matrix, type) * FUNCTION(matrix, type, new)(int cols, int rows);   \
                                                                               \
void FUNCTION(matrix, type, release)(struct TYPE(matrix, type) **matrix);

/* Generic matrix function accessors. */
#define matrix(type)                    TYPE(matrix, type)
#define matrix_new(type, cols, rows)    FUNCTION(matrix, type, new)(cols, rows)
#define matrix_release(type, m)         FUNCTION(matrix, type, release)(&m)

/* Define matrix prototypes from the provided definitions. */
#define TEMPLATE   MATRIX_PROTOTYPE
#include <matrix.def>
#undef TEMPLATE

#endif
