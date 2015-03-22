/*
 * Generic vector type.
 *
 * Author:  Ryan Davis
 * Date:    28/10/14
 */

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "template.h"

/* Vector prototype definitions. */
#define VECTOR_PROTOTYPE(name, type)                                           \
                                                                               \
struct TYPE(vector, name) {                                                    \
    /* Public */                                                               \
    int (*size)(const struct TYPE(vector, name) *this);                        \
    type (*elem)(const struct TYPE(vector, name) *this, int index);            \
    type (*first)(const struct TYPE(vector, name) *this);                      \
    type (*last)(const struct TYPE(vector, name) *this);                       \
                                                                               \
    void (*resize)(struct TYPE(vector, name) *this, int size);                 \
    void (*insert)(struct TYPE(vector, name) *this, type element, int index);  \
    void (*push_back)(struct TYPE(vector, name) *this, type data);             \
    type (*pop_back)(struct TYPE(vector, name) *this);                         \
                                                                               \
    struct TYPE(vector, name) * (*copy)(const struct TYPE(vector, name) *this);\
    void (*release)(struct TYPE(vector, name) **this);                         \
                                                                               \
    /* Private */                                                              \
    struct {                                                                   \
        int size;                                                              \
        type *elem;                                                            \
    } internals;                                                               \
};                                                                             \
                                                                               \
/* Class definition */                                                         \
extern const struct CLASS(vector, name, class) {                               \
    struct TYPE(vector, name) * (*new)(int size);                              \
} TYPE(vector, name);

/* Vector iterator */
#define foreach_vector(_type_, _elem_, _vec_, _body_)                          \
    if (_vec_ && _vec_->size(_vec_) > 0)                                       \
    {                                                                          \
        _type_ _elem_ = _vec_->first(_vec_);                                   \
        for (int _i_ = 0;                                                      \
            _i_ < _vec_->size(_vec_);                                          \
            ++_i_, _elem_ = _vec_->elem(_vec_, _i_))                           \
            _body_                                                             \
    }

/* Define vector prototypes from the provided definitions. */
#define TEMPLATE   VECTOR_PROTOTYPE
#include <vector.def>
#undef TEMPLATE

#endif
