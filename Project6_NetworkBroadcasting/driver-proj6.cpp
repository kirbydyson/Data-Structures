/* CSI 3334
 * Project 6 -- Network Broadcasting
 * Filename: driver-proj6.cpp
 * Student name: Kirby Dyson
 *
 * This file contains a program for network broadcasting.
 */

#include "graph-proj6.h"
#include "arrayheap-student-proj6.h"
#include <iostream>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

const int SIZE = 7;

/* main
 *  parameters:
 *      none
 *  return value:
 *      0 (indicating a successful run)
 *
 *  This function reads in a description of an existing network. Vertices
 *  are added to the graph and the server names are tracked. Then, the
 *  total delay for each server is calculated to find the fastest server.
 *  The shortest delay time is then output, or that no server can serve the
 *  entire network.
 */
int main() {
    map<string, int> nameToIndex;
    vector<bool> serverExists;
    vector<int> delayTimes;
    string from, to;
    int delay, totalMinTime, numVertices, verticeCount = 0;
    stringstream inpSS;

    cin >> numVertices;

    for (int i = 0; i < numVertices; i++) {
        cin >> from >> to >> delay;
        inpSS << from << " " << to << " " << delay << endl;

        if (nameToIndex.find(from) == nameToIndex.end()) {
            nameToIndex[from] = verticeCount;
            serverExists.push_back(from.size() >= SIZE &&
            from.substr(from.size() - SIZE) == "_server");
            verticeCount++;
        }

        if (nameToIndex.find(to) == nameToIndex.end()) {
            nameToIndex[to] = verticeCount;
            serverExists.push_back(to.size() >= SIZE &&
            to.substr(to.size() - SIZE) == "_server");
            verticeCount++;
        }
    }

    Graph g(nameToIndex.size());

    for (int i = 0; i < numVertices; i++) {
        inpSS >> from >> to >> delay;
        g.addEdge(nameToIndex[from], nameToIndex[to], delay);
    }

    totalMinTime = g.INFINITE_COST;

    for (int i = 0; i < serverExists.size(); i++) {
        if (serverExists[i]) {
            vector<int> numDelays = g.dijkstra(i);

            delayTimes.push_back(0);

            for (int j = 0; j < serverExists.size(); j++) {
                if(numDelays[j] >= 0 && delayTimes[i] < g.INFINITE_COST){
                    delayTimes[i] += numDelays[j];
                }
            }

            if (delayTimes[i] < g.INFINITE_COST) {
                totalMinTime = min(totalMinTime, delayTimes[i]);
            }
        }
        else{
            delayTimes.push_back(g.INFINITE_COST);
        }
    }

    if (totalMinTime >= g.INFINITE_COST) {
        cout << "no server can serve the whole network" << endl;
    }
    else {
        cout << "total delay: " << totalMinTime << endl;
        for (map<string, int>::iterator it = nameToIndex.begin();
        it != nameToIndex.end(); ++it) {
            if (serverExists[it->second] &&
            delayTimes[it->second] == totalMinTime) {
                cout << it->first << endl;
            }
        }
    }

    return 0;
}