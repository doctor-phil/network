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
	float** adjacencyMatrix;

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
void*		source_vertex(DirectedGraph*);
void		set_visited_field(DirectedGraph*, bool);
void		buildTree(DirectedGraph*, void*);
float		get_arc_weight(DirectedGraph*, void*, void*);
void		reset_parent_links(DirectedGraph*);
int		compareVertex(void*, void*);
LinkedList*	dijkstra(DirectedGraph*, void*, void*);
float**		all_pairs_shortest_paths(DirectedGraph*);
void		create_adjacency_matrix(DirectedGraph*);
float**		get_adjacency_matrix(DirectedGraph*);
DirectedGraph*  create_digraph_from_file(char*);
bool		contains_vertex(DirectedGraph*, void*);

#endif
