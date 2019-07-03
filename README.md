# perf_tests

```text
Run on (40 X 2195 MHz CPU s)
Load Average: 0.52, 0.58, 0.59
------------------------------------------------------------------------------
Benchmark                                    Time             CPU   Iterations
------------------------------------------------------------------------------
function_returning_int                   0.355 ns        0.359 ns   1000000000
function_throwing_int                     1539 ns         1535 ns       448000
throwing_function_returning_int          0.348 ns        0.344 ns   1000000000
function_returning_string                 17.2 ns         17.3 ns     40727273
function_throwing_string                  2234 ns         2246 ns       320000
throwing_function_returning_string        14.7 ns         14.8 ns     49777778
return_empty_struct                       6.88 ns         6.80 ns     89600000
return_filled_struct                      17.1 ns         16.9 ns     40727273
external_struct_alloc_return_normal      0.347 ns        0.344 ns   1000000000
external_struct_alloc_return_error        7.36 ns         7.32 ns     89600000
expected_success                         0.346 ns        0.344 ns   1000000000
expected_fail                            0.366 ns        0.359 ns   1000000000
copy_expected_success                     5.91 ns         5.86 ns    112000000
copy_expected_fail                        5.87 ns         5.86 ns    112000000
int_success                              0.346 ns        0.344 ns   1000000000
int_fail                                 0.346 ns        0.359 ns   1000000000
exception_success                        0.345 ns        0.344 ns   1000000000
exception_fail                            1826 ns         1842 ns       407273
set                                        869 ns          858 ns       746667
vector_binary_search_insert                675 ns          670 ns      1120000
no_deduplication                           488 ns          481 ns      1493333
fixed_bool_bookkeeping                     274 ns          276 ns      2488889
```

## Build

### Linux

- install vcpkg

```text

vcpkg install benchmark --triplet x64-linux
git clone https://github.com/rajan-chari/perf_tests.git
cd perf_tests
git submodule update --init --recursive
rm -rf build && mkdir build && cd build && cmake .. -DCMAKE_BUILD_TYPE=Release && make -j && ./perf_test && cd ..
```

### Windows

- install vcpkg

```text
vcpkg install benchmark --triplet x64-linux
git clone https://github.com/rajan-chari/perf_tests.git
cd perf_tests
git submodule update --init --recursive
```

- build project from solution file in Visual Studio 2017
