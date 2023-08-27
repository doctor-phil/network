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
		Vertex*		    get_vertex(DirectedGraph*, void*);
		bool		    add_vertex(DirectedGraph*, void*);
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

};

template<typename T> DirectedGraph<T>::DirectedGraph(){
	this->vertexList = new LinkedList<T>();
}
template<typename T> int DirectedGraph<T>::getSize(){

}


