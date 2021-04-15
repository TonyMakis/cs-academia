# Test Cases for C++ Linked List Implementation

## Instructions

Copy/download all of the files in this directory into your own directory containing your implementation of List.h (Including the weird looking `_util.h` and `_test.h` files).

There are several auto-scoring tester programs in this batch. The source files are listed below. Sometimes, due to variety of results running theses tests on various platforms with various memory consumptions, the time measured for some functions running may be off. To account for this, run each test at least 3 or so times to see if the tests pass.

>The tests are very strict, and if the function runs even a millisecond over the requirement it will fail. If you can run the test again and it passes, this is fine. If the time is way off however, the implementation needs work!!!

| Function | Completion | Test Driver | My Test Runs' Results
| :---     |   :----:   |    :---:    |   :---:   |
| `equal_to`        |   ✔️   |   [./t1_eq_to.cpp](./t1_eq_to.cpp)   |   [./img/t1.png](./img/t1.png)   |
| `count`           |   ✔️   |   [./t2_count.cpp](./t2_count.cpp)   |   [./img/t2.png](./img/t2.png)   |
| `length`          |   ✔️   |   [./t3_len.cpp](./t3_len.cpp)   |   [./img/t3.png](./img/t3.png)   |
| `pop_back`        |   ✔️   |   [./t4_pop_back.cpp](./t4_pop_back.cpp)   |   [./img/t4.png](./img/t4.png)   |
| `prefix`          |   ✔️   |   [./t5_prefix.cpp](./t5_prefix.cpp)   |   [./img/t5.png](./img/t5.png)   |
| `filter_leq`      |   ✔️   |   [./t6_filter.cpp](./t6_filter.cpp)   |   [./img/t6.png](./img/t6.png)   |
| `merge_with`      |   ✔️   |   [./t7_merge.cpp](./t7_merge.cpp)   |   [./img/t7.png](./img/t7.png)   |
| `fast_remove_all` |   ✔️   |   [./t8_rem_all.cpp](./t8_rem_all.cpp)   |   [./img/t8.png](./img/t8.png)   |
| `concat`          |   ✔️   |   [./t9_concat.cpp](./t9_concat.cpp)   |   [./img/t9.png](./img/t9.png)   |
| `insert_sorted`   |   ✔️   |   [./t10_insert_sorted.cpp](./t10_insert_sorted.cpp)   |   [./img/t10.png](./img/t10.png)   |
| `clone`           |   ✔️   |   [./t11_clone.cpp](./t11_clone.cpp)   |   [./img/t11.png](./img/t11.png)   |
| `print_rev`       |   ✔️   |   - N/A - Checked by eye   |   - N/A -   |
| `reverse`         |   ✔️   |   [./t12_reverse.cpp](./t12_reverse.cpp)   |   [./img/t12.png](./img/t12.png)   |
| `compare_with`    |   ✔️   |   [./t13_compare.cpp](./t13_compare.cpp)   |   [./img/t13.png](./img/t13.png)   |
| `suffix_maxes`    |   ✔️   |   [./t14_suff_maxes.cpp](./t14_suff_maxes.cpp)   |   [./img/t14.png](./img/t14.png)   |

To compile the test programs you can simply type `make` from the shell.

>You can also compile them directly one-by-one; be sure to use -std=c++11

When you run a test program, you will get a report for all of the individual tests that were run including points assigned. (Unless the program crashes, then you might only get the output before the crash).

Each test has a short description so you have some idea of the scenario being tested (details can be seen by examining the test programs themselves).

## My Results

### To see my own results with my Linked List implementation, check the [img](./img) folder for the test run results
