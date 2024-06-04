/* CSI 3334
 * Project 2 -- Word Melt Shortest-Path Solver
 * Filename: driver-proj2.cpp
 * Student name: Kirby Dyson
 *
 * This file contains the logic to solve a word melt puzzle using the shortest
 * path.
 */

#include <iostream>
#include <vector>
#include <map>
#include "maze-proj2.h"
#include "arrayqueue-student-proj2.h"

using namespace std;

/* main
 *  parameters:
 *      none
 *  return value:
 *      0 (indicating a successful run)
 *
 *  This function searches through a word melt puzzle to find the shortest
 *  sequence of changes to get from a starting word to a goal word. Valid
 *  words are input by the user. Each word is iterated through using
 *  breadth-first and put on the queue until valid words are found and the
 *  goal word is reached. If a solution is found, the sequence of valid words
 *  are output, but if no solution is found, "no solution" is output.
 */
int main(){
    Maze maze;
    Location curr, neighbor, end;
    ArrayQueue<Location> queue;
    vector<Location> vector;
    map<Location, Location> map;
    bool flag = false;

    cin >> maze;

    // Gets the beginning location, adds it to the queue, and initializes the
    // map location
    curr = maze.getStartLocation();
    queue.add(curr);
    map[curr] = curr;

    // Loop through the maze using breath-first search until a solution is
    // found or all possibilities have been searched
    while(!flag && queue.getLength() > 0){
        if(maze.isEndLocation(curr)){
            flag = true;
            end = curr;
        }
        curr = queue.getFront();
        queue.remove();
        curr.iterationBegin();
        while(!curr.iterationDone()){
            neighbor = curr.iterationCurrent();
            if(maze.isEndLocation(neighbor)) {
                map[neighbor] = curr;
                end = neighbor;
                flag = true;
            }
            else if(maze.isValidLocation(neighbor) && (map.find(neighbor) ==
            map.end())){
                map[neighbor] = curr;
                queue.add(neighbor);
            }
            curr.iterationAdvance();
        }
    }

    // Output the solutions in the correct order
    if(!flag){
        cout << "No solution" << endl;
    }
    else{
        cout << "Solution found" << endl;
        while(!(end == maze.getStartLocation())){
            vector.push_back(end);
            end = map[end];
        }
        vector.push_back(end);
        while(!vector.empty()){
            cout << vector.back() << endl;
            vector.pop_back();
        }
    }

    return 0;
}
