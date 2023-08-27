/*
 * This is a direcected graph header file - providing the forward declarations
 * for the directed_graph.c file.
 */

#pragma once

#include <iostream>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <float.h>
#include "linked_list.h"
#include "vertex.h"
#include "priority_queue.h"

#define MAX FLT_MAX

template<typename T> class DirectedGraph {

	class Vertex {

		public: 
			Vertex*     create_vertex(void*);
			bool        add_vertex_arc(Vertex*, Vertex*, float);
			bool        remove_vertex_arc(Vertex*, Vertex*);
			void*       get_data(Vertex*);
			LinkedList<T>* get_arc_list(Vertex*);
			bool	    been_visited(Vertex*);
			void        set_visited(Vertex*, bool);
			float       get_weight(Vertex*, Vertex*);
			bool	    change_vertex_weight(Vertex*, Vertex*, float);
			void	    set_vertex_distance(Vertex*, float);	
			float	    get_vertex_distance(Vertex*);
			void	    set_vertex_parent(Vertex*, Vertex*);
			Vertex*	    get_vertex_parent(Vertex*);
			bool	    has_arc_to_vertex(Vertex*, Vertex*);

		LinkedList<T>* arcList;
		T data;
		bool visited;
		float distance;
		Vertex* parent;

		private:

	};

	class Arc {
		public:
			Arc*        create_arc(Vertex*, float);
			void        set_arc_weight(Arc*, float);
			void        set_vertex(Arc*, Vertex*);
			float       _get_arc_weight(Arc*);
			Vertex*     get_arc_vertex(Arc*);
		
		Vertex* vertex;
		float weight;

		private:

	};

	public:
		DirectedGraph();
		int getSize();
		bool addVertex(T);
		bool		    remove_vertex(DirectedGraph*, void*);
		LinkedList*	    get_vertices(DirectedGraph*);
		LinkedList*	    get_arcs(DirectedGraph*, void*);
		bool		    add_arc(DirectedGraph*, void*, void*, float);
		bool		    remove_arc(DirectedGraph*, void*, void*);
		bool		    change_arc_weight(DirectedGraph*, void*, void*, float);
		int 		    connected_vertices_count(DirectedGraph*, void*);
		int		    _connected_vertices_count_recursive(DirectedGraph*, void*);
		void*		    source_vertex(DirectedGraph*);
		void		    set_visited_field(DirectedGraph*, bool);
		void		    buildTree(DirectedGraph*, void*);
		float		    get_arc_weight(DirectedGraph*, void*, void*);
		void		    reset_parent_links(DirectedGraph*);
		int		    compareVertex(void*, void*);
		LinkedList*	    dijkstra(DirectedGraph*, void*, void*);
		float**		    all_pairs_shortest_paths(DirectedGraph*);
		void		    create_adjacency_matrix(DirectedGraph*);
		float**		    get_adjacency_matrix(DirectedGraph*);
		bool 		    contains_vertex(DirectedGraph*, void*);
		DirectedGraph*      create_digraph_from_file(char*);
		float		    extract_value(int, int, char*);
		float*		    float_arr_from_str(char*);
		int		    value_count(char*);
		std::ostream& 	    operator<<(std::ostream& o, DirectedGraph& net);
	
	private:
		LinkedList<T>* vertexList;
		int valueSize;
		float** adjacencyMatrix;

		Vertex* getVertex(T);

};

/*
 * Constructs a Directed Graph object. 
 */
template<typename T> DirectedGraph<T>::DirectedGraph(){
	this->vertexList = new LinkedList<T>();
	this->adjacencyMatrix = nullptr;
}

/* 
 * Returns the number of vertices in the Directed Graph.
 */
template<typename T> int DirectedGraph<T>::getSize(){
	return this->vertexList->getSize();
}

/*
 * Searches the Directed Graph for a vertex that contains the value parameter.
 * A pointer to that vertex is returned if found, otherwise nullptr is returned.
 */
template<typename T> Vertex* getVertex(T value) {
	if(value == nullptr)
		return nullptr;

	int size = this->vertexList->getSize();
	
	// For each vertex in the vertex list.
	for(int i = 0; i < size; i++) {

		// Retrieve the vertex at index i in the vertex list.
		Vertex* v = this->vertexList->get(i);

		// If the data fieled variable in the vertex is equal to the element parameter. 
		if(v->data == value) {
			// Return this vertex pointer.
			return v;
		}
	}

	return nullptr;
}

/*
 * The add vertex function creates a Vertex* pointer and adds it to the Directed Graph struct.
 * True is returned if the vertex was successfully added to the Directed Graph. Otherwie false 
 * is returned.
 */
template<typename T> bool DirectedGraph<T>::addVertex(T element){
	// If either parameter is NULL, return false.
	if(element == nullptr)
		return false;

	// Instantiate a Vertex struct while passing in the element parameter.
	Vertex* v = create_vertex(element);

	// Return the call to linkedlist add last function while passing in Directed Graph's vertex list and the instantiated vertex.
	return	this->vertexList->addLast(v);
}


