/*
This file describes the weights of the vertices in a path graph
(with the weights listed in the order in which vertices appear in the path).
It has the following format:

[weight of first vertex]
[weight of second vertex]

...

For example, the second line of the file is "6395702," indicating that the weight of the second vertex of the graph is 6395702.

Your task in this problem is to run the dynamic programming algorithm (and the reconstruction procedure)
from lecture on this data set. 
The question is: of the vertices 1, 2, 3, 4, 17, 117, 517, and 997,
which ones belong to the maximum-weight independent set? (By "vertex 1" we mean the first vertex of the graph
---there is no vertex 0.) In the box below, enter a 8-bit string, where the ith bit should be 1 if the ith of
these 8 vertices is in the maximum-weight independent set, and 0 otherwise. For example, if you think that the
vertices 1, 4, 17, and 517 are in the maximum-weight independent set and the other four vertices are not,
then you should enter the string 10011010 in the box below.
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

vector<int> loadData() {
    vector<int> V;
    fstream file("./data.txt");
    string str;
    while (getline(file, str)) {
        int w = stoi(str);
        V.push_back(w);
    }
    return V;
}

map<int, int> DP(const vector<int> & V) {
    map<int, int> A;
    A[0] = 0;
    A[1] = V[0];
    int numVertices = V.size();
    for (int i = 2; i <= numVertices; i ++) {
        int wi = V[i - 1];
        A[i] = max(A[i - 1], A[i - 2] + wi);
    }
    return A;
}

set<int> reconstruction(const map<int, int> & A, const vector<int> & V) {
    set<int> S;
    int i = V.size();
    while (i > 1) {
        int wi = V[i - 1];
        if (A.at(i - 1) >= A.at(i - 2) + wi) {
            i --;
        } else {
            S.insert(i);
            i -= 2;
        }
    }
    // Base case:
    // Above code handles everything include the second vertex.
    // If the second vertex is not included, we can add the first one for free.
    if (S.find(2) == S.end()) {
        S.insert(1);
    }

    return S;
}

int main() {
    vector<int> V = loadData();
    cout << "Number of vertices = " << V.size() << endl;
    map<int, int> A = DP(V);
    cout << A.size() << endl;
    set<int> S = reconstruction(A, V);

    int targets [8] = {1, 2, 3, 4, 17, 117, 517, 997};

    for (int t : targets) {
        if (S.find(t) == S.end()) {
            cout << "0";
        } else {
            cout << "1";
        }
    }
    cout << endl;
    return 0;
}
