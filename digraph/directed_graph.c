/*
 * This directed_graph.c file implements the behavior of a directed graph structure.
 */

#include <stdio.h>
#include "linked_list.h"
#include "priority_queue.h"
#include "directed_graph.h"

/*
 * This main is strictly for testing purposes only. To be removed once code is finalized.
 */
int main(int argc, char** argv)
{
	DirectedGraph* graph = initialize_digraph(sizeof(int), "Vertex");

	int one = 1;
	int* onePtr = &one;
	int two = 2;
	int* twoPtr = &two;
	int three = 3;
	int* threePtr = &three;
	int four = 4;
	int* fourPtr = &four;
	int five = 5;
	int* fivePtr = &five;

	bool r1 = add_vertex(graph, onePtr);
	bool r2 = add_vertex(graph, twoPtr);
	bool r3 = add_vertex(graph, threePtr);
	bool r4 = add_vertex(graph, fourPtr);
	bool r5 = add_vertex(graph, fivePtr);

//	if(r1 && r2 && r3 && r4 && r5)
//		printf("add_vertex returned true for each vertex added!\n");

	LinkedList* vList = get_vertices(graph);

	for(int i = 0; i < digraph_size(graph); i++)
	{	
		Vertex* v = (Vertex*) linked_list_get(vList, i);
//		printf("Vertex %d holds data %d\n", (i+1), *(int*)v->data);
	}

/*	printf("Testing remove_vertex now\n");

	int otherThree = 3;
	int* otherThreePtr = &otherThree;

	remove_vertex(graph, otherThreePtr);

	LinkedList* newList = get_vertices(graph);

	for(int i = 0; i < digraph_size(graph); i++)
	{
		Vertex* v = linked_list_get(newList, i);
		printf("Vertex %d holds data %d\n", (i+1), *(int*)v->data);
	}
*/
	
	add_arc(graph, onePtr, twoPtr, 1);
	add_arc(graph, onePtr, threePtr, 2.5);
	add_arc(graph, onePtr, fourPtr, 5);
	add_arc(graph, twoPtr, threePtr, .5);
	add_arc(graph, threePtr, twoPtr, 1);
	add_arc(graph, threePtr, fourPtr, 3);
	add_arc(graph, threePtr, fivePtr, 1.5);
	add_arc(graph, fivePtr, fourPtr, 1);

	LinkedList* oneArcs = get_arcs(graph, onePtr);
	LinkedList* twoArcs = get_arcs(graph, twoPtr);
	LinkedList* threeArcs = get_arcs(graph, threePtr);
	
//	printf("V1 arc list size = %d, V2 arc list size = %d, and V3 arc list size = %d\n",
//	 linked_list_size(oneArcs), linked_list_size(twoArcs), linked_list_size(threeArcs));
	for(int i = 0; i < linked_list_size(oneArcs); i++)
	{
		Arc* onearc = (Arc*) linked_list_get(oneArcs, i);
//		printf("V1 has an arc to %d with weight %f\n", *(int*)onearc->vertex->data, onearc->weight);
	}
	printf("\n");
	for(int i = 0; i < linked_list_size(twoArcs); i++)
	{
		Arc* twoarc = (Arc*) linked_list_get(twoArcs, i);
//		printf("V2 has an arc to %d with weight %f\n", *(int*)twoarc->vertex->data, twoarc->weight);
	}
	printf("\n");
	for(int i = 0; i < linked_list_size(threeArcs); i++)
	{
		Arc* arc = (Arc*) linked_list_get(threeArcs, i);
//		printf("V3 has an arc to %d with weight %f\n", *(int*)arc->vertex->data, arc->weight);
	}
/*	printf("\n changing arc weights now\n\n");	
	change_arc_weight(graph, onePtr, twoPtr, 195);
	change_arc_weight(graph, threePtr, fourPtr, 137);
	change_arc_weight(graph, onePtr, fivePtr, 455);

	LinkedList* A1 = get_arcs(graph, onePtr);
	for(int i = 0; i < linked_list_size(A1); i++)
	{
		Arc* a = (Arc*) linked_list_get(A1, i);
		printf("V1 has an arc to %d with weight %f\n", *(int*)a->vertex->data, a->weight);
		printf("call on get arc weight %f\n", get_arc_weight(graph, onePtr, a->vertex->data));
	}
	printf("\n");
	LinkedList* a3 = get_arcs(graph, threePtr);
	for(int i = 0; i < linked_list_size(a3); i++)
	{
		Arc* a = (Arc*) linked_list_get(a3, i);
		printf("V3 has an arc to %d with weight %f\n", *(int*)a->vertex->data, a->weight);
		printf("call on get arc weight %f\n", get_arc_weight(graph, threePtr, a->vertex->data));
	}
	
	printf("\n Testing the remove arc functionality now\n\n");

	remove_arc(graph, onePtr, threePtr);
	remove_arc(graph, threePtr, twoPtr);
	remove_arc(graph, fivePtr, fourPtr);
	remove_arc(graph, threePtr, fourPtr);

	LinkedList* arc1 = get_arcs(graph, onePtr);
	for(int i = 0; i < linked_list_size(arc1); i++)
	{
		Arc* a = (Arc*) linked_list_get(arc1, i);
		printf("V1 has arc to %d with weight %f\n", *(int*)a->vertex->data, a->weight);
	}

	LinkedList* arc3 = get_arcs(graph, threePtr);
	for(int i = 0; i < linked_list_size(arc3); i++)
	{
		Arc* a = (Arc*) linked_list_get(arc3, i);
		printf("V3 has arc to %d with weight %f\n", *(int*)a->vertex->data, a->weight);
	}
*/
/*
	int oneSource = connected_vertices_count(graph, onePtr);

	int threeSource = connected_vertices_count(graph, threePtr);

	int fiveSource = connected_vertices_count(graph, fivePtr);

	int twoSource = connected_vertices_count(graph, twoPtr);

	printf("V1 mem location %p\n", onePtr);
	printf("V2 mem location %p\n", twoPtr);
	printf("V3 mem location %p\n", threePtr);
	printf("V4 mem location %p\n", fourPtr);
	printf("V5 mem location %p\n", fivePtr);
	
	printf("Vertices connected to V1 are %d | expected %d\n", oneSource, 4);

	printf("Vertices connected to V3 are %d | expected %d\n", threeSource, 3);

	printf("Vertices connected to V5 are %d | expected %d\n", fiveSource, 0);	

	printf("Vertices connected to V2 are %d | expected %d\n", twoSource, 3);	
*/	
	printf("\nDijkstra algo testing now\n");
	printf("Shortest path from V1 to V4\n");
	LinkedList* dList = dijkstra(graph, onePtr, fourPtr);

	for(int i = 0; i < linked_list_size(dList); i++)
	{
		Vertex* v = linked_list_get(dList, i);
		printf("%d |", *(int*)v->data);
	}
	printf("\n");



	return 0;
}

