#pragma once

#include "graph.h"
#include <stdexcept>

template<typename EdgeT>
class AdjacencyMatrix : public Graph<EdgeT> {
 public:
  constexpr static EdgeT null_edge_value = EdgeT{0};

  AdjacencyMatrix(size_t size)
    : mat_(size, std::vector<EdgeT>(size, null_edge_value))
  {
  }

  virtual ~AdjacencyMatrix() = default;


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
