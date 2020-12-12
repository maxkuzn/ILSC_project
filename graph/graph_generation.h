#pragma once

#include "graph.h"
#include "graph_generation_impl.h"

// Creates a random graph with probability of each edge is equal to prob
void fill_random(Graph& graph, double prob);

template <class GraphImplementation>
GraphImplementation generate_random(size_t size, double prob) {
  GraphImplementation graph(size);
  fill_random(graph, prob);
  return graph;
}


// Creates a complete graph
void fill_complete(Graph& graph);

template <class GraphImplementation>
GraphImplementation generate_complete(size_t size) {
  GraphImplementation graph(size);
  fill_complete(graph);
  return graph;
}


// Create a cycle graph
// So each vertex (v) is connected to the next (v + 1) vertex
void fill_cycle(Graph& graph);

template <class GraphImplementation>
GraphImplementation generate_cycle(size_t size) {
  GraphImplementation graph(size);
  fill_cycle(graph);
  return graph;
}


// Create a bidirectional cycle graph
// So each vertex (v) is connected to the next (v + 1) and to the previous (v - 1)
// verteces
void fill_bidirectional_cycle(Graph& graph);

template <class GraphImplementation>
GraphImplementation generate_bidirectional_cycle(size_t size) {
  GraphImplementation graph(size);
  fill_bidirectional_cycle(graph);
  return graph;
}


// Create a bidirectional binary tree
void fill_binary_tree(Graph& graph);

template <class GraphImplementation>
GraphImplementation generate_binary_tree(size_t size) {
  GraphImplementation graph(size);
  fill_binary_tree(graph);
  return graph;
}

