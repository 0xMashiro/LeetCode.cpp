#include "leetcode/problems/fizz-buzz-multithreaded.h"

namespace leetcode {
namespace problem_1195 {

void FizzBuzz::fizz(function<void()> printFizz) {
  while (true) {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this] {
      return current > n || (current % 3 == 0 && current % 5 != 0);
    });
    if (current > n) {
      return;
    }
    printFizz();
    current++;
    cv.notify_all();
  }
}

void FizzBuzz::buzz(function<void()> printBuzz) {
  while (true) {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this] {
      return current > n || (current % 5 == 0 && current % 3 != 0);
    });
    if (current > n) {
      return;
    }
    printBuzz();
    current++;
    cv.notify_all();
  }
}

void FizzBuzz::fizzbuzz(function<void()> printFizzBuzz) {
  while (true) {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this] {
      return current > n || (current % 15 == 0);
    });
    if (current > n) {
      return;
    }
    printFizzBuzz();
    current++;
    cv.notify_all();
  }
}

void FizzBuzz::number(function<void(int)> printNumber) {
  while (true) {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this] {
      return current > n || (current % 3 != 0 && current % 5 != 0);
    });
    if (current > n) {
      return;
    }
    printNumber(current);
    current++;
    cv.notify_all();
  }
}

}  // namespace problem_1195
}  // namespace leetcode
