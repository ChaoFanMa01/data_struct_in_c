/** \file stack_illustration.h
 * Macros and functon declarations for testing stack.
 */

#ifndef STACK_ILLUSTRATION_H
#define STACK_ILLUSTRATION_H

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "stack.h"

/** \def print_int_color(color, num)
 * Macro function to print an integer in given color
 */
#undef print_int_color
#ifdef CHAR_TYPE
#define print_int_color(ch) ({\
    printf("----------\n");\
	printf("| \033[31m%c\033[0m |\n", ch);\
})
#else
#define print_int_color(num) ({\
    printf("----------\n");\
	printf("| \033[31m%4d\033[0m |\n", num);\
})
#endif

/** \def print_int_default(num)
 *
 * Macro function to print an integer in
 * default color.
 */
#undef print_int_default
#ifdef CHAR_TYPE
#define print_int_default(ch) ({\
    printf("----------\n");\
    printf("| %c |\n", ch);\
})
#else
#define print_int_default(num) ({\
    printf("----------\n");\
	printf("| %4d |\n", num);\
})
#endif

void print_stack(pstack ps);
void print_choice(void);

#endif
