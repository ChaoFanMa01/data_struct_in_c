/** \file header.h
 *
 * This file defines macros used across files 
 * for the data structure lecture.
 */

#ifndef _DATA_STRUCTURE_HEADER_H
#define _DATA_STRUCTURE_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>

/** \def
 * Conditional compilation macro.
 * When a stack storing char type, given this macro,
 * commenting it away otherwise.
 */
#define CHAR_TYPE

#define OK     0   /**< For OK status */
#define ERROR -1   /**< For error status */

#define TRUE    1  /**< For true status */
#define FALSE   0  /**< For false status */

//#ifdef CHAR_TYPE
//typedef char       value_type;
//#else
typedef int        value_type;
//#endif

typedef int     weight_type;
typedef ssize_t size_type;

/**
 * Prints common messages, ended with a new line.
 */
#define print_msg(str, var...) (printf(str "\n", ## var))

/**
 * Prints error message provided by errno flag,
 * and terminates with exit(-1).
 */
#define error_exit(error) ({\
    printf("%s" "\n", strerror(error));\
    exit(ERROR);\
})

/**
 * Prints error message provided caller, and
 * terminates with exit(-1).
 */
#define error_dump(str, var...) ({\
    printf(str "\n", ## var);\
    exit(ERROR);\
})

#define error_null(str, var...) ({\
    printf(str "\n", ## var);\
    return NULL;\
})

#define error_negative(str, var...) ({\
    printf(str "\n", ## var);\
	return ERROR;\
})
#endif
