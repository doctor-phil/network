/*
#include <stdio.h>
#include "linked_list.h"
#include "priority_queue.h"
#include "directed_graph.h"

int main(int argc, char** argv)
{
	// Instantiating a DirectedGraph struct.
	DirectedGraph* digraph = initialize_digraph(sizeof(char),"char");

	// Creating elements to add to grapg
	char* a = "a";
	char* b = "b";
	char* c = "c";
	char* d = "d";
	char* e = "e";
	char* f = "f";

	// Adding elements to graph.
	add_vertex(digraph, a);
	add_vertex(digraph, b);
	add_vertex(digraph, c);
	add_vertex(digraph, d);
	add_vertex(digraph, e);
	add_vertex(digraph, f);

	// Creating edges between vertices and assigning weights.
	add_arc(digraph, a, b, 4);
	add_arc(digraph, a, e, 2);
	add_arc(digraph, a, f, 1);
	add_arc(digraph, b, c, 5);
	add_arc(digraph, b, a, 6);
	add_arc(digraph, c, e, 4);
	add_arc(digraph, d, e, 3);
	add_arc(digraph, d, b, 2);
	add_arc(digraph, e, d, 3);
	add_arc(digraph, e, b, 2);
	add_arc(digraph, e, f, 1);
	add_arc(digraph, f, d, 3);

	// Retrieving a linkedlist of the vertices.
	LinkedList* vertexList = get_vertices(digraph);

	// Calling the void function to create the adjacency matrix for the digraph.
	create_adjacency_matrix(digraph);


	// Retrieving the adjacecny matrix as a 2D array.
	float** adjMtx = get_adjacency_matrix(digraph);


	// Formatting for adjacency matrix printing.
	printf("    ");
	for(int i = 0; i < linked_list_size(vertexList); i++)
	{
		Vertex* u = linked_list_get(vertexList, i);
		printf("%s ", get_data(u));
	}
	printf("\n");

	// Printing adjacency matrix.
	for(int i = 0; i < digraph_size(digraph); i++)
	{
		Vertex* u = linked_list_get(vertexList, i);
		printf("%s | ", get_data(u));
	
		for(int j = 0; j < digraph_size(digraph); j++)
		{
			Vertex* v = linked_list_get(vertexList, j);
			
			// If this edge weight is less than my max edge weight, print 0.
			if(!(has_arc_to_vertex(u, v)))
			{
				printf("0 ");

			// Otherwise print the edge value.
			} else {
				printf("%.0f ", adjMtx[i][j]);
			}
		}
		printf("\n");
	}
	printf("\n");



	// Calling all pairs shortest paths algorithm, retrieved as a 2D array.	
	float** paths = all_pairs_shortest_paths(digraph);

	// Formatting for all pairs shortest paths matrix.
	printf("    ");
	for(int i = 0; i < linked_list_size(vertexList); i++)
	{
		Vertex* u = linked_list_get(vertexList, i);
		printf("%s ", get_data(u));
	}
	printf("\n");

	// Printing all pairs shortest paths matrix.
	for(int i = 0; i < digraph_size(digraph); i++)
	{
		Vertex* v = linked_list_get(vertexList, i);
		printf("%s | ",get_data(v));
	
		for(int j = 0; j < digraph_size(digraph); j++)
		{
			printf("%.0f ", paths[i][j]);
		}
		printf("\n");
	}


	
	return 0;
}
*/

