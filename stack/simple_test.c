/** \file simple_test.c
 *
 * Function definitions for testing stack.
 */

#include "stack_illustration.h"

#undef CHAR_TYPE

int
main(int argc, char *argv[]) {
    value_type    val, *pval;
	pstack ps;
	char cmd;

	if (argc != 1)
	    error_dump("parameter error.");

	if ((ps = create_stack()) == NULL)
	    error_negative("error");
	
	print_choice();
	cmd = getchar();
	while (cmd != 'Q') {
	    switch (cmd) {
		    case 'P':
			    printf("Enter an integer between 0 and 99: ");
				scanf("%d", &val);
				push(ps, val);
				print_stack(ps);
				break;
			case 'p':
			    pop(ps);
				print_stack(ps);
				print_stack(ps);
				break;
			case 'T':
			    pval = get_top(ps);
				printf("The top value is %d\n", *pval);
				break;
			case 'C':
			    clear_stack(ps);
				break;
			case 'D':
			    print_stack(ps);
				break;
			default:
			    break;
		}
		print_choice();
		while (getchar() != '\n') ;
		cmd = getchar();
	}
	free_stack(ps);
	return 0;
}
