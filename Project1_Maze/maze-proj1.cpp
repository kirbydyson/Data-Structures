/* CSI 3334
 * Project 1 -- Two-dimensional Maze Solver
 * Filename: maze-proj1.cpp
 * Student name: Kirby Dyson
 *
 * This file implements the functions from the Maze class.
 */

#include <iostream>
#include "maze-proj1.h"

using namespace std;

/* Maze
 *  parameters:
 *      none
 *  return value:
 *      none
 *
 *  This function is the constructor for the Maze class and initializes all
 *  the data members that it can.
 */
Maze::Maze(void){
    this->validLocationCount = 0;
    this->validLocations = nullptr;
}

/* ~Maze
 *  parameters:
 *      none
 *  return value:
 *      none
 *
 *  This function is the destructor for the Maze class and frees any
 *  memory that the object is using.
 */
Maze::~Maze(){
    delete[] this->validLocations;
}

/* getStartLocation
 *  parameters:
 *      none
 *  return value:
 *      the starting location for the maze
 *
 *  This function returns the starting location of the maze.
 */
Location Maze::getStartLocation(void) const{
    return this->startLocation;
}

/* isValidLocation
 *  parameters:
 *      loc -- given Location that will be checked for validity
 *  return value:
 *      True if the given Location is in the valid list of locations,
 *      otherwise false
 *
 *  This function validates if the given Location is in the maze.
 */
bool Maze::isValidLocation(const Location &loc) const{
    for(int i = 0; i < this->validLocationCount; i++){
        if(loc == this->validLocations[i]){
            return true;
        }
    }
    return false;
}

/* isEndLocation
 *  parameters:
 *      loc -- given location that will be checked to see if it is the end
 *      location of the maze
 *  return value:
 *      True if the given Location is the end of the maze, otherwise false
 *
 *  This function validates if the given location is the end location of the
 *  maze.
 */
bool Maze::isEndLocation(const Location &loc) const{
    return loc == this->endLocation;
}

/* &operator>>
 *  parameters:
 *      is -- input stream the data will be read into
 *      m -- Maze object that will be populated with data read from input
 *  return value:
 *      an istream with all the valid locations in the maze
 *
 *  This function provides a means of streaming in a Maze object.
 */
istream &operator>>(istream &is, Maze &m){
    delete[] m.validLocations;

    is >> m.validLocationCount;
    m.validLocations = new Location[m.validLocationCount];

    for(int i = 0; i < m.validLocationCount; i++){
        is >> m.validLocations[i];
    }
    is >> m.startLocation >> m.endLocation;

    return is;
}