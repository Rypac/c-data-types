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
 * Simple test of a vector containing integer elements.
 * This demonstrates the methods available to the vector template container.
 */
void int_test(void)
{
    struct vector_int *vec = vector_int.new(0);

    vec->resize(vec, 1);
    vec->insert(vec, 0, 0);

    for (int i = 1; vec->size(vec) < 10; i *= 2)
    {
        vec->push_back(vec, i);
    }

    printf("First element = %d\n", vec->first(vec));
    printf("Last element = %d\n", vec->last(vec));

    foreach_vector(int, element, vec,
    {
        printf("%d\n", element);
    })

    while (vec->size(vec) > 0)
    {
        printf("%d\n", vec->pop_back(vec));
    }

    vec->release(&vec);
}

/*
 * Test a template within a template.
 * This test uses a vector template containing point_double elements, both of
 * which are generated from the template definitions.
 */
void point_test(void)
{
    struct vector_point_double *vec = vector_point_double.new(0);

    for (int i = 0; vec->size(vec) < 5; ++i)
    {
        struct point_double *point = point_double.new(i, i, i);
        vec->push_back(vec, point);
    }

    foreach_vector(struct point_double *, point, vec,
    {
        printf("Point: x = %0.1f, y = %0.1f, z = %0.1f\n",
            point->x, point->y, point->z);
    })

    while (vec->size(vec) > 0)
    {
        struct point_double *point = vec->pop_back(vec);
        point_double.release(&point);
    }

    vec->release(&vec);
}

int main(void)
{
    int_test();
    point_test();

    return 0;
}
