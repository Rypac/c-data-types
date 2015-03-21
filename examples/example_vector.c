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
    struct vector(int) *vec = vector(int).new(0);

    for (int i = 1; i < 200; i *= 2)
    {
        vector(int).push_back(vec, i);
    }

    int i;
    foreach_vector(i, vec)
    {
        printf("%d\n", i);
    }

    vector(int).release(&vec);

    return 0;
}
