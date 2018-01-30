#ifndef _ARRAY_LIST_ILLUSTRATION_H
#define _ARRAY_LIST_ILLUSTRATION_H

#include <stdlib.h>
#include <string.h>       // For strcmp(), strcpy().
#include <time.h>         // For srand(), rand().
#include <unistd.h>       // For sleep().
#include "../../header.h"
#include "array_list.h"

/** \def print_color(color, num)
 *
 * Macro function to print an integer in 
 * given color.
 */
#define print_int_color(color, num) ({\
    printf("\033[%s%3d\033[0m|", color, num);\
})

/** \def print_int_default(num)
 *
 * Macro function to print an integer in
 * default color.
 */
#define print_int_default(num) ({\
    printf("%3d|", num);\
})

void print_line(size_type n);
void print_array_list(parray_list pa, size_type begin, size_type end, size_type b, size_type e, const char *color);
void print_array_list_all_default(parray_list pa);
void print_array_list_single(parray_list pa, size_type index, const char *color);
void print_array_list_multi(parray_list pa, size_type b, size_type e, const char *color);
parray_list random_array_list(size_type n);
void print_choice(void);

#endif
