#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <map>
#include <stack>
#include <algorithm>

#include "DirGraph.h"

using namespace std;

vector< pair<int, int> > loadData(string fileDir);

void firstPassDFSLoop(DirGraph* g);
void firstPassDFS(DirGraph* g, int s);

void secondPassDFSLoop(DirGraph* g);
void secondPassDFS(DirGraph* g, int s);


// Global Variables.
int t;
int s;
unordered_map <int, bool> explored;

stack<int> finishTimeStack;
unordered_map <int, int> leader;

vector< pair<int, int> > loadData(string fileDir) {
  vector< pair<int, int> > edgeList;
  std::ifstream infile(fileDir);

  int a, b;
  while (infile >> a >> b) {
    // std::cout << a << "->" << b << std::endl;
    pair<int, int> pair(a, b);
    edgeList.push_back(pair);
  }

  infile.close();
  return edgeList;
}


void DFS(DirGraph* g, int i, int pass) {
  // Mark this node as explored.
  explored.at(i) = true;  

  if (pass == 2) {
    leader.at(i) = s;
  }

  // Explore unexplored neighbors of s
  for (int w : g -> adjList[i]) {
    if (!explored.at(w)) {
      DFS(g, w, pass);
    }
  }

  if (pass == 1) {
    // For the first run only, record the finish time.
    finishTimeStack.push(i);
  }
}


void FirstDFSLoop(DirGraph* g) {
  // Initialize global trackers. 
  for (int v = 1;  v <= g -> n; v++) {
    explored[v] = false;
  }

  for (int v = 1;  v <= g -> n; v++) {
    // cout << v << endl;
    if (!explored.at(v)) {
      DFS(g, v, 1);
    }
  }
}


void SecondDFSLoop(DirGraph* g) {
  // Initialize global trackers. 
  for (int v = 1;  v <= g -> n; v++) {
    explored[v] = false;
    leader[v] = -1;
  }

  s = 0;

  // Go through vertices by decreasing order.
  while (!finishTimeStack.empty()) {
    auto v = finishTimeStack.top();
    finishTimeStack.pop();
    if (!explored.at(v)) {
      // set the global tracker of leader.
      s = v;
      DFS(g, v, 2);
    }
  }
}

bool wayToSort(int i, int j) { return i > j; }

int main() {
  vector< pair<int, int> > edgeList = loadData(string("./graph_edge_list.txt"));
  // vector< pair<int, int> > edgeList = loadData(string("./list.txt"));

  cout << "Creating the graph" << endl;
  DirGraph* g = new DirGraph(edgeList);

  cout << "m = " << g -> m << endl;
  cout << "n = " << g -> n << endl; 

  cout << "Creating the reversed graph" << endl;
  DirGraph* gRev = g -> getReverseGraph();

  cout << "Running the first pass of DFS" << endl;
  FirstDFSLoop(gRev);

  cout << "Running the second pass of DFS" << endl;
  SecondDFSLoop(g);

  // for (auto kv : f) {
  //   cout << "f(" << kv.first << ")=" << kv.second << endl;
  // }

  // for (auto kv : l) {
  //   cout << "leader(" << kv.first << ")=" << kv.second << endl;
  // }

  cout << "Sorting results" << endl;
  unordered_map<int, int> SCC_counters;

  for (auto kv : leader) {
    // cout << "leader (" << kv.first << ") is " << kv.second << endl;
    if (SCC_counters.count(kv.second) > 0) {
      SCC_counters[kv.second] ++;
    } else {
      SCC_counters[kv.second] = 1;
    }
  }

  vector<int> SCCs;
  for (auto kv : SCC_counters) {
    // Size, component lead
    SCCs.push_back(kv.second);
  }

  sort(SCCs.begin(), SCCs.end(), wayToSort);

  int z = 0;
  for (int size : SCCs) {
    cout << "Component size = " << size << endl;
    z ++;
    if (z > 5) {break;}
  }

  return 0;
}