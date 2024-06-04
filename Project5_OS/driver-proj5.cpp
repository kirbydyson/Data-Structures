/* CSI 3334
 * Project 5 -- Real-Time Batch Operating System Simulator
 * Filename: driver-proj5.cpp
 * Student name: Kirby Dyson
 *
 * This file implements a program which simulates a batch OS.
 */

#include <iostream>
#include "arrayheap-student-proj5.h"
#include "process-proj5.h"

using namespace std;

/* main
 *  parameters:
 *      none
 *  return value:
 *      0 (indicating a successful run)
 *
 *  This function reads in a number of processes, keeping processes that are
 *  ready to run in memory in a heap once its submission time has been reached
 *  by reading one process ahead in the input. Each process will be compared
 *  by their deadline and/or their required time. All processes will either run
 *  or be skipped. The ending OS clock value, number of processes that are run,
 *  and number of processes that are skipped will be output.
 */
int main() {
    int n;
    int sysTime = 0;
    int runs = 0, skips = 0;
    int id = 0;
    int input;
    Process *process = new Process();
    ArrayHeap<Process> heap;

    cin >> n >> *process;
    input = n;

    while(n > 0){
        while(process->getSubmissionTime() <= sysTime && input > 0){
            heap.insert(*process);
            id++;
            input--;
            delete process;
            process = new Process(id);
            if(input > 0){
                cin >> *process;
            }
        }

        if(heap.getNumItems() == 0){
            sysTime++;
        }
        else{
            Process curr = heap.getMinItem();
            heap.removeMinItem();
            n--;
            if(curr.canComplete(sysTime)){
                sysTime = curr.run(sysTime);
                runs++;
            }
            else{
                skips++;
                cout << "skipping process id " << curr.getId() << " at " << sysTime << endl;
                sysTime++;
            }
        }
    }
    delete process;

    cout << "final clock is                 " << sysTime << endl;
    cout << "number of processes run is     " << runs << endl;
    cout << "number of processes skipped is " << skips << endl;

    return 0;
}
