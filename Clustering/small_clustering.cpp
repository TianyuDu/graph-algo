/*
Input format:
This file describes a distance function (equivalently, a complete graph with edge costs). It has the following format:

[number_of_nodes]

[edge 1 node 1] [edge 1 node 2] [edge 1 cost]

[edge 2 node 1] [edge 2 node 2] [edge 2 cost]

...
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <map>

#include "graph.h"

using namespace std;

int K = 4; // Number of clusters.
int numNode;


vector<Edge> loadData() {
    vector<Edge> edgeList;
    fstream file("./clustering1.txt");
    string line, value;

    getline(file, line);
    cout << line << endl;
    numNode = stoi(line);

    while (getline(file, line)) {
        stringstream X(line);
        int node1, node2, cost;
        X >> node1 >> node2 >> cost;
        pair<int, int> p = make_pair(node1, node2);
        Edge e = make_pair(p, cost);
        edgeList.push_back(e);
    }
    return edgeList;
}


int clustering(vector<Edge> & edgeList, map<int, set<int> > & adjList) {
    // Start from low cost edges.
    sort(edgeList.begin(), edgeList.end(), compareEdgeWeight);
    map< int, set<int> > T;
    for (auto kv : adjList) {
        set<int> N;
        T[kv.first] = N;
    }
    int c = numNode;
    int z = 0;
    for (auto e : edgeList) {
        pair<int, int> nodePair = e.first;
        int node1 = nodePair.first;
        int node2 = nodePair.second;
        if (! BFS(T, node1, node2)) {
            // There is no current u-v path, so adding edge (u, v) does not create cycle.
            T.at(node1).insert(node2);
            T.at(node2).insert(node1);
            // Every time such merging happens, the number of current clusters is reduced by one.
            c --;
        }
        if (c == K - 1) {
            // The clustering algorithm should half when c = K.
            // At the first time c = K - 1, we are looking at a edge (p, q)
            // with the lowest cost and  there is no p-q path in the resulted clustering
            // (If there is p-q path, counter c would not decrease.)
            // Therefore, p and q belongs to different clusters.
            // By definition, d(p, q) is the minimum spacing between nodes from different clusters.
            return e.second;
        }
    }
}

int main() {
    vector<Edge> edgeList = loadData();
    auto adjList = edgeList2AdjList(edgeList);

    cout << "Number of nodes = " << numNode << endl;
    cout << "Number of edges = " << edgeList.size() << endl;
    cout << adjList.size() << endl;
    int minSeparation = clustering(edgeList, adjList);
    return 0;
}
