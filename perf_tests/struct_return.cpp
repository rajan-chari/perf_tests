#include <benchmark/benchmark.h>

using namespace std;

struct status
{
  int err_code;
  string err_msg;
};

static status good = {0,""};
status good_return_status()
{
  return good;
}

status bad_return_status()
{
  status s = {1,"This is an error"};
  return s;
}

template<typename R, R FN()>
static void struct_fun(benchmark::State& state)
{
  status s;
  for (auto _ : state)
  {
    benchmark::DoNotOptimize(s = FN());
  }
}

auto return_empty_struct = struct_fun<status, good_return_status>;
BENCHMARK(return_empty_struct);

auto return_filled_struct = struct_fun<status, bad_return_status>;
BENCHMARK(return_filled_struct);

int ds_rank_good(status* ret)
{
  return 1;
}

int ds_rank_bad(status* ret)
{
  if (ret != nullptr)
  {
    ret->err_code = 1;
    ret->err_msg = "This is an error";
  }

  return 1;
}

template<int FN(status*)>
static void ext_struct_alloc(benchmark::State& state)
{
  status s;
  int ret;
  for (auto _ : state)
  {
    benchmark::DoNotOptimize(ret = FN(&s));
  }
}

auto external_struct_alloc_return_normal = ext_struct_alloc<ds_rank_good>;
BENCHMARK(external_struct_alloc_return_normal);

auto external_struct_alloc_return_error = ext_struct_alloc<ds_rank_bad>;
BENCHMARK(external_struct_alloc_return_error);
