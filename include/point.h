/*
 * Generic point type.
 *
 * Author:  Ryan Davis
 * Date:    28/10/14
 */

#ifndef _POINT_H_
#define _POINT_H_

#include "template.h"

/* Point prototype definitions. */
#define POINT_PROTOTYPE(name, type)                                            \
                                                                               \
struct TYPE(point, name) {                                                     \
    type x;                                                                    \
    type y;                                                                    \
    type z;                                                                    \
};                                                                             \
                                                                               \
/* Class definition */                                                         \
extern const struct CLASS(point, name, class) {                                \
    struct TYPE(point, name) * (*new)(type x, type y, type z);                 \
    struct TYPE(point, name) * (*copy)(const struct TYPE(point, name) *point); \
    void (*release)(struct TYPE(point, name) **point);                         \
} TYPE(point, name);

/* Define point prototypes from the provided definitions. */
#define TEMPLATE    POINT_PROTOTYPE
#include <point.def>
#undef TEMPLATE

#endif
