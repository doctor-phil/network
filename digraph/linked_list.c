/*
 * This file implements the functions decalred in the 
 * linked_list.h header file - the behavior of a linked list data structure.
 */

#include "linked_list.h"

LinkedList* linked_list_initialize(int item, char* name)
{
	LinkedList* list = malloc(sizeof(*list));
	
	if(list == NULL)
		return NULL;

	list->first    = NULL;
	list->last     = NULL;
	list->size     = 0;
	list->itemSize = item;
	list->typeName = malloc(strlen(name));

	strcpy(list->typeName, name);

	return list;
}

bool linked_list_add_at(LinkedList* list, int index, void* element)
{
	if(list == NULL || element == NULL)
		return false;

	if(index < 0 || index > list->size)
		return false;

	Node* node = malloc(sizeof(*node));
	node->data = malloc(list->itemSize);
	memcpy(node->data, element, list->itemSize);

	if(list->size == 0)
	{
		list->first = node;
		list->last  = node;
		node->next  = NULL;
		node->prev  = NULL;
	}

	else if(index == 0)
	{
		node->next        = list->first;
		node->prev        = NULL;
		list->first->prev = node;
		list->first       = node;
	}

	else if(index == list->size)
	{
		node->prev       = list->last;
		node->next       = NULL;
		list->last->next = node;
		list->last       = node;	
	}

	else 
	{
		int i = 0;
		Node* temp = list->first;
		while(i < index)
		{
			temp = temp->next;
			i++;
		}

		node->next       = temp;
		node->prev       = temp->prev;
		temp->prev->next = node;
		temp->prev       = node;
	}

	list->size++;
	
	return true;
}

bool linked_list_add_first(LinkedList* list, void* element)
{
	if(list == NULL || element == NULL)
	{
		return false;
	}

	else 
	{
		return linked_list_add_at(list,0,element);
	}
}

bool linked_list_add_last(LinkedList* list, void* element)
{
	if(list == NULL || element == NULL)
	{
		return false;
	}

	else 
	{
		return linked_list_add_at(list, list->size, element);
	}

}

void* linked_list_get(LinkedList* list, int index)
{
	if(list == NULL)
		return NULL;

	if(index < 0 |index >= list->size)
		return NULL;

	if(index == 0)
	{
		return list->first->data;
	}	

	else if(index == list->size)
	{
		return list->last->data;
	}

	else
	{
		Node* temp = list->first;
	
		for(int i = 0; i < index; i++)
			temp = temp->next;

		return temp->data;	
	}
}

int linked_list_index_of(LinkedList* list, void* element)
{
	if(list == NULL || element == NULL)
		return -1;
	
	Node* temp = list->first;

	for(int i = 0; i < list->size; i++)
	{
		if(memcmp(temp->data, element, list->itemSize) == 0)
			return i;

		temp = temp->next;
	}

	return -1;
}

void* linked_list_remove(LinkedList* list, int index)
{
	if(list == NULL || index < 0 || index >= list->size)
		return NULL;

	void* element = malloc(list->itemSize);
	
	if(list->size == 1)
	{
		memcpy(element,list->first->data, list->itemSize);
		list->first = NULL;
		list->last  = NULL;

		list->size--;

		return element;
	}
	else if(index == 0)
	{
		memcpy(element, list->first->data, list->itemSize);
		
		list->first       = list->first->next;
		list->first->prev = NULL;

		list->size--;

		return element;
	}
	else if(index == list->size - 1)
	{
		memcpy(element, list->last->data, list->itemSize);
		
		list->last       = list->last->prev;
		list->last->next = NULL;
	
		list->size--;

		return element;
	}
	else
	{
		Node* temp = list->first;

		for(int i = 0; i < index; i++)
			temp = temp->next;

		memcpy(element, temp->data, list->itemSize);

		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;

		list->size--;
	
		return element;
	}
}

void* linked_list_remove_first(LinkedList* list)
{
	if(list == NULL)
	{
		return NULL;
	} else
	{
		return linked_list_remove(list, 0);
	}
}

void* linked_list_remove_last(LinkedList* list)
{
	if(list == NULL)
	{
		return NULL;
	} else 
	{
		return linked_list_remove(list, list->size - 1);
	}
}

int linked_list_size(LinkedList* list)
{
	if(list == NULL)
	{
		return -1;
	} else {
		return list->size;
	}
}

void linked_list_swap(LinkedList* list, int index1, int index2)
{
	if(list == NULL || index1 > list->size - 1 || index2 > list->size - 1)
		return;

	void* temp1 = linked_list_remove(list,index1);
	void* temp2 = linked_list_remove(list, index2 - 1);

	linked_list_add_at(list, index1, temp2);
	linked_list_add_at(list, index2, temp1);
}
