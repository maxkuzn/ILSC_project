#include "gtest/gtest.h"

#include <graph/paths_counts.h>
#include <graph/adjacency_matrix.h>
#include <graph/flatten_adjacency_matrix.h>

#include <vector>

template <typename T>
class PathCountsTest : public testing::Test {
};

using GraphImplementations = ::testing::Types<
  AdjacencyMatrix<std::uint8_t>,
  FlattenAdjacencyMatrix<bool>
>;

TYPED_TEST_SUITE(PathCountsTest, GraphImplementations,);

using Matrix2d = std::vector<std::vector<std::uint32_t>>;

// Helper function to test equality of all edges
template<typename GraphT>
void ASSERT_GRAPH_EQ(const GraphT& graph, size_t n_nodes, const Matrix2d& target_matrix){
  ASSERT_EQ( graph.size(), n_nodes );
  ASSERT_EQ( graph.size(), target_matrix.size() );
  ASSERT_EQ( graph.size(), target_matrix[0].size() );

  for (size_t row_idx = 0; row_idx < n_nodes; ++row_idx) {
    for (size_t col_idx = 0; col_idx < n_nodes; ++col_idx) {
      ASSERT_EQ( graph(row_idx, col_idx), target_matrix[row_idx][col_idx] );
    }
  }
};

TYPED_TEST(PathCountsTest, Naive) {
  using GraphImplementation = TypeParam;
  /*
   *  1 0 1 0            
   *  1 0 1 1     
   *  0 1 0 1
   *  0 0 0 0
   */
  const size_t N_NODES = 4;
  auto graph = GraphImplementation{ N_NODES };
  graph.add_edge(0, 0);
  graph.add_edge(0, 2);
  graph.add_edge(1, 0);
  graph.add_edge(1, 2);
  graph.add_edge(1, 3);
  graph.add_edge(2, 1);
  graph.add_edge(2, 3);

  //  Number of paths of exactly 3 jumps:
  auto path_len = 3;
  Matrix2d target = {
    {2, 1, 2, 2},
    {2, 1, 2, 2},
    {1, 1, 1, 1},
    {0, 0, 0, 0}
  };
  ASSERT_GRAPH_EQ( count_paths_of_len(graph, path_len), N_NODES, target );
}
