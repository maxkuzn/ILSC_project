#pragma once

#include "adjacency_matrix.h"

AdjacencyMatrix find_all_paths_counts(const AdjacencyMatrix& graph, size_t /*max_len*/) {
    return AdjacencyMatrix(graph.size());
}