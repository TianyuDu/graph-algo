/*
The format is:

[# of nodes] [# of bits for each node's label]

[first bit of node 1] ... [last bit of node 1]

[first bit of node 2] ... [last bit of node 2]

...

For example, the third line of the file "0 1 1 0 0 1 1 0 0 1 0 1 1 1 1 1 1 0 1 0 1 1 0 1" denotes the 24 bits associated with node #2.

The distance between two nodes uu and vv in this problem is defined as the Hamming distance--- the number of differing bits --- between the two nodes' labels. For example, the Hamming distance between the 24-bit label of node #2 above and the label "0 1 0 0 0 1 0 0 0 1 0 1 1 1 1 1 1 0 1 0 0 1 0 1" is 3 (since they differ in the 3rd, 7th, and 21st bits).

The question is: what is the largest value of kk such that there is a kk-clustering with spacing at least 3? That is, how many clusters are needed to ensure that no pair of nodes with all but 2 bits in common get split into different clusters?

NOTE: The graph implicitly defined by the data file is so big that you probably can't write it out explicitly, let alone sort the edges by cost. So you will have to be a little creative to complete this part of the question. For example, is there some way you can identify the smallest distances without explicitly looking at every pair of nodes?

*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <boost/algorithm/string.hpp>
#include <boost/pending/disjoint_sets.hpp>
#include <boost/unordered/unordered_set.hpp>

using namespace std;
using namespace boost;

int numNodes, numBits;

map< int, vector<int> > loadData() {
    vector< vector<bool> > data;

    fstream file("./clustering_big.txt");
    string line;
    getline(file, line);
    stringstream X(line);
    X >> numNodes >> numBits;

    vector<int> nodeValues;
    while (getline(file, line)) {
        // Convert to binary string.
        erase_all(line, " ");
        // Convert to decimal representations.
        int v = stoi(line, nullptr, 2);
        nodeValues.push_back(v);
    }
    // key: value of nodes.
    // value: set of nodes with values = key.
    map< int, vector<int> > valueToNodes;
    for (int i = 0; i < numNodes; i++) {
        int v = nodeValues[i];
        if (valueToNodes.count(v) == 0) {
            vector<int> N;
            valueToNodes[v] = N;
        }
        valueToNodes.at(v).push_back(i);
    }
    return valueToNodes;
}

set<int> getBitMaps() {
    // Create a set of bit masks.
    set<int> M;
    // All Hamming distance = 1 pairs of nodes.
    // Only 1 out of 24 bits flipped.
    for (int i = 0; i < numBits; i ++) {
        M.insert(pow(2, i));
    }
    // All Hamming distance = 2 pairs of nodes.
    // 2 out of 24 bits flipped.
    for (int i = 0; i < numBits; i ++) {
        for (int j = 0; j < numBits; j ++) {
            if (i != j) {
                int shift = pow(2, i) + pow(2, j);
                M.insert(shift);
            }
        }
    }
    return M;
}

int main() {
    auto data = loadData();
    cout << "num of nodes = " << numNodes << endl;
    cout << "num of bits = " << numBits << endl;
    // Create disjoint set representation.
    vector<int> rank (numNodes);
    vector<int> parent (numNodes);
    disjoint_sets<int*, int*> ds(&rank[0], &parent[0]);
    unordered_set<int> elements;
    for (int i = 0; i < numNodes; i ++) {
        ds.make_set(i);
        elements.insert(i);
    }

    // Initialize the disjoint set of nodes.
    // There are numNode clusters initially.
    cout << ds.count_sets(elements.begin(), elements.end()) << endl;
    cout << data.size() << endl;
    // Union all elements with the same representations.
    for (auto kv : data) {
        // for each (value, list of nodes) pair.
        int value = kv.first;
        vector<int> nodeList = kv.second;
        int node0 = nodeList[0];  // take the leading node as the leader.
        for (auto iter = nodeList.begin() + 1; iter != nodeList.end(); iter++) {
            // union everything with the same value (Hamming distance = 0) together.
            int node1 = *iter;
            ds.union_set(node0, node1);
        }
    }

    cout << ds.count_sets(elements.begin(), elements.end()) << endl;

    auto M = getBitMaps();
    cout << "Number of bitshifts = " << M.size() << endl;
    for (int s : M) {
        for (auto kv : data) {
            int value = kv.first;
            int node1 = kv.second[0];
            int shiftedValue = value ^ s;  // Take XOR, i.e., bit-wise shift whenever ont particular bit in the bit mask is 1.
            // Leave unchanged if the corresponding bit in the bit mask is zero.
            // If there are other nodes with the same value as the shifted value, these nodes have Hamming distance of either 1 or 2
            // from node1, union those nodes with node1.
            if (data.count(shiftedValue) > 0) {
                int node2 = data.at(shiftedValue)[0];
                ds.union_set(node1, node2);
            }
        }
    }

    cout << ds.count_sets(elements.begin(), elements.end()) << endl;
}
