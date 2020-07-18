#include <utility>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>

using namespace std;

typedef pair< pair<int, int>, int> Edge; // pair(pair(node1, node2), cost).


map< int, set<int> > edgeList2AdjList(const vector<Edge> & edgeList) {
    map< int, set<int> > adjList;
    for (auto e : edgeList) {
        int u, v;
        auto p = e.first;
        u = p.first;
        v = p.second;
        if (adjList.count(u) == 0) {
            set<int> N;
            adjList[u] = N;
        }
        adjList.at(u).insert(v);

        if (adjList.count(v) == 0) {
            set<int> N;
            adjList[v] = N;
        }
        adjList.at(v).insert(u);
    }
    return adjList;
}

bool compareEdgeWeight(const Edge & a, const Edge & b){
    return a.second < b.second;
}

bool BFS(const map< int, set<int> > G, const int & s, const int & t) {
    // BFS, search s-t path in G, return true if there is such a path.
    queue<int> q;
    unordered_map<int, bool> traversed;
    for (auto kv : G) {  // mark all nodes as untraversed.
        traversed[kv.first] = false;
    }
    q.push(s);
    while (! q.empty()) {
        int u = q.front();
        q.pop();
        traversed.at(u) = true;  // Mark as traversed.
        if (u == t) { return true; }  // Found target.
        for (int v : G.at(u)) { 
            if (! traversed.at(v)) {
                q.push(v);
            }
        }
    }
    return false;
}
