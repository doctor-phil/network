/*
 * This directed_graph.c file implements the behavior of a directed graph structure.
 */

#include <stdio.h>
#include "linked_list.h"
#include "priority_queue.h"
#include "directed_graph.h"

/*
 * This main is strictly for testing purposes and to serve as an example of how to use the Directed Graph struct only. 
 * This is to be removed once code is finalized.
 */

/*
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

	printf("Testing remove_vertex now\n");

	int otherThree = 3;
	int* otherThreePtr = &otherThree;

	remove_vertex(graph, otherThreePtr);

	LinkedList* newList = get_vertices(graph);

	for(int i = 0; i < digraph_size(graph); i++)
	{
		Vertex* v = linked_list_get(newList, i);
		printf("Vertex %d holds data %d\n", (i+1), *(int*)v->data);
	}

	
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
	printf("\n changing arc weights now\n\n");	
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
}*/

float* all_pairs_shortest_paths(DirectedGraph* graph)
{
	if(graph == NULL)
	{
		float zero = 0;
		float* space = malloc(sizeof(*space));
		space = &zero;
		return space;
	}

	// This segment of code creates the adjacency matrix for the DirectedGraph* struct.
	LinkedList* vertices = get_vertices(graph);
	int n = linked_list_size(vertices);

	// Creating an n x n matrix where n is the number of vertices in the DirectedGraph.
	float adjMtx[n][n];

	// For each vertex in the graph.
	for(int i = 0; i < n; i ++)
	{
		// Retrieve the vertex at index i.
		Vertex* source = linked_list_get(vertices,i);

		// For each vertex in the graph.
		for(int j = 0; j < n; j++)
		{
			// Retrieve the vertex at index j.
			Vertex* destination = linked_list_get(vertices, j);

			// If an Arc exists from the source to destination vertex.
			if(has_arc_to_vertex(source, destination))
			{
				// Then insert the Arc's weight into the adjacency matrix table.
				adjMtx[i][j] = get_weight(source, destination);

			// Otherwise, insert the largest float value into the adjacency matrix table.
			} else {
				adjMtx[i][j] = FLT_MAX;
			}
		}
	}

	// This segment of code implements the Floyd Warshall algorithm.
	
	// For each vertex in the graph.
	for(int k = 0; k < n; k++)
	{
		// For each vertex row in the square adjacency matrix.
		for(int i = 0; i < n; i++)
		{
			// For each vertex column in the square adjacency matrix.
			for(int j = 0; j < n; j++)
			{
				// Let the i,j index equal the minimum of the adjacency matrix i,j element or the sum of elements i,k and k,j.
				adjMtx[i][j] = (adjMtx[i][j] < (adjMtx[i][k] + adjMtx[k][j])) ? adjMtx[i][j] : (adjMtx[i][k] + adjMtx[k][j]);
			}
		}
	}

	// Return a pointer to the first element in the shortest paths matrix.
	//return &adjMtx[0][0];
	
	// TEMPORARY FIX FOR BUG TESTING
	float* space = malloc(sizeof(*space));
	float value = 1.0;
	space = &value;
	return space;
}

/*
 * Creates and returns a Directed Graph pointer.
 */
DirectedGraph* initialize_digraph(int dataSize, char* dataTypeName)
{
	DirectedGraph* graph = malloc(sizeof(*graph));

	// If allocation request unsuccessful, then return NULL.	
	if(graph == NULL)
		return NULL;

	// Initialize the linkedList struct and assign the valueSize variable.
	graph->vertexList = linked_list_initialize(sizeof(Vertex), dataTypeName);
	graph->valueSize  = dataSize;
	
	return graph;
}

/* 
 * Takes a Directed Graph pointer and if the Directed Graph pointer is not NULL, the number
 * if vertices in the Directed Graph struct is returned, otherwise -1 is returned.
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
 * This function searches the Directed Graph for a vertex and, if it exists in the Directed Graph struct,
 * returns a pointer to that vertex, otherwise NULL is returned.
 */ 
