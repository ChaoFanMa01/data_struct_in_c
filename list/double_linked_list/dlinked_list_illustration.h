/** \file linked_list_illustration.h
 *
 * Macros, function declarations for illustrating
 * how to use linked list.
 */

#ifndef DLINKED_LIST_H
#define DLINKED_LIST_H

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "../../header.h"
#include "double_linked_list.h"

/** \def print_color(color, num)
 *
 * Macro function to print an integer in 
 * given color.
 */
#undef print_int_color
#define print_int_color(color, num) ({\
    printf("|\033[%s%3d\033[0m|<-->", color, num);\
})

/** \def print_int_default(num)
 *
 * Macro function to print an integer in
 * default color.
 */
#undef print_int_default
#define print_int_default(num) ({\
    printf("|%3d|<-->", num);\
})

static void print_line(size_type n);
void print_dlinked_list(pdlinked_list pdll, size_type begin, size_type end, size_type b, size_type e, const char *color);
void print_dlinked_list_all_default(pdlinked_list pdll);
void print_dlinked_list_single(pdlinked_list pa, size_type index, const char *color);
void print_dlinked_list_multi(pdlinked_list pa, size_type b, size_type e, const char *color);
pdlinked_list random_dlinked_list(size_type n);
static void print_choice(void);
#endif
