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
