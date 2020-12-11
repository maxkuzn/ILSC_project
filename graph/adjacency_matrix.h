#pragma once

#include "graph.h"
#include <stdexcept>

template<typename EdgeT, EdgeT _NotNullNode = EdgeT{1}, EdgeT _NullNode = EdgeT{0}>
class AdjacencyMatrix : public Graph {
 public:
  AdjacencyMatrix(size_t size)
    : mat_(size, std::vector<EdgeT>(size, _NullNode))
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
    mat_[from][to] = _NotNullNode;
  }

  void remove_edge(size_t from, size_t to) override {
    mat_[from][to] = _NullNode;
  }

 private:
  std::vector<std::vector<EdgeT>> mat_;
};
