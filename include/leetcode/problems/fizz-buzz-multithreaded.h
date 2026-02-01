#include "leetcode/core.h"

namespace leetcode {
namespace problem_1195 {

class FizzBuzz {
 private:
  int n;
  int current = 1;
  std::mutex mtx;
  std::condition_variable cv;

 public:
  FizzBuzz(int n) : n(n) {}

  void fizz(function<void()> printFizz);

  void buzz(function<void()> printBuzz);

  void fizzbuzz(function<void()> printFizzBuzz);

  void number(function<void(int)> printNumber);
};

}  // namespace problem_1195
}  // namespace leetcode
