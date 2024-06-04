/* CSI 3334
 * Project 5 -- Real-Time Batch Operating System Simulator
 * Filename: arrayheap-student-proj5.h
 * Student name: Kirby Dyson
 *
 * This file implements the functions from the templated ArrayHeap class
 */

#ifndef PROJECT5_OS_ARRAYHEAP_STUDENT_PROJ5_H
#define PROJECT5_OS_ARRAYHEAP_STUDENT_PROJ5_H

#include "arrayheap-prof-proj5.h"
#include <algorithm>

using namespace std;

/* ArrayHeap
 *  parameters:
 *      none
 *  return value:
 *      none
 *
 *  This function is the default constructor for an empty ArrayHeap.
 */
template <class T>
ArrayHeap<T>::ArrayHeap(){
    this->numItems = 0;
    this->capacity = 5;
    this->data = new T[this->capacity];
    this->heapAndFreeStack = new int[this->capacity];

    for(int i = 0; i < this->capacity; i++){
        this->heapAndFreeStack[i] = i;
    }
}

/* ArrayHeap
 *  parameters:
 *      h -- given ArrayHeap to copy
 *  return value:
 *      none
 *
 *  This function is the copy constructor.
 */
template <class T>
ArrayHeap<T>::ArrayHeap(ArrayHeap<T> const &h){
    this->numItems = h.numItems;
    this->capacity = h.capacity;
    this->data = new T[this->capacity];
    this->heapAndFreeStack = new int[this->capacity];

    for(int i = 0; i < this->capacity; i++){
        this->data[i] = h.data[i];
        this->heapAndFreeStack[i] = h.heapAndFreeStack[i];
    }
}

/* ~ArrayHeap
 *  parameters:
 *      none
 *  return value:
 *      none
 *
 *  This function is the destructor.
 */
template <class T>
ArrayHeap<T>::~ArrayHeap(){
    delete[] this->data;
    delete[] this->heapAndFreeStack;
}

/* getMinItem
 *  parameters:
 *      none
 *  return value:
 *      minimum item in the heap
 *
 *  This function returns the minimum item at the top of the heap.
 */
template <class T>
T const &ArrayHeap<T>::getMinItem() const{
    return this->data[this->heapAndFreeStack[0]];
}

/* getNumItems
 *  parameters:
 *      none
 *  return value:
 *      number of items in the heap
 *
 *  This function returns the number of items that are on the heap.
 */
template <class T>
int ArrayHeap<T>::getNumItems() const{
    return this->numItems;
}

/* bubbleUp
 *  parameters:
 *      ndx -- given index to start at
 *  return value:
 *      none
 *
 *  This function starts at the item given by ndx, and moves it up
 *  the heap towards the root to preserve the heap order property.
 */
template <class T>
void ArrayHeap<T>::bubbleUp(int ndx){
    if(ndx <= 0){
        return;
    }

    int parent = (ndx - 1) / 2;
    if(this->data[this->heapAndFreeStack[ndx]] <
    this->data[this->heapAndFreeStack[parent]]){
        swap(this->heapAndFreeStack[ndx], this->heapAndFreeStack[parent]);
        bubbleUp(parent);
    }
}

/* bubbleDown
 *  parameters:
 *      ndx -- given index to start at
 *  return value:
 *      none
 *
 *  This function starts at the item given by ndx, and moves it down
 *  the heap towards the leaves to preserve the heap order property.
 */
template <class T>
void ArrayHeap<T>::bubbleDown(int ndx){
    int child1 = 2 * ndx + 1;
    int child2 = 2 * ndx + 2;

    if(child1 < this->numItems){
        int lesserChild = child1;
        if((child2 < this->numItems) and
        (this->data[this->heapAndFreeStack[child2]] <
        this->data[this->heapAndFreeStack[child1]])){
            lesserChild = child2;
        }

        if(this->data[this->heapAndFreeStack[lesserChild]] <
        this->data[this->heapAndFreeStack[ndx]]){
            swap(this->heapAndFreeStack[lesserChild],
                 this->heapAndFreeStack[ndx]);
            bubbleDown(lesserChild);
        }
    }
}

/* insert
 *  parameters:
 *      item -- given item to insert
 *  return value:
 *      none
 *
 *  This function inserts the given item into the heap (at the bottom)
 *  and then restores the heap order property by bubbling up.
 */
template <class T>
void ArrayHeap<T>::insert(T const &item){
    if(this->capacity == this->numItems){
        this->doubleCapacity();
    }

    this->data[this->heapAndFreeStack[this->numItems]] = item;
    this->bubbleUp(this->numItems);
    this->numItems++;
}

/* removeMinItem
 *  parameters:
 *      none
 *  return value:
 *      none
 *
 *  This function removes the minimum item at the root of the heap,
 *  places the last element in the root's position, and bubbles down.
 */
template <class T>
void ArrayHeap<T>::removeMinItem(){
    this->numItems--;
    swap(this->heapAndFreeStack[0], this->heapAndFreeStack[this->numItems]);
    this->bubbleDown(0);
}

/* operator=
 *  parameters:
 *      ah -- given heap to copy
 *  return value:
 *      none
 *
 *  This function makes this object have the same logical structure
 *  as the given heap, resizing as necessary.
 */
template <class T>
ArrayHeap<T> const &ArrayHeap<T>::operator=(ArrayHeap<T> const &ah){
    if(this != &ah){
        delete[] this->data;
        delete[] this->heapAndFreeStack;

        this->numItems = ah.numItems;
        this->capacity = ah.capacity;
        this->data = new T[this->capacity];
        this->heapAndFreeStack = new int[this->capacity];

        for(int i = 0; i < this->capacity; i++){
            this->data[i] = ah.data[i];
            this->heapAndFreeStack[i] = ah.heapAndFreeStack[i];
        }
    }
    return *this;
}

/* doubleCapacity
 *  parameters:
 *      none
 *  return value:
 *      none
 *
 *  This function doubles the capacity of the heap.
 */
template <class T>
void ArrayHeap<T>::doubleCapacity(){
    int tempCapacity = this->capacity;
    this->capacity *= 2;
    T *dataTemp = new T[this->capacity];
    int *heapTemp = new int[this->capacity];

    for(int i = 0; i < tempCapacity; i++){
        dataTemp[i] = this->data[i];
        heapTemp[i] = this->heapAndFreeStack[i];
    }

    for(int i = tempCapacity; i < this->capacity; i++){
        heapTemp[i] = i;
    }

    delete[] this->data;
    delete[] this->heapAndFreeStack;
    this->data = dataTemp;
    this->heapAndFreeStack = heapTemp;

}

#endif //PROJECT5_OS_ARRAYHEAP_STUDENT_PROJ5_H