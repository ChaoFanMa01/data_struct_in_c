#include "array_list_illustration.h"


/** \fn void print_line(size_type n)
 * \brief Print a line with given width.
 */
void
print_line(size_type n) {
    for (size_type i = 0; i < n; i++)
	    printf("-");
	printf("\n");
}

/** \fn print_array_list(parray_list pa, size_type begin, size_type end, size_type b, size_type e, const char *color)
 * 
 * Print an array list. The elements begin indices b and e will
 * be printed in given color, and others will be printed in 
 * default color.
 * \param pa The array list.
 * \param begin The begining index to be printed.
 * \param b The beginning index to be printed in given
 *          color. Now, only support red and white.
 * \param e The end index to be printed in given color.
 * \param end The end index to be printed.
 * \param color Given color. Can only be red or white, now.
 */
void print_array_list(parray_list pa, size_type begin, 
    size_type end, size_type b, size_type e,
	const char *color) {
	char cmd[10];
	size_type cnt;
	if (begin > end || begin < 0 || end >= pa->size ||
	    b > e)
	    return;
	
	cnt = (end - begin + 1) * 4 + 1;
	print_line(cnt);

	if (strcmp(color, "red") == 0)
	    strcpy(cmd, "31m");
	else if (strcmp(color, "white") == 0)
	    strcpy(cmd, "37m");
	else
	    strcpy(cmd, "32m");
	printf("|");
	for (size_type i = 0; i <= end; i++)
	    if (b < begin || e > end)
		    print_int_default(*(pa->items + i));
		else if (i >= begin && i < b)
		    print_int_default(*(pa->items + i));
		else if (i >= b && i <= e)
		    print_int_color(cmd, *(pa->items + i));
		else if (i > e && i <= end)
		    print_int_default(*(pa->items + i));
	printf("\n");

	print_line(cnt);
}

/** \fn void print_array_list_all_default(parray_list pa)
 * \brief Print the entire array list in default color.
 */
void
print_array_list_all_default(parray_list pa) {
    print_array_list(pa, 0, pa->size - 1, pa->size,
	    pa->size, "");
}

/** \fn void print_array_list_single(parray_list pa, size_type index, const char *color)
 *
 * Print the entire array list while one element in given index
 * printed in given color.
 * \param pa The array list.
 * \param index The index of the element to be printed in
 *        given color.
 * \param color Given color.
 */
void
print_array_list_single(parray_list pa, 
    size_type index, const char *color) {
    print_array_list(pa, 0, pa->size - 1, index, index, color);
}

/** \fn void print_array_list_multi(parray_list pa, size_type b, size_type e, const char *color)
 * 
 * Print the entire array list while the elements between
 * given indices b and e are printed in given color.
 * \param pa The array list.
 * \param b The beginning index of color-printing elements.
 * \param e The end index of color-printing elements.
 * \param color Given color.
 */
void
print_array_list_multi(parray_list pa, size_type b,
    size_type e, const char *color) {
	print_array_list(pa, 0, pa->size - 1, b, e, color);
}

/** \rn parray_list random_array_list(size_type n)
 * \brief Randomly generate an array list with given
 *        number of elements.
 * \param n The given number.
 * \return Return null pointer on memory allocation 
 *         error, non-null pointer otherwise.
 */
parray_list
random_array_list(size_type n) {
    parray_list pa;

	if ((pa = create_array_list()) == NULL)
	    error_null("memory allocation error.");

	for (size_type i = 0; i < n; i++)
	    al_insert_tail(pa, rand() % 100);
	
	return pa;
}

/** \fn void print_choice(void)
 * \brief Print the choice command.
 */
void
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
	parray_list pa;
	char cmd;
	value_type val, num;

	if (argc != 2)
	    error_dump("parameter error.");
	n = atoi(argv[1]);

	if ((pa = random_array_list(n)) == NULL)
	    error_negative("error");

	print_array_list_all_default(pa);

    print_choice();
    cmd = getchar();
	while (cmd != 'Q') {
	    switch (cmd) {
		    case 'I':
			    printf("Enter an integer between 0 and 99: ");
				scanf("%d", &val);
				printf("Where to insert this integer: ");
				scanf("%d", &num);
				n = al_find(pa, num, NULL);
				al_insert_before(pa, num, val, NULL);
				print_array_list_single(pa, n, "red");
				print_array_list_multi(pa, n + 1, pa->size - 1,
				    "white");
				break;
			case 'H':
			    printf("Enter an integer between 0 and 99: ");
				scanf("%d", &val);
				al_insert_head(pa, val);
				print_array_list_single(pa, 0, "red");
				break;
			case 'T':
			    printf("Enter an integer between 0 and 99: ");
				scanf("%d", &val);
				al_insert_tail(pa, val);
				print_array_list_single(pa, pa->size - 1, "red");
				break;
			case 'D':
			    printf("Which one you wish to delete: ");
				scanf("%d", &val);
				al_delete_value(pa, val, NULL);
				print_array_list_all_default(pa);
				break;
			case 'E':
			    if (al_is_empty(pa) == TRUE)
				    print_msg("This array list is empty");
				else
				    print_msg("This array list is not empty");
				break;
			case 'C':
			    al_clear(pa);
				print_msg("This array list has been cleared");
				break;
			case 'S':
			    printf("The current size of this list is %ld\n",
				    size_of_array_list(pa));
				break;
			case 'F':
			    printf("Whose index do you want to find: ");
				scanf("%d", &val);
				printf("The index of %d is %ld\n", val,
				    al_find(pa, val, NULL));
				break;
			default:
			    break;
		}
        print_choice();
		while (getchar() != '\n') ; 
        cmd = getchar();
	}
	free_array_list(pa);
	return 0;
}
