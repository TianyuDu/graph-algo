#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <map>
#include <set>
#include <boost/algorithm/string.hpp>
#include <boost/assign/std/vector.hpp>

using namespace std;
using namespace boost;
using namespace boost::assign;


typedef map< int, vector< pair<int, int> > > adjacentListGraph;

adjacentListGraph loadData() {
    ifstream file("./dijkstra data.txt");
    string str;

    map< int, vector< pair<int, int> > > adjacentList;

    erase_all(str, " ");

    while (getline(file, str)) {
        vector<string>  splitVec;
        split(splitVec, str, is_any_of("\t"));

        int thisNode = stoi(splitVec[0]);

        vector< pair<int, int> > Neightbors;

        for (auto it = ++splitVec.begin(); it != splitVec.end()-1; ++it) {
            vector<string> p;
            split(p, *it, is_any_of(","));

            int node = stoi(p[0]);
            int weight = stoi(p[1]);

            Neightbors.push_back(make_pair(node, weight));
        }
        adjacentList[thisNode] = Neightbors;
    }

    return adjacentList;
}


map<int, int> SingleSourceShortestPath(const adjacentListGraph G, int s) {
    // The naive implementation, runtime = O(m*n).
    int numVertices = G.size();

    cout << "Number of vertices = " << numVertices << endl;

    set<int> X;  // Set of explored vertices.
    map<int, int> A; // Knowned shorted path length
    // A[vertex] is the length of shortest path from s to vertex.
    // Keys of A should be exactly the same as X through the algorithm.

    X.insert(s);  // Initialize explored list.
    A[s] = 0;  // Base case, the legnth of shortest path from s to itself is 0.

    while (X.size() < numVertices) {  // while there are still unexplored nodes.
        map<int, int> frontierScores;  // To hold the Dijkstra's greedy score for each nodes at the frontior.
        // map[score] = node, we use the score as keys and node identity as the value.
        for (int v : X) {
            for (auto p: G.at(v)) {  // look at all outgoing edges of vertex v.
                int u = p.first;  // the neighbour vertex.
                int length = p.second;  // the length of edge (v, u).
                if (X.find(u) == X.end()) {  // if u not in X yet.
                    int score = A[v] + length;  // compute Dijkstra's greedy score.
                    frontierScores[score] = u;  // If there are multiple nodes with the same score, just take the last one encountered, it does not matter.
                }
            }
        }
        // Map's keys are automatically sorted in ascending order.
        // Take the first pair of keys.
        int s = frontierScores.begin() -> first;  // key of the map is score.
        int n = frontierScores.begin() -> second;  // value of the map is node.

        X.insert(n);
        A[n] = s;
    }

    return A;
}


int main () {
    auto G = loadData();
    auto A = SingleSourceShortestPath(G, 1);
    // for (auto v : G) {cout << v.first << endl;}

    vector<int> v;
    v += 7,37,59,82,99,115,133,165,188,197;
    for (int q : v) {
        cout << "A[" << q << "] = " << A.at(q) << endl;
    }
}