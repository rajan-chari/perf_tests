#include <stdexcept>
#include <benchmark/benchmark.h>

template<typename R, R r>
R ex_fun() {  throw r; }

template<typename R, R r>
R ret_fun() {  return r; }

using namespace std;

string s_ret_fun() { return "this is a return val"; }
string s_throw_fun() { throw string("this is a return val"); }

template <typename R, R FN()>
static void ex_handler_fun(benchmark::State& state)
{
  R retval;

  for (auto _ : state)
  {
    try { benchmark::DoNotOptimize(FN()); }
    catch (const R& val) {}
  }
}

template <typename R, R FN()>
static void ret_handler_fun(benchmark::State& state)
{
  R retval;

  for (auto _ : state)
  {
    benchmark::DoNotOptimize(retval = FN());
  }
}

struct result
{
  int val;
  string msg;
};

auto function_returning_int = ret_handler_fun<int, ret_fun<int, 1>>;
BENCHMARK(function_returning_int);

auto function_throwing_int = ex_handler_fun<int, ex_fun<int, 1>>;
BENCHMARK(function_throwing_int);

auto throwing_function_returning_int = ex_handler_fun<int, ret_fun<int, 1>>;
BENCHMARK(throwing_function_returning_int);

auto function_returning_string = ret_handler_fun<string, s_ret_fun>;
BENCHMARK(function_returning_string);

auto function_throwing_string = ex_handler_fun<string, s_throw_fun>;
BENCHMARK(function_throwing_string);

auto throwing_function_returning_string = ex_handler_fun<string, s_ret_fun>;
BENCHMARK(throwing_function_returning_string);

