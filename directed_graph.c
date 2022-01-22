/*
 * This directed_graph.c file implements the behavior of a directed graph structure.
 */

#include <stdio.h>
#include "linked_list.h"
#include "priority_queue.h"
#include "directed_graph.h"

/*
 * The all_pairs_shortest_paths function implements the Floyd-Warshall algorithm that finds the shortest path
 * of all pairs of vertices in a graph in O(n^3) time. This functon returns an allocated 2D array matrix 
 * representation of the shortes path of any pair of vertices. Note: this matrix can be interpreted as the
 * shortest path from the i row vertex to the j column vertex and not vice versa. 
 */
float** all_pairs_shortest_paths(DirectedGraph* graph)
{
	// If the graph parameter is NULL, immediately return NULL.
	if(graph == NULL)
	{
		return NULL;
	}

	// Retrieve the number of vertices in the graph struct.
	int n = digraph_size(graph);

	// If the adjacency matrix is not yet created, call the function to create it.
	if(graph->adjacencyMatrix == NULL)
	{
		create_adjacency_matrix(graph);
	}

	// Call get_adjacency_matrix function on the graph parameter.
	float** adjMtx = get_adjacency_matrix(graph);
	
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

	// Returning a reference to the first float pointer in the 2D array.
	return &adjMtx[0];
}

/*
 * Creates and returns a DirectedGraph pointer. The int dataSize parameter is
 * the number of bytes of the data type to be stored in the DirectedGraph. The
 * number of bytes can be retrieved from the "sizeof(type)" function where
 * "type" is the data type to be stored in the DirectedGraph. The char*
 * dataTypeName represents the name of the data type being stored in the 
 * DirectedGraph structure. 
 */
DirectedGraph* initialize_digraph(int dataSize, char* dataTypeName)
{
	DirectedGraph* graph = (DirectedGraph*)malloc(sizeof(*graph));

	// If allocation request unsuccessful, then return NULL.	
	if(graph == NULL)
		return NULL;

	// Initialize the linkedList struct and assign the valueSize variable.
	graph->vertexList      = linked_list_initialize(sizeof(Vertex), dataTypeName);
	graph->valueSize       = dataSize;
	graph->adjacencyMatrix = NULL;
	
	return graph;
}

/*
 * This function creates an adjacency matrix of the vertices in the DirectedGraph struct
 * and has the graph's adjacencyMatrix struct variable point to this allocated adjacency matrix.
 */
void create_adjacency_matrix(DirectedGraph* graph)
{
	// If the graph parameter is NULL, return immediately.
	if(graph == NULL)
		return;

	// Retrieve the vertex list and size of the graph struct parameter.
	LinkedList* vertices = get_vertices(graph);
	int n                = digraph_size(graph);

	// Declaring the adjacency matrix variable to hold n arrays of n elements. 
	float** adjMtx = (float**) malloc( n * sizeof(float*));
	
	// For each vertex in the vertex list.
	for(int i = 0; i < n; i++)
	{
		// Allocate memory for the array in row i.
		adjMtx[i] = (float*) malloc(n * sizeof(float));

		// Retrieve the source vertex at index i.
		Vertex* source = (Vertex*)linked_list_get(vertices, i);
		
		// For each vertex in the vertex list.
		for(int j = 0; j < n; j++)
		{
			// Retrieve the destination vertex at index j;
			Vertex* destination = (Vertex*)linked_list_get(vertices, j);
			
			// If there is an arc from the source to destination vertex.
			if(has_arc_to_vertex(source, destination))
			{
				// Then add the weight of this arc to the adjacency matrix at index i,j.
				adjMtx[i][j] = get_weight(source, destination);

			// Otherwise thre is no arc, therefore add the maximum float value to index i,j.
			} else {
				adjMtx[i][j] = FLT_MAX;
			}	
		}
	}

	// Assign graph's adjacency matrix pointer to the first element of this calculated adjacency matrix.
	graph->adjacencyMatrix = &adjMtx[0];
}

/*
 * The get_adjacency_matrix function returns the adjacency matrix stored within the DirectedGraph parameter.
 * If the graph parameter is NULL, NULL is returned. Otherwise the value stored in the graph's adjacency matrix
 * float pointer is returned.
 */
