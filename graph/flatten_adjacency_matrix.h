#pragma once

#include "graph.h"
#include <stdexcept>

class FlattenAdjacencyMatrix : public Graph {
 public:
  FlattenAdjacencyMatrix(size_t size)
    : size_(size)
    , mat_(size * size, false)
  {
  }

  ~FlattenAdjacencyMatrix() = default;


  size_t size() const override {
    return size_;
  }

  bool has_edge(size_t from, size_t to) const override {
    return mat_[from * size_ + to];
  }

  void add_edge(size_t from, size_t to) override {
    mat_[from * size_ + to] = true;
  }

  void remove_edge(size_t from, size_t to) override {
    mat_[from * size_ + to] = false;
  }

 private:
  const size_t size_;
  std::vector<bool> mat_;
};

