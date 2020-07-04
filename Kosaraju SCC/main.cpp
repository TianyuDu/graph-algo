/*
Kosaraju 's two pass algorithm to detect strongly connected components in directed graph.

Date: Jul 3, 2020
*/
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <stack>
#include <algorithm>

#include "DirGraph.h"

using namespace std;


// ==== Global Variables =====
// int t;  // Current time step, used to track finishing time in the first pass of DFS.
int s;  // Current leading nodes, used in the second pass of DFS.
unordered_map <int, bool> explored;  // Record which nodes has been explored.

stack<int> finishTimeStack;  // Finish time each nodes in the first pass of DFS.
unordered_map <int, int> leader;  // node leader[i] leads to the first discovery of node i.

// ============================

vector< pair<int, int> > loadData(string fileDir) {
  vector< pair<int, int> > edgeList;
  std::ifstream infile(fileDir);

  int a, b;
  while (infile >> a >> b) {
    pair<int, int> pair(a, b);
    edgeList.push_back(pair);
  }

  infile.close();
  return edgeList;
}


void DFS(DirGraph* g, int i, int pass) {
  // Mark this node as explored.
  explored.at(i) = true;  

  // In the second pass of DFS, s leads to the discovery of i.
  if (pass == 2) {
    leader.at(i) = s;
  }

  // Explore unexplored neighbors of s
  for (int w : g->adjList[i]) {
    if (!explored.at(w)) {
      DFS(g, w, pass);
    }
  }

  if (pass == 1) {
    // In the first pass of DFS, record the finihsing time of node i.
    finishTimeStack.push(i);
  }
}


void FirstDFSLoop(DirGraph* g) {
  // g here should be the reversed graph.

  // Initialize global trackers. 
  // Nodes are labelled from 1 to g->n.
  for (int v = 1;  v <= g->n; v++) {
    explored[v] = false;
  }

  // The exploring order does not matter in the first pass.
  for (int v = 1;  v <= g->n; v++) {
    if (!explored.at(v)) {
      DFS(g, v, 1);
    }
  }
}


void SecondDFSLoop(DirGraph* g) {
  // Initialize global trackers. 
  for (int v = 1;  v <= g->n; v++) {
    explored[v] = false;
    leader[v] = -1;
  }
  s = -1; // Set curent leader to -1. NULL also works.

  // Go through nodes by decreasing finish time in the first pass of DFS.
  while (!finishTimeStack.empty()) {
    int v = finishTimeStack.top();
    finishTimeStack.pop();
    if (!explored.at(v)) {
      // set the global tracker of leader.
      // node s leads to the discovery of all nodes (include itself)
      // explored in this call of DFS.
      s = v;
      DFS(g, v, 2);
    }
  }
}

// For sorting vectors.
bool wayToSort(int i, int j) { return i > j; }

int main() {
  vector< pair<int, int> > edgeList = loadData(string("./graph_edge_list.txt"));
  // vector< pair<int, int> > edgeList = loadData(string("./list.txt"));

  cout << "Creating the graph" << endl;
  DirGraph* g = new DirGraph(edgeList);

  cout << "m = " << g->m << endl;
  cout << "n = " << g->n << endl; 

  cout << "Creating the reversed graph" << endl;
  DirGraph* gRev = g->getReverseGraph();

  cout << "Running the first pass of DFS" << endl;
  FirstDFSLoop(gRev);

  cout << "Running the second pass of DFS" << endl;
  SecondDFSLoop(g);

  cout << "Sorting results" << endl;
  unordered_map<int, int> sccCounters;


  // Compute the size of the component leading by each leader.
  for (auto kv : leader) {
    if (sccCounters.count(kv.second) > 0) {
      sccCounters[kv.second] ++;
    } else {
      sccCounters[kv.second] = 1;
    }
  }

  // Record the size of components.
  vector<int> sccSizes;
  for (auto kv : sccCounters) {
    sccSizes.push_back(kv.second);
  }

  sort(sccSizes.begin(), sccSizes.end(), wayToSort);

  // Report the size of the five largest components.
  int z = 0;
  for (int size : sccSizes) {
    cout << "Component size = " << size << endl;
    z ++;
    if (z > 5) {break;}
  }

  return 0;
}