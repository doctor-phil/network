/*

 * This vertex.h file provides the forward declarations for the vertex.c file.
 */ 

#ifndef __VERTEX_HEADER
#define __VERTEX_HEADER

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "linked_list.h"

typedef struct _Vertex
{
	//LinkedList* arcList;
	void* data;
	bool visited;
	float distance;
	struct _Vertex* parent;

} Vertex;

typedef struct _Arc
{
	Vertex* vertex;
	float weight;

} Arc;

Vertex*     create_vertex(void*);
bool        add_vertex_arc(Vertex*, Vertex*, float);
bool        remove_vertex_arc(Vertex*, Vertex*);
void*       get_data(Vertex*);
//LinkedList* get_arc_list(Vertex*);
bool	    been_visited(Vertex*);
void        set_visited(Vertex*, bool);
float       get_weight(Vertex*, Vertex*);
bool	    change_vertex_weight(Vertex*, Vertex*, float);
void	    set_vertex_distance(Vertex*, float);	
float	    get_vertex_distance(Vertex*);
void	    set_vertex_parent(Vertex*, Vertex*);
Vertex*	    get_vertex_parent(Vertex*);
bool	    has_arc_to_vertex(Vertex*, Vertex*);

Arc*        create_arc(Vertex*, float);
void        set_arc_weight(Arc*, float);
void        set_vertex(Arc*, Vertex*);
float       _get_arc_weight(Arc*);
Vertex*     get_arc_vertex(Arc*);

#endif