Vertex* get_vertex(DirectedGraph* graph, void* element)
{
	if(graph == NULL || element == NULL)
		return NULL;

	// Retrieve a local pointer of the Directed Graph's vertex list.
	LinkedList* list = graph->vertexList;
	
	// For each vertex in the vertex list.
	for(int i = 0; i < linked_list_size(list); i++)
	{
		// Retrieve the vertex at index i in the vertex list.
		Vertex* v = (Vertex*) linked_list_get(list, i);

		// If the data fieled variable in the vertex is equal to the element parameter. 
		if(memcmp(v->data, element, graph->valueSize) == 0)
		{
			// Return this vertex.
			return v;
		}
	}

	return NULL;		
}

/*
 * The add vertex function creates a Vertex* pointer and adds it to the Directed Graph struct.
 * True is returned if the vertex was successfully added to the Directed Graph. Otherwie false 
 * is returned.
 */
bool add_vertex(DirectedGraph* graph, void* element)
{
	// If either parameter is NULL, return false.
	if(graph == NULL || element == NULL)
		return false;

	// Instantiate a Vertex struct while passing in the element parameter.
	Vertex* v = create_vertex(element);

	// Return the call to linkedlist add last function while passing in Directed Graph's vertex list and the instantiated vertex.
	return	linked_list_add_last(graph->vertexList, v);
}

/*
 * The remove function removes a specific Vertex* pointer from the Directed Graph struct.
 */
bool remove_vertex(DirectedGraph* graph, void* element)
{
	// If either parameter is NULL, return false.
	if(graph == NULL || element == NULL)
		return false;
	
	// Store vertex list's current size in a local variable.	
	int prevSize = linked_list_size(graph->vertexList);

	// For each vertex in the vertex list.
	for(int i = 0; i < prevSize; i++)
	{
		// Retrieve the vertex in the vertex list at index i.
		Vertex* v = (Vertex*) linked_list_get(graph->vertexList, i);

		// If this vertex is equivalent to the element parameter		
		if(memcmp(v->data, element, graph->valueSize) == 0)
		{
			// Remove this vertex from the vertex list and break from loop.
			linked_list_remove(graph->vertexList, i);
			break;
		}
	}

	// If the previous size minus the current size equals 1 return true, else return false.
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
		return NULL;
	}

	// Retrieve vertex pointer from graph associated with the element parameter.
	Vertex* v = get_vertex(graph, element);

	// Return this vertex's arc list.
	return get_arc_list(v);	
}

/*
 * The add arc function takes a DirectedGraph* struct pointer, a void* pointer to 
 * the origin vertex, a void* pointer to the destination vertex, and a float value
 * representing the weight of the arc. The function then creates an arc from the
 * origin vertex to the destination vertex with the appropriate weight assigned.
 * This function returns true if the arc between origin and destination was added
 * to the Directed Graph struct successfully, otherwise false is returned.
 */
bool add_arc(DirectedGraph* graph, void* origin, void* destination, float cost)
{
	// If any one of the graph, origin, or destination parameter is NULL, return false.
	if(graph == NULL || origin == NULL || destination == NULL)
		return false;

	// Otherwise retrieve the Vertices associated with the origin and destination parameters.
	Vertex* start = get_vertex(graph, origin);
	Vertex* end   = get_vertex(graph, destination);

	// Return the call to add vertex arc function with the two vertices and the arc weight.
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

	int count  = _connected_vertices_count_recursive(graph, origin) - 1; 	
	set_visited_field(graph, false);

	return count;
}

/*
 * The _connected_vertices_count_recursive function takes a DirectedGraph* struct pointer 
 * and a void* origin pointer to a vertex. This function recursively visits each vertex 
 * traversable via the vertx's arc list that has already not been visited and counts the
 * number of vertices. The count of the number of vertices visited is returned to the client.
 * If either parameter is NULL, -1 is returned.
 */
