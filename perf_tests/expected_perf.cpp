#include <benchmark/benchmark.h>

#include <system_error>
#include <iostream>
#include "error_code_common.h"

#include "../sub/expected/include/tl/expected.hpp"

struct big_struct
{
  int i;
  std::string a;
  std::string b;
  std::vector<int> v;
};

struct error_struct
{
  std::error_code code;
  std::string* msg;
};

template<bool success>
std::error_code error_code_int(int& return_value)
{
    if(!success)
    {
        return error_code::fail;
    }

    return_value = 1;
    return error_code::success;
}

template<bool success>
std::error_code error_code_struct(big_struct& return_value)
{
    if(!success)
    {
        return error_code::fail;
    }

    return_value =  big_struct{1,"abc", "abcabcabca", {1,2,3}};
    return error_code::success;
}

template<bool success>
std::error_code error_code_void()
{
    if(!success)
    {
        return error_code::fail;
    }

    return error_code::success;
}

template<bool success>
static void perf_errc_int(benchmark::State &state)
{
  for (auto _ : state)
  {
    int final_value;
    auto result = error_code_int<success>(final_value);
    if (result)
    {
      auto code = result.value();
    }
    benchmark::ClobberMemory();
  }
}

template<bool success>
static void perf_errc_struct(benchmark::State &state)
{
  for (auto _ : state)
  {
    big_struct final_value;
    auto result = error_code_struct<success>(final_value);
    if (result)
    {
      auto code = result.value();
    }
    benchmark::ClobberMemory();
  }
}

template<bool success>
static void perf_errc_void(benchmark::State &state)
{
  for (auto _ : state)
  {
    auto result = error_code_void<success>();
    if (result)
    {
      auto code = result.value();
    }
    benchmark::ClobberMemory();
  }
}

auto perf_errc_int_success = perf_errc_int<true>;
auto perf_errc_int_fail = perf_errc_int<false>;
BENCHMARK(perf_errc_int_success);
BENCHMARK(perf_errc_int_fail);

auto perf_errc_struct_success = perf_errc_struct<true>;
auto perf_errc_struct_fail = perf_errc_struct<false>;
BENCHMARK(perf_errc_struct_success);
BENCHMARK(perf_errc_struct_fail);

auto perf_errc_void_success = perf_errc_void<true>;
auto perf_errc_void_fail = perf_errc_void<false>;
BENCHMARK(perf_errc_void_success);
BENCHMARK(perf_errc_void_fail);

template<bool success>
std::error_code error_code_with_message_int(int& return_value, error_struct* info)
{
  if(!success)
  {
    if(info)
    {
      info->code = error_code::fail;
      info->msg = new std::string("this is a dynamic message");
    }
      return error_code::fail;
  }

    return_value = 1;
    return error_code::success;
}

template<bool success>
std::error_code error_code_with_message_struct(big_struct& return_value, error_struct* info)
{
    if(!success)
    {
          if(info)
    {
      info->code = error_code::fail;
      info->msg = new std::string("this is a dynamic message");
    }
        return error_code::fail;
    }

    return_value =  big_struct{1,"abc", "abcabcabca", {1,2,3}};
    return error_code::success;
}

template<bool success>
std::error_code error_code_with_message_void(error_struct* info)
{
    if(!success)
    {
          if(info)
    {
      info->code = error_code::fail;
      info->msg = new std::string("this is a dynamic message");
    }
        return error_code::fail;
    }

    return error_code::success;
}

template<bool with_info, typename T, std::error_code func(T&, error_struct*)>
static void perf_errc_struct_template(benchmark::State &state)
{
  error_struct info;
  for (auto _ : state)
  {
    T final_value;
    if(with_info)
    {
      auto result = func(final_value, &info);
      if (result)
      {
        auto code = info.code;
      }
    }
    else
    {
      auto result = func(final_value, nullptr);
      if (result)
      {
        auto code = result.value();
      }
    }

    benchmark::ClobberMemory();
  }
}

