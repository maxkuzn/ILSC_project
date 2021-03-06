#include "gtest/gtest.h"

#include <graph/adjacency_matrix.h>
#include <graph/flatten_adjacency_matrix.h>
#include <graph/adjacency_matrix_openmp.h>
#include <graph/flatten_adjacency_matrix_openmp.h>


template <typename T>
class GraphTest : public testing::Test {
};

using GraphImplementations = ::testing::Types<
  AdjacencyMatrix,
  FlattenAdjacencyMatrix,
  AdjacencyMatrixOpenMP,
  FlattenAdjacencyMatrixOpenMP
>;
TYPED_TEST_SUITE(GraphTest, GraphImplementations,);


TYPED_TEST(GraphTest, Constructor) {
  using GraphImplementation = TypeParam;

  size_t size = 5;
  GraphImplementation graph(size);
  ASSERT_EQ(graph.size(), size);
}

TYPED_TEST(GraphTest, AddEdge) {
  using GraphImplementation = TypeParam;

  GraphImplementation graph(5);

  for (size_t i = 0; i != graph.size(); ++i) {
    for (size_t j = 0; j != graph.size(); ++j) {
      ASSERT_FALSE(graph.has_edge(i, j));
      ASSERT_FALSE(graph(i, j));
    }
  }

  size_t from = 1;
  size_t to = 3;
  graph.add_edge(from, to);

  for (size_t i = 0; i != graph.size(); ++i) {
    for (size_t j = 0; j != graph.size(); ++j) {
      if (i == from && j == to) {
        ASSERT_TRUE(graph.has_edge(i, j));
        ASSERT_TRUE(graph(i, j));
      } else {
        ASSERT_FALSE(graph.has_edge(i, j));
        ASSERT_FALSE(graph(i, j));
      }
    }
  }
}

TYPED_TEST(GraphTest, OperatorEquals) {
  using GraphImplementation = TypeParam;

  GraphImplementation lhs5(5), rhs4(4);
  ASSERT_FALSE(lhs5 == rhs4);

  GraphImplementation rhs5(5);
  ASSERT_TRUE(lhs5 == rhs5);

  lhs5.add_edge(0, 0, 100);
  lhs5.add_edge(1, 4, 101);
  lhs5.add_edge(4, 5, 102);
  ASSERT_FALSE(lhs5 == rhs5);

  rhs5.add_edge(0, 0, 100);
  rhs5.add_edge(1, 4, 101);
  rhs5.add_edge(4, 5, 102);
  ASSERT_TRUE(lhs5 == rhs5);

  // check against not-equal weights
  rhs5.remove_edge(0, 0);
  rhs5.add_edge(0, 0, 10000);
  ASSERT_FALSE(lhs5 == rhs5);
}

TYPED_TEST(GraphTest, FromGraphConstructor) {
  using GraphImplementation = TypeParam;

  size_t n_nodes = 5;
  GraphImplementation graph(n_nodes);

  graph.add_edge(0, 0, 100);
  graph.add_edge(1, 4, 101);
  graph.add_edge(4, 5, 102);

  GraphImplementation copy_graph(graph);
  ASSERT_TRUE(graph == copy_graph);

  AdjacencyMatrix other_type_graph(graph);
  ASSERT_TRUE(graph == other_type_graph);

  graph.remove_edge(0, 0);
  ASSERT_FALSE(graph == copy_graph);
  ASSERT_FALSE(graph == other_type_graph);
}

