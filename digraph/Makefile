# This is a Makefile for compiling the directed graph project.

# Defining the compiler
COMPILER = gcc

# Defining the c standard
CSTD = --std=c18

# Specifying the c files to compile with
C_FILES = linked_list.c vertex.c priority_queue.c

# Specifying the header files to compile with
H_FILES = linked_list.h vertex.h priority_queue.h directed_graph.h

# Defining a variable to hold various library flags
LIB_FLAGS = -g 

# Specifying the c file that hold the main
MAIN = directed_graph.c

# Defining the call to make
all: digraph

# Defining part 1 of the call to make
digraph: $(H_FILES) $(MAIN)
	$(COMPILER) $(CSTD) $(MAIN) $(C_FILES) -o digraph $(LIB_FLAGS)

# Implementing the clean Makefile functionality
clean:
	rm -f digraph
