// Copyright 2019 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <algorithm>
#include <cmath>
#include <functional>
#include <random>
#include <vector>

#include <benchmark/benchmark.h>
#include "bench/utils.h"
#include <xnnpack/AlignedAllocator.h>
#include <xnnpack/common.h>
#include <xnnpack/params.h>
#include <xnnpack/vunary.h>


static void f32_sigmoid(
  benchmark::State& state,
  xnn_f32_vunary_ukernel_function sigmoid)
{
  const size_t elements = state.range(0);

  std::random_device random_device;
  auto rng = std::mt19937(random_device());
  auto f32rng = std::bind(std::uniform_real_distribution<float>(-10.0f, 10.0f), rng);

  std::vector<float, AlignedAllocator<float, 64>> x(elements);
  std::vector<float, AlignedAllocator<float, 64>> y(elements);
  std::generate(x.begin(), x.end(), std::ref(f32rng));
  std::fill(y.begin(), y.end(), std::nanf(""));

  for (auto _ : state) {
    sigmoid(elements * sizeof(float), x.data(), y.data(), nullptr /* params */);
  }

  state.counters["Freq"] = benchmark::utils::GetCurrentCpuFrequency();

  const size_t elements_per_iteration = elements;
  state.counters["elements"] =
    benchmark::Counter(uint64_t(state.iterations()) * elements_per_iteration, benchmark::Counter::kIsRate);

  const size_t bytes_per_iteration = 2 * elements * sizeof(float);
  state.counters["bytes"] =
    benchmark::Counter(uint64_t(state.iterations()) * bytes_per_iteration, benchmark::Counter::kIsRate);
}

#if XNN_ARCH_ARM || XNN_ARCH_ARM64
  BENCHMARK_CAPTURE(f32_sigmoid, neon_frac_p9_p10_nr1recps_x16, xnn_f32_sigmoid_ukernel__neon_frac_p9_p10_nr1recps_x16)
    ->RangeMultiplier(10)
    ->Range(1000, 1000000)
    ->UseRealTime();
  BENCHMARK_CAPTURE(f32_sigmoid, neonfma_p5_nr2fma_x16, xnn_f32_sigmoid_ukernel__neonfma_p5_nr2fma_x16)
    ->RangeMultiplier(10)
    ->Range(1000, 1000000)
    ->UseRealTime();
#endif  // XNN_ARCH_ARM || XNN_ARCH_ARM64

#if XNN_ARCH_X86 || XNN_ARCH_X86_64
  BENCHMARK_CAPTURE(f32_sigmoid, sse2_p5_div_x8, xnn_f32_sigmoid_ukernel__sse2_p5_div_x8)
    ->RangeMultiplier(10)
    ->Range(1000, 1000000)
    ->UseRealTime();
  BENCHMARK_CAPTURE(f32_sigmoid, sse2_p5_div_x16, xnn_f32_sigmoid_ukernel__sse2_p5_div_x16)
    ->RangeMultiplier(10)
    ->Range(1000, 1000000)
    ->UseRealTime();
  BENCHMARK_CAPTURE(f32_sigmoid, sse41_p5_div_x8, xnn_f32_sigmoid_ukernel__sse41_p5_div_x8)
    ->RangeMultiplier(10)
    ->Range(1000, 1000000)
    ->UseRealTime();
  BENCHMARK_CAPTURE(f32_sigmoid, sse41_p5_div_x16, xnn_f32_sigmoid_ukernel__sse41_p5_div_x16)
    ->RangeMultiplier(10)
    ->Range(1000, 1000000)
    ->UseRealTime();
#endif  // XNN_ARCH_X86 || XNN_ARCH_X86_64

#ifndef XNNPACK_BENCHMARK_NO_MAIN
BENCHMARK_MAIN();
#endif