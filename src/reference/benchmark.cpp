#include "src/implementation.hpp"
#include "src/reference/implementation.hpp"

#include "benchmark/benchmark.h"

/***************************************************************/
// Templated Benchmark to compare both challenge and reference
template <int (*T)(std::string_view, std::string_view)>
void BM_LongestCommonSequence(benchmark::State &state)
{
    std::string input(state.range(0), 'A');
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(T(input, input));
    }
    state.SetComplexityN(state.range(0));
}

/***************************************************************/
BENCHMARK_TEMPLATE(BM_LongestCommonSequence, &challenge::get_length_of_longest_common_sequence)->RangeMultiplier(2)->Range(1 << 0, 1 << 12)->Complexity();
BENCHMARK_TEMPLATE(BM_LongestCommonSequence, &reference::get_length_of_longest_common_sequence)->RangeMultiplier(2)->Range(1 << 0, 1 << 12)->Complexity();

// Run the benchmark
BENCHMARK_MAIN();