/*
 * Creates and returns a Directed Graph pointer.
 */
DirectedGraph* initialize_digraph(int dataSize, char* dataTypeName)
{
	DirectedGraph* graph = malloc(sizeof(*graph));
	
	if(graph == NULL)
		return NULL;

	graph->vertexList = linked_list_initialize(sizeof(Vertex), dataTypeName);
	graph->valueSize  = dataSize;
	
	return graph;
}

/* 
 * Takes a graph pointer and returns the number of vertices in the directed graph structure.
 */ 
int digraph_size(DirectedGraph* graph)
{
	if(graph == NULL)
	{
		return -1;
	}
	else
	{
		return linked_list_size(graph->vertexList);
	}
}

/*
 * This function searches the Directed Graph for a vertex and returns a pointer
 * to that vertex if it exists, and returns NULL if not.
 */ 
Vertex* get_vertex(DirectedGraph* graph, void* element)
{
	if(graph == NULL || element == NULL)
		return NULL;

	LinkedList* list = graph->vertexList;
	
	for(int i = 0; i < linked_list_size(list); i++)
	{
		Vertex* v = (Vertex*) linked_list_get(list, i);

		if(memcmp(v->data, element, graph->valueSize) == 0)
		{
			return v;
		}
	}

	return NULL;		
}

