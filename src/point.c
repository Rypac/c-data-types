/*
 * Generic point type.
 *
 * Author:  Ryan Davis
 * Date:    28/10/14
 */

#include <stdlib.h>
#include "point.h"

/* Point function definitions. */
#define POINT_FUNCTIONS(name, type)                                            \
                                                                               \
static struct TYPE(point, name) * FUNCTION(point, type, new)(                  \
    type x,                                                                    \
    type y,                                                                    \
    type z)                                                                    \
{                                                                              \
    struct TYPE(point, name) *point = malloc(sizeof(struct TYPE(point, name)));\
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
static struct TYPE(point, name) * FUNCTION(point, type, copy)(                 \
    const struct TYPE(point, name) *p)                                         \
{                                                                              \
    return FUNCTION(point, type, new)(p->x, p->y, p->z);                       \
}                                                                              \
                                                                               \
static void FUNCTION(point, type, release)(struct TYPE(point, name) **point)   \
{                                                                              \
    if (point && *point)                                                       \
    {                                                                          \
        free(*point);                                                          \
        *point = NULL;                                                         \
    }                                                                          \
}                                                                              \
                                                                               \
/* Class definition */                                                         \
const struct CLASS(point, name, class) TYPE(point, name) = {                   \
    .new = &FUNCTION(point, name, new),                                        \
    .copy = &FUNCTION(point, name, copy),                                      \
    .release = &FUNCTION(point, name, release)                                 \
};

/* Define point functions from the provided definitions. */
#define TEMPLATE    POINT_FUNCTIONS
#include <point.def>
#undef TEMPLATE
