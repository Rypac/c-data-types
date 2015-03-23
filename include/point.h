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
#define POINT_PROTOTYPE(name, T)                                               \
                                                                               \
struct point_## name {                                                         \
    T x;                                                                       \
    T y;                                                                       \
    T z;                                                                       \
};

#define point_create(p, _x, _y, _z) {                                          \
    p = malloc(sizeof(*(p)));                                                  \
    point_init(p, _x, _y, _z);                                                 \
}

#define point_init(p, _x, _y, _z) {                                            \
    (p)->x = (_x);                                                             \
    (p)->y = (_y);                                                             \
    (p)->z = (_z);                                                             \
}

#define point_destroy(p) {                                                     \
    free(p);                                                                   \
}

/* Define point prototypes from the provided definitions. */
#define TEMPLATE    POINT_PROTOTYPE
#include "point.def"
#undef TEMPLATE

#endif
