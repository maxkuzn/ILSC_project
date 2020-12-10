#pragma once

#include "adjacency_matrix.h"

template<typename NodeT>
AdjacencyMatrix<std::uint32_t> find_all_paths_counts(const AdjacencyMatrix<NodeT>& graph, size_t /*max_len*/) {
    return AdjacencyMatrix<std::uint32_t>(graph.size());
}