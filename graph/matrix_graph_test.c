#include <unistd.h>
#include <time.h>
#include "matrix_graph.h"

int manual_init_graph(pgraph pg);
int random_init_graph(pgraph pg);
void print_graph(pgraph pg);

int
main(int argc, char *argv[]) {
    size_type n;
	pgraph pg;
	srand((unsigned)time(NULL));

	if (argc != 2)
	    error_dump("parameter error");
	n = atoi(argv[1]);

    if ((pg = create_graph(n, UDG)) == NULL)
	    error_dump("creation error");
	
	random_init_graph(pg);

	print_graph(pg);

	return 0;
}

void
print_graph(pgraph pg) {
    for (size_type i = 0; i < pg->order; i++) {
	    printf("%3d| key %3d|", i, pg->vertices[i]->data);
		for (size_type j = 0; j < pg->order; j++)
		    printf("%d|", pg->vertices[i]->adj_list[j]);
		printf("\n");
	}
}

int
random_init_graph(pgraph pg) {
    size_type    num, temp;
    for (size_type i = 0; i < pg->order; i++) {
	    pg->vertices[i]->data = rand() % 100;
		num = rand() % pg->order;
		if (pg->type == DG) {
		    for (size_type j = 0; j < num; j++)
		        pg->vertices[i]->adj_list[rand() % pg->order] = 1;
		} else if (pg->type == UDG) {
		    for (size_type j = 0; j < num; j++) {
			    temp = rand() % pg->order;
			    pg->vertices[i]->adj_list[temp] = 1;
				pg->vertices[temp]->adj_list[i] = 1;
			}
		}
	}
	return OK;
}

int
manual_init_graph(pgraph pg) {
    value_type    val;
	char          cmd;
	size_type     pos;

	for (size_type i = 0; i < pg->order; i++) {
	    printf("Enter value for this vertex: ");
		scanf("%d", &val);
		pg->vertices[i]->data = val;
		printf("Add an edge (or arc) ? (y/n) ");
		while(getchar() != '\n');
		cmd = getchar();
		while (cmd == 'y') {
		    printf("Enter the ID of this neighbor: ");
			scanf("%d", &pos);
			pg->vertices[i]->adj_list[pos] = 1;
			pg->size++;
			printf("Add an edge (or arc)? (y/n) ");
			while (getchar() != '\n') ;
			cmd = getchar();
		}
	}

	return OK;
}