/*
 * The add vertex function creates a Vertex* pointer and adds it to the Directed Graph struct.
 */
bool add_vertex(DirectedGraph* graph, void* element)
{
	if(graph == NULL || element == NULL)
		return false;

	Vertex* v = create_vertex(element);

	return	linked_list_add_last(graph->vertexList, v);
}

/*
 * The remove function removes a specific Vertex* pointer from the Directed Graph struct.
 */
bool remove_vertex(DirectedGraph* graph, void* element)
{
	if(graph == NULL || element == NULL)
		return false;
	
		
	int prevSize = linked_list_size(graph->vertexList);

	for(int i = 0; i < prevSize; i++)
	{
		Vertex* v = (Vertex*) linked_list_get(graph->vertexList, i);

		// If this vertex is equivalent to the element parameter		
		if(memcmp(v->data, element, graph->valueSize) == 0)
		{
			linked_list_remove(graph->vertexList, i);
			break;
		}
	}

	// If the previous size minus the current size equals 1
	if((prevSize - linked_list_size(graph->vertexList)) == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
 * This function returns the list of vertices within the Directed Graph struct.
 */
LinkedList* get_vertices(DirectedGraph* graph)
{
	if(graph == NULL)
		return NULL;

	return graph->vertexList;
}

/*
 * This function returns the list of arcs that the void* vertex points to.
 */
LinkedList* get_arcs(DirectedGraph* graph, void* element)
{
	if(graph == NULL || element == NULL)
	{
		printf("returning NULL from get_arcs\n");
		return NULL;
	}
	Vertex* v = get_vertex(graph, element);

	return get_arc_list(v);	
}

/*
 * The add arc function takes a DirectedGraph* struct pointer, and void* pointer to 
 * the origin vertex, a void* pointer to the destination vertex, and a float value
 * representing the weight of the arc. The function then creates an arc from the
 * origin vertex to the destination vertex with the appropriate weight assigned.
 */
bool add_arc(DirectedGraph* graph, void* origin, void* destination, float cost)
{
	if(graph == NULL || origin == NULL || destination == NULL)
		return false;

	Vertex* start = get_vertex(graph, origin);
	Vertex* end   = get_vertex(graph, destination);

	return add_vertex_arc(start, end, cost);
}

/*
 * The remove arc function removes the arc in the specific DirectedGraph* struct pointer
 * that goes from the void* origin veretx to the void* destination vertex.
 */
bool remove_arc(DirectedGraph* graph, void* origin, void* destination)
{
	if(graph == NULL || origin == NULL || destination == NULL)
		return false;

	Vertex* start = get_vertex(graph, origin);
	Vertex* end   = get_vertex(graph, destination);

	return remove_vertex_arc(start, end);
}

/*
 * The change_arc_weight changes the weight of a specifc arc within the DirectedGraph* struct.
 * The specific arc's weight that is changed is the one from the void* origin vertex to the 
 * void* destination vertex.
 */
bool change_arc_weight(DirectedGraph* graph, void* origin, void* destination, float cost)
{
	if(graph == NULL || origin == NULL || destination == NULL)
		return false;

	Vertex* start = get_vertex(graph, origin);
	Vertex* end   = get_vertex(graph, destination);
	
	return change_vertex_weight(start, end, cost);
}

/*
 * The get_arc_weight function returns the weight of the arc from the void* origin vertex to 
 * the void* destination vertex within the DirectedGraph* struct.
 */
float get_arc_weight(DirectedGraph* graph, void* origin, void* destination)
{
	if(graph == NULL || origin == NULL || destination == NULL)
		return -1;

	Vertex* start = get_vertex(graph, origin);
	Vertex* end   = get_vertex(graph, destination);

	return get_weight(start, end); 
}

/*
 * The connected_vertices_count function takes a DirectedGraph* struct pointer and a void* 
 * pointer to a vertex, calls a helper recursive function, resets all the vertices visited
 * field to false, and returns the count of the vertices traversable from the void* origin
 * vertex. 
 */
int connected_vertices_count(DirectedGraph* graph, void* origin)
{
	if(graph == NULL || origin == NULL)
		return -1;

	int count  = _connected_vertices_count_recursive(graph, origin) - 1; // Is the - 1 here proper?	
	set_visited_field(graph, false);

	return count;
}

/*
 * The _connected_vertices_count_recursive function takes a DirectedGraph* struct pointer 
 * and a void* origin pointer to a vertex. This function recursively visits each vertex 
 * traversable via the vertx's arc list that has already not been visited and counts the
 * number of vertices. The count of the number of vertices visited is returned to the client.
 */
int _connected_vertices_count_recursive(DirectedGraph* graph, void* origin)
{
	if(graph == NULL || origin == NULL)
		return -1;

	int count = 0;
	
	Vertex* start = get_vertex(graph, origin);
	printf("Current Vertex: %d\n", *(int*)start->data);	// code here for testing
	if(!(been_visited(start)))
	{
		set_visited(start, true);
		count = 1;

		LinkedList* list = get_arc_list(start);  		// changed this method from get_arc_list(start);

		// This printing and for loop here are strictly for testing
		printf("diGraph.c: Arc List size: %d\n", linked_list_size(list));
		for(int i = 0; i < linked_list_size(list); i++)
		{
			Arc* arc = (Arc*) linked_list_get(list, i);
			printf("%d | ", *(int*)arc->vertex->data);
		}
		printf("\n");
		// End of testing for loop		

		for(int i = 0; i < linked_list_size(list); i++)
		{
			Arc* arc = (Arc*) linked_list_get(list, i);
			printf("Visiting %d\n", *(int*)arc->vertex->data);    // code here for testing
			
			// If the next vertex in the arc list has not been visited
			if(!(been_visited(arc->vertex)))
			{	
				void* ptr = (void*) arc->vertex->data;				
				count += _connected_vertices_count_recursive(graph, ptr);	
			}
		}		
	}

	return count;
}

/*
 *  
 */
bool is_strongly_connected(DirectedGraph* graph)
{

}

/*
 * The source_vertex function takes a DirectedGraph* struct pointer parameter and
 * traverses the Directed Graph structure from each vertex. The vertex from which
 * all vertices can be visited is returned.
 */
void* source_vertex(DirectedGraph* graph)
{
	if(graph == NULL)
		return NULL;

	LinkedList* list = get_vertices(graph);

	for(int i = 0; i < linked_list_size(list); i++)
	{
		void* v   = linked_list_get(list, i);
		int count = connected_vertices_count(graph, v);
				
		// If the number of vertices visited is equal to the number of
		// of vertices in the graph.
		if(count == linked_list_size(list))
		{
			set_visited_field(graph, false);
		
			return v;
		}

		set_visited_field(graph, false);
	}

	return NULL;
}

/*
 *
 */
bool has_cycle(DirectedGraph* graph)
{

}

/*
 * The set_visited_field function changes the visited data member for all
 * vertex structs within the DirectedGraph* struct to hte bool value parameter.
 */
void set_visited_field(DirectedGraph* graph, bool value)
{
	if(graph == NULL)
		return;

	for(int i = 0; i < linked_list_size(graph->vertexList); i++)
	{
		Vertex* v  = (Vertex*) linked_list_get(graph->vertexList, i);
		set_visited(v, value);
	}
}

/*
 * The reset_parent_links function changes the parent reference of eac vertex struct
 * within the DirectedGraph* struct to NULL.
 */
void reset_parent_links(DirectedGraph* graph)
{
	if(graph == NULL)
		return;

	for(int i = 0; i < linked_list_size(graph->vertexList); i++)
	{
		Vertex* v = (Vertex*) linked_list_get(graph->vertexList, i);
		v->parent = NULL;
	}
}

/*
 * A compare function used to compare vertex structs. This function
 * accepts two vertex* structs as void*, casts them to Vertex*,
 * and compares them based on their distance data member.
 */
int compareVertex(void* a, void* b)
{
	if(a == NULL || b == NULL)
		return -1;

	Vertex* v1 = (Vertex*) a;
	Vertex* v2 = (Vertex*) b;

	return (int) v1->distance - v2->distance;
}

/*
 * This buildTree funciton implements dijkstra's algorithm. It takes a DirectedGraph* struct
 * pointer and a void* origin vertex struct pointer, then creates a shotest path list by
 * assigning the parent data members for each vertex struct.
 * 
 */
void buildTree(DirectedGraph* graph, void* origin)
{
	if(graph == NULL || origin == NULL)
		return;
	
	// Get a linkedlist of the vertices in the graph.
	LinkedList* vList = get_vertices(graph);

	// For each vertex in the linkedlist.
	for(int i = 0; i < linked_list_size(vList); i++)
	{	
		// get the vertex at the index and assign its distance data field to MAX.
		Vertex* v = (Vertex*) linked_list_get(vList, i);
		set_vertex_distance(v, MAX);		
	}

	// Initializing the PriorityQueue struct with the compareVertex function as a parameter.
	PriorityQueue* pq = pQueue_initialize(sizeof(Vertex), "Vertex", compareVertex);
	Vertex* start     = get_vertex(graph, origin);
	
	// These two lines of code are for setting up dijkstra's algorithim (below).
	set_vertex_distance(start, 0);
	pQueue_enqueue(pq, start);
	
	// While the priority queue contains elements.
	while(pQueue_size(pq) > 0)
	{
		// Dequeue a vertex from the priority queue.
		Vertex* v = (Vertex*) pQueue_dequeue(pq);
		
		// If this vertex has already been visited.
		if(been_visited(v))
		{
			// Force a new iteration of the while loop.
			continue;
		}
		
		// Set the vertex's visited data member to true.
		set_visited(v, true);

		// Retrieve the list of arcs from this vertex.
		LinkedList* arcList = get_arc_list(v);

		// For each arc from this vertex.
		for(int i = 0; i < linked_list_size(arcList); i++)
		{
			// Get the arc at this index and the vertex.
			Arc* arc       = (Arc*) linked_list_get(arcList, i);
			Vertex* vtex   = arc->vertex;

			// Calculate a new distance.
			float distance = get_vertex_distance(v) + arc->weight; // changed the get_vertex_distance( ) from vtex to v

			// If the vertex's diatance is greater than the calculated distance.
			printf("vertex current distance %f calculated distance %f\n", get_vertex_distance(vtex), distance);
			if(get_vertex_distance(vtex) > distance)
			{
				/*
				 * Assign the calculated distance to the current vertex,
				 * assign the parent value for this vertex and the vertex 
				 * being dequeued, and enqueue this vertex. 
				 */
				set_vertex_distance(vtex, distance);
				set_vertex_parent(vtex, v);
				pQueue_enqueue(pq, vtex);
				printf("parent %d has child %d with distance %f\n", *(int*)v->data, *(int*)vtex->data, distance);
			}
		}	
	} 
}

/*
 * The dijkstra function below constructs a shortest path within the DirectedGraph* struct 
 * from the void* origin vertex to the void* destination vertex. A LinkedList* of Vertex structs 
 * of this shotest path is returned to the client. Note: the returned LinkedList* is linear 
 * from origin vertex to destination vertex.
 */
LinkedList* dijkstra(DirectedGraph* graph, void* origin, void* destination)
{
	if(graph == NULL || origin == NULL || destination == NULL)
		return NULL;

	LinkedList* vList = linked_list_initialize(sizeof(Vertex), "Vertex");

	buildTree(graph, origin);
	Vertex* end = get_vertex(graph, destination);

	while(end != NULL)
	{
		linked_list_add_first(vList, end); // Should this be adding pointers to the Vertex data members instead?
		end = get_vertex_parent(end);
	}	

	reset_parent_links(graph);
	set_visited_field(graph, false);

	return vList;
}

