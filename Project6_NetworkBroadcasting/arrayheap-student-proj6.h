/* CSI 3334
 * Project 6 -- Network Broadcasting
 * Filename: arrayheap-student-proj6.h
 * Student name: Kirby Dyson
 *
 * This file implements the functions from the templated ArrayHeap class
 */

#ifndef PROJECT6_NETWORKBROADCASTING_ARRAYHEAP_STUDENT_PROJ6_H
#define PROJECT6_NETWORKBROADCASTING_ARRAYHEAP_STUDENT_PROJ6_H

#include "arrayheap-prof-proj6.h"
#include <algorithm>
#include <iostream>

using namespace std;

/* ArrayHeap
 *  parameters:
 *      none
 *  return value:
 *      none
 *
 *  This function is the default constructor for an empty ArrayHeap.
 */
template <typename T>
ArrayHeap<T>::ArrayHeap(){
    numItems = 0;
    capacity = 10;
    data = new T[capacity];
    heapAndFreeStack = new int[capacity];
    dataToHeap = new int[capacity];

    for(int i = 0; i < capacity; i++){
        heapAndFreeStack[i] = i;
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
template <typename T>
ArrayHeap<T>::ArrayHeap(ArrayHeap<T> const &h){
    numItems = h.numItems;
    capacity = h.capacity;

    delete []data;
    delete []heapAndFreeStack;
    delete []dataToHeap;

    data = new T[capacity];
    heapAndFreeStack = new int[capacity];
    dataToHeap = new int[capacity];

    for (int i = 0; i < capacity; i++) {
        heapAndFreeStack[i] = h.heapAndFreeStack[i];
        data[i] = h.data[i];
        dataToHeap[i] = h.dataToHeap[i];
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
template <typename T>
ArrayHeap<T>::~ArrayHeap(){
    delete []data;
    delete []heapAndFreeStack;
    delete []dataToHeap;

    data = nullptr;
    heapAndFreeStack = nullptr;
    dataToHeap = nullptr;
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
template <typename T>
ArrayHeap<T> const &ArrayHeap<T>::operator=(ArrayHeap<T> const &ah){
    if(this != &ah){
        numItems = ah.numItems;
        capacity = ah.capacity;

        delete []data;
        delete []heapAndFreeStack;
        delete []dataToHeap;

        data = new T[capacity];
        heapAndFreeStack = new int[capacity];

        for(int i = 0; i < capacity; i++){
            heapAndFreeStack[i] = ah.heapAndFreeStack[i];
            data[i] = ah.data[i];
            dataToHeap[i] = ah.dataToHeap[i];
        }
    }

    return *this;
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
template <typename T>
int ArrayHeap<T>::insert(T const &item){
    if(numItems == capacity){
        doubleCapacity();
    }

    int n = heapAndFreeStack[numItems];

    data[heapAndFreeStack[numItems]] = item;
    dataToHeap[heapAndFreeStack[numItems]] = numItems;
    bubbleUp(numItems);

    numItems++;
    return n;
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
template <typename T>
void ArrayHeap<T>::removeMinItem(){
    if(numItems == 0){
        return;
    }
    swap(dataToHeap[heapAndFreeStack[0]],
         dataToHeap[heapAndFreeStack[numItems - 1]]);
    swap(heapAndFreeStack[0], heapAndFreeStack[numItems - 1]);

    numItems--;

    bubbleDown(0);
}

/* getMinItem
 *  parameters:
 *      none
 *  return value:
 *      minimum item in the heap
 *
 *  This function returns the minimum item at the top of the heap.
 */
template <typename T>
T const &ArrayHeap<T>::getMinItem() const{
    return data[heapAndFreeStack[0]];
}

/* getNumItems
 *  parameters:
 *      none
 *  return value:
 *      number of items in the heap
 *
 *  This function returns the number of items that are on the heap.
 */
template <typename T>
int ArrayHeap<T>::getNumItems() const{
    return numItems;
}

/* isOnHeap
 *  parameters:
 *      key -- given key to check if on heap
 *  return value:
 *      true if key is on heap, false otherwise
 *
 *  This function checks to see if a given key is on the heap.
 */
template <typename T>
bool ArrayHeap<T>::isOnHeap(int key) const{
    if (key >= 0 && key < capacity) {
        if (dataToHeap[key] >= 0 && dataToHeap[key] < numItems) {
            if (heapAndFreeStack[dataToHeap[key]] == key) {
                return true;
            }
        }
    }
    return false;
}

/* changeItemAtKey
 *  parameters:
 *      key -- given index of item to replace
 *      newItem -- given item to replace the old item
 *  return value:
 *      none
 *
 *  This function takes a key and a new item, uses the new item
 *  to replace the old item at data[key], and performs bubble
 *  operations as necessary to maintain heap order.
 */
template <typename T>
void ArrayHeap<T>::changeItemAtKey(int key, T const &newItem){
    if(isOnHeap(key)){
        data[key] = newItem;

        bubbleUp(dataToHeap[key]);
        bubbleDown(dataToHeap[key]);
    }
    else{
        return;
    }
}

/* doubleCapacity
 *  parameters:
 *      none
 *  return value:
 *      none
 *
 *  This function doubles the capacity of the heap.
 */
template <typename T>
void ArrayHeap<T>::doubleCapacity(){
    capacity *= 2;

    T *temp = new T[capacity];
    int *tempHeap = new int[capacity];
    int *tempDataToHeap = new int[capacity];

    //init values of heap
    for(int i = 0; i < capacity; i++){
        tempHeap[i] = i;
        tempDataToHeap[i] = -1;
    }

    for(int i = 0; i < capacity / 2; i++){
        tempHeap[i] = heapAndFreeStack[i];
        temp[i] = data[i];
        tempDataToHeap[i] = dataToHeap[i];
    }

    delete []data;
    delete []heapAndFreeStack;
    delete []dataToHeap;

    data = temp;
    heapAndFreeStack = tempHeap;
    dataToHeap = tempDataToHeap;
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
template <typename T>
void ArrayHeap<T>::bubbleUp(int ndx){
    if(ndx == 0){
        return;
    }

    int parent = (ndx - 1) / 2;

    if( data[heapAndFreeStack[ndx]] < data[heapAndFreeStack[parent]]){
        swap(dataToHeap[heapAndFreeStack[ndx]],
             dataToHeap[heapAndFreeStack[parent]]);
        swap(heapAndFreeStack[ndx], heapAndFreeStack[parent]);

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
template <typename T>
void ArrayHeap<T>::bubbleDown(int ndx){
    int size = getNumItems();
    int left = 2 * ndx + 1;
    int right = 2 * ndx + 2;

    if(size <= left){
        return;
    }

    int min = ndx;

    if(left < size){
        int lesserChild = left;

        if((right < numItems) && (data[heapAndFreeStack[right]]
        < data[heapAndFreeStack[left]])){
            lesserChild = right;
        }

        if(data[heapAndFreeStack[lesserChild]] < data[heapAndFreeStack[ndx]]){
            swap(dataToHeap[heapAndFreeStack[ndx]],
                 dataToHeap[heapAndFreeStack[lesserChild]]);
            swap(heapAndFreeStack[ndx], heapAndFreeStack[lesserChild]);
            bubbleDown(lesserChild);
        }
    }
}

#endif //PROJECT6_NETWORKBROADCASTING_ARRAYHEAP_STUDENT_PROJ6_H
