/*
 * Generic vector type.
 *
 * Author:  Ryan Davis
 * Date:    28/10/14
 */

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <template.h>

/* Vector prototype definitions. */
#define VECTOR_PROTOTYPE(name, type)                                           \
                                                                               \
struct TYPE(vector, name) {                                                    \
    int size;                                                                  \
    type *elem;                                                                \
};                                                                             \
                                                                               \
/* Class definition */                                                         \
extern const struct CLASS(vector, name, class) {                               \
    struct TYPE(vector, name) * (*new)(int size);                              \
    struct TYPE(vector, name) * (*copy)(const struct TYPE(vector, name) *vec); \
    void (*resize)(struct TYPE(vector, name) *vec, int size);                  \
    void (*push_back)(struct TYPE(vector, name) *vec, type data);              \
    type (*pop_back)(struct TYPE(vector, name) *vec);                          \
    void (*release)(struct TYPE(vector, name) **vec);                          \
} TYPE(vector, name);

/* Vector iterator */
#define foreach_vector(_type_, _elem_, _vec_, _body_)                          \
    if (_vec_ && _vec_->size > 0)                                              \
    {                                                                          \
        _type_ _elem_ = _vec_->elem[0];                                        \
        for (int _i_ = 0; _i_ < _vec_->size; ++_i_, _elem_ = _vec_->elem[_i_]) \
            _body_                                                             \
    }

/* Define vector prototypes from the provided definitions. */
#define TEMPLATE   VECTOR_PROTOTYPE
#include <vector.def>
#undef TEMPLATE

#endif
