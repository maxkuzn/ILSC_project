#pragma once

#include "adjacency_matrix.h"

template<typename EdgeT>
AdjacencyMatrix<std::uint32_t> find_all_paths_counts(const AdjacencyMatrix<EdgeT>& graph, size_t path_len) {
    return AdjacencyMatrix<std::uint32_t>(graph.size());
}