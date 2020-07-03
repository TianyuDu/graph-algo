#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <map>

using namespace std;


class DirGraph {
  public:
    vector< pair<int, int> > edgeList;
    map< int, vector<int> > adjList;
    vector<int> Vertices;
    int n; // number of vertices.
    int m; // number of edges.

    DirGraph() {};
    DirGraph(vector< pair<int, int> > edges) {
      this->edgeList = edges;

      unordered_map<int, int> counts;
      for (auto e : edgeList) {
        counts[e.first] = 1;
        counts[e.second] = 1;
        if (this->adjList.count(e.first) > 0) {
          this->adjList.at(e.first).push_back(e.second);
        } else {
          vector<int> init;
          init.push_back(e.second);
          this->adjList[e.first] = init;
        }
      }

    this->Vertices.reserve(counts.size());

    for (auto kv : counts) {
      this->Vertices.push_back(kv.first);
    }

    this->n = this->Vertices.size();
    this->m = this->edgeList.size();

  }

    DirGraph* getReverseGraph() {
      vector< pair<int, int> > reversedEdgeList;
      for (pair<int, int> e : edgeList) {
        pair<int, int> reversedEdge(e.second, e.first);
        reversedEdgeList.push_back(reversedEdge);
      }
      DirGraph* r = new DirGraph(reversedEdgeList);
      return r;
    };

    void printEdges() {
      int c = 0;
      for (pair<int, int> e : this->edgeList) {
        cout << e.first << "->" << e.second << std::endl;
        c ++;
        if (c >= 20) {break;}
      }
    };
};
