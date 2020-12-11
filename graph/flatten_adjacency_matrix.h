#pragma once

#include "graph.h"

template<typename EdgeT>
class FlattenAdjacencyMatrix : public Graph<EdgeT> {
 public:
  constexpr static EdgeT null_edge_value = EdgeT{0};

  FlattenAdjacencyMatrix(size_t size)
    : size_(size)
    , mat_(size * size, null_edge_value)
  {
  }

  ~FlattenAdjacencyMatrix() = default;


  size_t size() const override {
    return size_;
  }

  bool has_edge(size_t from, size_t to) const override {
    return mat_[from * size_ + to] != null_edge_value;
  }

  EdgeT operator()(size_t from, size_t to) const override {
    return mat_[from * size_ + to];
  }

  void add_edge(size_t from, size_t to, EdgeT weight = EdgeT{1}) override {
    mat_[from * size_ + to] = weight;
  }

  void remove_edge(size_t from, size_t to) override {
    mat_[from * size_ + to] = null_edge_value;
  }

 private:
  const size_t size_;
  std::vector<EdgeT> mat_;
};

