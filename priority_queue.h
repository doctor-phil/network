/*
 * This file implementes a template Priority Queue data structure.
 * The types accepted include type T, the elements to be stored in
 * the structure and type K, the priority of the elements. 
 * 
 * Type K must implement the > operator, otherwise undfined 
 * behavior results.
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

private:
	LinkedList<T>* list;
    LinkedList<K>* priorities;

    void sort();
};

template<typename T, typename K> PriorityQueue<T,K>::PriorityQueue() {
    this->list       = new LinkedList<T>();
    this->priorities = new LinkedList<K>();
}

template<typename T, typename K> bool PriorityQueue<T, K>::enqueue(T element, K priority) {
    bool result = this->list->add_last(element);
    this->priorities->add_last(priority);
    sort();

    return result;
}

template<typename T, typename K> T PriorityQueue<T, K>::dequeue() {
    this->priorities->remove_first();
    return this->list->remove_first();
}

template<typename T, typename K> T PriorityQueue<T, K>::peek() {
    return this->list->getFirst();
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
            K inner = this->priorities->get(j);
            
            // If the items need to be swapped, call the swap LinkedList function.
            if(inner > outer) {
                this->list->swap(i, j);
                this->priorities->swap(i, j);
            }
        }
    }
}