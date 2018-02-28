#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "avl_tree.h"

void print(value_type key);

int
main(int argc, char *argv[]) {
    int size;
	value_type key;
	char cmd = 'Y';
	pavl_tree tree;

	srand(time(NULL));

    if (argc != 2)
	    error_dump("Parameter error");

    size = atoi(argv[1]);

	if ((tree = create_avl_tree()) == NULL)
	    error_dump("Fail to create an AVL tree");
	
	printf("creating avl...\n");
	for (int i = 0; i < size; i++)
	    avl_recur_insert(tree, rand() % 100, NULL);

    printf("printing avl:\n");
    avl_recur_inorder_walk(tree, print);

    while (1) {
	    print_msg("(I)nsert, (R)emove, or (Q)uit: ");
		cmd = getchar();
	    switch (cmd) {
		    case 'I':
			    printf("Enter an integer to be inserted: ");
				scanf("%d", &key);
				avl_recur_insert(tree, key, NULL);
				avl_recur_inorder_walk(tree, print);
				break;
			case 'R':
			    printf("Enter an integer to be removed: ");
				scanf("%d", &key);
				avl_recur_remove(tree, key, NULL);
				avl_recur_inorder_walk(tree, print);
				break;
			case 'Q':
			    return 0;
		}
		while (getchar() != '\n');
	}

	return 0;
}

void
print(value_type key) {
    printf("%d\n", key);
}
