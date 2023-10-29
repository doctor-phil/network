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
		DirectedGraph();	// Tested
		int getSize();		// Tested
		bool addVertex(T);	// Tested
		bool removeVertex(T); // Tested
		LinkedList<T>*	    get_arcs(DirectedGraph*, void*);
		bool addArc(T, T, K);	// Tested
		bool removeArc(T, T);	// Tested
		bool changeArcWeight(T, T, K); // Tested
		int  connectedVerticesCount(T); // Tested
		Vertex<T,K>* sourceVertex();  // Tested
		void setVisitedField(bool);	// Tested
		void		    buildTree(DirectedGraph*, void*);
		K     getArcWeight(T, T);	// Tested
		void		    resetParentLinks();		// Implemented
		int		    compareVertex(void*, void*);	// Maybe require the user to ensure that T or K (which one?) implements the "comparable interface". I need to develop this interface.
		LinkedList<T>*	    dijkstra(DirectedGraph*, void*, void*);
		float**		    all_pairs_shortest_paths(DirectedGraph*);
		void		    create_adjacency_matrix(DirectedGraph*);
		float**		    get_adjacency_matrix(DirectedGraph*);
		bool 		    contains_vertex(DirectedGraph*, void*);
		DirectedGraph<T,K>*      create_digraph_from_file(char*);
		float		    extract_value(int, int, char*);
		float*		    float_arr_from_str(char*);
		int		    valueCount(char*);			// Implemented
		//std::ostream& 	    operator<<(std::ostream& o, DirectedGraph& net);
		void enumerateVertices();
		
	private:
		LinkedList<Vertex<T,K>*>* vertexList;
		int valueSize;
		float** adjacencyMatrix;
		Vertex<T, K>* getVertex(T);	// Tested
		LinkedList<Vertex<T,K>*>* getVertices();	// Tested
		int  connectedVerticesCountHelper(Vertex<T,K>*); // Tested

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
 * A pointer to that vertex is returned if found.
 */
