#include "gtest/gtest.h"

#include <graph/adjacency_matrix.h>
#include <graph/flatten_adjacency_matrix.h>


template <typename T>
class GraphTest : public testing::Test {
};

using GraphImplementations = ::testing::Types<
  AdjacencyMatrix<bool>,
  FlattenAdjacencyMatrix<bool>
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

