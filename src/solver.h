#pragma once
#include "graph.h"

#include <algorithm>
#include <iostream>

class Solver {
public:
  void Solve(const Graph& graph);
  void PrintSolution();

private:
  vector<int> inflect_vertexes;
  void ComplexGraphSolver(const Graph& graph);
  void SparseGraphSolver(const Graph& graph);
};

