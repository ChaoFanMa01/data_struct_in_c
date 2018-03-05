/** @file matrix_graph.c
 *
 * Definitions for types and functions.
 */

#include "matrix_graph.h"


/** @fn pgraph create_graph(size_type n, graph_type t)
 *
 * Create an empty graph with n vertices.
 */
pgraph
create_graph(size_type n, graph_type t) {
    pgraph    pg;
    
	if ((pg = malloc(sizeof(struct graph) + sizeof(pgraph) * (n - 1)))
	     == NULL)
	    error_null("memory error: create_graph()");
	
	for (size_type i = 0; i < n; i++) {
	    if ((pg->vertices[i] = malloc(sizeof(struct vertex) + 
		     sizeof(int) * (n - 1))) == NULL)
	        error_null("memory error: create_graph()");
		for (size_type j = 0; j < n; j++)
		    pg->vertices[i]->adj_list[j] = 0;
	}

    pg->order = n;
	pg->size = 0;
	pg->type = t;
	
	return pg;
}

