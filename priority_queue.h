/*
 * This file provides the forward declarations for the priority_queue.c file.
 */

#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include "linked_list.h"

template<typename T, typename K> class PriorityQueue {

public:
    PriorityQueue();
    bool enqueue(T, K);
    T dequeue();
    T peek();
    int getSize();
    bool contains(T);
    void sort();

private:
	LinkedList<T>* list;
    LinkedList<K>* priorities;
};

template<typename T, typename K> PriorityQueue<T,K>::PriorityQueue() {
    this->list       = new LinkedList<T>();
    this->priorities = new LinkedList<K>();
}

template<typename T, typename K> bool PriorityQueue<T, K>::enqueue(T element, K priority)
{
    bool result = this->list->add_first(element);
    this->priorities->add_first(priority);
    sort();

    return result;
}

template<typename T, typename K> T PriorityQueue<T, K>::dequeue() {
    this->priorities->remove_last();
    return this->list->remove_last();
}

template<typename T, typename K> T PriorityQueue<T, K>::peek() {
    return this->list->getLast();
}

template<typename T, typename K> int PriorityQueue<T, K>::getSize() {
    return this->list->getSize();
}

template<typename T, typename K> bool PriorityQueue<T, K>::contains(T element) {
    return -1 != this->list->index_of(element);
}

template<typename T, typename K> void PriorityQueue<T, K>::sort() {
    int size = this->list->getSize();

    for(int i = 0; i < size; i++) {
        K outer = this->priorities->get(i);

        for(int j = i + 1; j < size; j++) {
            K inner     = this->priorities->get(j);

            // If the items need to be swapped, call the swap LinkedList function.
            if(inner > outer) {
                this->list->swap(i, j);
                this->priorities->swap(i,j);
            }
        }
    }
}



