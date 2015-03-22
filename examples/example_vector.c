/*
 * Vector examples.
 *
 * Author:  Ryan Davis
 * Date:    22/03/15
 */

#include <stdio.h>
#include "point.h"
#include "vector.h"

/*
 * Simple example of a vector containing integer elements.
 *
 * This demonstrates use of the provided vector macros which are not confined to
 * a specific type of vector container.
 */
void vector_int_example(void)
{
    struct vector_int *vec;
    vector_new(vec, 2);

    printf("After initialisation:\n");
    printf("Size = %d\n", vector_size(vec));
    printf("Capacity = %d\n\n", vector_capacity(vec));

    vector_insert(vec, 1, 0);
    vector_insert(vec, 5, 1);

    for (int i = 1; vector_size(vec) < 10; i *= 2)
    {
        vector_push_back(vec, i);
    }

    foreach_vector(int, element, vec,
    {
        printf("%d\n", element);
    })

    printf("After adding elements:\n");
    printf("Size = %d\n", vector_size(vec));
    printf("Capacity = %d\n\n", vector_capacity(vec));

    vector_shrink(vec);

    printf("After shrinking:\n");
    printf("Size = %d\n", vector_size(vec));
    printf("Capacity = %d\n\n", vector_capacity(vec));

    while (vector_size(vec) > 0)
    {
        int element;
        vector_pop_back(vec, &element);
        printf("%d\n", element);
    }

    vector_release(vec);
}

/*
 * Example of using a template within a template.
 *
 * This example uses a vector template containing point_double elements, both of
 * which are generated from the template definitions.
 *
 * The functions provided by the vector template are used here as can be seen by
 * the long function names.
 */
void vector_point_example(void)
{
    struct vector_point_double *vec = vector_point_double_new(0);

    for (int i = 0; vector_point_double_size(vec) < 5; ++i)
    {
        struct point_double *point = point_double.new(i, i, i);
        vector_point_double_push_back(vec, point);
    }

    foreach_vector(struct point_double *, point, vec,
    {
        printf("Point: x = %0.1f, y = %0.1f, z = %0.1f\n",
            point->x, point->y, point->z);
    })

    while (vector_point_double_size(vec) > 0)
    {
        struct point_double *point = vector_point_double_pop_back(vec);
        point_double.release(&point);
    }

    vector_point_double_release(&vec);
}

int main(void)
{
    vector_int_example();
    vector_point_example();

    return 0;
}
