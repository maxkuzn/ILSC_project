#pragma once

#include "graph.h"
#include <stdexcept>

class AdjacencyMatrix : public Graph<AdjacencyMatrix> {
 public:
  AdjacencyMatrix(size_t size);

  virtual ~AdjacencyMatrix() = default;


  size_t size() const override {
    return mat_.size();
  }

  bool has_edge(size_t from, size_t to) const override {
    return mat_[from][to];
  }

  void add_edge(size_t from, size_t to) override {
    mat_[from][to] = true;
  }

  void remove_edge(size_t from, size_t to) override {
    mat_[from][to] = false;
  }

  AdjacencyMatrix find_paths_with_length(size_t /*max_len*/) const override {
    throw std::runtime_error("Not implemented");
  }

 private:
  std::vector<std::vector<bool>> mat_;
};

// Some errors occurs in MacOS if we define constructor inline in the class
inline AdjacencyMatrix::AdjacencyMatrix(size_t size)
  : mat_(size, std::vector<bool>(size, false))
{
}

