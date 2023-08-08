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

int LinkedList::index_of(void* element)
{
	if(this == nullptr || element == nullptr)
		return -1;
	
	Node* temp = this->first;

	for(int i = 0; i < this->size; i++)
	{
		if(memcmp(temp->data, element, this->itemSize) == 0)
			return i;

		temp = temp->next;
	}

	return -1;
}

/*
 * The linked_list_remove function removes an element from the linkedlist struct
 * at a specific index. The data value stored at this index is returned to the caller.
 */
void* LinkedList::remove(int index)
{
	// If the list is NULL or if the index is out of bounds, return immediately.
	if(this == nullptr || index < 0 || index >= this->size)
		return nullptr;

	// Allocate memory for the data value to be returned.
	void* element = malloc(this->itemSize);
	
	// If the list contains only 1 element.
	if(this->size == 1)
	{
		// Copy the data from first element, make first and last references NULL.
		memcpy(element,this->first->data, this->itemSize);
		this->first = NULL;
		this->last  = NULL;

		// Decrement the size of the list and return the element.
		this->size--;

		return element;
	}
	// Else if the list is greater than 1 element but the index is 0.
	else if(index == 0)
	{
		// Copy the data from first into the element variable.
		memcpy(element, this->first->data, this->itemSize);
		
		// Make first now point to the second element in the list.
		this->first       = this->first->next;
		this->first->prev = NULL;

		this->size--;

		return element;
	}
	// Else if the index is the last element in the list.
	else if(index == this->size - 1)
	{
		// Copy the data from last into the element.
		memcpy(element, this->last->data, this->itemSize);
		
		// Make the new last reference the second to last element.
		this->last       = this->last->prev;
		this->last->next = NULL;
	
		this->size--;

		return element;
	}
	// Else the element to remove is somewhere between the first and last element of the list.
	else
	{
		// Creating a local temporary Node reference to walk the list.
		Node* temp = this->first;

		// For each Node in the list less that the index, walk Node reference through the list.
		for(int i = 0; i < index; i++)
			temp = temp->next;

		// Copy the data value into the element variable.
		memcpy(element, temp->data, this->itemSize);

		// Adjust next and prev references to remove the temp node reference from the list.
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;

		this->size--;
	
		return element;
	}
}

/*
 * The linked_list_remove_first function removes the first element of the Linkedlist struct.
 */
void* LinkedList::remove_first()
{
	if(this == nullptr)
	{
		return nullptr;
	} else
	{
		return this->remove(0);
	}
}

/*
 * The linked_list_remove_last function removes the last element of the linkedlist struct.
 */
void* LinkedList::remove_last()
{
	if(this == nullptr)
	{
		return nullptr;
	} else 
	{
		return this->remove(this->size - 1);
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
