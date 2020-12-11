#include "gtest/gtest.h"

#include <graph/paths_counts.h>
#include <graph/graph_generation.h>

TEST(AllPathsCounts, AdjacencyMatrixNaive) {
  /*
   *  1 0 1 0            
   *  1 0 1 1     
   *  0 1 0 1
   *  0 0 0 0
   */
  const size_t N_NODES = 4;
  auto graph = AdjacencyMatrix<std::uint8_t>{ N_NODES };
  graph.add_edge(0, 0);
  graph.add_edge(0, 2);
  graph.add_edge(1, 0);
  graph.add_edge(1, 2);
  graph.add_edge(1, 3);
  graph.add_edge(2, 1);
  graph.add_edge(2, 3);

  //  Number of paths of exactly 3 jumps:
  auto path_len = 3;
  size_t target[][N_NODES] = {
    {2, 1, 2, 2},
    {2, 1, 2, 2},
    {1, 1, 1, 1},
    {0, 0, 0, 0}
  };
  auto counts_matrix = count_paths_of_len(graph, path_len);
  auto ASSERT_GRAPH_EQ = [](const auto& graph, const auto& target_matrix){
    for (size_t row_idx = 0; row_idx < N_NODES; ++row_idx) {
      for (size_t col_idx = 0; col_idx < N_NODES; ++col_idx) {
        ASSERT_EQ( graph(row_idx, col_idx), target_matrix[row_idx][col_idx] );
      }
    }
  };
  ASSERT_GRAPH_EQ( counts_matrix, target );
}
