/*
 * This is a direcected graph header file - providing the forward declarations
 * for the directed_graph.c file.
 */

#ifndef __DIRECTED_GRAPH_HEADER
#define __DIRECTED_GRAPH_HEADER

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <float.h>
#include "linked_list.h"
#include "vertex.h"
#include "priority_queue.h"

#define MAX FLT_MAX

typedef struct _DirectedGraph
{
	LinkedList* vertexList;
	int valueSize;

} DirectedGraph;

DirectedGraph*  initialize_digraph(int, char*);
int		digraph_size(DirectedGraph*);
Vertex*		get_vertex(DirectedGraph*, void*);
bool		add_vertex(DirectedGraph*, void*);
bool		remove_vertex(DirectedGraph*, void*);
LinkedList*	get_vertices(DirectedGraph*);
LinkedList*	get_arcs(DirectedGraph*, void*);
bool		add_arc(DirectedGraph*, void*, void*, float);
bool		remove_arc(DirectedGraph*, void*, void*);
bool		change_arc_weight(DirectedGraph*, void*, void*, float);
int 		connected_vertices_count(DirectedGraph*, void*);
int		_connected_vertices_count_recursive(DirectedGraph*, void*);
bool		is_strongly_connected(DirectedGraph*);
void*		source_vertex(DirectedGraph*);
bool		has_cycle(DirectedGraph*);
void		set_visited_field(DirectedGraph*, bool);
void		buildTree(DirectedGraph*, void*);
float		get_arc_weight(DirectedGraph*, void*, void*);
void		reset_parent_links(DirectedGraph*);
int		compareVertex(void*, void*);
LinkedList*	dijkstra(DirectedGraph*, void*, void*);

#endif
