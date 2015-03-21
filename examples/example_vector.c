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

    vector_int.resize(vec, 1);
    vec->elem[0] = 0;

    for (int i = 1; vec->size < 10; i *= 2)
    {
        vector_int.push_back(vec, i);
    }

    foreach_vector(int, element, vec,
    {
        printf("%d\n", element);
    })

    while (vec->size > 0)
    {
        printf("%d\n", vector_int.pop_back(vec));
    }

    vector_int.release(&vec);

    return 0;
}
