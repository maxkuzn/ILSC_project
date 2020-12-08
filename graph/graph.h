#pragma once

#include <vector>


template <class Derived>
class Graph {
 public:
  virtual ~Graph() = default;


  virtual size_t size() const = 0;

  virtual bool has_edge(size_t from, size_t to) const = 0;
  bool operator()(size_t from, size_t to) const {
    return this->has_edge(from, to);
  }

  virtual void add_edge(size_t from, size_t to) = 0;
  virtual void remove_edge(size_t from, size_t to) = 0;

  virtual Derived find_paths_with_length(size_t max_len) const = 0;
};

