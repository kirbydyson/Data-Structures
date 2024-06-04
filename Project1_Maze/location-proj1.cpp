/* CSI 3334
 * Project 1 -- Two-dimensional Maze Solver
 * Filename: location-proj1.cpp
 * Student name: Kirby Dyson
 *
 * This file implements the functions from the Location class.
 */

#include <iostream>
#include "location-proj1.h"

using namespace std;

/* Location
 *  parameters:
 *      none
 *  return value:
 *      none
 *
 *  This function is the constructor for the Location class so all data members
 *  are set to their default value.
 */
Location::Location() {
    this->row = 0;
    this->col = 0;
    this->nextDirection = RIGHT;
}

/* iterationBegin
 *  parameters:
 *      none
 *  return value:
 *      none
 *
 *  This function initializes the iteration capability of a Location object.
 */
void Location::iterationBegin(){
    this->nextDirection = RIGHT;
}

/* iterationCurrent
 *  parameters:
 *      none
 *  return value:
 *      Location of the neighboring location object
 *
 *  This function creates a copy of the current Location object and modifies
 *  the copy so that it represents a different location, returning the neighbor
 *  it created.
 */
Location Location::iterationCurrent() const{
    Location neighbor;

    neighbor.row = this->row;
    neighbor.col = this->col;

    if(nextDirection == RIGHT){
        neighbor.col++;
    }
    else if(nextDirection == DOWN){
        neighbor.row++;
    }
    else if(nextDirection == LEFT){
        neighbor.col--;
    }
    else if(nextDirection == UP){
        neighbor.row--;
    }

    return neighbor;
}

/* iterationAdvance
 *  parameters:
 *      none
 *  return value:
 *      none
 *
 *  This function moves the iteration forward so that a different neighbor
 *  is returned the next time iterationCurrent() is called.
 */
void Location::iterationAdvance(){
    this->nextDirection++;

}

/* iterationDone
 *  parameters:
 *      none
 *  return value:
 *      True when all neighbors of a Location have been iterated over,
 *      otherwise false
 *
 *  This function checks to see if all iterations have been completed.
 */
bool Location::iterationDone() const{
    return this->nextDirection == DONE;
}

/* operator==
 *  parameters:
 *      loc -- given Location that will be checked for equality
 *  return value:
 *      True if the Location objects are equal, otherwise false
 *
 *  This function checks to see if two Location objects represent the same row
 *  and column (are equal).
 */
bool Location::operator==(const Location &loc) const{
    return this->row == loc.row && this->col == loc.col;
}

/* &operator<<
 *  parameters:
 *      os -- output stream the data will be sent to
 *      loc -- given Location that will be output
 *  return value:
 *      an ostream with the location of the Location object
 *
 *  This function provides a means of streaming a Location out.
 */
ostream &operator<<(ostream &os, const Location &loc){
    os << loc.row << ' ' << loc.col;
    return os;
}

/* &operator>>
 *  parameters:
 *      is -- input stream the data will read into
 *      loc -- given Location that will be read from the stream
 *  return value:
 *      an istream with the location of the Location object
 *
 *  This function proves a means of streaming a Location in.
 */
istream &operator>>(istream &is, Location &loc){
    is >> loc.row >> loc.col;
    return is;
}
