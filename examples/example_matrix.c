/*
 * Examples of using vector types.
 *
 * Author:  Ryan Davis
 * Date:    25/10/14
 */

#include <stdio.h>
#include "matrix.h"

int matrix_test(void)
{
    struct matrix_int *matrix = matrix_new(int, 15, 10);

    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->cols; j++)
        {
            matrix->data[i][j] = i + j;
        }
    }

    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->cols; j++)
        {
            printf("%d ", matrix->data[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    matrix_release(int, matrix);

    return 0;
}
