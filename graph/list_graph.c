/** @file list_graph.c
 *
 * Definitions for types and functions.
 */

#include "list_graph.h"

/** @fn pgraph create_graph(void)
 *
 * Create an empty graph.
 */
pgraph
create_graph(void) {
    pgraph pg;

	if ((pg = malloc(sizeof(struct graph))) == NULL)
	    error_null("memory error: create_graph()");
	
	pg->order = 0;
	pg->size = 0;
	pg->type = UDG;

	return pg;
}

/** @fn pgraph create_graph_n(size_type n)
 *
 * Create a graph with n uninitialized vertices.
 */
pgraph
create_graph_n(size_type n) {
    pgraph pg;

	if ((pg = malloc(sizeof(struct graph) + 
	     sizeof(pvertex) * (n - 1))) == NULL)
	    error_null("memory error: create_graph()");
	
	pg->order = n;
	pg->size = 0;
	pg->type = UDG;

	return pg;
}

/** @fn pvertex create_vertex(value_type data)
 *
 * Create a vertex with given value.
 */
pvertex
create_vertex(value_type data) {
    pvertex pv;

	if ((pv = (pvertex)malloc(sizeof(struct vertex))) == NULL)
	    error_null("memory error: create_vertex()");
	pv->data = data;
	pv->head = NULL;

	return pv;
}

/** @fn pedge create_edge(size_type id, weight_type w)
 *
 * Create an edge with given weight.
 * @param id The id of vertex joined by this edge.
 * @param w The weight of this edge.
 */
pedge
create_edge(size_type id, weight_type w) {
    pedge pe;

	if ((pe = (pedge)malloc(sizeof(struct edge))) == NULL)
	    error_null("memory error: create_edge()");
	pe->v_id = id;
	pe->weight = w;
	pe->next = NULL;

	return pe;
}

/** @fn int set_vertext_data(pgraph pg, size_type pos, value_type val)
 *
 * Storing a value in given vertex of a graph.
 * @param pg The graph.
 * @param pos The vertex with this ID will be set.
 * @param val Given value.
 * @return Returns -1 on error, 0 otherwise.
 */
int
set_vertex_data(pgraph pg, size_type pos, value_type val) {
    if (pos < 0 || pos > pg->order)
	    return ERROR;
	pg->vertices[pos]->data = val;

	return OK;
}

/** @fn int set_vertices_data(pgraph pg, size_type from, size_type to, value_type vals[])
 *
 * Storing values in continue vertices of a graph.
 * @param pg A graph
 * @param from The beginning index of these continue vertices.
 * @param to The end index of these continue vertices.
 * @param vals The values to be stored.
 */
int
set_vertices_data(pgraph pg, size_type from, size_type to,
                  value_type vals[]) {
    if (from < 0 || from > to || to > pg->order)
	    return ERROR;
	for (size_type i = 0; from <= to; from++, i++)
	    set_vertex_data(pg, from, vals[i]);

	return OK;
}

/** @fn void insert_edge(pgraph pg, size_type v, pedge pe)
 *
 * Insert an edge to the adjacent list of a vertex.
 * @param v The vertex ID.
 * @param pe An edge.
 */
void
insert_edge(pgraph pg, size_type v, pedge pe) {
    pedge cnt;

	if (pg->vertices[v]->head == NULL) {
	    pg->vertices[v]->head = pe;
	} else {
    	for (cnt = pg->vertices[v]->head; cnt->next != NULL; 
		     cnt = cnt->next) ;
		cnt->next = pe;
	}
	pg->size++;
}

/** @fn int add_edge(pgraph pg, size_type v1, size_type v2, weight_type w)
 *
 * Add an edge with given weight to a graph between two vertices.
 * @param pg A graph.
 * @param v1 The first vertex.
 * @param v2 The second vertex.
 * @param w The weight of this edge.
 */
