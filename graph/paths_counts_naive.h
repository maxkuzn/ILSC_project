#pragma once

#include <vector>

// NOTE(laralex): The output graph has the same base type (like AdjacencyMatrix),
// but a different Edge type (since we count number of paths, it's an integer)
template<typename GraphT>
GraphT count_paths_of_len(const GraphT& graph, size_t path_len) {

  auto buffer_1 = GraphT(graph.size());
  auto buffer_2 = decltype(buffer_1)(graph.size());
  for (size_t a = 0; a < graph.size(); ++a){
    for (size_t b = 0; b < graph.size(); ++b) {
      if (graph.has_edge(a, b)) {
        buffer_1.add_edge(a, b, 1);
      }
    }
  }
  auto result = path_len % 2 == 1 ? decltype(buffer_1)(buffer_1) : decltype(buffer_1)(graph.size());
  path_len /= 2;

  // O(logP) power calculation
  bool is_previous_buffer_1 = true;
  while (path_len > 0){
    auto& previous_buffer = is_previous_buffer_1 ? buffer_1 : buffer_2;
    auto& updated_buffer = is_previous_buffer_1 ? buffer_2 : buffer_1;

    // find updated_buffer = previous_buffer ** 2
    for (size_t i = 0; i < previous_buffer.size(); ++i){
      for (size_t j = 0; j < previous_buffer.size(); ++j) {
        std::uint32_t edge_weight = 0;
        for (size_t k = 0; k < previous_buffer.size(); ++k) {
          edge_weight += previous_buffer(i, k) * previous_buffer(k, j);
        }
        updated_buffer.add_edge(i, j, edge_weight);
      }
    }

    // add updated_buffer to result
    std::vector<std::uint32_t> tmp_col(result.size());
    if (path_len % 2 == 1) {
      for (size_t j = 0; j < updated_buffer.size(); ++j) {
        for (size_t i = 0; i < updated_buffer.size(); ++i){
          tmp_col[i] = 0;
          for (size_t k = 0; k < updated_buffer.size(); ++k) {
            tmp_col[i] += updated_buffer(i, k) * result(k, j);
          }
        }
        for (size_t i = 0; i < updated_buffer.size(); ++i) {
          result.add_edge(i, j, tmp_col[i]);
        }
      }
    }

    path_len /= 2;
    is_previous_buffer_1 ^= 1; // invert bool
  }
  return result;
}

