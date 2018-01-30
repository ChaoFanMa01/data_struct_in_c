#include "dlinked_list_illustration.h"

/** \fn static void print_line(size_type n)
 * \brief Print a line with given width.
 */
static void
print_line(size_type n) {
    for (size_type i = 0; i < n; i++)
	    for (size_type j = 0; j < 9; j++)
		    if (j < 5)
			    printf("-");
			else
			    printf(" ");
	printf("\n");
}

/** \fn void print_dlinked_list(pdlinked_list pdll, size_type begin, size_type end, size_type b, size_type e, const char *color)
 *
 * Print a double linked list. The elements begin indices b and e will
 * be printed in given color, and others will be printed in 
 * default color.
 * \param pdll The double linked list.
 * \param begin The begining index to be printed.
 * \param b The beginning index to be printed in given
 *          color. Now, only support red and white.
 * \param e The end index to be printed in given color.
 * \param end The end index to be printed.
 * \param color Given color. Can only be red or white, now.
 */
void
print_dlinked_list(pdlinked_list pdll, size_type begin,
                  size_type end, size_type b, size_type e,
				  const char *color) {
    char cmd[10];
    size_type cnt;
    if (begin > end || begin < 0 || end >= pdll->size ||
	      b > e || pdll == NULL)
		  return;

    cnt = end - begin + 1;
	print_line(cnt);

	if (strcmp(color, "red") == 0)
	    strcpy(cmd, "31m");
	else if (strcmp(color, "white") == 0)
	    strcpy(cmd, "37m");
	else
	    strcpy(cmd, "32m");
	pdll_node node = pdll->head;
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

/** \fn void print_dlinked_list_all_default(pdlinked_list pdll)
 * \brief Print the entire double linked list in default color.
 */
void
print_dlinked_list_all_default(pdlinked_list pdll) {
    print_dlinked_list(pdll, 0, pdll->size - 1, pdll->size,
	    pdll->size, "");
}

/** \fn void print_dlinked_list_single(pdlinked_list pdll, size_type index, const char *color)
 *
 * Print the entire double linked list while one element in given index
 * printed in given color.
 * \param pdll The linked list.
 * \param index The index of the element to be printed in
 *        given color.
 * \param color Given color.
 */
void
print_dlinked_list_single(pdlinked_list pdll, 
    size_type index, const char *color) {
    print_dlinked_list(pdll, 0, pdll->size - 1, index, index, color);
}

/** \fn void print_dlinked_list_multi(pdlinked_list pdll, size_type b, size_type e, const char *color)
 * 
 * Print the entire double linked list while the elements between
 * given indices b and e are printed in given color.
 * \param pdll The double linked list.
 * \param b The beginning index of color-printing elements.
 * \param e The end index of color-printing elements.
 * \param color Given color.
 */
void
print_dlinked_list_multi(pdlinked_list pdll, size_type b,
    size_type e, const char *color) {
	print_dlinked_list(pdll, 0, pdll->size - 1, b, e, color);
}

/** \fn pdlinked_list random_linked_list(size_type n)
 * \brief Randomly generate a double linked list with given
 *        number of elements.
 * \param n The given number.
 * \return Return null pointer on memory allocation 
 *         error, non-null pointer otherwise.
 */
pdlinked_list
random_dlinked_list(size_type n) {
    pdlinked_list pdll;

	if ((pdll = create_dlinked_list()) == NULL)
	    error_null("memory allocation error.");

	for (size_type i = 0; i < n; i++)
	    insert_tail(pdll, rand() % 100);
	
	return pdll;
}

/** \fn static void print_choice(void)
 * \brief Print the choice command.
 */
static void
print_choice(void) {
    printf("Please enter the command\n"
	    "(Q)uit, (I)nsert before, (i)nsert after\n"
		"insert (H)ead,\n"
		"insert (T)ail, (D)elete, check (E)mpty,\n"
		"(C)lear, check (S)ize, (F)ind:\n");
}

int
main(int argc, char *argv[]) {
    size_type n;
	srand(time(NULL));
	pdlinked_list pdll;
	char cmd;
	value_type val, num;

	if (argc != 2)
	    error_dump("parameter error.");
	n = atoi(argv[1]);

	if ((pdll = random_dlinked_list(n)) == NULL)
	    error_negative("error");

	print_dlinked_list_all_default(pdll);

    print_choice();
    cmd = getchar();
	while (cmd != 'Q') {
	    switch (cmd) {
		    case 'I':
			    printf("Enter an integer between 0 and 99: ");
				scanf("%d", &val);
				printf("Where to insert this integer: ");
				scanf("%d", &num);
				n = get_index(pdll, num, NULL);
				if (insert_before(pdll, num, val, NULL) < 0)
				    print_msg("insert error");
				print_dlinked_list_single(pdll, n, "red");
				print_dlinked_list_multi(pdll, n + 1, pdll->size - 1,
				    "white");
				break;
			case 'i':
			    printf("Enter an integer between 0 and 99: ");
				scanf("%d", &val);
				printf("Where to insert this integer: ");
				scanf("%d", &num);
				n = get_index(pdll, num, NULL);
				if (insert_after(pdll, num, val, NULL) < 0)
				    print_msg("insert error");
				print_dlinked_list_single(pdll, n, "red");
				print_dlinked_list_multi(pdll, n + 1, pdll->size - 1,
				    "white");
				break;
			case 'H':
			    printf("Enter an integer between 0 and 99: ");
				scanf("%d", &val);
				insert_head(pdll, val);
				print_dlinked_list_single(pdll, 0, "red");
				break;
			case 'T':
			    printf("Enter an integer between 0 and 99: ");
				scanf("%d", &val);
				insert_tail(pdll, val);
				print_dlinked_list_single(pdll, pdll->size - 1, "red");
				break;
			case 'D':
			    printf("Which one you wish to delete: ");
				scanf("%d", &val);
				delete_value(pdll, val, NULL);
				print_dlinked_list_all_default(pdll);
				break;
			case 'E':
			    if (is_empty(pdll) == TRUE)
				    print_msg("This double linked list is empty");
				else
				    print_msg("This double linked list is not empty");
				break;
			case 'C':
			    clear(pdll);
				print_msg("This double linked list has been cleared");
				break;
			case 'S':
			    printf("The current size of this list is %ld\n",
				    size_of_dlinked_list(pdll));
				break;
			case 'F':
			    printf("Whose index do you want to find: ");
				scanf("%d", &val);
				printf("The index of %d is %ld\n", val,
				    get_index(pdll, val, NULL));
				break;
			default:
			    break;
		}
        print_choice();
		while (getchar() != '\n') ; 
        cmd = getchar();
	}
	free_dlinked_list(pdll);
	return 0;
}
