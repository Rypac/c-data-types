/*
 * Generic point type.
 *
 * Author:  Ryan Davis
 * Date:    28/10/14
 */

#ifndef _POINT_H_
#define _POINT_H_

#include <template.h>

/* Point prototype definitions. */
#define POINT_PROTOTYPE(type)                                                  \
                                                                               \
struct TYPE(point, type) {                                                     \
    type x;                                                                    \
    type y;                                                                    \
    type z;                                                                    \
};                                                                             \
                                                                               \
struct TYPE(point, type) * FUNCTION(point, type, new)(type x, type y, type z); \
                                                                               \
struct TYPE(point, type) * FUNCTION(point, type, copy)(                        \
    const struct TYPE(point, type) *point);                                    \
                                                                               \
void FUNCTION(point, type, add)(                                               \
    struct TYPE(point, type) *p1,                                              \
    const struct TYPE(point, type) *p2);                                       \
                                                                               \
void FUNCTION(point, type, subtract)(                                          \
    struct TYPE(point, type) *p1,                                              \
    const struct TYPE(point, type) *p2);                                       \
                                                                               \
void FUNCTION(point, type, release)(struct TYPE(point, type) **point);

/* Generic point function accessors. */
#define point(type)                     TYPE(point, type)
#define point_new(type, x, y, z)        FUNCTION(point, type, new)(x, y, z)
#define point_copy(type, p)             FUNCTION(point, type, copy)(p)
#define point_add(type, p1, p2)         FUNCTION(point, type, add)(p1, p2)
#define point_subtract(type, p1, p2)    FUNCTION(point, type, subtract)(p1, p2)
#define point_release(type, p)          FUNCTION(point, type, release)(&p)

/* Define point prototypes from the provided definitions. */
#define TEMPLATE    POINT_PROTOTYPE
#include <point.def>
#undef TEMPLATE

#endif
