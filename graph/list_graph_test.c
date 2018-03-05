#include <unistd.h>
#include <time.h>
#include "list_graph.h"

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

    if ((pg = create_graph_n(n)) == NULL)
	    error_dump("creation error");
	
	random_init_graph(pg);

	print_graph(pg);

	return 0;
}

void
print_graph(pgraph pg) {
    for (size_type i = 0; i < pg->order; i++) {
	    printf("%3d| key %3d|", i, pg->vertices[i]->data);
		for (pedge pe = pg->vertices[i]->head; pe != NULL;
		     pe = pe->next)
		    printf("--%3d-->|%4d|", pe->weight, pe->v_id);
		printf("\n");
	}
}

int
random_init_graph(pgraph pg) {
    size_type num;
	for (size_type i = 0; i< pg->order; i++)
	    if ((pg->vertices[i] = create_vertex(rand() % 100)) == NULL)
		    return ERROR;
    for (size_type i = 0; i < pg->order; i++) {
		num = rand() % pg->order;
		if (pg->type == DG) {
		    for (size_type j = 0; j < num; j++)
			    add_arc(pg, i, rand() % pg->order, rand() % 100);
		} else if (pg->type == UDG) {
		    for (size_type j = 0; j < num; j++)
			    add_edge(pg, i, rand() % pg->order, rand() % 100);
		}
	}
	return OK;
}
