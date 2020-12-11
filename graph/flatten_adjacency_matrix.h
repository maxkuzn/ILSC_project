#pragma once

#include "graph.h"

template<typename EdgeT, EdgeT NullEdge_ = EdgeT{0}>
class FlattenAdjacencyMatrix : public Graph<EdgeT> {
 public:
  FlattenAdjacencyMatrix(size_t size)
    : size_(size)
    , mat_(size * size, NullEdge_)
  {
  }

  ~FlattenAdjacencyMatrix() = default;


  size_t size() const override {
    return size_;
  }

  bool has_edge(size_t from, size_t to) const override {
    return mat_[from * size_ + to] != NullEdge_;
  }

  EdgeT operator()(size_t from, size_t to) const override {
    return mat_[from * size_ + to];
  }

  void add_edge(size_t from, size_t to, EdgeT weight = EdgeT{1}) override {
    mat_[from * size_ + to] = weight;
  }

  void remove_edge(size_t from, size_t to) override {
    mat_[from * size_ + to] = NullEdge_;
  }

 private:
  const size_t size_;
  std::vector<EdgeT> mat_;
};

