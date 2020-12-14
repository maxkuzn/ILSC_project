#include <benchmark/benchmark.h>

#include <graph/graph.h>

#include <graph/adjacency_matrix.h>
#include <graph/flatten_adjacency_matrix.h>
#include <graph/adjacency_matrix_openmp.h>
#include <graph/flatten_adjacency_matrix_openmp.h>

#include <graph/paths_counts.h>
#include <graph/graph_generation.h>

template <typename GraphT>
static void BM_FindPaths(benchmark::State& state) {
  size_t size = state.range(0);
  size_t len = state.range(1);
  auto graph = generate_bidirectional_cycle<GraphT>(size);
  for (auto _ : state) {
    benchmark::DoNotOptimize(count_paths_of_len(graph, len));
  }
}

static void Arguments(benchmark::internal::Benchmark* b) {
  std::vector<long> sizes { 16, 64, 256, 512 };
  for (auto size : sizes) {
    b->Args({size, 4});
    b->Args({size, 16});
    b->Args({size, 128});
  }
}

BENCHMARK_TEMPLATE(BM_FindPaths, AdjacencyMatrix)
  ->Apply(Arguments)
  ->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_FindPaths, FlattenAdjacencyMatrix)
  ->Apply(Arguments)
  ->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_FindPaths, AdjacencyMatrixOpenMP)
  ->Apply(Arguments)
  ->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_FindPaths, FlattenAdjacencyMatrixOpenMP)
  ->Apply(Arguments)
  ->Unit(benchmark::kMillisecond);

// Run the benchmark
BENCHMARK_MAIN();

