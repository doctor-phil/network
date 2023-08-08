/*
 * This file implements the functions decalred in the 
 * linked_list.h header file - the behavior of a linked list data structure.
 */

#include "linked_list.h"

LinkedList::LinkedList(int item, char* name)
{
	this->first    = nullptr;
	this->last     = nullptr;
	this->size     = 0;
	this->itemSize = item;
	//this->typeName = (char*)malloc(strlen(name));

	strcpy(this->typeName, name);
}

bool linked_list_add_at(LinkedList* list, int index, void* element)
{
	if(list == NULL || element == NULL)
		return false;

	if(index < 0 || index > list->size)
		return false;

	Node* node = (Node*)malloc(sizeof(*node));
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

bool LinkedList::add_last(void* element)
{
	if(this == nullptr|| element == nullptr)
	{
		return false;
	}

	else 
	{
		return linked_list_add_at(this, this->size, element);
	}

}

void* LinkedList::get(int index)
{
	if(this == nullptr)
		return nullptr;

	if(index < 0 |index >= this->size)
		return nullptr;

	if(index == 0)
	{
		return this->first->data;
	}	

	else if(index == this->size)
	{
		return this->last->data;
	}

	else
	{
		Node* temp = this->first;
	
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

/*
 * The linked_list_remove function removes an element fron the linledlist struct
 * at a specific index. The data value stored at this index is returned to the caller.
 */
void* linked_list_remove(LinkedList* list, int index)
{
	// If the list is NULL or if the index is out of bounds, return immediately.
	if(list == NULL || index < 0 || index >= list->size)
		return NULL;

	// Allocate memory for the data value to be returned.
	void* element = malloc(list->itemSize);
	
	// If the list contains only 1 element.
	if(list->size == 1)
	{
		// Copy the data from first element, make first and last references NULL.
		memcpy(element,list->first->data, list->itemSize);
		list->first = NULL;
		list->last  = NULL;

		// Decrement the size of the list and return the element.
		list->size--;

		return element;
	}
	// Else if the list is greater than 1 element but the index is 0.
	else if(index == 0)
	{
		// Copy the data from first into the element variable.
		memcpy(element, list->first->data, list->itemSize);
		
		// Make first now point to the second element in the list.
		list->first       = list->first->next;
		list->first->prev = NULL;

		list->size--;

		return element;
	}
	// Else if the index is the last element in the list.
	else if(index == list->size - 1)
	{
		// Copy the data from last into the element.
		memcpy(element, list->last->data, list->itemSize);
		
		// Make the new last reference the second to last element.
		list->last       = list->last->prev;
		list->last->next = NULL;
	
		list->size--;

		return element;
	}
	// Else the element to remove is somewhere between the first and last element of the list.
	else
	{
		// Creating a local temporary Node reference to walk the list.
		Node* temp = list->first;

		// For each Node in the list less that the index, walk Node reference through the list.
		for(int i = 0; i < index; i++)
			temp = temp->next;

		// Copy the data value into the element variable.
		memcpy(element, temp->data, list->itemSize);

		// Adjust next and prev references to remove the temp node reference from the list.
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;

		list->size--;
	
		return element;
	}
}

/*
 * The linked_list_remove_first funciton removes the first elemnt of the linkedlist struct.
 */
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

/*
 * The linked_list_remove_last function removes the last element of the linkedlist struct.
 */
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

/*
 * the linked_list_size returns the size of the linked list struct.
 */
int LinkedList::getSize() {
    return this->size;
}

/*
 * The linked_list_swap function swaps the elements in two specific indexes within the linkedlist struct.
 */
void LinkedList::swap(int index1, int index2)
{
	// If the list variable is NULL, or if either index references are out of bounds, return immediately.
	if(this == nullptr || index1 > this->size - 1 || index2 > this->size - 1)
		return;

	void* temp1 = linked_list_remove(this,index1);
	void* temp2 = linked_list_remove(this, index2 - 1);

	linked_list_add_at(this, index1, temp2);
	linked_list_add_at(this, index2, temp1);
}

/*
 * This function returns a pointer to the first in the list structure.
 */
Node* LinkedList::getFirst() {
    return this->first;
}

/*
 * This function returns a pointer to the last node in the list structure.
 */
Node* LinkedList::getLast() {
    return this->last;
}

/*
 * Returns the byte size of the item being stored in the list.
 */
int LinkedList::getItemSize() {
    return this->itemSize;
}

/*
 * Returns the name of the type being stored in the list.
 */
char* LinkedList::getTypeName() {
    return this->typeName;
}
