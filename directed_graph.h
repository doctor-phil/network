/*
 * This file provides the declaration and implementation of the
 digraph template class.
 */

#pragma once

#include <iostream>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <float.h>
#include "linked_list.h"
//#include "vertex.h"
#include "vertex0.h"
#include "priority_queue.h"

#define MAX FLT_MAX

template<typename T, typename K> class DirectedGraph {
	public:
		DirectedGraph();
		int getSize();
		bool addVertex(T);
		bool removeVertex(T);
		LinkedList<T>*	    get_arcs(DirectedGraph*, void*);
		bool addArc(T, T, K);
		bool removeArc(T, T);
		bool		    change_arc_weight(DirectedGraph*, void*, void*, float);
		int 		    connected_vertices_count(DirectedGraph*, void*);
		int		    _connected_vertices_count_recursive(DirectedGraph*, void*);
		void*		    source_vertex(DirectedGraph*);
		void setVisitedField(bool);
		void		    buildTree(DirectedGraph*, void*);
		float		    get_arc_weight(DirectedGraph*, void*, void*);
		void		    reset_parent_links(DirectedGraph*);
		int		    compareVertex(void*, void*);
		LinkedList<T>*	    dijkstra(DirectedGraph*, void*, void*);
		float**		    all_pairs_shortest_paths(DirectedGraph*);
		void		    create_adjacency_matrix(DirectedGraph*);
		float**		    get_adjacency_matrix(DirectedGraph*);
		bool 		    contains_vertex(DirectedGraph*, void*);
		DirectedGraph<T,K>*      create_digraph_from_file(char*);
		float		    extract_value(int, int, char*);
		float*		    float_arr_from_str(char*);
		int		    value_count(char*);
		//std::ostream& 	    operator<<(std::ostream& o, DirectedGraph& net);
		
	private:
		LinkedList<Vertex<T,K>*>* vertexList;
		int valueSize;
		float** adjacencyMatrix;
		Vertex<T, K>* getVertex(T);
		LinkedList<Vertex<T,K>*>* getVertices();

};

/*
 * Constructs a Directed Graph object. 
 */
template<typename T, typename K> DirectedGraph<T, K>::DirectedGraph(){
	this->vertexList = new LinkedList<Vertex<T,K>*>();
	this->adjacencyMatrix = nullptr;
}

/* 
 * Returns the number of vertices in the Directed Graph.
 */
template<typename T, typename K> int DirectedGraph<T, K>::getSize(){
	return this->vertexList->getSize();
}

/*
 * Searches the Directed Graph for a vertex that contains the value parameter.
 * A pointer to that vertex is returned if found, otherwise nullptr is returned.
 */
template<typename T, typename K>  Vertex<T,K>* DirectedGraph<T, K>::getVertex(T value){
	if(value == nullptr)
		return nullptr;

	int size = this->vertexList->getSize();
	
	// For each vertex in the vertex list.
	for(int i = 0; i < size; i++) {

		// Retrieve the vertex at index i in the vertex list.
		Vertex<T,K>* v = this->vertexList->get(i);

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
template<typename T, typename K> bool DirectedGraph<T, K>::addVertex(T element){

	// Instantiate a Vertex struct while passing in the element parameter.
	Vertex<T,K>* v = new Vertex<T,K>(element);

	// Return the call to linkedlist add last function while passing in Directed Graph's vertex list and the instantiated vertex.
	return	this->vertexList->addLast(v);
}

/*
 * The remove function removes a specific Vertex containing the 
 element parameter from the Directed Graph, if found.
 */
template<typename T, typename K> bool DirectedGraph<T, K>::removeVertex(T element){
	// If element is a nullptr return false.
	if(element == nullptr)
		return false;
	
	// Store vertex list's current size in a local variable.	
	int prevSize = this->vertexList->getSize();

	// For each vertex in the vertex list.
	for(int i = 0; i < prevSize; i++) {

		// Retrieve the vertex in the vertex list at index i.
		Vertex<T,K>* v = this->vertexList->get(i);

		// If this vertex is equivalent to the element parameter		
		if(v->data == element) {
			// Remove this vertex from the vertex list and break from loop.
			this->vertexList->remove(i);
			return true;
		}
	}

	return false;
}

/*
 * Returns the list of vertices in the Directed Graph.
 */
template<typename T, typename K> LinkedList<Vertex<T,K>*>* DirectedGraph<T, K>::getVertices(){
	return this->vertexList;
}

/*
 * The add arc function takes a DirectedGraph* struct pointer, a void* pointer to 
 * the origin vertex, a void* pointer to the destination vertex, and a float value
 * representing the weight of the arc. The function then creates an arc from the
 * origin vertex to the destination vertex with the appropriate weight assigned.
 * This function returns true if the arc between origin and destination was added
 * to the Directed Graph struct successfully, otherwise false is returned.
 */
template<typename T, typename K> bool DirectedGraph<T,K>::addArc(T origin, T destination, K cost) {

	// If either origin or destination parameter is nullptr, return false.
	if(origin == nullptr || destination == nullptr)
		return false;

	// Otherwise retrieve the Vertices associated with the origin and destination parameters.
	Vertex<T,K>* start = getVertex(origin);
	Vertex<T,K>* end   = getVertex(destination);

	// Return the call to add vertex arc function with the two vertices and the arc weight.
	return start->addArc(end, cost);
} 


/*
 * The remove arc function removes the arc from the origin veretx to the destination vertex
 * parameters.
 */
template<typename T, typename K> bool DirectedGraph<T,K>::removeArc(T origin, T destination) {
	if(origin == nullptr || destination == nullptr)
		return false;

	Vertex<T,K>* start = getVertex(origin);
	return start->removeArc(destination);
}

/*
 * The set_visited_field function changes the visited data member for all
 * vertex structs within the DirectedGraph* struct to the value of the bool parameter.
 */
template<typename T, typename K> void DirectedGraph<T, K>::setVisitedField(bool value) {

	// For each vertex in the Directed Graph's vertex list.
	for(int i = 0; i < this->vertexList; i++) {
		// Retrieve the vertex struct at index i.
		Vertex<T,K>* v  = this->vertexList->get(i);
		v->setVisited(value);
	}
}