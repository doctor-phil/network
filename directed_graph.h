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
#include "priority_queue.h"

#define MAX FLT_MAX

template<typename T, typename K> class DirectedGraph {

	class Vertex {
		public: 
			Vertex(T data){
				this->data = data;
				this->arcList = new LinkedList<Arc*>();
				this->visited = false;
				this->distance = 0;
				this->parent = nullptr;
			}

			/*
			 * This function adds an arc struct going from the Vertex* origin parameter
			 * to the Vertex* dest parameter with a weight of the float price parameter.   
			 */
			bool addArc(Vertex* destination, K weight) {
					if(destination == nullptr)
						return false;

				Arc* arc = new Arc(destination, weight);

				int prevSize = this->arcList->getSize();
				
				this->arcList->add_last(arc);	

				if(this->arcList->getSize() - prevSize == 1) {
					return true;
				} else {
					return false;
				}
			}

			bool removeArc(Vertex* destination){
				if(destination == nullptr)
					return false;
				
				int prevSize = this->arcList->getSize();

				for(int i = 0; i < prevSize; i++) {
					Arc* arc = this->arcList->get(i);

					if(arc->vertex->data == destination->data) {
						this->arcList->remove(i);
						break;
					}
				}

				if(prevSize - this->arcList->getSize() == 1) {
					return true;
				} else {
					return false;
				}
			}

			T getData() {
				return this->data;
			}

			LinkedList<Arc*>* get_arc_list() {
				return this->arcList;
			}

			bool getVisited() {
				return this->visited;
			}

			void setVisited(bool visit) {
				this->visited = visit;
			}

			/*
			 * The get_weight function takes a Vertex* origin vertex that goes to the 
			 * Vertex* destination vertex parameter and returns the weight of that arc 
			 * if such an arc exists. -1 is returned if no such arc exists.
			 */
			K getWeight(Vertex* destination) {
				if(destination == nullptr)
					return -1;

				for(int i = 0; i < this->arcList->getSize(); i++) {
					Arc* arc = this->arcList->get(i);
					
					// If the destination vertex is found in this vertex's arc list.	
					// MAY NEED TO COMPARE THE VERTICES AND NOT THE DATA BASED ON MEMORY ADDRESS	
					if(this->data == destination->data) {
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
			bool changeWeight(Vertex* destination, K weight) {
				if(destination == nullptr)
					return false;

				for(int i = 0; i < this->arcList->getSize(); i++) {
					Arc* arc  = this->arcList->get(i);

					// If this arc's vertex is equal to the destination vertex
					// MAY NEED TO COMPARE THE VERTICES AND NOT THE DATA BASED ON MEMORY ADDRESS
					if(destination->data == arc->vertex->data) {
						arc->setWeight(weight);
						return true;
					}
				}

				return false;
			}

			void setDistance(K distance) {
				this->distance = distance;
			}	

			K getDistance() {
				return this->distance;
			}

			void setParent(Vertex* v) {
				this->parent = v;
			}

			Vertex* getParent() {
				return this->parent;
			}
			
			bool hasArc(Vertex* v) {

			}

		private:
			LinkedList<Arc*>* arcList;
			T data;
			bool visited;
			K distance;
			Vertex* parent;
	};

	class Arc {
		public:
			Arc(Vertex* vertex, K weight) {
				this->vertex = vertex;
				this->weight = weight;
			}

			void setWeight(K weight) {
				this->weight = weight;
			}

			void setVertex(Vertex* vertex){
				this->vertex = vertex;
			}

			K getWeight(){
				return this->weight;
			}

			Vertex* getVertex() {
				return this->vertex;
			}
		
		private:
			Vertex* vertex;
			K weight;
	};

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
		LinkedList<T>* vertexList;
		int valueSize;
		float** adjacencyMatrix;
		Vertex* getVertex(T);
		LinkedList<T>* getVertices();

};

/*
 * Constructs a Directed Graph object. 
 */
template<typename T, typename K> DirectedGraph<T, K>::DirectedGraph(){
	this->vertexList = new LinkedList<T>();
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
template<typename T, typename K>  Vertex* DirectedGraph<T, K>::getVertex(T value){
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
template<typename T, typename K> bool DirectedGraph<T, K>::addVertex(T element){
	// If either parameter is NULL, return false.
	if(element == nullptr)
		return false;

	// Instantiate a Vertex struct while passing in the element parameter.
	Vertex* v = create_vertex(element);

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
		Vertex* v = this->vertexList->get(i);

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
template<typename T, typename K> LinkedList<T>* DirectedGraph<T, K>::getVertices(){
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
	Vertex* start = getVertex(origin);
	Vertex* end   = getVertex(destination);

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

	Vertex* start = getVertex(origin);
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
		Vertex* v  = this->vertexList->get(i);
		v->setVisited(value);
	}
}