#include "gtest/gtest.h"

#include <graph/adjacency_matrix.h>
#include <graph/flatten_adjacency_matrix.h>
#include <graph/paths_counts.h>

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

TYPED_TEST(PathCountsTest, Naive) {
  using GraphImplementation = TypeParam;
  /* INPUT
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

  {
    /* Number of paths of exactly 3 jumps:
    *  2 1 2 2            
    *  2 1 2 2     
    *  1 1 1 1
    *  0 0 0 0
    */
    size_t path_len = 3;
    auto paths_counts = count_paths_of_len(graph, path_len);
    auto expected_paths_counts = decltype(paths_counts){ N_NODES };
    expected_paths_counts.add_edge(0,0,2);
    expected_paths_counts.add_edge(0,1,1);
    expected_paths_counts.add_edge(0,2,2);
    expected_paths_counts.add_edge(0,3,2);

    expected_paths_counts.add_edge(1,0,2);
    expected_paths_counts.add_edge(1,1,1);
    expected_paths_counts.add_edge(1,2,2);
    expected_paths_counts.add_edge(1,3,2);

    expected_paths_counts.add_edge(2,0,1);
    expected_paths_counts.add_edge(2,1,1);
    expected_paths_counts.add_edge(2,2,1);
    expected_paths_counts.add_edge(2,3,1);

    ASSERT_TRUE(  paths_counts == expected_paths_counts );
  }
  
    {
    /* Number of paths of exactly 3 jumps:
    *  2 1 2 2            
    *  2 1 2 2     
    *  1 1 1 1
    *  0 0 0 0
    */
    size_t path_len = 11;
    auto paths_counts = count_paths_of_len(graph, path_len);
    auto expected_paths_counts = decltype(paths_counts){ N_NODES };
    expected_paths_counts.add_edge(0,0,89);
    expected_paths_counts.add_edge(0,1,55);
    expected_paths_counts.add_edge(0,2,89);
    expected_paths_counts.add_edge(0,3,89);

    expected_paths_counts.add_edge(1,0,89);
    expected_paths_counts.add_edge(1,1,55);
    expected_paths_counts.add_edge(1,2,89);
    expected_paths_counts.add_edge(1,3,89);

    expected_paths_counts.add_edge(2,0,55);
    expected_paths_counts.add_edge(2,1,34);
    expected_paths_counts.add_edge(2,2,55);
    expected_paths_counts.add_edge(2,3,55);

    ASSERT_TRUE(  paths_counts == expected_paths_counts );
  }

}
