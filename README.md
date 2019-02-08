# Single-header C++ Stopwatch

[![MIT License](http://img.shields.io/badge/license-MIT-blue.svg?style=flat)](LICENSE)

A single-header C++ stopwatch.

## Usage

Wrap a region which you want to measure

```cpp
#include "stopwatch.hpp"
#include <iostream>
#include <unistd.h>

void func() {
  static stopwatch::timer<> timer("test");
  timer.start();
  usleep(10000);
  timer.stop();
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
test: elapsed 403689122 (10 times) Average 4.03689e+07
```

## Why

We want to measure the elapsed time for a function which is called many times.
But the function is sometimes inlined, and `perf` cannot capture the function.
This library allows you to measure the time of such inlined funciton.

## Reference

I referred to the following repository to develop this code.

[https://github.com/sailormoon/stopwatch](https://github.com/sailormoon/stopwatch)

## License

This software is released under the MIT License, see LICENSE.