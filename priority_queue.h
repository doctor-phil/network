/*
 * This file provides the forward declarations for the priority_queue.c file.
 */

#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include "linked_list.h"

template<typename T> class PriorityQueue
{
public:
    PriorityQueue(int, int (*)(void*, void*));
    bool		    pQueue_enqueue(PriorityQueue*, void*);
    void*		    pQueue_dequeue(PriorityQueue*);
    void*		    pQueue_peek(PriorityQueue*);
    int         	    pQueue_size(PriorityQueue*);
    bool		    pQueue_contains(PriorityQueue*, void*);
    void		    _pQueue_sort(PriorityQueue*);

private:
	LinkedList<T>* list;
	int(*compare)(void*, void*);
};



