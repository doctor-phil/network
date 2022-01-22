# network

## Project Description
This project aims to provide a library of services for network related activities. The directed_graph.c file implements a directed graph and can represent node adjacencies in both the adjacency list and adjacency matrix representations. Dijkstra's shortest path and Floyd-Warshall's all pairs shortest paths algorithms have been implemented. In addition, reading adjacency matrix representations from files to construct the directed graph structure is also supported.
  
## Installing & Running
Clone the repository as appropriate for your machine. Instructions on how to clone a repository for your specific machine can be found at this [GitHub webpage](https://docs.github.com/en/repositories/creating-and-managing-repositories/cloning-a-repository). 
<br />
<br />
To use the DiGraph structure and its features, write your code in the file main.c. All services for the DiGraph structure are supported in this file. 

### Compiling & Using the DiGraph
What follows in this section is examples of how to compile from the command line, initialize the structure, create and add vertices to the structure, add weighted arcs between vertices in the structure, and a note on adjacency representations. For more detail regarding the functions cited mentioned below, please see the appropriate files in the repository.
<br />
#### Compiling
The command `make digraph` can be used to compile from a command line environment. The resulting `digraph` executable file will be created.
  
#### Initializing 
The DiGraph struct is initialized based on the size of the type to be stored in the vertices. For example, here is a directed graph that stores char types.
```
DirectedGraph* digraph = initialize_digraph(sizeof(char),"char");
```

#### Creating Vertices
The DiGraph accepts pointers ot the data to be stored in each vertex. After creating the pointers to the data to be stored in each vertex, the `add_vertex()` function will create the vertex, initialize its variables, and add it to the sigraph structure. An example can be found below.
```
char* a = "a";
char* b = "b";
char* c = "c";
add_vertex(digraph, a);
add_vertex(digraph, b);
add_vertex(digraph, c);
```
#### Adding Arcs
To add arcs between vertices, both vertices must exist in the DiGraph structure. The `add_arc()` function will create an arc in the DiGraph from the first vertex to the second with the specified weight. An exmaple can be found below.
```
add_arc(digraph, a, b, 4.005);
add_arc(digraph, a, c, 253);
```
#### Adjacency Representations
The DiGraph structure initially represents all arcs between vertices as an adjacency list. To construct the adjacency matrix representation, the `create_adjacency_matrix()` function must be called. The function `get_adjacency_matrix()` returns a 2D array, representing the adjacency matrix. An example of each function call follows.
```
create_adjacency_matrix(digraph);

float** adjMtx = get_adjacency_matrix(digraph);
```
## Licence & Copyright
Licensed under the [MIT License](LICENSE). <br />
Copyright (c) 2021 Philip Solimine and Michael St. Denis
