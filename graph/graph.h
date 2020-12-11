#pragma once

#include <vector>

template<typename EdgeT>
class Graph {
 public:
  virtual ~Graph() = default;

  virtual size_t size() const = 0;

  virtual bool has_edge(size_t from, size_t to) const = 0;
  virtual EdgeT operator()(size_t from, size_t to) const = 0;

  virtual void add_edge(size_t from, size_t to, EdgeT weight = EdgeT{1}) = 0;
  virtual void remove_edge(size_t from, size_t to) = 0;
};

