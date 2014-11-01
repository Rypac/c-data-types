/*
 * Point examples.
 *
 * Author:  Ryan Davis
 * Date:    28/10/14
 */

#include <stdio.h>
#include <point.h>

int main(void)
{
    struct point(double) *point_1 = point_new(double, 1.1, 2.2, 3.3);
    struct point(int) *point_2 = point_new(int, 1, 2, 3);

    printf("I am a double type point with:\nx = %f\ny = %f\nz = %f\n",
        point_1->x, point_1->y, point_1->z);
    printf("I am an integer type point with:\nx = %d\ny = %d\nz = %d\n",
        point_2->x, point_2->y, point_2->z);

    point_release(double, point_1);
    point_release(int, point_2);

    return 0;
}
