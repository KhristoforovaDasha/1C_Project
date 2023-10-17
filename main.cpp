#include <iostream>
#include "src/graph.h"
#include "src/solver.h"

using std::cin;
using std::cout;

int main(){
  int edge_num;
  cin >> edge_num;
  vector<pair<int, int>> edges(edge_num);
  for(auto& edge: edges) {
    cin >> edge.first >> edge.second;
  }
  Graph graph(edges);

  Solver solver;
  solver.Solve(graph);
  solver.PrintSolution();
  return 0;
}
