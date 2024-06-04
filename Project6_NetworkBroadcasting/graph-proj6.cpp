/* CSI 3334
 * Project 6 -- Network Broadcasting
 * Filename: graph-proj6.cpp
 * Student name: Kirby Dyson
 *
 * This file implements the functions from the Graph class
 */

#include "graph-proj6.h"
#include <iostream>
#include <vector>
#include <list>
#include "arrayheap-student-proj6.h"

/* addEdge
 *  parameters:
 *      from -- given start for edge
 *      to -- given end for edge
 *      cost -- given cost of going to each vertex
 *  return value:
 *      none
 *
 *  This function adds an edge connecting (from -> to) with the given cost.
 */
void Graph::addEdge(int from, int to, int cost){
    adjacencyList[from].push_back(Edge(to, cost));
}

/* dijkstra
 *  parameters:
 *      source -- given source vertex
 *  return value:
 *      a vector that lists the shortest path cost of going from the
 *      source vertex to each vertex in the graph
 *
 *  This function finds the shortest paths to all other vertices in the
 *  graph.
 */
vector<int> Graph::dijkstra(int source) const{
    const int numVertices = adjacencyList.size();
    vector<int> distanceList(numVertices, INFINITE_COST);
    vector<int> keys(numVertices, -1);
    ArrayHeap<pair<int, int> > frontier;
    pair<int, int> sourcePair = make_pair(0, source);

    distanceList[source] = 0;

    keys[source] = frontier.insert(sourcePair);

    while (frontier.getNumItems() != 0) {
        int u = frontier.getMinItem().second;
        frontier.removeMinItem();

        for(list<Edge>::const_iterator i = adjacencyList[u].begin();
        i != adjacencyList[u].end(); i++){
            int v = i->to;
            int weight = i->cost;

            if (distanceList[u] + weight < distanceList[v]) {
                distanceList[v] = weight + distanceList[u];

                if (!frontier.isOnHeap(keys[v])) {
                    keys[v] = frontier.insert(make_pair(distanceList[v], v));
                }
                else {
                    frontier.changeItemAtKey(keys[v],make_pair
                    (distanceList[v], v));
                }
            }
        }
    }
    return distanceList;
}