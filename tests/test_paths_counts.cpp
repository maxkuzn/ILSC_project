#include "gtest/gtest.h"

#include <graph/paths_counts.h>
#include <graph/graph_generation.h>

TEST(AllPathsCounts, AdjacencyMatrixNaive) {
  auto n_nodes = 10;
  auto graph = generate_binary_tree<AdjacencyMatrix>(n_nodes);
  auto max_path_len = 5;
  auto counts_matrix = find_all_paths_counts(graph, max_path_len);
}
