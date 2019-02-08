# Single-header C++ Stopwatch

[![MIT License](http://img.shields.io/badge/license-MIT-blue.svg?style=flat)](LICENSE)

A single-header C++ stopwatch.

## Usage

Wrap a region which you want to measure.

```cpp
#include "stopwatch.hpp"
#include <iostream>
#include <unistd.h>

void func() {
  static stopwatch::timer<> timer1("func1");
  static stopwatch::timer<> timer2("func2");
  timer1.start(); // Measure this whole function

  timer2.start(); // Measure some part of this function
  usleep(5000);
  timer2.stop();

  usleep(5000);

  timer1.stop();
}

int main() {
  for (int i = 0; i < 10; i++) {
    std::cout << i << std::endl;
    func();
  }
}
```

It outputs the results at the end of the program as follows.

```sh
$ g++ test.cpp
$ ./a.out
0
1
2
3
4
5
6
7
8
9
func2: elapsed 194801680 (10 times) Average 1.94802e+07
func1: elapsed 385134752 (10 times) Average 3.85135e+07
```

## Why

We want to measure the elapsed time for a function which is called many times.
But the function is sometimes inlined, and some profiler such as `perf` cannot capture it.
This library allows you to measure the elapsed time of such inlined funcitons.
It is also possible to measure a part of a function.

## Reference

I referred to the following repository to develop this code.

[https://github.com/sailormoon/stopwatch](https://github.com/sailormoon/stopwatch)

## License

This software is released under the MIT License, see LICENSE.