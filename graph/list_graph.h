/** @file list_graph.h
 *
 * Declarations for types and functions.
 */

#ifndef _LIST_GRAPH_H
#define _LIST_GRAPH_H

#include <stdlib.h>
#include <sys/types.h>
#include "../header.h"

typedef enum {DG,UDG} graph_type;

struct edge;
typedef struct edge *pedge;

struct edge {
    size_type    v_id;     /**< Vertex ID of this neighbor */
	weight_type  weight;   /**< Weight of this edge */
	pedge        next;     /**< Pointer to next edge */
};

typedef struct vertex {
    value_type    data;    /**< Value stored in this vertex */
	pedge         head;    /**< First edge joining this vertex */
} *pvertex;

typedef struct graph {
    size_type    order;   /**< Number of vertices */
	size_type    size;    /**< Number of edges */
	graph_type   type;    /**< Directed or undirected graph */
	pvertex      vertices[1];
} *pgraph;

pgraph create_graph(void);
pgraph create_graph_n(size_type n);
pvertex create_vertex(value_type data);
pedge create_edge(size_type id, weight_type w);
int set_vertex_data(pgraph pg, size_type pos, value_type val);
int set_vertices_data(pgraph pg, size_type from, size_type to, value_type vals[]);
void insert_edge(pgraph pg, size_type v, pedge pe);
int add_edge(pgraph pg, size_type v1, size_type v2, weight_type w);
int add_arc(pgraph pg, size_type head, size_type tail, weight_type w);
int depth_first_search(pgraph pg, void (*print)(value_type));
#endif
