/*
 * This file implements the functions declared in the
 * linked_list.h header file - the behavior of a linked list data structure.
 */
/*
#include "linked_list.h"
#include <string>


template<typename T> LinkedList<T>::LinkedList(int item) {
	this->first    = nullptr;
	this->last     = nullptr;
	this->size     = 0;
	//this->itemSize = item;
}

/*
 * Adds the element parameter at the given index parameter to the list. True is returned
 * if the element was successfully added to the list at the index.
 */
/*
template<typename T> bool LinkedList<T>::add_at(int index, T element) {

	if(index < 0)
		return false;

    if(index > this->size)
        return add_last(element);

//	Node* node = (Node*)malloc(sizeof(*node));
//	node->data = malloc(this->itemSize);
    Node* node = new Node();

//	memcpy(node->data, element, this->itemSize);
    node->data = element;

	if(this->size == 0)	{
		this->first = node;
		this->last  = node;
		node->next  = nullptr;
		node->prev  = nullptr;

	} else if(index == 0)	{
		node->next        = this->first;
		node->prev        = nullptr;
		this->first->prev = node;
		this->first       = node;

	} else if(index == this->size) {
		node->prev       = this->last;
		node->next       = nullptr;
		this->last->next = node;
		this->last       = node;

	} else {
		int i = 0;
		Node* temp = this->first;
		while(i < index) {
			temp = temp->next;
			i++;
		}

		node->next       = temp;
		node->prev       = temp->prev;
		temp->prev->next = node;
		temp->prev       = node;
	}

	this->size++;
	return true;
}

/*
 * Adds the element parameter to be the first item in the list.
 */
/*
template<typename T> bool LinkedList<T>::add_first(T element) {
		return add_at(0,element);
}

/*
 * Adds the element parameter to the list such that it is the last item.
 */
/*
template<typename T> bool LinkedList<T>::add_last(T element) {
		return add_at(this->size, element);
}

/*
 * Returns the value stored at the index parameter. If the index is out of bounds
 * then nullptr is returned.
 */
/*
template<typename T> T LinkedList<T>::get(int index) {

	if(index < 0 |index >= this->size)
		return NULL;

	if(index == 0) {
		return this->first->data;

	} else if(index == this->size) {
		return this->last->data;

	} else {
		Node* temp = this->first;
	
		for(int i = 0; i < index; i++)
			temp = temp->next;

		return temp->data;	
	}
}

/*
 * Returns the index of the first occurrence of the element parameter. If the element
 * is not found, or if the element is a nullptr, then -1 is returned.
 */
/*
template<typename T> int LinkedList<T>::index_of(T element) {
	
	Node* temp = this->first;

	for(int i = 0; i < this->size; i++)	{
	//	if(memcmp((temp->data), element, this->itemSize) == 0)
        if(temp->data == element)
			return i;

		temp = temp->next;
	}

	return -1;
}

/*
 * The linked_list_remove function removes an element from the Linkedlist struct
 * at a specific index. The data value stored at this index is returned to the caller.
 */
/*
template<typename T> T LinkedList<T>::remove(int index){

	// If the list is NULL or if the index is out of bounds, return immediately.
	if(index < 0 || index >= this->size)
		return NULL;

	// Allocate memory for the data value to be returned.
	//void* element = malloc(this->itemSize);
    T element = NULL;
	
	// If the list contains only 1 element.
	if(this->size == 1)	{
		// Copy the data from first element, make first and last references NULL.
		//memcpy(static_cast<void *>(element),this->first->data, this->itemSize);
        element = this->first->data;
		this->first = nullptr;
		this->last  = nullptr;

		// Decrement the size of the list and return the element.
		this->size--;
		return element;
	}
	// Else if the list is greater than 1 element but the index is 0.
	else if(index == 0)	{
		// Copy the data from first into the element variable.
	//	memcpy(static_cast<void *>(element), this->first->data, this->itemSize);
        element = this->first->data;
		
		// Make first now point to the second element in the list.
		this->first       = this->first->next;
		this->first->prev = nullptr;

		this->size--;
		return element;
	}
	// Else if the index is the last element in the list.
	else if(index == this->size - 1) {
		// Copy the data from last into the element.
		//memcpy(element, this->last->data, this->itemSize);
		element = this->last->data;

		// Make the new last reference the second to last element.
		this->last       = this->last->prev;
		this->last->next = nullptr;
	
		this->size--;

		return element;
	}
	// Else the element to remove is somewhere between the first and last element of the list.
	else {
		// Creating a local temporary Node reference to walk the list.
		Node* temp = this->first;

		// For each Node in the list less that the index, walk Node reference through the list.
		for(int i = 0; i < index; i++)
			temp = temp->next;

		// Copy the data value into the element variable.
		//memcpy(element, temp->data, this->itemSize);

        element = temp->data;

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
/*
template<typename T> T LinkedList<T>::remove_first() {
    return this->remove(0);
}

/*
 * The remove_last function removes the last element of the linkedlist struct.
 */
/*
template<typename T> T LinkedList<T>::remove_last() {
    return this->remove(this->size - 1);
}

/*
 * The getSize returns the size of the linked list struct.
 */
/*
template<typename T> int LinkedList<T>::getSize() {
    return this->size;
}

/*
 * The swap function swaps the elements in two specific indexes within the Linkedlist.
 */
/*
template<typename T> void LinkedList<T>::swap(int index1, int index2) {
	// If either indices are out of bounds, return immediately.
	if( index1 >= this->size || index2 >= this->size)
		return;

    if(index1 < 0 || index2 < 0)
        return;

	T temp1 = this->get(index1);
	T temp2 = this->get(index2);

    if(index1 > index2){
        this->remove(index1);
        this->remove(index2);
        this->add_at(index2, temp1);
        this->add_at(index1, temp2);
    } else {
        this->remove(index2);
        this->remove(index1);
        this->add_at(index1, temp2);
        this->add_at(index2, temp1);
    }
}

/*
 * This function returns a pointer to the first in the list structure.
 */
/*
template<typename T> T LinkedList<T>::getFirst() {
    return this->first->data;
}

/*
 * This function returns a pointer to the last node in the list structure.
 */
/*
template<typename T> T LinkedList<T>::getLast() {
    return this->last->data;
}

/*
 * Returns the byte size of the item being stored in the list.
 */
/*
template<typename T> int LinkedList<T>::getItemSize() {
    return this->itemSize;
}

template class LinkedList<int>;
template class LinkedList<char>;
template class LinkedList<bool>;
template class LinkedList<std::string>;
template class LinkedList<float>;
template class LinkedList<double>;
*/