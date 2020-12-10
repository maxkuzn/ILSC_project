#pragma once

#include "graph.h"
#include <stdexcept>

template<typename NodeT, NodeT _NotNullNode = NodeT{1}, NodeT _NullNode = NodeT{0}>
class FlattenAdjacencyMatrix : public Graph {
 public:
  FlattenAdjacencyMatrix(size_t size)
    : size_(size)
    , mat_(size * size, _NullNode)
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
    mat_[from * size_ + to] = _NotNullNode;
  }

  void remove_edge(size_t from, size_t to) override {
    mat_[from * size_ + to] = _NullNode;
  }

 private:
  const size_t size_;
  std::vector<NodeT> mat_;
};

