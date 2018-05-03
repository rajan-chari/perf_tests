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

auto empty_struct_ret = struct_fun<status, good_return_status>;
BENCHMARK(empty_struct_ret);

auto filled_struct_ret = struct_fun<status, bad_return_status>;
BENCHMARK(filled_struct_ret);

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

auto ext_struct_alloc_good = ext_struct_alloc<ds_rank_good>;
BENCHMARK(ext_struct_alloc_good);

auto ext_struct_alloc_bad = ext_struct_alloc<ds_rank_bad>;
BENCHMARK(ext_struct_alloc_bad);
