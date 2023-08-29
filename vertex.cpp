/*
 * This vertex.c file implements a Vertex struct for a directed graph structure.
 */

#include "vertex.h"
#include "linked_list.h"
		
/*
 * Creates and returns a Vertex* pointer. Takes a parameter void* pointer of a value
 * to be stored in the Vertex struct.
 */
/*
Vertex* create_vertex(void* element)
{
	Vertex* v = (Vertex*)malloc(sizeof(*v));

	if(v == NULL)
		return NULL;
	
	v->data = malloc(sizeof(element));
	memcpy(v->data, element, sizeof(element));

	v->arcList  = linked_list_initialize(sizeof(Arc), (char*)"Arc");
	v->visited  = false;
	v->distance = 0;	
	v->parent   = NULL;
 
	return v;
}

/*
 * This function adds an arc struct going from the Vertex* origin parameter
  to the Vertex* dest parameter with a weight of the float price parameter.   
 */
/*
bool add_vertex_arc(Vertex* origin, Vertex* dest, float price)
{
	if(origin == NULL || dest == NULL)
		return false;

	Arc* arc = create_arc(dest, price);

	int prevSize = linked_list_size(origin->arcList);

	linked_list_add_last(origin->arcList, arc);	

	if(linked_list_size(origin->arcList) - prevSize == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
 * Removes an arc going from the origin Vertex* to the destination Vertex*.
 * returns true if removes successfully.
 */
/*
bool remove_vertex_arc(Vertex* origin, Vertex* destination)
{
	if(origin == NULL || destination == NULL)
		return false;

	LinkedList* list = origin->arcList;
	
	int prevSize = linked_list_size(list);

	for(int i = 0; i < linked_list_size(list); i++)
	{
		Arc* arc = (Arc*)linked_list_get(list, i);
		Vertex* elem = (Vertex*) arc->vertex;

		if(elem == destination) 
		{
			linked_list_remove(list, i);
			break;
		}
	}

	if(prevSize - linked_list_size(list) == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * The get_data function returns the data field of the vertex* parameter.
 * If the vertex pointer parameter is null, null is returned. Otherwise,
 * the data stored in the vertex pointer is returned.
 */
/*
void* get_data(Vertex* v)
{
	if(v == NULL)
	{
		return NULL;
	}
	else
	{
		return v->data;
	}
}

LinkedList* get_arc_list(Vertex* v)
{
	if(v == NULL)
	{

		return NULL;
	}
	else
	{
		return v->arcList;
	}
}

bool been_visited(Vertex* v)
{
	if(v == NULL)
	{
		return false;
	}
	else
	{
		return v->visited;
	}
}

void set_visited(Vertex* v, bool value)
{
	if(v == NULL)
		return;
	
	v->visited = value;
}

/*
 * The get_weight function takes a Vertex* origin vertex that goes to the 
 * Vertex* destination vertex parameter and returns the weight of that arc 
 * if such an arc exists. -1 is returned if no such arc exists.
 */
/*
float get_weight(Vertex* origin, Vertex* destination)
{
	if(origin == NULL || destination == NULL)
		return -1;

	LinkedList* list = get_arc_list(origin);

	for(int i = 0; i < linked_list_size(list); i++)
	{
		Arc* arc = (Arc*) linked_list_get(list, i);
		
		// If the vertex in this arc list matches the destination vertex		
		if(memcmp(arc->vertex, destination, sizeof(destination)) == 0)
		{
			return arc->weight;
		}
	}
	
	return -1;
}

/*
 * The change_vertex_weight function takes an origin and destination Vertex* and changes the
 * weight associated with the arc from the origin vertex to the destination vertex to the
 * value of the cost parameter. 
 */
/*
bool change_vertex_weight(Vertex* origin, Vertex* destination, float cost)
{
	if(origin == NULL || destination == NULL)
		return false;

	LinkedList* list = get_arc_list(origin);

	for(int i = 0; i < linked_list_size(list); i++)
	{
		Arc* arc  = (Arc*) linked_list_get(list, i);

		// If this arc's vertex is equal to the destination vertex
		if(memcmp(arc->vertex, destination, sizeof(destination)) == 0)
		{
			set_arc_weight(arc, cost);
			return true;
		}
	}

	return false;
}

void set_vertex_distance(Vertex* v, float value)
{
	if(v == NULL)
		return;

	v->distance = value;
}

float get_vertex_distance(Vertex* v)
{
	if(v == NULL)
		return -1;

	return v->distance;
}

void set_vertex_parent(Vertex* child, Vertex* adult)
{
	if(child == NULL || adult == NULL)
		return;

	child->parent = adult;
}


Vertex* get_vertex_parent(Vertex* v)
{
	if(v == NULL)
		return NULL;

	return v->parent;
}

/*
 * The has_arc_to_vertex funciton takes a source and destination vertex pointers, searches
 * the Arc list of the source vertex and returns true if the destination vertex is found in
 * the Arc list. Otherwise false is returned.
 */
/*
bool has_arc_to_vertex(Vertex* source, Vertex* destination)
{
	// If either the source or destination vertex are null, return false.
	if(source == NULL || destination == NULL)
		return false;

	// Retrieve the list of Arcs from the source vertex.
	LinkedList* list = get_arc_list(source);

	// For each Arc in the Arc list.
	for(int i = 0; i < linked_list_size(list); i++)
	{
		// Retrieve the Arc at index i in the list of Arcs.
		Arc* arc = (Arc*) linked_list_get(list, i);
		
		// If this Arc's vertex is equal to the destination vertex.
		if(memcmp(arc->vertex, destination, sizeof(destination)) == 0)
		{
			// Immediately return true.
			return true;
		}
	}

	// Otherwise, the destination vertex is not found in the Arc list, return false.
	return false;
	
}


Arc* create_arc(Vertex* v, float price)
{
	Arc* arc = (Arc*)malloc(sizeof(*arc));
	
	if(arc == NULL || v == NULL)
		return NULL;

	arc->vertex = v;
	arc->weight   = price;

	return arc;
}

void set_arc_weight(Arc* arc, float price)
{
	if(arc == NULL)
		return;

	arc->weight = price;
}

void set_vertex(Arc* arc, Vertex* v)
{
	if(arc == NULL || v == NULL)
		return;

	arc->vertex = v;
}

float _get_arc_weight(Arc* arc)
{
	if(arc == NULL)
	{
		return -1;
	} 
	else 
	{
		return arc->weight;
	}
}

Vertex* get_arc_vertex(Arc* arc)
{
	if(arc == NULL)
	{
		return NULL;
	}
	else
	{
		return arc->vertex;
	}


}
 */
