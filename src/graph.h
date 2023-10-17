#pragma once
#include <vector>

using std::vector;
using std::size_t;
using std::pair;
using std::max;

class Graph {
public:
  Graph(const vector<pair<int, int>>& edges);
  size_t Size() const;
  vector<int>& operator[] (int ind) {
    return graph[ind];
  }
  const vector<int>& operator[] (int ind) const{
    return graph[ind];
  }
  int EdgeSize() const {return edge_size;}
  int VertexSize() const {return vertex_size;}
private:
  int edge_size;
  int vertex_size;
  vector<vector<int> > graph;
};
