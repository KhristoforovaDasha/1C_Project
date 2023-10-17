#include "solver.h"

using std::cin;
using std::cout;

struct vertex_score {
  int vertex;
  int edge_num;
};

bool compare(const vertex_score& first, const vertex_score& second) {
  return first.edge_num > second.edge_num;
}

int find_no_infect(const vector<vertex_score>& vertexes_scores, vector<uint8_t>& infect, vector<int>& inflect_vertexes,
                   int& ind) {
  int vertex_num = vertexes_scores.size();
  while (infect[vertexes_scores[ind].vertex] && ind < vertex_num) {
    ++ind;
  }
  if (ind < vertex_num) {
    infect[vertexes_scores[ind].vertex] = 1;
    inflect_vertexes.push_back(vertexes_scores[ind].vertex);
    return ind;
  } else {
    return -1;
  }
}

int infect_component(const Graph& graph, int vertex, vector<uint8_t>& used, vector<int>& infect) {
  used[vertex] = 1;
  int infect_count = 0;
  bool is_leaf = 1;
  for(const auto& neighbor : graph[vertex]) {
    if(!used[neighbor]) {
      is_leaf = 0;
      infect_count += infect_component(graph, neighbor, used, infect);
    }
  }
  if (infect_count <= 0 || is_leaf) {
    infect.push_back(vertex);
    return 1;
  } else if (infect_count == 1) {
    return -int(graph.Size()); // hint to infect the parent
  } else {
    return 0;
  }
}

void Solver::Solve(const Graph& graph) {
  int edge_size = graph.EdgeSize();
  int vertex_size = graph.VertexSize();
  if (edge_size >= vertex_size * vertex_size / 8) {
    ComplexGraphSolver(graph);
  } else {
    SparseGraphSolver(graph);
  }
}

void Solver::PrintSolution() {
  cout << inflect_vertexes.size() <<'\n';
  sort(inflect_vertexes.begin(), inflect_vertexes.end());
  for(const auto& vertex : inflect_vertexes) {
    cout << vertex + 1 <<" ";
  }
}

// сортируем по количеству рёбер и заражаем сначала вершины, у которых большая степень
// хорошо работает для графов с большим количеством рёбер
void Solver::ComplexGraphSolver(const Graph& graph) {
  vector<vertex_score> vertexes_scores(graph.Size());
  for (int i = 0; i < graph.Size(); ++i) {
    vertexes_scores[i] = {i, int(graph[i].size())};
  }
  std::sort(vertexes_scores.begin(), vertexes_scores.end(), compare);
  vector<uint8_t> infect(graph.Size(), 0);
  int ind = 0;
  int vertex_num = vertexes_scores.size();
  while (ind < vertex_num) {
    int first_vert = find_no_infect(vertexes_scores, infect, inflect_vertexes, ind);
    int second_vert = find_no_infect(vertexes_scores, infect, inflect_vertexes, ind);
    if (ind >= vertex_num) {
      break;
    }

    vector<uint8_t> second_neighbor(vertex_num);
    for (const auto& neighbor: graph[second_vert]) {
      second_neighbor[neighbor] = 1;
    }
    for (const auto& neighbor: graph[first_vert]) {
      if (second_neighbor[neighbor]) {
        infect[neighbor] = 1;
      }
    }
  }
}

// бёрем вершину, строим дерево обхода дфс, начиная с этой вершины
// дальше заражаем все листья в дереве обхода дфс и поднимаясь вверх по дереву заражаем остальные вершины
// хорошо будет работать для разреженных графов и для графов, которые почти как деревья
void Solver::SparseGraphSolver(const Graph& graph) {
  int infect_sz = graph.Size();
  for(size_t start_vert = 0; start_vert < graph.Size(); ++start_vert) {
    vector<int> infect;
    vector<uint8_t> used(graph.Size(), 0);
    infect_component(graph, start_vert, used, infect);
    for (size_t i = 0; i < graph.Size(); ++i) {
      if (!used[i]) {
        infect_component(graph, i, used, infect);
      }
    }
    if (infect.size() < infect_sz) {
      inflect_vertexes = infect;
      infect_sz = infect.size();
    }
  }
}
