/* CSI 3334
 * Project 1 -- Two-dimensional Maze Solver
 * Filename: stack-proj1.cpp
 * Student name: Kirby Dyson
 *
 * This file implements the functions from the Stack class.
 */

#include <iostream>
#include <cassert>
#include "stack-proj1.h"

using namespace std;

/* LocationStack
 *  parameters:
 *      none
 *  return value:
 *      none
 *
 *  This function is the constructor for the LocationStack class and
 *  initializes all the data members that it can.
 */
LocationStack::LocationStack(void){
    this->top = nullptr;
}

/* ~LocationStack
 *  parameters:
 *      none
 *  return value:
 *      none
 *
 *  This function is the destructor for the LocationStack class and frees
 *  any memory that the object uses.
 */
LocationStack::~LocationStack(){
    delete this->top;
}

/* push
 *  parameters:
 *      loc -- given location to push onto the stack
 *  return value:
 *      none
 *
 *  This function pushes a location onto the LocationStack.
 */
void LocationStack::push(const Location &loc){
    this->top = new LocationStackNode(loc, this->top);
}

/* pop
 *  parameters:
 *      none
 *  return value:
 *      none
 *
 *  This function removes a location from the LocationStack.
 */
void LocationStack::pop(void){
    assert(!isEmpty());

    LocationStackNode *temp = this->top;
    this->top = this->top->getNextNode();
    temp->setNextNode(nullptr);
    delete temp;
}

/* getTop
 *  parameters:
 *      none
 *  return value:
 *      location from the top of the stack
 *
 *  This function returns the location from the top of the LocationStack.
 */
const Location &LocationStack::getTop(void) const{
    assert(!isEmpty());

    return this->top->getLocation();
}

/* isEmpty
 *  parameters:
 *      none
 *  return value:
 *      True if the stack is empty, false otherwise
 *
 *  This function validates if the LocationStack is empty or not.
 */
bool LocationStack::isEmpty(void) const{
    return this->top == nullptr;
}

/* isOn
 *  parameters:
 *      loc -- given location that will be checked if it is on the stack
 *  return value:
 *      True if the given location is on the stack, false otherwise
 *
 *  This function validates if the given location is on the LocationStack.
 */
bool LocationStack::isOn(const Location &loc) const{
    LocationStackNode *temp = this->top;
    while(temp != nullptr){
        if(loc == temp->getLocation()){
            return true;
        }
        temp = temp->getNextNode();
    }
    return false;
}

/* &operator<<
 *  parameters:
 *      os -- the output stream that the data will be sent to
 *      s -- locations from the stack that will be output
 *  return value:
 *      an ostream with all the locations in the maze
 *
 *  This function streams out the stack from bottom to top.
 */
ostream &operator<<(ostream &os, const LocationStack &s){
    LocationStackNode *curr = s.top;
    LocationStackNode *prev = nullptr;
    LocationStackNode *next = nullptr;

    while(curr != nullptr){
        next = curr->getNextNode();
        curr->setNextNode(prev);
        prev = curr;
        curr = next;
    }
    curr = prev;
    prev = nullptr;

    while(curr != nullptr){
        os << curr->getLocation() << endl;
        next = curr->getNextNode();
        curr->setNextNode(prev);
        prev = curr;
        curr = next;
    }

    return os;
}

/* LocationStackNode
 *  parameters:
 *      loc -- given location to set the location member to
 *      next - pointer to the next node in the stack
 *  return value:
 *      none
 *
 *  This function is the constructor for the LocationStackNode class and
 *  initializes all the data members that it can.
 */
LocationStackNode::LocationStackNode(const Location &loc, LocationStackNode *next){
    this->location = loc;
    this->nextNode = next;
}

/* ~LocationStackNode
 *  parameters:
 *      none
 *  return value:
 *      none
 *
 *  This function is the destructor for the LocationStackNode class and frees any memory
 *  that the object uses.
 */
LocationStackNode::~LocationStackNode(){
    delete this->nextNode;
}

/* getLocation
 *  parameters:
 *      none
 *  return value:
 *      location on the stack
 *
 *  This function returns a location from the LocationStackNode.
 */
const Location &LocationStackNode::getLocation() const{
    return this->location;
}

/* getNextNode
 *  parameters:
 *      none
 *  return value:
 *      next node on the stack
 *
 *  This function returns the next node on the LocationStackNode.
 */
LocationStackNode *LocationStackNode::getNextNode() const{
    return this->nextNode;
}

/* Maze
 *  parameters:
 *      next -- pointer to what will be the next node
 *  return value:
 *      none
 *
 *  This function sets the next node on the LocationStackNode.
 */
void LocationStackNode::setNextNode(LocationStackNode *next){
    this->nextNode = next;
}