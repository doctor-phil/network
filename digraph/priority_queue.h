/*
 * This file provides the forward declarations for the priority_queue.c file.
 */

#ifndef __PRIORITYQUEUE_HEADER
#define __PRIORITYQUEUE_HEADER

#include <stdlib.h>
#include <stdbool.h>
#include "linked_list.h"

typedef struct _PriorityQueue
{
	LinkedList* list;
	int(*compare)(void*, void*);
} PriorityQueue;

PriorityQueue*	pQueue_initialize(int, char*, int (*)(void*, void*));
bool		pQueue_enqueue(PriorityQueue*, void*);
void*		pQueue_dequeue(PriorityQueue*);
void*		pQueue_peek(PriorityQueue*);
int		pQueue_size(PriorityQueue*);
bool		pQueue_contains(PriorityQueue*, void*);
void		_pQueue_sort(PriorityQueue*);


#endif
