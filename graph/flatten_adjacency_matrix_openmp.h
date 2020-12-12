#pragma once

#include "graph_openmp.h"

class FlattenAdjacencyMatrixOpenMP : public GraphOpenMP {
 public:
  constexpr static EdgeT null_edge_value = EdgeT{0};

  FlattenAdjacencyMatrixOpenMP(size_t size)
    : size_(size)
    , mat_(size * size, null_edge_value)
  {
  }

  FlattenAdjacencyMatrixOpenMP(const Graph& other)
    : size_(other.size())
    , mat_(other.size() * other.size(), null_edge_value)
  {
    for (size_t from = 0; from < other.size(); ++from) {
      for (size_t to = 0; to < other.size(); ++to) {
        if (other.has_edge(from, to)) {
          mat_[from * size_ + to] = other(from, to);
        }
      }
    }
  }

  ~FlattenAdjacencyMatrixOpenMP() = default;


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

