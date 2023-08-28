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

			bool addArc(Vertex* destination, K weight) {
					if(destination == nullptr)
						return false;

				Arc* arc = new Arc(destination, price);

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

			LinkedList<T>* get_arc_list(Vertex*);

			bool getVisited() {
				return this->visited;
			}

			void setVisited(bool visit) {
				this->visited = visit;
			}

			float       getWeight(Vertex*, Vertex*);
			bool	    change_vertex_weight(Vertex*, Vertex*, float);

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
		LinkedList<T>*	    dijkstra(DirectedGraph*, void*, void*);
		float**		    all_pairs_shortest_paths(DirectedGraph*);
		void		    create_adjacency_matrix(DirectedGraph*);
		float**		    get_adjacency_matrix(DirectedGraph*);
		bool 		    contains_vertex(DirectedGraph*, void*);
		DirectedGraph<T,K>*      create_digraph_from_file(char*);
		float		    extract_value(int, int, char*);
		float*		    float_arr_from_str(char*);
		int		    value_count(char*);
		std::ostream& 	    operator<<(std::ostream& o, DirectedGraph& net);
		
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
	Vertex* start = get_vertex(graph, origin);
	Vertex* end   = get_vertex(graph, destination);

	// Return the call to add vertex arc function with the two vertices and the arc weight.
	return add_vertex_arc(start, end, cost);
} 
