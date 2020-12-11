#pragma once

// NOTE(laralex): The output graph has the same base type (like AdjacencyMatrix),
// but a different Edge type (since we count number of paths, it's an integer)
template<template<typename> typename GraphT, typename EdgeT>
GraphT<std::uint32_t> count_paths_of_len(const GraphT<EdgeT>& graph, size_t path_len) {
  auto edges_flags = GraphT<std::uint32_t>(graph.size());
  for (size_t a = 0; a < graph.size(); ++a){
    for (size_t b = 0; b < graph.size(); ++b) {
      if (graph.has_edge(a, b)) {
        edges_flags.add_edge(a, b, 1);
      }
    }
  }

  // naive O(N) multiplication with plenty of hacks to make it work
  auto result = decltype(edges_flags)(edges_flags);
  for (size_t p = 0; p < path_len - 1; ++p){
    auto result_copy = decltype(result)(result);
    for (size_t i = 0; i < result.size(); ++i){
      for (size_t j = 0; j < result.size(); ++j) {
        result.remove_edge(i, j);
        for (size_t k = 0; k < result.size(); ++k) {
          result.add_edge(i, j, result(i, j) + result_copy(i, k) * edges_flags(k, j));
        }
      }
    }
    
  }
//  std::cout << result(0, 0) << " " << result(0, 1) << " " << result(0, 2) << " " << result(0, 3) << std::endl;
  return result;
}
