#pragma once

#include "graph.h"
#include <stdexcept>

template<typename EdgeT, EdgeT NullEdge_ = EdgeT{0}>
class AdjacencyMatrix : public Graph<EdgeT> {
 public:
  AdjacencyMatrix(size_t size)
    : mat_(size, std::vector<EdgeT>(size, NullEdge_))
  {
  }

  virtual ~AdjacencyMatrix() = default;


  size_t size() const override {
    return mat_.size();
  }

  bool has_edge(size_t from, size_t to) const override {
    return mat_[from][to] != NullEdge_;
  }

  EdgeT operator()(size_t from, size_t to) const override {
    return mat_[from][to];
  }

  void add_edge(size_t from, size_t to, EdgeT weight = EdgeT{1}) override {
    mat_[from][to] = weight;
  }

  void remove_edge(size_t from, size_t to) override {
    mat_[from][to] = NullEdge_;
  }

 private:
  std::vector<std::vector<EdgeT>> mat_;
};
