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
    LinkedList(int);
    bool 	      add_at(int, T);
    bool 	      add_first(T);
    bool	      add_last(T);
    T    	      get(int);
    int 	      index_of(T);
    T    	      remove(int);
    T    	      remove_first();
    T    	      remove_last();
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
