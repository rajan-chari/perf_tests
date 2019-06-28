# perf_tests

```text
Run on (8 X 2112 MHz CPU s)
05/03/18 08:33:54
-------------------------------------------------------------
Benchmark                      Time           CPU Iterations
-------------------------------------------------------------
int_ret_fun                    1 ns          1 ns  497777778
int_ex_fun                  1517 ns       1496 ns     407273
int_no_ex_fun                  1 ns          1 ns  448000000
str_ret_fun                   50 ns         50 ns   10000000
str_no_ex_fun                 47 ns         48 ns   15448276
str_ex_fun                  1601 ns       1604 ns     448000
empty_struct_ret               6 ns          6 ns  112000000
filled_struct_ret             51 ns         50 ns   11200000
ext_struct_alloc_good          1 ns          1 ns  560000000
ext_struct_alloc_bad           3 ns          3 ns  213333333
```

| Use case              | returns       | throws | caller try/catch | Notes                   |
|-----------------------|---------------|--------|------------------|-------------------------|
| int_ret_fun           | int           | no     | no               | returns int             |
| int_ex_fun            | int           | int    | yes              | throws int              |
| int_no_ex_fun         | int           | no     | yes              | try/catch no throw      |
| str_ret_fun           | string        | no     | no               | returns string          |
| str_no_ex_fun         | string        | no     | yes              | try/catch no throw      |
| str_ex_fun            | string        | string | yes              | throw string            |
| empty_struct_ret      | empty struct  | no     | no               | return an empty struct  |
| filled_struct_ret     | filled struct | no     | no               | return a filled struct  |
| ext_struct_alloc_good | int           | no     | no               | caller allocated struct |
| ext_struct_alloc_bad  | int           | no     | no               | caller allocated struct |

Build:
install vcpkg

