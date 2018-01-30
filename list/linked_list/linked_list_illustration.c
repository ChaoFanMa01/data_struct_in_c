#include "linked_list_illustration.h"

/** \fn static void print_line(size_type n)
 * \brief Print a line with given width.
 */
static void
print_line(size_type n) {
    for (size_type i = 0; i < n; i++)
	    for (size_type j = 0; j < 8; j++)
		    if (j < 5)
			    printf("-");
			else
			    printf(" ");
	printf("\n");
}

/** \fn void print_linked_list(plinked_list pll, size_type begin, size_type end, size_type b, size_type e, const char *color)
 *
 * Print a linked list. The elements begin indices b and e will
 * be printed in given color, and others will be printed in 
 * default color.
 * \param pll The linked list.
 * \param begin The begining index to be printed.
 * \param b The beginning index to be printed in given
 *          color. Now, only support red and white.
 * \param e The end index to be printed in given color.
 * \param end The end index to be printed.
 * \param color Given color. Can only be red or white, now.
 */
void
print_linked_list(plinked_list pll, size_type begin,
                  size_type end, size_type b, size_type e,
				  const char *color) {
    char cmd[10];
    size_type cnt;
    if (begin > end || begin < 0 || end >= pll->size ||
	      b > e || pll == NULL)
		  return;

    cnt = end - begin + 1;
	print_line(cnt);

	if (strcmp(color, "red") == 0)
	    strcpy(cmd, "31m");
	else if (strcmp(color, "white") == 0)
	    strcpy(cmd, "37m");
	else
	    strcpy(cmd, "32m");
	pll_node node = pll->head;
	for (size_type i = 0; node != NULL; i++, node = node->next)
	    if (b < begin || e > end)
		    print_int_default(node->item);
		else if (i >= begin && i < b)
		    print_int_default(node->item);
		else if (i >= b && i <= e)
		    print_int_color(cmd, node->item);
		else if (i > e && i <= end)
		    print_int_default(node->item);
	printf("|>\n");
	print_line(cnt);
}

/** \fn void print_linked_list_all_default(plinked_list pll)
 * \brief Print the entire linked list in default color.
 */
void
print_linked_list_all_default(plinked_list pll) {
    print_linked_list(pll, 0, pll->size - 1, pll->size,
	    pll->size, "");
}

/** \fn void print_linked_list_single(plinked_list pll, size_type index, const char *color)
 *
 * Print the entire linked list while one element in given index
 * printed in given color.
 * \param pll The linked list.
 * \param index The index of the element to be printed in
 *        given color.
 * \param color Given color.
 */
void
print_linked_list_single(plinked_list pll, 
    size_type index, const char *color) {
    print_linked_list(pll, 0, pll->size - 1, index, index, color);
}

/** \fn void print_linked_list_multi(plinked_list pll, size_type b, size_type e, const char *color)
 * 
 * Print the entire linked list while the elements between
 * given indices b and e are printed in given color.
 * \param pll The linked list.
 * \param b The beginning index of color-printing elements.
 * \param e The end index of color-printing elements.
 * \param color Given color.
 */
void
print_linked_list_multi(plinked_list pll, size_type b,
    size_type e, const char *color) {
	print_linked_list(pll, 0, pll->size - 1, b, e, color);
}

/** \fn plinked_list random_linked_list(size_type n)
 * \brief Randomly generate a linked list with given
 *        number of elements.
 * \param n The given number.
 * \return Return null pointer on memory allocation 
 *         error, non-null pointer otherwise.
 */
plinked_list
random_linked_list(size_type n) {
    plinked_list pll;

	if ((pll = create_linked_list()) == NULL)
	    error_null("memory allocation error.");

	for (size_type i = 0; i < n; i++)
	    insert_linked_list_tail(pll, rand() % 100);
	
	return pll;
}

/** \fn static void print_choice(void)
 * \brief Print the choice command.
 */
static void
print_choice(void) {
    printf("Please enter the command\n"
	    "(Q)uit, (I)nsert before, insert (H)ead,\n"
		"insert (T)ail, (D)elete, check (E)mpty,\n"
		"(C)lear, check (S)ize, (F)ind:\n");
}

int
main(int argc, char *argv[]) {
    size_type n;
	srand(time(NULL));
	plinked_list pll;
	char cmd;
	value_type val, num;

	if (argc != 2)
	    error_dump("parameter error.");
	n = atoi(argv[1]);

	if ((pll = random_linked_list(n)) == NULL)
	    error_negative("error");

	print_linked_list_all_default(pll);

    print_choice();
    cmd = getchar();
	while (cmd != 'Q') {
	    switch (cmd) {
		    case 'I':
			    printf("Enter an integer between 0 and 99: ");
				scanf("%d", &val);
				printf("Where to insert this integer: ");
				scanf("%d", &num);
				n = get_index(pll, num, NULL);
				if (insert(pll, val, num, NULL) < 0)
				    print_msg("insert error");
				print_linked_list_single(pll, n, "red");
				print_linked_list_multi(pll, n + 1, pll->size - 1,
				    "white");
				break;
			case 'H':
			    printf("Enter an integer between 0 and 99: ");
				scanf("%d", &val);
				insert_linked_list_head(pll, val);
				print_linked_list_single(pll, 0, "red");
				break;
			case 'T':
			    printf("Enter an integer between 0 and 99: ");
				scanf("%d", &val);
				insert_linked_list_tail(pll, val);
				print_linked_list_single(pll, pll->size - 1, "red");
				break;
			case 'D':
			    printf("Which one you wish to delete: ");
				scanf("%d", &val);
				delete_value(pll, val, NULL);
				print_linked_list_all_default(pll);
				break;
			case 'E':
			    if (is_empty(pll) == TRUE)
				    print_msg("This linked list is empty");
				else
				    print_msg("This linked list is not empty");
				break;
			case 'C':
			    clear(pll);
				print_msg("This linked list has been cleared");
				break;
			case 'S':
			    printf("The current size of this list is %ld\n",
				    size_of_linked_list(pll));
				break;
			case 'F':
			    printf("Whose index do you want to find: ");
				scanf("%d", &val);
				printf("The index of %d is %ld\n", val,
				    get_index(pll, val, NULL));
				break;
			default:
			    break;
		}
        print_choice();
		while (getchar() != '\n') ; 
        cmd = getchar();
	}
	free_linked_list(pll);
	return 0;
}
