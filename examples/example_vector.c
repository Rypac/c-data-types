/*
 * Vector examples.
 *
 * Author:  Ryan Davis
 * Date:    22/03/15
 */

#include <stdio.h>
#include <vector.h>

int main(void)
{
    struct vector_int *vec = vector_int.new(0);

    vec->resize(vec, 1);
    vec->insert(vec, 0, 0);

    for (int i = 1; vec->size(vec) < 10; i *= 2)
    {
        vec->push_back(vec, i);
    }

    printf("First = %d\n", vec->first(vec));
    printf("Last = %d\n", vec->last(vec));

    foreach_vector(int, element, vec,
    {
        printf("%d\n", element);
    })

    while (vec->size(vec) > 0)
    {
        printf("%d\n", vec->pop_back(vec));
    }

    vec->release(&vec);

    return 0;
}
