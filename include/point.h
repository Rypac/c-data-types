/*
 * Generic point type.
 */

#ifndef _POINT_H_
#define _POINT_H_

#include <stdlib.h>

/* Point prototype definitions. */
#define POINT_PROTOTYPE(name, T)                                               \
                                                                               \
struct point_## name {                                                         \
    T x;                                                                       \
    T y;                                                                       \
    T z;                                                                       \
};

#define point_create(p, x, y, z) {                                             \
    if (((p) = malloc(sizeof(*(p)))))                                          \
    {                                                                          \
       point_init(p, x, y, z);                                                 \
    }                                                                          \
}

#define point_init(p, _x, _y, _z) {                                            \
    (p)->x = (_x);                                                             \
    (p)->y = (_y);                                                             \
    (p)->z = (_z);                                                             \
}

#define point_destroy(p) {                                                     \
    free(p);                                                                   \
}

/* Define point prototypes from the XMACRO definitions. */
#define TEMPLATE    POINT_PROTOTYPE
#include "point.def"
#undef TEMPLATE

#endif
