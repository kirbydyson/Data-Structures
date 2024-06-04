/* CSI 3334
 * Project 2 -- Word Melt Shortest-Path Solver
 * Filename: arrayqueue-student-proj2.h
 * Student name: Kirby Dyson
 *
 * This file implements the functions from the templated ArrayQueue class.
 */

#ifndef PROJECT2_WORDMELT_ARRAYQUEUE_STUDENT_PROJ2_H
#define PROJECT2_WORDMELT_ARRAYQUEUE_STUDENT_PROJ2_H

#include "arrayqueue-prof-proj2.h"
#include <cassert>

/* ArrayQueue
 *  parameters:
 *      none
 *  return value:
 *      none
 *
 *  This function is the default constructor for the ArrayQueue class and
 *  initializes all the data members that it can.
 */
template <class Base>
ArrayQueue<Base>::ArrayQueue(){
    this->length = 0;
    this->capacity = 5;
    this->front = 0;
    this->data = new Base[this->capacity];
}

/* ArrayQueue
 *  parameters:
 *      q -- data to be copied
 *  return value:
 *      none
 *
 *  This function is the copy constructor for the ArrayQueue class and
 *  creates a deep copy of the given ArrayQueue object.
 */
template <class Base>
ArrayQueue<Base>::ArrayQueue(const ArrayQueue<Base> &q){
    this->length = q.length;
    this->capacity = q.capacity;
    this->front = 0;
    this->data = new Base[this->capacity];

    for(int i = 0; i < this->length; i++){
        this->data[i] = q.data[(q.front + i) % this->capacity];
    }
}

/* ~ArrayQueue
 *  parameters:
 *      none
 *  return value:
 *      none
 *
 *  This function is the destructor and cleans up any memory that the
 *  ArrayQueue has dynamically allocated.
 */
template <class Base>
ArrayQueue<Base>::~ArrayQueue(){
    delete[] this->data;
    this->length = 0;
    this->capacity = 0;
    this->front = 0;
}

/* add
 *  parameters:
 *      item -- given element to add to the queue
 *  return value:
 *      none
 *
 *  This function adds an element to the back of the queue.
 */
template <class Base>
void ArrayQueue<Base>::add(const Base &item){
    if(this->length >= this->capacity){
        this->doubleCapacity();
    }
    this->data[(this->front + this->length) % this->capacity] = item;
    this->length++;
}

/* remove
 *  parameters:
 *      none
 *  return value:
 *      none
 *
 *  This function removes one item from the front of the queue.
 */
template <class Base>
void ArrayQueue<Base>::remove(){
    this->length--;
    this->front = (this->front + 1) % this->capacity;
}

/* ArrayQueue
 *  parameters:
 *      none
 *  return value:
 *      item at the front of the queue
 *
 *  This function returns the item at the front of the queue.
 */
template <class Base>
const Base &ArrayQueue<Base>::getFront() const{
    return this->data[this->front];
}

/* ArrayQueue
 *  parameters:
 *      none
 *  return value:
 *      length of the queue
 *
 *  This function returns the length of the queue
 */
template <class Base>
int ArrayQueue<Base>::getLength() const{
    return this->length;
}

/* &ArrayQueue
 *  parameters:
 *      q -- given array to set equal
 *  return value:
 *      deep copy of the given queue
 *
 *  This function first checks to see if the queue we are assigning to is
 *  the same as this, and if not, makes a deep copy of the given queue.
 */
template <class Base>
const ArrayQueue<Base> &ArrayQueue<Base>::operator=(const ArrayQueue<Base> &q){
    if(this != &q){
        delete[] this->data;
        this->length = q.length;
        this->capacity = q.capacity;
        this->front = 0;
        this->data = new Base[this->capacity];

        for(int i = 0; i < this->length; i++){
            this->data[i] = q.data[(q.front + i) % this->capacity];
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
 *  This function doubles the capacity of the ArrayQueue, and updates
 *  the data members for the newly allocated array.
 */
template <class Base>
void ArrayQueue<Base>::doubleCapacity(){
    Base *temp = this->data;
    this->capacity *= 2;
    this->data = new Base[this->capacity];

    for(int i = 0; i < this->length; i++){
        this->data[i] = temp[(this->front + i) % this->length];
    }
    delete[] temp;
    this->front = 0;
}

#endif //PROJECT2_WORDMELT_ARRAYQUEUE_STUDENT_PROJ2_H
