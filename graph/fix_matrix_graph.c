/** @file fix_matrix_graph.c
 *
 * Definitions for types and functions.
 */

typedef struct graph {
    ssize_type    order;   /**< Number of vertices */
	ssize_type    size;    /**< Number of edges */
	graph_type    type;    /**< Directed or undirected graph */
	                       /**< Values stored in vertices */
    value_type    vertices[MAX_VERTICES];
	                       /**< Adjacent matrix */
	int           matrix[MAX_VERTICES][MAX_VERTICES];
} *pgraph;
