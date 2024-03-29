#include <stdio.h>
#include "linked_list.h"
#include "priority_queue.h"
//#include "directed_graph.h"
#include <iostream>
#include <string>
#include <cstring>

class Animal{
public:
    Animal(std::string str){
        this->name = str;
    }

    std::string getName(){
        return this->name;
    }

    int compare(Animal a){
        return std::strcmp(this->name.c_str(), a.getName().c_str());
    }
private:
    std::string name;
};

int main(int argc, char** argv)
{

    LinkedList<Animal*> AList = LinkedList<Animal*>();

    Animal* a = new Animal("Fluffy");
    Animal* b = new Animal("Scruffy");
    Animal* c = new Animal("Moe");

    AList.add_last(a);
    AList.add_first(b);
    AList.add_at(1,c);

    for (int i = 0; i < AList.getSize(); ++i) {
        Animal* x = AList.get(i);
        std::cout << i << ": " << x->getName() << "\n";
    }

    Animal* d = AList.remove(1);
    Animal* e = AList.remove_first();
    Animal* f = AList.remove_last();

    std::cout << "First: " << e->getName() << "\n";
    std::cout << "Middle: " << d->getName() << "\n";
    std::cout << "Last: " << f->getName() << "\n";

///	delete d;
//	delete e;
//	delete f;

    AList.add_last(a);
    AList.add_first(b);
    AList.add_at(1,c);

    Animal* g = AList.getFirst();
    Animal* h = AList.getLast();

    std::cout << "First: " << g->getName() << "\n";
    std::cout << "Last: " << h->getName() << "\n";

//	delete g;
//	delete h;

    int aIdx = AList.index_of(a);
    int bIdx = AList.index_of(b);
    int cIdx = AList.index_of(c);

 //   std::cout << "Index of Fluffy (expected 2): " << aIdx << "\n";
 //   std::cout << "Index of Moe (expected 1): " << cIdx << "\n";
 //   std::cout << "Index of Scruffy (expected 0): " << bIdx << "\n";

    std::cout << "swapping 0 and 2\n";
    AList.swap(0,2);
    std::cout << "Index of Fluffy (expected 0): " << AList.index_of(a)<< "\n";
    std::cout << "Index of Scruffy (expected 2): " << AList.index_of(b) << "\n";

    std::cout << "swapping 0 and 2 ... again\n";
    AList.swap(2,0);
    std::cout << "Index of Fluffy (expected 2): " << AList.index_of(a)<< "\n";
    std::cout << "Index of Scruffy (expected 0): " << AList.index_of(b) << "\n";

    printf("\nPriority Queue Testing\n\n");

    PriorityQueue<Animal*, int>* pq = new PriorityQueue<Animal*, int>();

    // Need to determine how to compare objects.
    // Override an operator? Do all primitives and std::string support operator < ?

    
    pq->enqueue(a, 0);
	std::cout << "added " << a->getName() << "\n";
	
//	std::cout << "Animal peeked is (expected Fluffy): " << pq->peek()->getName() << "\n";

    pq->enqueue(b, 1);
	std::cout << "added " << b->getName() << "\n";

//	std::cout << "Peeking after added Fluffy and Scruffy with priorities 0 and 1\n";
//	std::cout << "Animal peeked is (expected Scruffy): " << pq->peek()->getName() << "\n";

    pq->enqueue(c, 2);
	std::cout << "added " << c->getName() << "\n";
	Animal* ab = new Animal("Jim");
	pq->enqueue(ab, 5);
	Animal* ac = new Animal("Bob");
	pq->enqueue(ac, 3);
	Animal* ad = new Animal("Beth");
	pq->enqueue(ad, 2);
	Animal* ae = new Animal("Becky");
	pq->enqueue(ae, 2);

	Animal* cd = new Animal("Larry");
	Animal* mo = new Animal("Moe");
 
	std::cout << "Contains Beth? expected true: " << pq->contains(ad) << "\n";
	std::cout << "Contains Larry? epected false: " << pq->contains(cd) << "\n";
	std::cout << "Contains a new Moe? epected false: " << pq->contains(mo) << "\n";
	std::cout << "Dequeue (expected Jim) " << pq->dequeue()->getName()<< "\n";
	std::cout << "Dequeue (expected Bob) "<< pq->dequeue()->getName()<< "\n";
	std::cout << "Dequeue (expected Moe) " << pq->dequeue()->getName()<< "\n";
	std::cout << "Dequeue (expected(Beth) " << pq->dequeue()->getName()<< "\n";
	std::cout << "Dequeue (expected Becky) " << pq->dequeue()->getName()<< "\n";
	std::cout << "Dequeue (expected Scruffy) " << pq->dequeue()->getName()<< "\n";
	std::cout << "Dequeue (expected Fluffy) " << pq->dequeue()->getName()<< "\n";
	std::cout << "list size (expected 0): " << pq->getSize() << "\n";

/*
    LinkedList<int>* list = new LinkedList<int>();

    list->add_first(0);
    for(int i = 1; i < 99; i++){
        list->add_at(i,i);
    }
    list->add_last(99);

    int size = list->getSize();

    for (int i = 0; i < size; ++i) {
        int item = list->get(i);
        printf("%d\n", item);
    }

    int first = list->remove_first();
    int last  = list->remove_last();
    
    printf("first %d\n", first);
    printf("last %d\n", last);

    for (int i = list->getSize()-1; i >=0; i--){
        int element = list->remove(i);
        printf("%d\n", element);
    }
*/


	// Instantiating a DirectedGraph struct.
/*	DirectedGraph* digraph = initialize_digraph(sizeof(char),"char");

	// Creating elements to add to graph.
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
*/
    /*
     * The code below demonstrates how to create a DiGraph from a csv file, create, retrieve and print the
     * adjacency matrix, print the String representation of a DiGraph to standard output, and compute and print
     * the all pairs' shortest paths algorithm (Floyd-Warshall) to standard output.
     */

//	DirectedGraph* digraph = create_digraph_from_file((char*)"test_adjacency.csv");

	// Retrieving a linkedlist of the vertices.
	/*LinkedList* vertexList = get_vertices(digraph);

	// Calling the void function to create the adjacency matrix for the digraph.
	create_adjacency_matrix(digraph);


	// Retrieving the adjacecny matrix as a 2D array.
	float** adjMtx = get_adjacency_matrix(digraph);


	// Formatting for adjacency matrix printing.
	printf("    ");
	for(int i = 0; i < linked_list_size(vertexList); i++)
	{
		Vertex* u = (Vertex*)linked_list_get(vertexList, i);
		printf("%d        ", *(int*) get_data(u));
	}
	printf("\n");

	// Printing adjacency matrix.
	for(int i = 0; i < digraph_size(digraph); i++)
	{
		Vertex* u = (Vertex*)linked_list_get(vertexList, i);
		printf("%d | ", *(int*) get_data(u));
	
		for(int j = 0; j < digraph_size(digraph); j++)
		{
			Vertex* v = (Vertex*)linked_list_get(vertexList, j);
			
			// If this edge weight is less than my max edge weight, print 0.
			if(!(has_arc_to_vertex(u, v)))
			{
				printf("0 ");

			// Otherwise print the edge value.
			} else {
				printf("%f ", adjMtx[i][j]);
			}
		}
		printf("\n");
	}
	printf("\n");

    // The code below prints a String representation of a Digraph to standard output.
	std::cout << *digraph << std::endl;
	
	// Calling all pairs shortest paths algorithm, retrieved as a 2D array.	
	float** paths = all_pairs_shortest_paths(digraph);

	// Formatting for all pairs shortest paths matrix.
	printf("    ");
	for(int i = 0; i < linked_list_size(vertexList); i++)
	{
		Vertex* u = (Vertex*)linked_list_get(vertexList, i);
		printf("%s ", (char*)get_data(u));
	}
	printf("\n");

	// Printing all pairs shortest paths matrix.
	for(int i = 0; i < digraph_size(digraph); i++)
	{
		Vertex* v = (Vertex*)linked_list_get(vertexList, i);
		printf("%s | ",(char*)get_data(v));
	
		for(int j = 0; j < digraph_size(digraph); j++)
		{
			printf("%.0f ", paths[i][j]);
		}
		printf("\n");
	}
	 */


	
	return 0;
}

