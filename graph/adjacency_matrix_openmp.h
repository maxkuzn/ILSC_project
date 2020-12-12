#pragma once

#include "graph_openmp.h"
#include <type_traits>

class AdjacencyMatrixOpenMP : public GraphOpenMP {
 public:
  AdjacencyMatrixOpenMP(size_t size)
    : mat_(size, std::vector<EdgeT>(size, null_edge_value))
  {
  }

  AdjacencyMatrixOpenMP(const Graph& other)
    : mat_(other.size(), std::vector<EdgeT>(other.size(), null_edge_value))
  {
    for (size_t from = 0; from < other.size(); ++from) {
      for (size_t to = 0; to < other.size(); ++to) {
        if (other.has_edge(from, to)) {
          mat_[from][to] = other(from, to);
        }
      }
    }
  }

  virtual ~AdjacencyMatrixOpenMP() = default;


  size_t size() const override {
    return mat_.size();
  }

  bool has_edge(size_t from, size_t to) const override {
    return mat_[from][to] != null_edge_value;
  }

  EdgeT operator()(size_t from, size_t to) const override {
    return mat_[from][to];
  }

  void add_edge(size_t from, size_t to, EdgeT weight = EdgeT{1}) override {
    mat_[from][to] = weight;
  }

  void remove_edge(size_t from, size_t to) override {
    mat_[from][to] = null_edge_value;
  }

 private:
  std::vector<std::vector<EdgeT>> mat_;
};
