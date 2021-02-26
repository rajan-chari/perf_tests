#include <memory>
#include <benchmark/benchmark.h>

using namespace std;

const size_t OPS = 1024*32;

int test_fn(int8_t* data, size_t data_sz)
{
  // Number of ops = data_sz
  // iter = OPS / data_sz

  size_t iter = OPS/data_sz;

  for(int k = 0; k < iter; ++k)
  {
    for(size_t i = 0; i < data_sz; ++i)
    {
      data[i] = i%256;
    }

    for(size_t i = 0; i < data_sz; ++i)
    {
      data[i] = data[i]-1;
    }
  }

  return 1;
}

template<int SZ,int FN(int8_t* data, size_t data_sz)>
static void mem_test(benchmark::State& state)
{
  int ret;
  int8_t data[SZ];

  for (auto _ : state)
  {
    benchmark::DoNotOptimize(ret = FN(data, SZ));
  }
}

//auto mem_perf_4 = mem_test<4,test_fn>;
//auto mem_perf_8 = mem_test<8,test_fn>;
//auto mem_perf_16 = mem_test<16,test_fn>;
//auto mem_perf_32 = mem_test<32,test_fn>;
//auto mem_perf_64 = mem_test<64,test_fn>;
//auto mem_perf_128 = mem_test<128,test_fn>;
//auto mem_perf_256 = mem_test<256,test_fn>;
//auto mem_perf_512 = mem_test<512,test_fn>;
auto mem_perf_1024 = mem_test<1024,test_fn>;
auto mem_perf_2048 = mem_test<2048,test_fn>;
auto mem_perf_4096 = mem_test<4096,test_fn>;
auto mem_perf_8192 = mem_test<8192,test_fn>;

//BENCHMARK(mem_perf_4);
//BENCHMARK(mem_perf_8);
//BENCHMARK(mem_perf_16);
//BENCHMARK(mem_perf_32);
//BENCHMARK(mem_perf_64);
//BENCHMARK(mem_perf_128);
//BENCHMARK(mem_perf_256);
//BENCHMARK(mem_perf_512);
BENCHMARK(mem_perf_1024);
BENCHMARK(mem_perf_2048);
BENCHMARK(mem_perf_4096);
BENCHMARK(mem_perf_8192);
