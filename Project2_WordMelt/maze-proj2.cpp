/* CSI 3334
 * Project 2 -- Word Melt Shortest-Path Solver
 * Filename: maze-proj2.cpp
 * Student name: Kirby Dyson
 *
 * This file implements the functions from the Maze class.
 */

#include <cassert>
#include "maze-proj2.h"

/* Maze
 *  parameters:
 *      none
 *  return value:
 *      none
 *
 *  This function is the constructor for the Maze class and
 *  initializes all the data members that it can.
 */
Maze::Maze(void){
    this->validLocations = set<Location>();
}

/* getStartLocation
 *  parameters:
 *      none
 *  return value:
 *      the starting location of the Maze
 *
 *  This function returns the starting location of the maze.
 */
Location Maze::getStartLocation(void) const{
    return this->startLocation;
}

/* isValidLocation
 *  parameters:
 *      loc -- given location that will be checked for validity
 *  return value:
 *      true if the given location is in the valid list of locations,
 *      false otherwise
 *
 *  This function validates if the given location is in the Maze.
 */
bool Maze::isValidLocation(const Location &loc) const{
    return this->validLocations.find(loc) != this->validLocations.end();
}

/* isEndLocation
 *  parameters:
 *      loc -- given location that will be checked to see if it is the end
 *      location of the maze
 *  return value:
 *      true if the given location is the end location, false otherwise
 *
 *  This function validates if the given location is the end location of
 *  the maze.
 */
bool Maze::isEndLocation(const Location &loc) const{
    return loc == this->endLocation;
}

/* &operator>>
 *  parameters:
 *      is -- input stream the data will be read into
 *      m -- Maze object that will be populated with data read from input
 *  return value:
 *      an istream with all the valid locations in the Maze
 *
 *  This function provides a means of streaming in a Maze object.
 */
istream &operator>>(istream &is, Maze &m){
    m.validLocations.clear();

    int n;
    Location loc;

    is >> n;
    assert(n <= 20000);
    for(int i = 0; i < n; i++){
        is >> loc;
        m.validLocations.insert(loc);
    }
    is >> m.startLocation >> m.endLocation;

    return is;
}