template<bool with_info, std::error_code func(error_struct*)>
static void perf_errc_struct_void(benchmark::State &state)
{
   error_struct info;
  for (auto _ : state)
  {
    if(with_info)
    {
      auto result = func(&info);
      if (result)
      {
        auto code = info.code;
      }
    }
    else
    {
      auto result = func(nullptr);
      if (result)
      {
        auto code = result.value();
      }
    }

    benchmark::ClobberMemory();
  }
}

auto perf_errcmsg_int_success = perf_errc_struct_template<false, int, error_code_with_message_int<true>>;
auto perf_errcmsg_int_fail = perf_errc_struct_template<false, int, error_code_with_message_int<false>>;
auto perf_errcmsg_int_fail_with_info = perf_errc_struct_template<true, int, error_code_with_message_int<false>>;
BENCHMARK(perf_errcmsg_int_success);
BENCHMARK(perf_errcmsg_int_fail);
BENCHMARK(perf_errcmsg_int_fail_with_info);

auto perf_errcmsg_struct_success = perf_errc_struct_template<false, big_struct, error_code_with_message_struct<true>>;
auto perf_errcmsg_struct_fail = perf_errc_struct_template<false, big_struct, error_code_with_message_struct<false>>;
auto perf_errcmsg_struct_fail_with_info = perf_errc_struct_template<true, big_struct, error_code_with_message_struct<false>>;
BENCHMARK(perf_errcmsg_struct_success);
BENCHMARK(perf_errcmsg_struct_fail);
BENCHMARK(perf_errcmsg_struct_fail_with_info);

auto perf_errcmsg_void_success = perf_errc_struct_void<false, error_code_with_message_void<true>>;
auto perf_errcmsg_void_fail = perf_errc_struct_void<false, error_code_with_message_void<false>>;
auto perf_errcmsg_void_fail_with_info = perf_errc_struct_void<true, error_code_with_message_void<false>>;
BENCHMARK(perf_errcmsg_void_success);
BENCHMARK(perf_errcmsg_void_fail);
BENCHMARK(perf_errcmsg_void_fail_with_info);

template<bool success, bool with_message>
int exception_int()
{
  if(!success)
  {
    if(with_message)
    {
      throw error_struct{error_code::fail, new std::string("this is a dynamic message")};
    }
    else
    {
      throw error_struct{error_code::fail, nullptr};
    }
  }

  return 1;
}

template<bool success, bool with_message>
big_struct exception_struct()
{
    if(!success)
  {
    if(with_message)
    {
      throw error_struct{error_code::fail, new std::string("this is a dynamic message")};
    }
    else
    {
      throw error_struct{error_code::fail, nullptr};
    }
  }

  return big_struct{1,"abc", "abcabcabca", {1,2,3}};
}

template<bool success, bool with_message>
void exception_void()
{
    if(!success)
  {
    if(with_message)
    {
      throw error_struct{error_code::fail, new std::string("this is a dynamic message")};
    }
    else
    {
      throw error_struct{error_code::fail, nullptr};
    }
  }
}

template<typename T, T func()>
static void perf_exception_template(benchmark::State &state)
{
  for (auto _ : state)
  {
    try
    {
      T res = func();
    }
    catch(const error_struct& err)
    {
      auto code = err.code;
    }

    benchmark::ClobberMemory();
  }
}

template<void func()>
static void perf_exception_void_template(benchmark::State &state)
{
   for (auto _ : state)
  {
    try
    {
      func();
    }
    catch(const error_struct& err)
    {
      auto code = err.code;
    }

    benchmark::ClobberMemory();
  }
}

auto perf_exception_int_success = perf_exception_template<int, exception_int<true, false>>;
auto perf_exception_int_fail = perf_exception_template<int, exception_int<false, false>>;
auto perf_exception_int_fail_with_message = perf_exception_template<int, exception_int<false, true>>;
BENCHMARK(perf_exception_int_success);
BENCHMARK(perf_exception_int_fail);
BENCHMARK(perf_exception_int_fail_with_message);

