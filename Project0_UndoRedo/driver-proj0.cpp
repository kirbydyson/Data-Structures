/* CSI 3334
 * Project 0 -- Undo Redo
 * Filename: driver-proj0.cpp
 * Student name: Kirby Dyson
 *
 * This file contains a program that uses a stack to allow undo and redo
 * commands using a given text (a word).
 */

#include <iostream>
#include <string>
#include <stack>
#include <cassert>
#include <sstream>

using namespace std;

const int MAX = 1000;

/* main
 *  parameters:
 *      argc -- the number of arguments from the command line
 *      argv -- the command line argument values
 *  return value: 0 (indicating a successful run)
 *
 *  This function reads in a number of lines, each containing a command of
 *  either type, undo, or redo. Type places a single word onto the typing
 *  stack, undo removes the last word from the typing stack and places it
 *  on the undo stack, and redo removes the last word from the undo stack
 *  and places it on the typing stack. Once all the commands have been
 *  read, two lines are output containing the typing stack and the undo stack
 *  from bottom to top order.
 */
int main(int argc, char **argv){
    // these are the two stacks used to store the typed words and the undone
    // words
    stack<string> typing, undo;
    // these are the two stacks used to reverse the typed words and the undone
    // words
    stack<string> revTyping, revUndo;

    int n;
    char command;
    string text;
    stringstream typingSS, undoSS;

    cin >> n;

    // Checks that the number of lines does not exceed its maximum number
    assert(n <= MAX);

    for(int i = 0; i < n; i++){
        cin >> command;
        // Checks that a valid command is given to type, undo, or redo.
        assert(command == 't' || command == 'u' || command == 'r');
        if(command == 't'){
            cin >> text;
            typing.push(text);
        }
        else if(command == 'u'){
            if(!typing.empty()){
                undo.push(typing.top());
                typing.pop();
            }
            else{
                cout << "nothing to undo on command " << i + 1 << endl;
            }
        }
        else if(command == 'r'){
            if(!undo.empty()){
                typing.push(undo.top());
                undo.pop();
            }
            else{
                cout << "nothing to redo on command " << i + 1 << endl;
            }
        }
    }

    // Stores the contents of the typing stack into a stringstream and
    // then prints the stack from bottom to top by reversing its contents.
    while(!typing.empty()) {
        revTyping.push(typing.top());
        typing.pop();
    }
    while(!revTyping.empty()){
        typingSS << revTyping.top();
        revTyping.pop();
        if(!revTyping.empty()){
            typingSS << " ";
        }
    }
    cout << typingSS.str() << endl;

    // Stores the contents of the undo stack into a stringstream and
    // then prints the stack from bottom to top by reversing its contents.
    while(!undo.empty()) {
        revUndo.push(undo.top());
        undo.pop();
    }
    while(!revUndo.empty()){
        undoSS << revUndo.top();
        revUndo.pop();
        if(!revUndo.empty()){
            undoSS << " ";
        }
    }
    cout << undoSS.str() << endl;

    return 0;
}
