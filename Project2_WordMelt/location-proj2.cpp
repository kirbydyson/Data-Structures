/* CSI 3334
 * Project 2 -- Word Melt Shortest-Path Solver
 * Filename: location-proj2.cpp
 * Student name: Kirby Dyson
 *
 * This file implements the functions from the Location class.
 */

#include "location-proj2.h"

/* Location
 *  parameters:
 *      none
 *  return value:
 *      none
 *
 *  This function is the constructor for the Location class and
 *  initializes all the data members that it can.
 */
Location::Location(){
    this->iterationMode = CHANGE_LETTER;
    this->indexToChange = 0;
    this->nextLetter = 'a';
    this->word = " ";
}

/* iterationBegin
 *  parameters:
 *      none
 *  return value:
 *      none
 *
 *  This function initializes the iteration capability of a Location object.
 */
void Location::iterationBegin(void){
    this->iterationMode = CHANGE_LETTER;
    this->indexToChange = 0;
    this->nextLetter = 'a';
    if(this->word[0] == 'a'){
        this->nextLetter++;
    }
}

/* iterationCurrent
 *  parameters:
 *      none
 *  return value:
 *      location of the neighboring location object
 *
 *  This function creates a copy of the current Location object and modifies
 *  the copy so that it represents a different word, returning the neighbor
 *  it created.
 */
Location Location::iterationCurrent(void) const{
    Location neighbor;
    neighbor.word = this->word;

    switch(iterationMode){
        case CHANGE_LETTER:
            neighbor.word[this->indexToChange] = this->nextLetter;
            break;
        case INSERT_LETTER:
            neighbor.word.insert(this->indexToChange, 1, this->nextLetter);
            break;
        case DELETE_LETTER:
            neighbor.word.erase(this->indexToChange, 1);
            break;
        default:
            break;
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
void Location::iterationAdvance(void){
    switch(iterationMode){
        case INSERT_LETTER:
            if(this->nextLetter != 'z'){
                this->nextLetter++;
            }
            else if(this->word.length() >= this->indexToChange){
                this->nextLetter = 'a';
                this->indexToChange++;
            }
            if(this->indexToChange > this->word.size()){
                this->iterationMode++;
                this->indexToChange = 0;
                this->nextLetter = 'a';
            }
            break;
        case DELETE_LETTER:
            this->indexToChange++;
            if(this->word.size() <= this->indexToChange){
                this->iterationMode++;
                this->indexToChange = 0;
            }
            break;
        default:
            if(this->nextLetter != 'z'){
                this->nextLetter++;
            }
            else if(this->word.length() > this->indexToChange) {
                this->nextLetter = 'a';
                this->indexToChange++;
                if(this->word[this->indexToChange] == this->nextLetter) {
                    this->nextLetter++;
                }
            }
            if(this->word[this->indexToChange] == this->nextLetter){
                if(this->nextLetter >= 'z'){
                    this->indexToChange++;
                    this->nextLetter = 'a';
                    if(this->word[this->indexToChange] == 'a'){
                        this->nextLetter++;
                    }
                }
                else{
                    this->nextLetter++;
                }
            }
            if(this->indexToChange >= this->word.size()){
                this->iterationMode++;
                this->indexToChange = 0;
                this->nextLetter = 'a';
            }
            break;
    }
}

/* iterationDone
 *  parameters:
 *      none
 *  return value:
 *      true when all Locations of a location have been iterated over,
 *      false otherwise
 *
 *  This function checks to see if all iterations have been complete.
 */
bool Location::iterationDone(void) const{
    return this->iterationMode == DONE;
}

/* operator==
 *  parameters:
 *      loc -- given location that will be checked for equality
 *  return value:
 *      true if the Location objects are equal, otherwise false
 *
 *  This function checks to see if two Location objects represent the same word.
 */
bool Location::operator==(const Location &loc) const{
    return this->word == loc.word;
}

/* &operator<<
 *  parameters:
 *      os -- output stream the data will be sent to
 *      loc -- given Location that will be output
 *  return value:
 *      an ostream with the words of the Location object
 *
 *  This function provides a means of streaming a word out.
 */
ostream &operator<<(ostream &os, const Location &loc){
    os << loc.word;
    return os;
}

/* &operator>>
 *  parameters:
 *      is -- input stream the data will read into
 *      loc -- given Location that will be read from the stream
 *  return value:
 *      an istream with the words of the Location object
 *
 *  This function proves a means of streaming a word in.
 */
istream &operator>>(istream &is, Location &loc){
    is >> loc.word;
    return is;
}


/* operator<
 *  parameters:
 *      loc -- given Location that will be compared
 *  return value:
 *      true if the given word is greater than the current word,
 *      false otherwise
 *
 *  This function provides a means of comparing two Locations for purposes of
 *  keeping them in order.
 */
bool Location::operator<(const Location &loc) const{
    return this->word < loc.word;
}