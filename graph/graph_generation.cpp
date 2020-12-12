#include "graph_generation.h"
#include "graph.h"

#include <random>

void fill_random(Graph& graph, double prob) {
  static std::mt19937 gen(2038);
  std::uniform_real_distribution<double> dist(0.0, 1.0);
  for (size_t i = 0; i != graph.size(); ++i) {
    for (size_t j = 0; j != graph.size(); ++j) {
      if (dist(gen) < prob) {
        graph.add_edge(i, j);
      }
    }
  }
}

void fill_complete(Graph& graph) {
  for (size_t i = 0; i != graph.size(); ++i) {
    for (size_t j = 0; j != graph.size(); ++j) {
      graph.add_edge(i, j);
    }
  }
}

void fill_cycle(Graph& graph) {
  graph.add_edge(graph.size() - 1, 0);
  for (size_t i = 0; i + 1 < graph.size(); ++i) {
    graph.add_edge(i, i + 1);
  }
}

void fill_bidirectional_cycle(Graph& graph) {
  graph.add_edge(graph.size() - 1, 0);
  graph.add_edge(0, graph.size() - 1);
  for (size_t i = 0; i + 1 < graph.size(); ++i) {
    graph.add_edge(i, i + 1);
    graph.add_edge(i + 1, i);
  }
}

void fill_binary_tree(Graph& graph) {
  for (size_t i = 0; i != graph.size(); ++i) {
    size_t left = 2 * i + 1;
    if (left >= graph.size()) {
      break;
    }
    graph.add_edge(i, left);
    graph.add_edge(left, i);
    size_t right = 2 * i + 2;
    if (right >= graph.size()) {
      break;
    }
    graph.add_edge(i, right);
    graph.add_edge(right, i);
  }
}


