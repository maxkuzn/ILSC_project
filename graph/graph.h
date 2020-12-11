#pragma once

#include <vector>

template<typename EdgeT>
class Graph {
 public:
  virtual ~Graph() = default;

  virtual size_t size() const = 0;

  virtual bool has_edge(size_t from, size_t to) const = 0;
  virtual EdgeT operator()(size_t from, size_t to) const = 0;

  template<typename GraphT>
  bool operator==(const GraphT& other) const {
    if (this->size() != other.size()) { 
      return false; 
    }
    for (size_t a = 0; a != this->size(); ++a) {
      for (size_t b = 0; b != this->size(); ++b) {
        bool has_edge = this->has_edge(a, b); 
        if (has_edge != other.has_edge(a, b) || ( has_edge && (*this)(a, b) != other(a, b) )) {
          return false;
        }
      }
    }
    return true;
  }

  virtual void add_edge(size_t from, size_t to, EdgeT weight = EdgeT{1}) = 0;
  virtual void remove_edge(size_t from, size_t to) = 0;
};

