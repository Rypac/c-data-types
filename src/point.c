/*
 * Generic point type.
 *
 * Author:  Ryan Davis
 * Date:    28/10/14
 */

#include <stdlib.h>
#include <point.h>

/* Point function definitions. */
#define POINT_FUNCTIONS(type)                                                  \
                                                                               \
struct TYPE(point, type) * FUNCTION(point, type, new)(type x, type y, type z)  \
{                                                                              \
    struct TYPE(point, type) *point = malloc(sizeof(struct TYPE(point, type)));\
                                                                               \
    if (point)                                                                 \
    {                                                                          \
        point->x = x;                                                          \
        point->y = y;                                                          \
        point->z = z;                                                          \
    }                                                                          \
                                                                               \
    return point;                                                              \
}                                                                              \
                                                                               \
struct TYPE(point, type) * FUNCTION(point, type, copy)(                        \
    const struct TYPE(point, type) *p)                                         \
{                                                                              \
    return FUNCTION(point, type, new)(p->x, p->y, p->z);                       \
}                                                                              \
                                                                               \
void FUNCTION(point, type, add)(                                               \
    struct TYPE(point, type) *p1,                                              \
    const struct TYPE(point, type) *p2)                                        \
{                                                                              \
    p1->x += p2->x;                                                            \
    p1->y += p2->y;                                                            \
    p1->z += p2->z;                                                            \
}                                                                              \
                                                                               \
void FUNCTION(point, type, subtract)(                                          \
    struct TYPE(point, type) *p1,                                              \
    const struct TYPE(point, type) *p2)                                        \
{                                                                              \
    p1->x -= p2->x;                                                            \
    p1->y -= p2->y;                                                            \
    p1->z -= p2->z;                                                            \
}                                                                              \
                                                                               \
void FUNCTION(point, type, release)(struct TYPE(point, type) **point)          \
{                                                                              \
    if (point && *point)                                                       \
    {                                                                          \
        free(*point);                                                          \
        *point = NULL;                                                         \
    }                                                                          \
}

/* Define point functions from the provided definitions. */
#define TEMPLATE    POINT_FUNCTIONS
#include <point.def>
#undef TEMPLATE

// Unimplemented functions.
/*
double FUNCTION(point, dot)(const TYPE(point) *p1, const TYPE(point) *p2)
{
    return (double)(p1->x * p2->x + p1->y * p2->y + p1->z * p2->z);
}

double FUNCTION(point, magnitude)(const TYPE(point) *p)
{
    return sqrt(pow2(p1->x)+ pow2(p1->y) + pow2(p1->z));
}
*/
