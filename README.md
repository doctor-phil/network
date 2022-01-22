# network

## Project Description
This project aims to provide a library of services for network related activities. The directed_graph.c file implements a directed graph and can represent node adjacencies in both the adjacency list and adjacency matrix representations. Dijkstra's shortest path and Floyd-Warshall's all pairs shortest paths algorithms have been implemented. In addition, reading adjacency matrix representations from files to construct the directed graph structure is also supported.
  
## Installing & Running
Clone the repository as appropriate for your machine. Instructions on how to clone a repository for your specific machine can be found at this [GitHub webpage](https://docs.github.com/en/repositories/creating-and-managing-repositories/cloning-a-repository). 
<br />
<br />
To use the DiGraph structure and its features, write your code in the file main.c. All services for the DiGraph structure are supported in this file. 

### Compiling & Using the DiGraph
What follows in this section is examples of how to compile from the command line, initialize the structure, create and add vertices to the structure, and add arcs between vertices in the structure.
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


This package contains 4 files, not including this README. One is the Makefile which contains the compilation directive for the C program. 

The library header file network.h defines the class Scalefree for a scalefree network. Within this header file is the definition of the Scalefree() constructor which uses the Barabasi-Albert model of preferential attachment to draw a network with a scale-free degree distribution.

The C++ source code file scalefree.cpp contains the main() routine which initiates a scale-free network. The first command line argument given to this program, if it exists, is defined to be the number of nodes in the desired network. If there is no command line input, then this defaults to 10 nodes. The second command line argument, if it exists, defines the m0 starting number of nodes to include in the completely connected component which serves as the initiation of the network, before the rest of the n-m0 nodes are added with preferential attachment. The default value of m0 is 3. The third and final command line input is m, the number of links each new node will make when it is added to the network. The default value of m is 2. If assigned separately, m should be set to a value that is smaller than m0. This file outputs the adjacency matrix to stdout, but also will create a file called adjacency.csv which will store the adjacency matrix. (this file can become very large when n is large.)

The final file is plotgraph.r. This is an R script that uses the libraries igraph and ggplot2, inputs the adjacency.csv file, and outputs pdf and jpg images containing a visual representation of the graph along with its degree distribution on a log-log scale.

Dependencies:
network.h/scalefree.cpp - requires C++ <random> library, <iostream> and <fstream>, and <cmath>

plotgraph.r - requires "igraph" and "ggplot2" libraries for R
  
## Licence & Copyright
Licensed under the [MIT License](LICENSE). <br />
Copyright (c) 2021 Philip Solimine and Michael St. Denis
