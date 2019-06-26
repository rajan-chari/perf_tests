cmake_minimum_required(VERSION 3.5)

project(perf_tests CXX)
set(CMAKE_CXX_STANDARD 11)

find_package(benchmark REQUIRED)
find_package(Threads REQUIRED)

add_executable(perf_tests perf_tests/main.cpp perf_tests/exception_perf.cpp perf_tests/struct_return.cpp)
target_link_libraries(perf_tests Threads::Threads benchmark)
