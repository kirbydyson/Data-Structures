/* CSI 3334
 * Project 1 -- DFS Maze Solver
 * Filename: testmain.cpp
 * Student name: Derek Martinez
 * assignment: project 1
 * due date: September 5,2023
 * version: 1.0
*/

#include <iostream>
#include <sstream>
#include "location-proj1.h"
#include "maze-proj1.h"
#include "stack-proj1.h"

using namespace std;

int main(){
    //Testing location stack class
    LocationStack stack;

    //Fill stack
    Location loc1;

    Location loc2;
    string locS2 = "2 2";
    stringstream inSS(locS2);
    inSS >> loc2;

    Location loc3;
    string locS3 = "3 3";
    stringstream ss(locS3);
    ss >> loc3;

    stack.push(loc1);
    stack.push(loc2);
    stack.push(loc3);

    cout << "-----Stack Test-----" << endl;
    //Checking isOn function before pop
    if(stack.isOn(loc3)){
        cout << loc3 << " is on the stack!" << endl;
    }else{
        cout << loc3 << " is not on the stack!" << endl;
    }

    //check that push works
    if(stack.isEmpty()){
        cout << "ERROR" << endl;
    }else{
        cout << "There are objects in stack!" << endl;
    }
    //Print out first value
    Location top = stack.getTop();
    cout << "Top Location: " << top << " (should be 3,3)" << endl;
    stack.pop();

    top = stack.getTop();
    cout << "Top Location: " << top << " (should be 2,2)" << endl;
    stack.pop();

    top = stack.getTop();
    cout << "Top Location: " << top << " (should be 0,0)" << endl;
    stack.pop();
    //check for popped objects
    if(stack.isEmpty()){
        cout << "All objects have been popped" << endl;
    }else{
        cout << "There are objects in stack!" << endl;
    }
    //Checking isOn function after pop
    if(stack.isOn(loc3)){
        cout << loc3 << " is on the stack!" << endl;
    }else{
        cout << loc3 << " is not on the stack!" << endl;
    }

    cout << endl;
    cout << "-----Maze Test-----" << endl;
    Maze maze;
    string mazeData =
            "9\n"
            "0 0\n"
            "0 1\n"
            "0 3\n"
            "1 1\n"
            "1 2\n"
            "1 3\n"
            "2 1\n"
            "3 1\n"
            "3 3\n"
            "0 1\n"
            "3 3\n";
    stringstream mazeSS(mazeData);
    mazeSS >> maze;

    cout << "Start Location: " << maze.getStartLocation() << " (should be 0 1)..." << endl;
    return 0;
}
