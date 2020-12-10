#pragma once

#include "graph.h"
#include <stdexcept>

class AdjacencyMatrix : public Graph {
 public:
  AdjacencyMatrix(size_t size)
    : mat_(size, std::vector<bool>(size, false))
  {
  }

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

 private:
  std::vector<std::vector<bool>> mat_;
};

