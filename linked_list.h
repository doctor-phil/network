/*
 * This is a linked list data structure implementation. 
 */

#pragma once
#include <stdbool.h>
#include <string>
#include <stdlib.h>

template<typename T> class LinkedList {

    class Node {
    public:

        Node() {
            this->next = nullptr;
            this->prev = nullptr;
        }

        T data;
        Node* next;
        Node* prev;
    };

public:
    LinkedList();
    bool add_at(int index, T element);
    bool add_first(T element);
    bool add_last(T element);
    int index_of(T element);
    T get(int index);
    T remove(int index);
    T remove_first();
    T remove_last();
    void swap(int index1, int index2);
    T getFirst();
    T getLast();
    int getSize();

private:
    Node* first;
    Node* last;
    int   size;
    int   itemSize;

};

template<typename T> LinkedList<T>::LinkedList() {
    this->first    = nullptr;
    this->last     = nullptr;
    this->size     = 0;
}

template<typename T> bool LinkedList<T>::add_at(int index, T element){

    if(index < 0)
        return false;

    if(index > this->size)
        return add_last(element);

    Node *node = new Node();
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

template<typename T> bool LinkedList<T>::add_first(T element){
    return add_at(0,element);
}

template<typename T> bool LinkedList<T>::add_last(T element){
    return add_at(this->size, element);
}

template<typename T> T LinkedList<T>::get(int index){

    if (index == 0) {
        return this->first->data;

    } else if (index == this->size) {
        return this->last->data;

    } else {
        Node *temp = this->first;

        for (int i = 0; i < index; i++)
            temp = temp->next;

        return temp->data;
    }
}

/*
* Returns the index of the first occurrence of the element parameter. If the element
* is not found, or if the element is a nullptr, then -1 is returned.
*/
template<typename T> int LinkedList<T>::index_of(T element){

    Node* temp = this->first;

    for(int i = 0; i < this->size; i++)	{
        //	if(memcmp((temp->data), element, this->itemSize) == 0)
        if(temp->data == element)
            return i;

        temp = temp->next;
    }

    return -1;
}

template<typename T> T LinkedList<T>::remove(int index){

    // If the list contains only 1 element.
    if(this->size == 1)	{
        // Copy the data from first element, make first and last references NULL.
        T element = this->first->data;
        this->first = nullptr;
        this->last  = nullptr;

        // Decrement the size of the list and return the element.
        this->size--;
        return element;
    }
        // Else if the list is greater than 1 element but the index is 0.
    else if(index == 0)	{
        // Copy the data from first into the element variable.
        T element = this->first->data;

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
        T element = this->last->data;

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

        T element = temp->data;

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
template<typename T> T LinkedList<T>::remove_first() {
    return this->remove(0);
}

/*
* The remove_last function removes the last element of the Linkedlist struct.
*/
template<typename T> T LinkedList<T>::remove_last(){
    return this->remove(this->size - 1);
}

/*
* The swap function swaps the elements in two specific indexes within the Linkedlist.
*/
template< typename T> void LinkedList<T>::swap(int index1, int index2){
    // If the list variable is nullptr, or if either indices are out of bounds, return immediately.
    if(index1 >= this->size || index2 >= this->size)
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
template<typename T> T LinkedList<T>::getFirst() {
    return this->first->data;
}

/*
* This function returns a pointer to the last node in the list structure.
*/
template< typename T> T LinkedList<T>::getLast() {
    return this->last->data;
}

template<typename T> int LinkedList<T>::getSize() {
    return this->size;
}

template class LinkedList<int>;
template class LinkedList<char>;
template class LinkedList<bool>;
template class LinkedList<std::string>;
template class LinkedList<float>;
template class LinkedList<double>;
