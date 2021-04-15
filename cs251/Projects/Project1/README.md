# Project 1: Linked Lists

## Background Info

You are provided with a C++ implementation of a list Abstract Data Type (ADT) in which some functions are already written and some are not. Your job is to complete the unwritten functions. (In one case you will make modifications to improve the runtime of one already implemented function).

### Key Concepts Involved

- Linked-Lists
- Memory allocation & deallocation in C++
- Runtime (a little)
- Recursion

### Development Advice

- Start with the easier functions.
- Do lots of testing! Write multiple driver programs which perform lots of stress tests on the List class. Think carefully about boundary cases, etc.
- Develop things __incrementally__ -- after you've written a function, test it extensively before moving on
- Think carefully about __invariants__ -- for example, _"after I've completed some operation on a List have I made sure that front and back are correct in all possible scenarios?"_
- Look out for memory leaks!

## Project Guide

Examine the file List.h. There you will find an implementation of a List class with some functions not yet implemented; you will find __stubs__ for these functions.

If you search for the string `TODO` you will find all of the requirements. In most cases each task is the implementation of a particular member function. The one exception is the length function which already exists, but you need to make modifications so that it runs in constant time -- these modifications are mostly outside of the length function itself.

To finish the project, completion of all of the `TODO` items specified is required -- associated comments give details on the expectations.

### Functions to Write

| Function | Completion | Test Driver |
| :---     |   :----:   |    :---:    |
| `equal_to`        |   ✔️   |   [./tests/t1_eq_to.cpp](./tests/t1_eq_to.cpp)
| `count`           |   ✔️   |   [./tests/t2_count.cpp](./tests/t2_count.cpp)
| `length`          |   ✔️   |   [./tests/t3_len.cpp](./tests/t3_len.cpp)
| `pop_back`        |   ✔️   |   [./tests/t4_pop_back.cpp](./tests/t4_pop_back.cpp)
| `prefix`          |   ✔️   |   [./tests/t5_prefix.cpp](./tests/t5_prefix.cpp)
| `filter_leq`      |   ✔️   |   [./tests/t6_filter.cpp](./tests/t6_filter.cpp)
| `merge_with`      |   ✔️   |   [./tests/t7_merge.cpp](./tests/t7_merge.cpp)
| `fast_remove_all` |   ✔️   |   [./tests/t8_rem_all.cpp](./tests/t8_rem_all.cpp)
| `concat`          |   ✔️   |   [./tests/t9_concat.cpp](./tests/t9_concat.cpp)
| `insert_sorted`   |   ✔️   |   [./tests/t10_insert_sorted.cpp](./tests/t10_insert_sorted.cpp)
| `clone`           |   ✔️   |   [./tests/t11_clone.cpp](./tests/t11_clone.cpp)
| `print_rev`       |   ✔️   |   - N/A - Checked by eye
| `reverse`         |   ✔️   |   [./tests/t12_reverse.cpp](./tests/t12_reverse.cpp)
| `compare_with`    |   ✔️   |   [./tests/t13_compare.cpp](./tests/t13_compare.cpp)
| `suffix_maxes`    |   ✔️   |   [./tests/t14_suff_maxes.cpp](./tests/t14_suff_maxes.cpp)

## Project Structure

This is to be developed in one stage, procedurally. There are several source files provided:

- [List.h](./List.h) => starter code provided for List implementation
- [tests](./tests/README.md) => This is the set of tests used to grade this List implmentation!

## Restrictions for this Project

### What You CAN'T Do

- Modify any of the function __signatures__ (parameters and return types)
- Introduce any global variables

### What You CAN Do

- Add helper functions; you should make them private

>Note: if you want helper functions that do not have a "calling object" (like in traditional C), you designate them as static.

- Add data fields to the List class (to achieve one of the runtime requirements, a __bookkeeping__ field will come in handy!).

## My Solution in Action

The Linked List deliverable is implmented in `List.h`; as indicated above, the [TEST CASES](./tests) folder contains tests for the bulk of the functions it implements. The Linked List is of generic type, so it can store ints, strings, etc. To run the tests, head to the [TEST CASES](./tests) folder and run the `make` command! Then, you can run any of the executables that generates (They will be labelled as indicated above in the table).
