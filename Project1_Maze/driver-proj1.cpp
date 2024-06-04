/* CSI 3334
 * Project 1 -- Two-dimensional Maze Solver
 * Filename: driver-proj1.cpp
 * Student name: Kirby Dyson
 *
 * This file contains the logic to solve a maze.
 */

#include <iostream>
#include "maze-proj1.h"
#include "stack-proj1.h"

using namespace std;

/* main
 *  parameters:
 *      none
 *  return value:
 *      0 (indicating a successful run)
 *
 *  This function searches through a maze to find a path from the beginning
 *  to the end. Valid locations are input by the user. Each location
 *  is iterated through using depth-first search by searching from the right,
 *  down, left, and then up, and put on the stack until valid locations are
 *  found and the end of the maze is reached. If a solution is found, the
 *  sequence of valid locations are output, but if no solution is found,
 *  "no solution" is output.
 */
int main(){
    Maze maze;
    Location m, neighbor;
    LocationStack stack;
    bool flag = false;

    cin >> maze;

    // Gets the beginning location and initializes the iteration state of the
    // location, adding it to the stack
    m = maze.getStartLocation();
    m.iterationBegin();
    stack.push(m);

    // Loop through the maze until a solution is found or all possible paths
    // have been searched
    while(!flag && !maze.isEndLocation(stack.getTop())){
        m = stack.getTop();
        stack.pop();

        if(!m.iterationDone()){
            neighbor = m.iterationCurrent();
            m.iterationAdvance();
            neighbor.iterationBegin();
            stack.push(m);
            if(!stack.isOn(neighbor) && maze.isValidLocation(neighbor)){
                stack.push(neighbor);
            }
        }
        else if(stack.isEmpty()){
            flag = true;
        }
    }

    if(flag){
        cout << "No solution" << endl;
    }
    else{
        cout << "Solution found" << endl;
        cout << stack;
    }

    return 0;
}