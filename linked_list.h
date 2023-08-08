/*
 * This is a linked list data structure implementation. 
 */

#pragma once

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

class Node
{
public:
	void* data;
	Node* next;
	Node* prev;

};

class LinkedList
{
public:
    LinkedList(int, char*);
    bool 	    add_at(int, void*);
    bool 	    add_first(void*);
    bool	    add_last(void*);
    void* 	    get(int);
    int 	    index_of(void*);
    void* 	    remove(int);
    void* 	    remove_first();
    void* 	    remove_last();
    void	    swap(int, int);
    Node*       getFirst();
    Node*       getLast();
    int         getSize();
    int         getItemSize();
    char*       getTypeName();

private:
	Node* first;
	Node* last;
	int   size;
	int   itemSize;
	char* typeName;
};
