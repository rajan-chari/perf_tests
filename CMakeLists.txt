cmake_minimum_required(VERSION 3.10)
set(CMAKE_TOOLCHAIN_FILE "/home/ranaras/s/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_BUILD_TYPE Release)
project(perf_test)
add_executable(perf_test 
    perf_tests/main.cpp
    perf_tests/exception_perf.cpp 
    perf_tests/struct_return.cpp 
)
find_package(benchmark CONFIG REQUIRED)
target_link_libraries(perf_test PRIVATE benchmark::benchmark benchmark::benchmark_main)
