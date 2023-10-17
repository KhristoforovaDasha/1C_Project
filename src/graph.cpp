#include "graph.h"

Graph::Graph(const vector<pair<int, int>>& edges) :edge_size(edges.size()){
  int num_vertex = 0;
  for (auto& edge: edges){
    num_vertex = max(num_vertex, max(edge.first, edge.second));
  }
  graph.resize(num_vertex);

  for (auto& edge: edges){
    graph[edge.first - 1].push_back(edge.second - 1);
    graph[edge.second - 1].push_back(edge.first - 1);
  }
  vertex_size = graph.size();
}

size_t Graph::Size() const {
  return graph.size();
}