int _connected_vertices_count_recursive(DirectedGraph* graph, void* origin)
{
	// If either parameter is NULL, return -1.
	if(graph == NULL || origin == NULL)
		return -1;

	// Temporary count and start vertex variables.
	int count     = 0;
	Vertex* start = get_vertex(graph, origin);
	
	// If this start vertex has not been visited.
	if(!(been_visited(start)))
	{
		/*
 		 * Set this start vertex visited flag to true, count assigned to 1, 
 		 * and retrieve the arc list of this vertex.
 		 */
		set_visited(start, true);
		count            = 1;
		LinkedList* list = get_arc_list(start);  

		// For each arc in this vertex's arc list.
		for(int i = 0; i < linked_list_size(list); i++)
		{
			// Retrieve the arc struct at index i.
			Arc* arc = (Arc*) linked_list_get(list, i);
			
			// If the vertex in the arc struct has not been visited.
			if(!(been_visited(arc->vertex)))
			{	
				// Cast the data of this vertex to a void pointer local variable.
				void* ptr = (void*) arc->vertex->data;				

				// count in incremented by a call to connected_vertices_count_recursive function.
				count    += _connected_vertices_count_recursive(graph, ptr);	
			}
		}		
	}

	return count;
}


/*
 * The source_vertex function takes a DirectedGraph* struct pointer parameter and
 * traverses the Directed Graph structure from each vertex. The vertex from which
 * all vertices can be visited is returned. If no such vertex exists, then NULL
 * is returned.
 */
void* source_vertex(DirectedGraph* graph)
{
	if(graph == NULL)
		return NULL;

	// Retrieve the vertex list from the Dorected Graph struct.
	LinkedList* list = get_vertices(graph);

	// For each vertex in the vertex list.
	for(int i = 0; i < linked_list_size(list); i++)
	{
		// Retrieve the vertex at index i.
		void* v   = linked_list_get(list, i);

		// Retrieve the count of the call to connected_verteices_count function from this vertex.
		int count = connected_vertices_count(graph, v);
				
		// If number of vertices visited equals number of vertices in the graph.
		if(count == linked_list_size(list))
		{
			// Set the visieted falg for all vertices to false and return this vertex.
			set_visited_field(graph, false);
			return v;
		}

		// Set the visited flag for all vertices in the graph to false. 
		set_visited_field(graph, false);
	}

	return NULL;
}


/*
 * The set_visited_field function changes the visited data member for all
 * vertex structs within the DirectedGraph* struct to the value of the bool parameter.
 */
void set_visited_field(DirectedGraph* graph, bool value)
{
	// If the graph is null, immediately return.
	if(graph == NULL)
		return;

	// For each vertex in the Directed Graph's vertex list.
	for(int i = 0; i < linked_list_size(graph->vertexList); i++)
	{
		// Retrieve the vertex struct at index i.
		Vertex* v  = (Vertex*) linked_list_get(graph->vertexList, i);

		// Set the visited falg of this vertex to the value parameter.
		set_visited(v, value);
	}
}

/*
 * The reset_parent_links function changes the parent reference of eac vertex struct
 * within the DirectedGraph* struct to NULL.
 */
void reset_parent_links(DirectedGraph* graph)
{
	// If the graph parameter is NULL, immediately return.
	if(graph == NULL)
		return;

	// For each vertex in the Directed Graph's vertex list.
	for(int i = 0; i < linked_list_size(graph->vertexList); i++)
	{
		// Retrieve a reference to the vertex struct at index i.
		Vertex* v = (Vertex*) linked_list_get(graph->vertexList, i);

		// Assign the vertex's parent reference to NULL.
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

	// Casting void* paremeters to Vertex pointers.
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
			float distance = get_vertex_distance(v) + arc->weight; 

			// If the vertex's diatance is greater than the calculated distance.
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

	// Instantiate a Linkedlist struct to hold Vertex pointers.
	LinkedList* vList = linked_list_initialize(sizeof(Vertex), "Vertex");

	// Call to build a tree of parent links from the origin vertex within the Directed Graph.
	buildTree(graph, origin);

	// Retrieve the destination vertex from the Directed Graph. 
	Vertex* end = get_vertex(graph, destination);

	// While the end vertex variable is not NULL.
	while(end != NULL)
	{
		// Add the end variable vertex reference to the linkedlist struct.
		linked_list_add_first(vList, end); 

		// The end variable is updated to be the parent reference of the previous end variable.
		end = get_vertex_parent(end);
	}	

	// Reset all parent links and the visited field of each vertex to false.
	reset_parent_links(graph);
	set_visited_field(graph, false);

	// Return the vertex list of the shortest path, in order, from origin vertex to destination vertex.
	return vList;
}