auto perf_exception_struct_success = perf_exception_template<big_struct, exception_struct<true, false>>;
auto perf_exception_struct_fail = perf_exception_template<big_struct, exception_struct<false, false>>;
auto perf_exception_struct_fail_with_message = perf_exception_template<big_struct, exception_struct<false, true>>;
BENCHMARK(perf_exception_struct_success);
BENCHMARK(perf_exception_struct_fail);
BENCHMARK(perf_exception_struct_fail_with_message);

auto perf_exception_void_success = perf_exception_void_template<exception_void<true, false>>;
auto perf_exception_void_fail = perf_exception_void_template<exception_void<false, false>>;
auto perf_exception_void_fail_with_message = perf_exception_void_template<exception_void<false, true>>;
BENCHMARK(perf_exception_void_success);
BENCHMARK(perf_exception_void_fail);
BENCHMARK(perf_exception_void_fail_with_message);

template<bool success, bool with_message>
tl::expected<int, error_struct> expected_int()
{
  if(!success)
  {
    if(with_message)
    {
      return tl::make_unexpected(error_struct{error_code::fail, new std::string("this is a dynamic message")});
    }
    else
    {
      return tl::make_unexpected(error_struct{error_code::fail, nullptr});
    }
  }

  return 1;
}

template<bool success, bool with_message>
tl::expected<big_struct, error_struct> expected_struct()
{
  if(!success)
  {
    if(with_message)
    {
      return tl::make_unexpected(error_struct{error_code::fail, new std::string("this is a dynamic message")});
    }
    else
    {
      return tl::make_unexpected(error_struct{error_code::fail, nullptr});
    }
  }

  return big_struct{1,"abc", "abcabcabca", {1,2,3}};
}

template<bool success, bool with_message>
tl::expected<void, error_struct> expected_void()
{
  if(!success)
  {
    if(with_message)
    {
      return tl::make_unexpected(error_struct{error_code::fail, new std::string("this is a dynamic message")});
    }
    else
    {
      return tl::make_unexpected(error_struct{error_code::fail, nullptr});
    }
  }

  return tl::expected<void, error_struct>();
}

template<typename T, tl::expected<T, error_struct> func()>
static void perf_expected_template(benchmark::State &state)
{
  for (auto _ : state)
  {
    auto result = func();
    if (result.has_value())
    {
      const auto& value = result.value();
    }
    else
    {
      const auto& error = result.error();
    }

    benchmark::ClobberMemory();
  }
}

template<tl::expected<void, error_struct> func()>
static void perf_expected_void_template(benchmark::State &state)
{
  for (auto _ : state)
  {
    auto result = func();
    if (!result.has_value())
    {
      const auto& error = result.error();
    }

    benchmark::ClobberMemory();
  }
}

auto perf_expected_int_success = perf_expected_template<int, expected_int<true, false>>;
auto perf_expected_int_fail = perf_expected_template<int, expected_int<false, false>>;
auto perf_expected_int_fail_with_info = perf_expected_template<int, expected_int<false, true>>;
BENCHMARK(perf_expected_int_success);
BENCHMARK(perf_expected_int_fail);
BENCHMARK(perf_expected_int_fail_with_info);

auto perf_expected_struct_success = perf_expected_template<big_struct, expected_struct<true, false>>;
auto perf_expected_struct_fail = perf_expected_template<big_struct, expected_struct<false, false>>;
auto perf_expected_struct_fail_with_info = perf_expected_template<big_struct, expected_struct<false, true>>;
BENCHMARK(perf_expected_struct_success);
BENCHMARK(perf_expected_struct_fail);
BENCHMARK(perf_expected_struct_fail_with_info);

auto perf_expected_void_success = perf_expected_void_template<expected_void<true, false>>;
auto perf_expected_void_fail = perf_expected_void_template<expected_void<false, false>>;
auto perf_expected_void_fail_with_info = perf_expected_void_template<expected_void<false, true>>;
BENCHMARK(perf_expected_void_success);
BENCHMARK(perf_expected_void_fail);
BENCHMARK(perf_expected_void_fail_with_info);
