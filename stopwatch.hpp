/*
MIT License

Copyright (c) 2019 - present H. Watanabe
The latest version is available at
https://github.com/kaityo256/stopwatch

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#if defined(__APPLE__) && defined(__MACH__) && defined(__arm64__)
#define USE_CHRONO
#else
#endif

#pragma once
#include <chrono>
#include <cstdint>
#include <iostream>
#include <string>
#include <x86intrin.h>

namespace stopwatch {

#ifndef USE_CHRONO
struct rdtscp_clock {
  std::uint64_t sum; // Elapsed Cycle
  std::uint64_t now;
  std::uint32_t id;
  void start() {
    now = __rdtscp(&id);
  }
  void stop() {
    auto t = __rdtscp(&id);
    sum += (t - now);
  }
  uint64_t elapsed() {
    return sum;
  }
};
#endif

struct chrono_clock {
  std::chrono::milliseconds::rep sum; // Elapsed Time
  std::chrono::high_resolution_clock::time_point now;
  std::uint32_t id;
  void start() {
    now = std::chrono::high_resolution_clock::now();
  }
  void stop() {
    auto t = std::chrono::high_resolution_clock::now();
    sum += std::chrono::duration_cast<std::chrono::milliseconds>(t - now).count();
  }
  std::chrono::milliseconds::rep elapsed() {
    return sum;
  }
};

#ifdef USE_CHRONO
template <class Clock = rdtscp_clock>
#else
template <class Clock = chrono_clock>
#endif
struct timer {
  std::string name;
  Clock clock;
  std::uint32_t count; // Number of calls
  timer(const char *s) {
    name = s;
    count = 0;
  }
  void start() {
    count++;
    clock.start();
  }
  void stop() {
    clock.stop();
  }
  ~timer() {
    auto e = clock.elapsed();
    std::cerr << name << ": elapsed " << e;
    std::cerr << " (" << count << " times)";
    std::cerr << " Average " << static_cast<double>(e) / count << std::endl;
  }
};
} // namespace stopwatch
