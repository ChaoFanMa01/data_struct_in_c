/** \file simple_test.c
 *
 * Test for basic usage of queue.
 */

#include "plq_illustration.h"

void
print_choice(void) {
    printf("Enter your operation: \n"
	       "(E)nqueue, (D)equeue, (C)lear, (S)ize\n");
}

int
main(void) {
    value_type val, *pval;
	plinked_queue plq;
	char cmd;

	if ((plq = create_linked_queue()) == NULL)
	    error_negative("error");
	
	print_choice();
	cmd = getchar();
	while (cmd != 'Q') {
	    switch (cmd) {
		    case 'E':
			    printf("Enter an integer between 0 and 99: ");
				scanf("%d", &val);
				enqueue(plq, val);
				print_queue(plq);
				break;
			case 'D':
			    dequeue(plq);
				print_queue(plq);
				break;
			case 'C':
			    clear(plq);
				break;
			case 'S':
			    print_msg("The size of this queue is %ld\n", 
				          size(plq));
				break;
			default:
			    break;
		}
		print_choice();
		while (getchar() != '\n');
		cmd = getchar();
	}
	free_linked_queue(plq);
	return 0;
}
