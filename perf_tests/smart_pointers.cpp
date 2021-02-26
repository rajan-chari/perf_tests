#include <memory>
#include <benchmark/benchmark.h>

using namespace std;

struct a {int x;};

struct b
{
  b():x(0) {}
  int x;
};

template<typename S>
int new_empty_struct_fn()
{
  S* s = new S();
  benchmark::DoNotOptimize(s);
  delete s;
  return 1;
}

int make_shared_empty_struct_fn()
{
  shared_ptr<a> s = make_shared<a>();
  benchmark::DoNotOptimize(s);
  return 1;
}

int shared_empty_struct_fn()
{
  shared_ptr<a> s = shared_ptr<a>(new a());
  benchmark::DoNotOptimize(s);
  return 1;
}

int unique_ptr_empty_struct_fn()
{
  unique_ptr<a> s = unique_ptr<a>(new a());
  benchmark::DoNotOptimize(s);
  return 1;
}

template<int FN()>
static void ptr_test(benchmark::State& state)
{
  int ret;
  for (auto _ : state)
  {
    benchmark::DoNotOptimize(ret = FN());
    benchmark::ClobberMemory();
  }
}

//auto struct_shared_perf = ptr_test<shared_empty_struct_fn>;
//BENCHMARK(struct_shared_perf);
//auto struct_make_shared_perf = ptr_test<make_shared_empty_struct_fn>;
//BENCHMARK(struct_make_shared_perf);
//auto struct_unique_perf = ptr_test<unique_ptr_empty_struct_fn>;
//BENCHMARK(struct_unique_perf);
//auto struct_new_perf = ptr_test<new_empty_struct_fn>;
//BENCHMARK(struct_new_perf);
