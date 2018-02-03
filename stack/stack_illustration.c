/** \file stack_illustration.c
 *
 * Function definitions for testing stack.
 */

#include "stack_illustration.h"

/** \fn void print_stack(pstack ps)
 *
 * Print all values in a stack.
 */
void
print_stack(pstack ps) {
    if (ps == NULL || ps->items == NULL)
	    return;
    for (size_type i = ps->top - 1; i >= 0; i--)
	    if (i == ps->top - 1)
		    print_int_color(*(ps->items + i));
		else
		    print_int_default(*(ps->items + i));

	printf("---------over-\n");
}

void
print_choice(void) {
    printf("(P)ush, (p)op, (T)op, (C)lear, (D)isplay, (Q)uit: ");
}
