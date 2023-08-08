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
    LinkedList* linked_list_initialize(int, char*);
    bool 	    linked_list_add_at(LinkedList*, int, void*);
    bool 	    linked_list_add_first(LinkedList*, void*);
    bool	    linked_list_add_last(LinkedList*, void*);
    void* 	    linked_list_get(LinkedList*, int);
    int 	    linked_list_index_of(LinkedList*, void*);
    void* 	    linked_list_remove(LinkedList*, int);
    void* 	    linked_list_remove_first(LinkedList*);
    void* 	    linked_list_remove_last(LinkedList*);
    int	        linked_list_size(LinkedList*);
    void	    linked_list_swap(LinkedList*, int, int);
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
