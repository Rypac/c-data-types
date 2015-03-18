/*
 * Examples of using vector types.
 *
 * Author:  Ryan Davis
 * Date:    25/10/14
 */

#include <stdio.h>
#include <vector.h>
#include <matrix.h>

void matrix_printer(struct matrix(int) *matrix)
{
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->cols; j++)
        {
            printf("%d ", matrix->data[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    // Using the vector_type struct explicitly.
    struct vector_int *ints = vector_int_new(10);
    struct vector_float *floats = vector_float_new(20);

    // Fill the vector with test data.
    for (int i = 0; i < ints->size; i++)
    {
        ints->data[i] = i;
    }
    for (int i = 0; i < floats->size; i++)
    {
        floats->data[i] = i + 0.5;
    }

    // Print out the contents of the vectors.
    for (int i = 0; i < ints->size; i++)
    {
        printf("%d\n", ints->data[i]);
    }
    printf("\n");

    for (int i = 0; i < floats->size; i++)
    {
        printf("%f\n", floats->data[i]);
    }
    printf("\n");

    vector_int_release(&ints);
    vector_float_release(&floats);

    // Using the generic vector(type) macro. IMHO these are much more
    // aesthetically pleasing.
    struct vector(double) *vector = vector_new(double, 10);

    for (int i = 0; i < vector->size; i++)
    {
        vector->data[i] = i * 2.1;
    }
    for (int i = 0; i < vector->size; i++)
    {
        printf("%f\n", vector->data[i]);
    }
    printf("\n");

    struct vector(double) *copy = vector_copy(double, vector);

    printf("Min: %f\n", vector_min(double, vector));
    printf("Max: %f\n", vector_max(double, vector));
    printf("Min: %f\n", vector_min(double, copy));
    printf("Max: %f\n", vector_max(double, copy));

    printf("Copied vector size: %d\n", copy->size);

    vector_resize(double, copy, 5);

    printf("Copied vector size: %d\n", copy->size);
    for (int i = 0; i < copy->size; i++)
    {
        printf("%f\n", copy->data[i]);
    }
    printf("\n");

    vector_release(double, vector);
    vector_release(double, copy);

    // Test the same with a matrix.
    struct matrix_int *matrix = matrix_new(int, 15, 10);

    // Fill the matrix.
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->cols; j++)
        {
            matrix->data[i][j] = i + j;
        }
    }

    matrix_printer(matrix);
    matrix_release(int, matrix);

    return 0;
}
