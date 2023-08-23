/*
 * This priority_queue.c file implements the functions declared in the priority_queue.h file.
 * Note: a compare function pointer must be passed to the pQueue_initialize function 
 * to have the priority queue function properly. Otherwise, undefined behavior could occur. 
 *
 * Below is an example compare function that can be passed into the PriorityQueue struct
 * that is then used in _pQueue_sort to sort the PriorityQueue accordingly.
 *
 * int compareFunction(void* a, void* b)
 * {
          return (*(int*)a - *(int*)b);
 * }
 */

#include "priority_queue.h"
#include "linked_list.h"
#include <stdio.h>

/*
template<typename T> PriorityQueue<T>::PriorityQueue(int itemSize, int (*compareFunction)(void*,void*)) {

	this->list    = LinkedList<T>(itemSize);
	this->compare = compareFunction;
}
 */

/*
bool pQueue_enqueue(PriorityQueue* pq, void* element)
{
	if(pq == NULL || element == NULL)
		return false;

	bool result = linked_list_add_first(pq->list, element);

	_pQueue_sort(pq);

	return result;
}
 */
/*
void* pQueue_dequeue(PriorityQueue* pq)
{
	if(pq == NULL)
		return NULL;

	return linked_list_remove_last(pq->list);
}

void* pQueue_peek(PriorityQueue* pq)
{
	if(pq == NULL)
		return NULL;
	
	int end = linked_list_size(pq->list) - 1;

	return linked_list_get(pq->list, end);
}

int pQueue_size(PriorityQueue* pq)
{
	if(pq == NULL)
		return -1;

	return linked_list_size(pq->list);
}

bool pQueue_contains(PriorityQueue* pq, void* element)
{
	if(pq == NULL || element == NULL)
		return false;

	return -1 != linked_list_index_of(pq->list, element);
}

void _pQueue_sort(PriorityQueue* pq)
{
	if(pq == NULL)
		return;
	
	int size = linked_list_size(pq->list);

	for(int i = 0; i < size; i++)
	{
		void* outer = linked_list_get(pq->list, i);

		for(int j = i + 1; j < size; j++)
		{
			void* inner     = linked_list_get(pq->list, j);
			int directional = pq->compare(outer, inner);
			
			if(directional < 0)
			{
				// call linked_list_swap(int i, int j) here
				linked_list_swap(pq->list, i, j);
			}
		}
	}
}
*/