template<typename T, typename K>  Vertex<T,K>* DirectedGraph<T, K>::getVertex(T value){

	int size = this->vertexList->getSize();
	
	// For each vertex in the vertex list.
	for(int i = 0; i < size; i++) {

		// Retrieve the vertex at index i in the vertex list.
		Vertex<T,K>* v = this->vertexList->get(i);

		// If the data fieled variable in the vertex is equal to the element parameter. 
		if(v->getData() == value) {
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

	// Return the call to linkedlist add last function while passing in
	// Directed Graph's vertex list and the instantiated vertex.
	return this->vertexList->addLast(v);
}

/*
 * The remove function removes a specific Vertex containing the 
 element parameter from the Directed Graph, if found.
 */
template<typename T, typename K> bool DirectedGraph<T, K>::removeVertex(T element){

	// Store vertex list's current size in a local variable.	
	int prevSize = this->vertexList->getSize();
	bool found   = false;
	Vertex<T,K>* vtx;
	// For each vertex in the vertex list.
	for(int i = 0; i < prevSize; i++) {

		// Retrieve the vertex in the vertex list at index i.
		Vertex<T,K>* v = this->vertexList->get(i);

		// If this vertex is equivalent to the element parameter.	
		if(v->getData() == element) {
			// Remove this vertex from the vertex list.
			vtx = this->getVertex(element);
			this->vertexList->remove(i);
			found = true;
			break;
		}
	}

	if(found){
		for(int i = 0; i < this->vertexList->getSize(); i++){
			Vertex<T,K>* v = this->vertexList->get(i);
			v->removeArc(vtx);
		}
		return true;
	} else {
		return false;
	}
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

	// Retrieve the Vertices associated with the origin and destination parameters.
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
	Vertex<T,K>* start = getVertex(origin);
	Vertex<T,K>* end   = getVertex(destination);
	return start->removeArc(end);
}

/*
 * The set_visited_field function changes the visited data member for all
 * vertex structs within the DirectedGraph* struct to the value of the bool parameter.
 */
template<typename T, typename K> void DirectedGraph<T, K>::setVisitedField(bool value) {

	// For each vertex in the Directed Graph's vertex list.
	for(int i = 0; i < this->vertexList->getSize(); i++) {
		Vertex<T,K>* v  = this->vertexList->get(i);
		v->setVisited(value);
	}
}

template<typename T, typename K> void DirectedGraph<T, K>::enumerateVertices() {

	for(int i = 0; i < this->vertexList->getSize(); i++) {

		Vertex<T,K>* v = this->vertexList->get(i);
		std::map<Vertex<T,K>*, K> map = v->getArcMap();
		std::cout << v->getData() << ":\n";

		for(auto j = map.begin(); j != map.end(); j++){
			std::cout << "\t" << j->first->getData() << ": " << j->second << "\n";
		}
	}
}

template<typename T, typename K> bool DirectedGraph<T,K>:: changeArcWeight(T origin, T destination, K weight){
	Vertex<T,K>* start = this->getVertex(origin);
	Vertex<T,K>* end  = this->getVertex(destination);
	return start->changeWeight(end, weight);
}

template<typename T, typename K> K DirectedGraph<T,K>::getArcWeight(T origin, T destination){
	Vertex<T,K>* start = this->getVertex(origin);
	Vertex<T,K>* end  = this->getVertex(destination);
	return start->getWeight(end);
}

/*
 * The sourceVertex function traverses the Directed Graph structure from each 
 * vertex. The first vertex found from which all vertices can be visited is returned. 
 * If no such vertex exists, then NULL is returned.
 */
template<typename T, typename K> Vertex<T,K>* DirectedGraph<T,K>::sourceVertex(){
	int numOfVertices = this->vertexList->getSize();
	for(int i = 0; i < numOfVertices; i++){
		Vertex<T,K>* v = this->vertexList->get(i);
		int visited = this->connectedVerticesCountHelper(v);
		if(visited == numOfVertices){
			return v;
		}
	}

	return nullptr;
}

/*
 * The connectedVerticesCount function takes the data in the graph as a parameter, 
 * the origin to explore the graph from, calls a helper recursive function, resets 
 * all the vertices visited field to false, and returns the count of the vertices 
 * traversable from the origin parameter. 
 */
template<typename T, typename K> int DirectedGraph<T,K>::connectedVerticesCount(T origin){
	Vertex<T,K>* source = this->getVertex(origin);
	int count 			= 0;
	count 				+= this->connectedVerticesCountHelper(source);

	this->setVisitedField(false);
	return count;
}

/*
 * The connectedVerticesCountHelper function takesVertex pointer to serve as an origin vertex. 
 * The function then recursively visits each vertex traversable via the vertx's arcMap that 
 * has not been visited and counts the number of vertices. The count of the number of vertices
 * visited is returned to the client.
 */
template<typename T, typename K> int DirectedGraph<T,K>::connectedVerticesCountHelper(Vertex<T,K>* source){
	int count = 0;

	if(!source->getVisited()){
		source->setVisited(true);
		count++;

		for(auto const& it : source->getArcMap()){
			count += connectedVerticesCountHelper(it.first);
		}

	} else {
		return count;
	}

	return count;
}

/*
 * The resetParentLinks function changes the parent reference of each vertex in the graph's
 * vertexList to nullptr.
 */
template<typename T, typename K> void DirectedGraph<T,K>::resetParentLinks(){

	// For each vertex in the Directed Graph's vertex list.
	for(int i = 0; i < this->vertexList->getSize(); i++){
		// Retrieve a reference to the vertex struct at index i.
		Vertex<T,K>* v = this->vertexList->get(i);
		// Assign the vertex's parent reference to NULL.
		v->setParent(nullptr);
	}
}

/**
 * The valueCount function takes a char* parameter containing a csv of values and counts 
 * the number of values in the parameter string. This is equivalent to the number of commas
 * plus one.
 */
template<typename T, typename K> int DirectedGraph<T,K>::valueCount(char* buffer){
	int commas = 0;
	int size   = strlen(buffer);

	for(int i = 0; i < size; i++){ if(buffer[i] == ','){ commas++;}}
	commas++;

	return commas;
}