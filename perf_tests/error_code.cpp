#include <benchmark/benchmark.h>

#include <system_error>
#include <iostream>

constexpr int ERR_SUCCESS = 0;
constexpr int ERR_FAIL = 1;

#include "error_code_common.h"

std::string get_error_msg(int code)
{
    switch(code)
    {
        case 0:
            return "The operation succeeded.";
        case 1:
            return "The operation failed.";
        default:
            return "Unknown error code.";
    }
}

int function_that_can_fail_int(bool success, int& return_value)
{
    if(!success)
    {
        return ERR_FAIL;
    }

    return_value = 1;
    return ERR_SUCCESS;
}

std::string get_error_msg(error_code code)
{
    switch(code)
    {
        case error_code::success:
            return "The operation succeeded.";
        case error_code::fail:
            return "The operation failed.";
        default:
            return "Unknown error code.";
    }
}

error_code function_that_can_fail_enum(bool success, int& return_value)
{
    if(!success)
    {
        return error_code::fail;
    }

    return_value = 1;
    return error_code::success;
}

std::error_code function_that_can_fail_std(bool success, int& return_value)
{
    if(!success)
    {
        return error_code::fail;
    }

    return_value = 1;
    return error_code::success;
}

static void errc_int_success(benchmark::State &state)
{
  int final_value;

  for (auto _ : state)
  {
    auto result = function_that_can_fail_int(true, final_value);
    if (result != ERR_SUCCESS)
    {
      const auto& msg = get_error_msg(result);
    }
    benchmark::ClobberMemory();
  }
}

static void errc_int_fail(benchmark::State &state)
{
  int final_value;

  for (auto _ : state)
  {
    auto result = function_that_can_fail_int(false, final_value);
    if (result != ERR_SUCCESS)
    {
      const auto& msg = get_error_msg(result);
    }
    benchmark::ClobberMemory();
  }
}


static void errc_enum_success(benchmark::State &state)
{
  int final_value;

  for (auto _ : state)
  {
    auto result = function_that_can_fail_enum(true, final_value);
    if (result != error_code::success)
    {
      const auto& msg = get_error_msg(result);
    }
    benchmark::ClobberMemory();
  }
}

static void errc_enum_fail(benchmark::State &state)
{
  int final_value;

  for (auto _ : state)
  {
    auto result = function_that_can_fail_enum(false, final_value);
    if (result != error_code::success)
    {
      const auto& msg = get_error_msg(result);
    }
    benchmark::ClobberMemory();
  }
}

static void errc_std_error_code_success(benchmark::State &state)
{
  int final_value;

  for (auto _ : state)
  {
    auto result = function_that_can_fail_std(true, final_value);
    if (result)
    {
      const auto& msg = result.message();
    }
    benchmark::ClobberMemory();
  }
}

static void errc_std_error_code_fail(benchmark::State &state)
{
  int final_value;

  for (auto _ : state)
  {
    auto result = function_that_can_fail_std(false, final_value);
    if (result)
    {
      const auto& msg = result.message();
    }
    benchmark::ClobberMemory();
  }
}

BENCHMARK(errc_int_success);
BENCHMARK(errc_int_fail);
BENCHMARK(errc_enum_success);
BENCHMARK(errc_enum_fail);
BENCHMARK(errc_std_error_code_success);
BENCHMARK(errc_std_error_code_fail);
