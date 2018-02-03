/** \file brace_match.c
 *
 * Check whether input braces (including (), [], {}) are 
 * exactly matched.
 */

#define CHAR_TYPE

#include "stack_illustration.h"

int
main(void) {
    pstack ps;
	char ch, *pch;

	if ((ps = create_stack()) == NULL)
	    return -1;

	while ((ch = getchar()) != 'Q') {
	    switch (ch) {
		    case '(':
			    push(ps, ch);
				break;
			case '[':
			    push(ps, ch);
				break;
			case '{':
			    push(ps, ch);
				break;
			case ')':
			    pch = get_top(ps);
				if (*pch != '(') {
				    print_msg("mismatch");
					return -1;
				} else {
				    pop(ps);
				}
				break;
			case ']':
			    pch = get_top(ps);
				if (*pch != '[') {
				    print_msg("mismatch");
					return -1;
				} else {
				    pop(ps);
				}
				break;
			case '}':
			    pch = get_top(ps);
				if (*pch != '{') {
				    print_msg("mismatch");
					return -1;
				} else {
				    pop(ps);
				}
				break;
			default:
			    print_msg("mismatch");
				return -1;
		}
		print_stack(ps);
		while (getchar() != '\n');
	}
	print_msg("well matched");
	return 0;
}
