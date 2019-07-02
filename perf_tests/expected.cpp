#include <stdexcept>
#include <benchmark/benchmark.h>

#include "../sub/expected/include/tl/expected.hpp"

tl::expected<int, int> get_int_expected()
{
  return 1;
}

tl::expected<int, int> get_int_expected_fail()
{
  return tl::make_unexpected(1);
}

int get_int(int &val)
{
  val = 1;
  return 0;
}

int get_int_fail(int &val)
{
  return 1;
}

int get_int_exception()
{
  return 1;
}

int get_int_exception_fail()
{
  throw 1;
}

static void copy_expected_success(benchmark::State &state)
{
  tl::expected<int, int> expected_value;
  int final_value;
  for (auto _ : state)
  {
    benchmark::DoNotOptimize(expected_value = get_int_expected());
    if (expected_value.has_value())
    {
      final_value = expected_value.value();
    }
    benchmark::ClobberMemory();
  }
}

static void copy_expected_fail(benchmark::State &state)
{
  tl::expected<int, int> expected_value;
  int final_value;

  for (auto _ : state)
  {

    benchmark::DoNotOptimize(expected_value = get_int_expected_fail());
    if (expected_value.has_value())
    {
      final_value = expected_value.value();
    }
    benchmark::ClobberMemory();
  }
}

static void expected_success(benchmark::State &state)
{
  int final_val;
  for (auto _ : state)
  {
    auto value = get_int_expected();
    if (value.has_value())
    {
      final_val = value.value();
    }
    benchmark::ClobberMemory();
  }
}

static void expected_fail(benchmark::State &state)
{
  int final_val;
  for (auto _ : state)
  {
    auto value = get_int_expected_fail();
    if (value.has_value())
    {
      final_val = value.value();
    }
    benchmark::ClobberMemory();
  }
}

static void int_success(benchmark::State &state)
{
  int output_value, final_value;

  for (auto _ : state)
  {
    benchmark::DoNotOptimize(final_value = get_int(output_value));
    benchmark::ClobberMemory();
  }
}

static void int_fail(benchmark::State &state)
{
  int output_value, final_value;

  for (auto _ : state)
  {
    benchmark::DoNotOptimize(final_value = get_int_fail(output_value));
    benchmark::ClobberMemory();
  }
}

static void exception_success(benchmark::State &state)
{
  int final_value;

  for (auto _ : state)
  {
    try
    {
      benchmark::DoNotOptimize(final_value = get_int_exception());
      benchmark::ClobberMemory();
    }
    catch (const int &val)
    {
    }
  }
}

static void exception_fail(benchmark::State &state)
{
  int final_value;

  for (auto _ : state)
  {
    try
    {
      benchmark::DoNotOptimize(final_value = get_int_exception_fail());
      benchmark::ClobberMemory();
    }
    catch (const int &val)
    {
    }
  }
}

BENCHMARK(expected_success);
BENCHMARK(expected_fail);
BENCHMARK(copy_expected_success);
BENCHMARK(copy_expected_fail);
BENCHMARK(int_success);
BENCHMARK(int_fail);
BENCHMARK(exception_success);
BENCHMARK(exception_fail);