float** get_adjacency_matrix(DirectedGraph* graph)
{
	// If the graph parameter is NULL, immediately return NULL.
	if(graph == NULL)
		return NULL;

	// Otherwise return the value stored in the graph's adjacency matrix float pointer.
	return graph->adjacencyMatrix;
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
 * The create_digraph_from_file function takes a char* fileName parameter and creates
 * a DirectedGraph* struct via the adjacency matrix representation of a directed graph
 * in the file fileName. The file format is csv. Please see an example of the file
 * format below:
 *
 * 0,2,3,4
 * 1,0,0,2
 * 4,5,0,1
 * 0,0,3,0
 *
 * A DirectedGraph* struct pointer is returned with each vertex having an arc with its
 * noted weight to the corresponding vertex, as noted in the file.
 */
DirectedGraph* create_digraph_from_file(char* fileName)
{
	FILE* fp = fopen(fileName, "r");
	
	// If file pointer not successfully opened or fileName is NULL, return NULL.
	if(fp == NULL || fileName == NULL)
	{
		return NULL;
	}

	DirectedGraph* digraph = initialize_digraph(sizeof(int), "int");

	// Buffer to read each line of characters into.
	char elements[2000];

	int vertexCounter = 1;
	
	// While fgets does not read eof or the new line character.
	while(fgets(elements, sizeof(elements), fp) != NULL)  
	{
		int inVertexCounter = 1;

		int* thisVertex = &vertexCounter;
		
		// If thisVertex does not exist in the graph, add the vertex.
		if(!(contains_vertex(digraph, thisVertex)))
		{
			add_vertex(digraph, thisVertex);		
		}

		// Convert string to float and get the number of float values in this string.
		float* edgeWeights = float_arr_from_str(elements);
		int numWeights     = value_count(elements);

		// For each number of float values.
		for(int i = 0; i < numWeights; i++)
		{
			int* inVertex = &inVertexCounter;

			// If the inVertex does not exist in graph, then add the vertex.
			if(!(contains_vertex(digraph, inVertex)))
			{
				add_vertex(digraph, inVertex);
			}

			// Retrieve the edge weight at index i.
			float weight = edgeWeights[i];
			
			// If weight is not 0, then add edge with this weight from thisVertex to inVertex.
			// Otherwise the edge is 0, meaning there is no edge from thisVertex to inVertex.
			if(weight != 0.0)
			{
				add_arc(digraph, thisVertex, inVertex, weight);
			}

			inVertexCounter++;
		}

		vertexCounter++;
	}

	// Close the file.
	fclose(fp);
	
	// Return the pointer to the digraph struct.
	return digraph;
}

/**
 * The float_arr_from_str function converts a string parameter to a float 
 * array and returns this array of floats. 
 */
float* float_arr_from_str(char* str)
{
	// Retrieve number of characters and numerical values.
	int size   = strlen(str);
	int values = value_count(str);

	// Allocate memory for float array.
	float* arr = malloc(sizeof(*arr) * values);

	// For each value, assign it to 0 in the float array.
	for(int i = 0; i < values; i++)
		arr[i] = 0;

	// Declaring index references for the arrays.
	int index = 0;
	int start = 0;
	int end   = 0;

	// For each character in the string parameter.
	for(int i = 0; i < size; i++)
	{
		// If the character at index i is a ',' or 1 less than size.
		if(str[i] == ',' || (i + 1) == size)
		{
			// If the index is not 1 less than size.
			if((i + 1) != size)
			{
				end = i;
			} else {
				end = i + 1;
			}
			
			// Extract the value in string from start and end indicies and
			// store this value into float array arr.
			arr[index++] = extract_value(start, end, str);
			start        = i + 1;
		}
	}	

	// Return the float array.
	return arr;
}


/**
 * The extract_value function takes a start and end index pointer, and a char*
 * buffer and takes all characters between start (inclusive) and end (exclusive),
 * relocates these characters into an array, and then returns the float conversion
 * of this temporary array.
 */
float extract_value(int start, int end, char* buffer)
{
	int size  = end - start;
	int index = start;

	// Allocate a character pointer.
	char* val = malloc(sizeof(*val) * size);

	// For each character relocate character from buffer to char array.
	for(int i = 0; i < size; i++)
	{
		val[i] = buffer[index++];
	}

	// Allocate memory for float value to be returned.
	float* answer = malloc(sizeof(float));
	*answer       = atof(&val[0]);

	return *answer;
}

/**
 * The value_count function takes a char* parameter and counts the number of 
 * values in the parameter string. This is equivalent to the number of commas
 * plus one. The function returns the one plus the number of commas in the parameter
 * string, the number of values in the string.
 */
int value_count(char* buffer)
{
	int commas = 0;
	int size   = strlen(buffer);

	for(int i = 0; i < size; i++)
	{
		if(buffer[i] == ',')
			commas++;
	}
	commas++;

	return commas;
}

/*
 * The contains_vertex function takes a DirectedGraph struct pointer and a void
 * pointer to a data point to search for in the DirectedGraph. If the data point
 * is found true is returned, otherwise false is returned.
 */
bool contains_vertex(DirectedGraph* digraph, void* vertex)
{
	// If digraph or vertex are NULL, return false.
	if(digraph == NULL || vertex == NULL)
		return false;

	// Retrieve a local pointer to the DirectedGraph's vertex list.
	LinkedList* list = digraph->vertexList;

	// For each vertex in the vertex list.
	for(int i = 0; i < linked_list_size(list); i++)
	{
		// Retrieve the vertex at index i in the vertex list.
		Vertex* v = linked_list_get(list, i);

		// If the vetex parameter is the same as vertex v.
		if(memcmp(v->data, vertex, digraph->valueSize) == 0)
		{
			return true;
		}
	}
	
	return false;
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
	PriorityQueue* pq = pQueue_initialize(sizeof(Vertex), (char*)"Vertex", compareVertex);
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
	LinkedList* vList = linked_list_initialize(sizeof(Vertex), (char*)"Vertex");

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


/*
 * The << operator (associated with an output stream) prints the adjacency matrix of the
 * directed graph in comma-separated format. 
 *
 * Important: adjacency element i,j corresponds
 * with the link FROM i TO j
 */

/*
std::ostream& operator<<(std::ostream& o, DirectedGraph& net)
{
	int link = 0;
	LinkedList* v = get_vertices(&net);
	int size = v->size;
        create_adjacency_matrix(&net);
	float** A = get_adjacency_matrix(&net);
	for (int i=0;i<size;i++)
	{
		for (int j=0;j<size;j++)
		{
			if (A[i][j] != FLT_MAX) { o << A[i][j]; } else { o << 0; };
			if (j<(size-1)) { o << ","; } else { o << "\n"; }
			
		}
	}
	return (o);
}
*/

