/*
 * Common definitions for templates.
 */

#ifndef _TEMPATE_H_
#define _TEMPATE_H_

#define STRING(x)                   # x

#define CONCAT(a, b)                a ## b
#define CONCAT_3(a, b, c)           a ## b ## c
#define CONCAT_4(a, b, c, d)        a ## b ## c ## d
#define CONCAT_5(a, b, c, d, e)     a ## b ## c ## d ## e

#define TYPE(name, type)            CONCAT_3(name, _, type)
#define FUNCTION(name, type, func)  CONCAT_5(name, _, type, _, func)

#endif
