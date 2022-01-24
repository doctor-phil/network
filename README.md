# network

## Project Description
This project aims to provide a library of services for network related activities. The [directed_graph.c](firected_graph.c) file implements a directed graph, referred to as the "DiGraph" or "the structure" from here forward, and can represent node adjacencies in both the adjacency list and adjacency matrix representations. Dijkstra's shortest path and Floyd-Warshall's all pairs shortest paths algorithms have been implemented. In addition, reading adjacency matrix representations from files to construct the directed graph structure is also supported.

## Installing & Running
Clone the repository as appropriate for your machine. Instructions on how to clone a repository for your specific machine can be found at this [GitHub webpage](https://docs.github.com/en/repositories/creating-and-managing-repositories/cloning-a-repository). 
<br />
<br />
To use the DiGraph structure and its features, write your code in the file [main.c](main.c). All services for the DiGraph structure are supported in this file. 
### Compiling & Using the DiGraph
What follows in this section is examples of how to compile from the command line, initialize the structure, create and add vertices to the structure, add weighted arcs between vertices in the structure, a note on adjacency representations, how to use the shortest path functions, and how to constructe a DiGraph from a file. For more detail regarding the functions cited mentioned below, please see the appropriate files in the repository.
<br />
#### Compiling
The command `make` can be used to compile from a command line environment. The resulting `digraph` executable file will be created. The assocaited [Makefile](Makefile) uses the gcc compiler and the C18 standard.
#### Initializing 
The DiGraph structure is initialized based on the size of the type to be stored in the vertices. The structure uses void pointers, specifically `void*`, to perform operations within. Because a void pointer cannot be dereferenced in the C programming language, the size of the type must be specified when initializing the DiGraph structure. The benefit of using void pointers is that it allows the user to store any type as the data for the vertices in the graph. For example, here is a directed graph that stores char types.
```
DirectedGraph* digraph = initialize_digraph(sizeof(char),"char");
```
#### Creating Vertices
The DiGraph accepts pointers to the data to be stored in each vertex. After creating the pointers to the data to be stored in each vertex, the `add_vertex()` function will create the vertex, initialize its variables, and add it to the digraph structure. An example can be found below.
```
char* a = "a";
char* b = "b";
char* c = "c";
add_vertex(digraph, a);
add_vertex(digraph, b);
add_vertex(digraph, c);
```
#### Adding Arcs
To add arcs between vertices, both vertices must exist in the DiGraph structure. The `add_arc()` function will create an arc in the DiGraph from the first vertex to the second with the specified weight. Specifically, if we were to call `add_arc(digraph, a, b, .1000056)` when vertices *a* and *b* exist in the structure *digraph*, the `add_arc()` function would create an Arc struct, which is a structure that holds a pointer to the destination vertex, *b*, and a weight, *.1000056* in this example, and add this Arc structure to the origin's arc list, *a* in this case. Arc weights are of type float. For more detail about the Arc structure, please see the code and documentation in [vertex.c](vertex.c). An example can be found below.
```
add_arc(digraph, a, b, 4.005);
add_arc(digraph, a, c, 253);
```
#### Adjacency Representations
The DiGraph structure initially represents all arcs between vertices as an adjacency list. To construct the adjacency matrix representation, the `create_adjacency_matrix()` function must be called. The function `get_adjacency_matrix()` returns a 2D array, representing the adjacency matrix. The adjacency matrix entry at (i,j) is the weight of the arc from vertex *i* to vertex *j*. An example of each function call follows.
```
create_adjacency_matrix(digraph);
float** adjMtx = get_adjacency_matrix(digraph);
```
#### Shortest Paths
To retrieve the shortest path from vertex *a* to vertex *b*, the `dijkstra()` function could be used. This function returns a linkedlist structure of the vertices from *a* to *b*. The `all_pairs_shortest_paths()` function will compute and return a matrix of the shortest paths for all pairs of vertices in the graph structure, where the matrix entry (i,j) is the weight of the arc from vertex *i* to vertex *j*. Examples of calling these functions follow.
```
LinkedList* vList = dijkstra(a, b);
float** allPairs  = all_pairs_shortest_paths(digraph);
```
#### Building a DiGraph From a File
To construct a DiGraph from a file that holds an adjacency matrix representation, the `create_digraph_from_file()` function could be used. This function only takes name of the file as an argument. This file must follow a specific format for the adjacency matrix to be read. Please see the function description in [directed_graph.c](directed_graph.c) for details regarding the specific adjacency matrix format needed. Once this function completes, the structure will hold all vertices in an adjacency list representation. To retrieve the adjacency matrix from the structure, see the section above on [Adjacency Representations](#Adjacency-Representations).
```
DirectedGraph* digraph = create_digraph_from_file("fileName");
```

## Licence & Copyright
Licensed under the [MIT License](LICENSE). <br />
Copyright (c) 2021 Philip Solimine and Michael St. Denis
