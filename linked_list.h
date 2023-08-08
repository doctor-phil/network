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
    bool 	    linked_list_add_at(LinkedList*, int, void*);
    bool 	    linked_list_add_first(LinkedList*, void*);
    bool	    add_last(void*);
    void* 	    get(int);
    int 	    linked_list_index_of(LinkedList*, void*);
    void* 	    linked_list_remove(LinkedList*, int);
    void* 	    linked_list_remove_first(LinkedList*);
    void* 	    linked_list_remove_last(LinkedList*);
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
