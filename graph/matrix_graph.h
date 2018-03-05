/** @file matrix_graph.h
 *
 * Declarations for types and functions.
 */

#ifndef _MATRIX_GRAPH_H
#define _MATRIX_GRAPH_H

#include <stdlib.h>
#include <sys/types.h>
#include "../header.h"

typedef int            value_type;
typedef ssize_t        size_type;

typedef enum {DG, UDG} graph_type;

struct graph;
struct vertex;

typedef struct graph    *pgraph;
typedef struct vertex   *pvertex;

struct vertex {
    value_type  data;    /**< Value stored in this vertex */
	int         adj_list[1];/**< List for neighbors of this vertex*/
};

struct graph {
    size_type    order;  /**< Number of vertices */
	size_type    size;   /**< Nunber of edges (or arcs) */
	graph_type    type;   /**< Directed or undirected graph */
	pvertex       vertices[1];
};

/**
 * Create an empty graph with n vertices.
 */
pgraph create_graph(size_type n, graph_type t);

#endif
