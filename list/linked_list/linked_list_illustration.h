/** \file linked_list_illustration.h
 *
 * Macros, function declarations for illustrating
 * how to use linked list.
 */
 #ifndef _LINKED_LIST_ILLUSTRATION_H
 #define _LINKED_LIST_ILLUSTRATION_H

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "../../header.h"
#include "linked_list.h"

/** \def print_color(color, num)
 *
 * Macro function to print an integer in 
 * given color.
 */
#undef print_int_color
#define print_int_color(color, num) ({\
    printf("|\033[%s%3d\033[0m|-->", color, num);\
})

/** \def print_int_default(num)
 *
 * Macro function to print an integer in
 * default color.
 */
#undef print_int_default
#define print_int_default(num) ({\
    printf("|%3d|-->", num);\
})

static void print_line(size_type n);
void print_linked_list(plinked_list pll, size_type begin, size_type end, size_type b, size_type e, const char *color);
void print_linked_list_all_default(plinked_list pll);
void print_linked_list_single(plinked_list pa, size_type index, const char *color);
void print_linked_list_multi(plinked_list pa, size_type b, size_type e, const char *color);
plinked_list random_linked_list(size_type n);
static void print_choice(void);
#endif
