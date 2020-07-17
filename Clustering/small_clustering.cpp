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
#include <utility>
#include <vector>
#include <string>

using namespace std;

int K = 4; // Number of clusters.

bool comp(const pair< pair<int, int>, int > & a, const pair< pair<int, int>, int > & b){
    return a.second < b.second;
}

vector< pair< pair<int, int>, int> > loadData() {
    pair<pair<int, int>, int> data;
}