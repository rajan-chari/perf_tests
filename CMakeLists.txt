cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Release)

project(perf_tests CXX)

find_package(benchmark CONFIG REQUIRED)

include_directories(
  perf_tests
  sub/vw_master/explore
  sub/vw_master/vowpalwabbit
  /mnt/c/git/sparsehash-c11
  $CONDA_PREFIX
)

set(VW_HOME sub/vw_master/)

set(vw_source
  {VW_HOME}parse_primitives.cc
  {VW_HOME}vw_exception.cc
)

add_executable(perf_tests
    perf_tests/main.cpp
#    perf_tests/hashmap_perf.cpp
    perf_tests/string_view.cpp
    sub/vw_master/vowpalwabbit/parse_primitives.cc
    sub/vw_master/vowpalwabbit/vw_exception.cc
#    perf_tests/exception_perf.cpp
#    perf_tests/struct_return.cpp
#    perf_tests/expected.cpp
#    perf_tests/unique_insert_perf.cpp
)

target_link_libraries(perf_tests PRIVATE benchmark::benchmark benchmark::benchmark_main)
