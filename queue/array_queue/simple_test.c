/** \file simple_test.c
 *
 * Test for basic usage of queue.
 */

#include "aq_illustration.h"

void
print_choice(void) {
    printf("Enter your operation: \n"
	       "(E)nqueue, (D)equeue, (C)lear, (S)ize\n");
}

int
main(void) {
    value_type val, *pval;
	parray_queue paq;
	char cmd;

	if ((paq = create_array_queue()) == NULL)
	    error_negative("error");
	
	print_choice();
	cmd = getchar();
	while (cmd != 'Q') {
	    switch (cmd) {
		    case 'E':
			    printf("Enter an integer between 0 and 99: ");
				scanf("%d", &val);
				enqueue(paq, val);
				print_queue(paq);
				break;
			case 'D':
			    dequeue(paq);
				print_queue(paq);
				break;
			case 'C':
			    clear(paq);
				break;
			case 'S':
			    print_msg("The size of this queue is %ld\n", 
				          size(paq));
				break;
			default:
			    break;
		}
		print_choice();
		while (getchar() != '\n');
		cmd = getchar();
	}
	free_array_queue(paq);
	return 0;
}