int
add_edge(pgraph pg, size_type v1, size_type v2, weight_type w) {
    print_msg("add edge: %d", v1);
    pedge pe;
    if (v1 < 0 || v2 < 0 || v1 > pg->order || v2 > pg->order)
	    return ERROR;
    if ((pe = create_edge(v2, w)) == NULL)
	    return ERROR;
	insert_edge(pg, v1, pe);
	if ((pe = create_edge(v1, w)) == NULL)
	    return ERROR;
	insert_edge(pg, v2, pe);

	return OK;
}

/** @fn int add_arc(pgraph pg, size_type head, size_type tail, weight_type w)
 *
 * Add an arc with given weight to a graph.
 * @param pg A graph.
 * @param head The head of this arc.
 * @param tail The tail of this arc.
 * @param w The weight of this arc.
 */
int
add_arc(pgraph pg, size_type head, size_type tail, weight_type w) {
    pedge pe;
    if (head < 0 || tail < 0 || head > pg->order || tail > pg->order)
	    return ERROR;
	if ((pe = create_edge(tail, w)) == NULL)
	    return ERROR;
	insert_edge(pg, head, pe);

	return OK;
}

static int
is_in_stack(pstack ps, value_type val) {
    for (size_type i = 0; i < ps->top; i++)
	    if (*(ps->items + i) == val)
		    return TRUE;
	return FALSE;
}

/** @fn int depth_first_search(pgraph pg, void (*print)(value_type))
 *
 * Perform a depth frist traverse on a graph.
 * @param pg A graph.
 * @param print Function used to print data.
 */
int
depth_first_traverse(pgraph pg, void (*print)(value_type)) {
    pstack stack;
	parray_list list;
    int *top;

	if ((stack = create_stack()) == NULL)
	    return ERROR;
	if ((list = create_array_list()) == NULL)
	    return ERROR;
	
	push(stack, 0);
	while (stack_is_empty(stack) == FALSE) {
	    top = get_top(stack);
		if (pg->vertices[*top]->head == NULL) {
		    print(pg->vertices[*top]->data);
			al_insert_head(list, *top);
			pop(stack);
		} else if (al_find(list, *top, NULL) == ERROR) {
			al_insert_head(list, *top);
		    for (pedge pe = pg->vertices[*top]->head; pe != NULL;
			     pe = pe->next)
			    if (al_find(list, pe->v_id, NULL) == ERROR &&
				    is_in_stack(stack, pe->v_id) == FALSE)
				    push(stack, pe->v_id);
		} else {
		    print(pg->vertices[*top]->data);
			pop(stack);
		}
	}
	free_array_list(list);
	free_stack(stack);
	return OK;
}

/** @fn int breadth_first_traverse(pgraph pg, void (*print)(value_type))
 *
 * Perform a breadth first traverse over a graph.
 * @param pg A graph.
 * @param print Function used to print value.
 */
int
breadth_first_traverse(pgraph pg, void (*print)(value_type)) {
    parray_queue children, parents, temp;
	parray_list list;
	int *front;

	if ((children = create_array_queue()) == NULL)
	    return ERROR;
	if ((parents = create_array_queue()) == NULL)
	    return ERROR;
	if ((list = create_array_list()) == NULL)
	    return ERROR;
	
	enqueue(parents, 0);
	while (queue_is_empty(parents) != TRUE) {
	    while (queue_is_empty(parents) != TRUE) {
		    front = queue_get_front(parents);
			if (al_find(list, *front, NULL) == ERROR) {
			    print(pg->vertices[*front]->data);
				al_insert_head(list, *front);
				for (pedge pe = pg->vertices[*front]->head;
				     pe != NULL; pe = pe->next)
				    if (al_find(list, pe->v_id, NULL) == ERROR)
					    enqueue(children, pe->v_id);
			}
			dequeue(parents);
		}
		temp = parents;
		parents = children;
		children = temp;
	}
	return OK;
}
