/*
 * This is a linked list data structure implementation. 
 */

#pragma once

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


template<typename T> class LinkedList
{
    class Node
    {
    public:
        T data;
        Node* next;
        Node* prev;
    };

public:
    LinkedList<T> (int);
    bool 	      add_at(int, void*);
    bool 	      add_first(void*);
    bool	      add_last(void*);
    void* 	      get(int);
    int 	      index_of(void*);
    void* 	      remove(int);
    void* 	      remove_first();
    void* 	      remove_last();
    void	      swap(int, int);
    T             getFirst();
    T             getLast();
    int           getSize();
    int           getItemSize();

private:
	Node* first;
	Node* last;
	int   size;
	int   itemSize;


};
