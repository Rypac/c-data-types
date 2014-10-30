/*
 * Generic 2D matrix type.
 *
 * Author:  Ryan Davis
 * Date:    25/10/14
 */

#ifndef _MATRIX_H_
#define _MATRIX_H_

/* Definitions of any desired matrix types. */
#define MATRIX_TEMPLATE                                                        \
    MATRIX_DEFINE(int)                                                         \
    MATRIX_DEFINE(float)                                                       \
    MATRIX_DEFINE(double)

/* Matrix protoype definitions. */
#define MATRIX_PROTOTYPE(type)                                                 \
                                                                               \
struct matrix_##type {                                                         \
    int cols;                                                                  \
    int rows;                                                                  \
    type **data;                                                               \
};                                                                             \
                                                                               \
struct matrix_##type * matrix_##type##_new(int cols, int rows);                \
                                                                               \
void matrix_##type##_release(struct matrix_##type **matrix);

/* Defining the matrix prototypes from the initial definitions. */
#define MATRIX_DEFINE   MATRIX_PROTOTYPE
MATRIX_TEMPLATE
#undef MATRIX_DEFINE

/* Generic matrix function accessors. */
#define matrix(type)                    matrix_##type
#define matrix_new(type, cols, rows)    matrix_##type##_new(cols, rows)
#define matrix_release(type, matrix)    matrix_##type##_release(&matrix)

#endif
