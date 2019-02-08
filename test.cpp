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
