/** \file aq_illustration.h
 *
 * Macros, function declarations for illustrating 
 * how to use array implemented queue.
 */
#ifndef _AQ_ILLUSTRATION_H
#define _AQ_ILLUSTRATION_H

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "../../header.h"
#include "array_queue.h"

/** \def print_int_red(num)
 *
 * Macro function to print an integer in red.
 */
#define print_int_red(num) ({\
    printf("|\033[31m%3d\033[0m", num);\
})

/** \def print_int_white(num)
 *
 * Macro function to print an integer in white.
 */
#define print_int_white(num) ({\
    printf("|\033[37m%3d\033[0m", num);\
})

/** \def print_int_default(num)
 *
 * Macro function to print an integer in default color.
 */
#define print_int_default(num) ({\
    printf("|%3d", num);\
})

#define print_empty() ({\
    printf("|   ");\
})

void print_queue(parray_queue paq);
void print_line(size_type n);

#endif
