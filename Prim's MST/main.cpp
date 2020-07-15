#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <map>

using namespace std;

/*
Input format:
This file describes an undirected graph with integer edge costs. It has the format

[number_of_nodes] [number_of_edges]

[one_node_of_edge_1] [other_node_of_edge_1] [edge_1_cost]

[one_node_of_edge_2] [other_node_of_edge_2] [edge_2_cost]
*/

int numNodes, numEdges;

vector< vector<int> > loadData() {
    ifstream infile("./edges.txt");
    // ifstream infile("./small_sample.txt");

    vector< vector<int> > G;

    infile >> numNodes >> numEdges;

    int from, to, c;
    while (infile >> from >> to >> c) {
        vector<int> E;
        E.push_back(from);
        E.push_back(to);
        E.push_back(c);
        G.push_back(E);
    }
    return G;
}


bool comp(const vector<int> & a, const vector<int> & b) {return a[2] < b[2];}

bool is_crossing(const unordered_map<int, int> & X, const int & a, const int & b) {
    // a is in X but b is not in X.
    return (X.find(a) != X.end()) && (X.find(b) == X.end());
}

vector< vector<int> > MST(const vector< vector<int> > & G) {
    // O(mn) implementation.
    unordered_map<int, int> X; // addded nodes.
    vector< vector<int> > T; // the MST.
    // int s = G[0][0]; // an arbitrary starting node.
    int s = 1;
    X[s] = 1;  // add the initial node.
    cout << "Starting node s = " << s << endl;

    while (X.size() < numNodes) {
        // cout << "X = ";
        // for (auto v : X) {cout << v.first << ",";}
        // cout << endl;
        vector< vector<int> > frontior;  // frontior edges.

        // Loop over edges.
        for (vector<int> e : G) {
            // iterate through crossing edges.
            // check if one end is in X while the other end is not in X.
            if (is_crossing(X, e[0], e[1]) || is_crossing(X, e[1], e[0])) {
                frontior.push_back(e);
            }
        }
        // Sort based on the edge[2], the weight, ascending order.
        sort(frontior.begin(), frontior.end(), comp);
        // The crossign edge with least weight.
        vector<int> chosenEdge = *frontior.begin();

        // for (auto k : frontior) {
        //     cout << k[0] << "," << k[1] << "," << k[2] << endl;
        // }

        // Add the chosen edge to MST.
        T.push_back(chosenEdge);

        // Update both ends of the chosen edge in X.
        X[chosenEdge[0]] = 1;
        X[chosenEdge[1]] = 1;
    }

    int totalCost = 0;  // total cost of MST.
    cout << "Number of edges in MST = " << T.size() << endl;
    for (vector<int> e : T) {
        totalCost += e[2];
    }
    cout << "Cost = " << totalCost << endl;
    return T;
}

int main() {
    auto G = loadData();
    cout << "numNodes = " << numNodes << endl;
    cout << "numEdges = " << numEdges << endl;
    auto T = MST(G);
    return 0;
}