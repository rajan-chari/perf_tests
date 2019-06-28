# perf_tests

```text
Run on (56 X 2400 MHz CPU s)
CPU Caches:
  L1 Data 32K (x28)
  L1 Instruction 32K (x28)
  L2 Unified 256K (x28)
  L3 Unified 35840K (x2)
Load Average: 0.14, 0.34, 0.33
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
------------------------------------------------------------------------------
Benchmark                                    Time             CPU   Iterations
------------------------------------------------------------------------------
function_returning_int                   0.418 ns        0.418 ns   1000000000
function_throwing_int                     1849 ns         1849 ns       379129
throwing_function_returning_int          0.418 ns        0.418 ns   1000000000
function_returning_string                 21.4 ns         21.4 ns     32686348
function_throwing_string                  2781 ns         2781 ns       254596
throwing_function_returning_string        19.2 ns         19.2 ns     36396542
return_empty_struct                       4.18 ns         4.18 ns    167301886
return_filled_struct                      21.9 ns         21.9 ns     32291710
external_struct_alloc_return_normal      0.418 ns        0.418 ns   1000000000
external_struct_alloc_return_error        9.20 ns         9.20 ns     76105341


## Build

### Linux

```text
install vcpkg
vcpkg install benchmark --triplet x64-linux
rm -rf build && mkdir build && cd build && cmake .. -DCMAKE_BUILD_TYPE=Release && make -j && ./perf_test && cd ..
```

### Windows
