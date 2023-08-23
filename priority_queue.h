/*
 * This file provides the forward declarations for the priority_queue.c file.
 */

#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include "linked_list.h"

template<typename T> class PriorityQueue {

public:
    PriorityQueue();
    void setCompare(int (*)(void*, void*));
    bool enqueue(T);
    T dequeue();
    T peek();
    int getSize();
    bool contains(T);
    void sort();

private:
	LinkedList<T>* list;
	int(*compare)(void*, void*);
};

template<typename T> PriorityQueue<T>::PriorityQueue() {
    this->list    = new LinkedList<T>();
}

template<typename T> void PriorityQueue<T>::setCompare(int (*compareFunction)(void*,void*)) {
    this->compare = compareFunction;
}

template<typename T> bool PriorityQueue<T>::enqueue(T element)
{
    bool result = this->list->add_first(element);
    sort();

    return result;
}

template<typename T> T PriorityQueue<T>::dequeue() {
    return this->list->remove_last();
}

template< typename T> T PriorityQueue<T>::peek() {
    int end = this->list->getSize() - 1;
    return this->list->get(end);
}

template<typename T> int PriorityQueue<T>::getSize() {
    return this->list->getSize();
}

template<typename T> bool PriorityQueue<T>::contains(T element) {
    return -1 != this->list->index_of(element);
}

template<typename T> void PriorityQueue<T>::sort() {
    int size = this->list->getSize();

    for(int i = 0; i < size; i++) {
        T outer = this->list->get(i);

        for(int j = i + 1; j < size; j++) {
            void* inner     = this->list->get(j);
            int directional = this->compare(outer, inner);

            // If the items need to be swapped, call the swap LinkedList function.
            if(directional < 0) {
                this->list->swap(i, j);
            }
        }
    }
}



