cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Release)

project(perf_tests CXX)

find_package(benchmark CONFIG REQUIRED)

add_executable(perf_tests
    perf_tests/main.cpp
    perf_tests/exception_perf.cpp
    perf_tests/struct_return.cpp
    perf_tests/expected.cpp
    perf_tests/unique_insert_perf.cpp
    perf_tests/error_code.cpp
    perf_tests/expected_perf.cpp
    perf_tests/error_code_common.cpp
)

target_link_libraries(perf_tests PRIVATE benchmark::benchmark benchmark::benchmark_main)
