#include "leetcode/problems/fizz-buzz-multithreaded.h"

#include "gtest/gtest.h"

#include <thread>

namespace leetcode {
namespace problem_1195 {

class FizzBuzzMultithreadedTest : public ::testing::Test {};

TEST_F(FizzBuzzMultithreadedTest, Example1) {
  int n = 15;
  FizzBuzz fizzBuzz(n);

  vector<string> result;
  std::mutex result_mtx;

  auto printFizz = [&result, &result_mtx]() {
    std::lock_guard<std::mutex> lock(result_mtx);
    result.push_back("fizz");
  };

  auto printBuzz = [&result, &result_mtx]() {
    std::lock_guard<std::mutex> lock(result_mtx);
    result.push_back("buzz");
  };

  auto printFizzBuzz = [&result, &result_mtx]() {
    std::lock_guard<std::mutex> lock(result_mtx);
    result.push_back("fizzbuzz");
  };

  auto printNumber = [&result, &result_mtx](int x) {
    std::lock_guard<std::mutex> lock(result_mtx);
    result.push_back(std::to_string(x));
  };

  std::thread t1([&]() { fizzBuzz.fizz(printFizz); });
  std::thread t2([&]() { fizzBuzz.buzz(printBuzz); });
  std::thread t3([&]() { fizzBuzz.fizzbuzz(printFizzBuzz); });
  std::thread t4([&]() { fizzBuzz.number(printNumber); });

  t1.join();
  t2.join();
  t3.join();
  t4.join();

  vector<string> expected = {"1", "2", "fizz", "4", "buzz",
                              "fizz", "7", "8", "fizz", "buzz",
                              "11", "fizz", "13", "14", "fizzbuzz"};
  EXPECT_EQ(expected, result);
}

TEST_F(FizzBuzzMultithreadedTest, Example2) {
  int n = 5;
  FizzBuzz fizzBuzz(n);

  vector<string> result;
  std::mutex result_mtx;

  auto printFizz = [&result, &result_mtx]() {
    std::lock_guard<std::mutex> lock(result_mtx);
    result.push_back("fizz");
  };

  auto printBuzz = [&result, &result_mtx]() {
    std::lock_guard<std::mutex> lock(result_mtx);
    result.push_back("buzz");
  };

  auto printFizzBuzz = [&result, &result_mtx]() {
    std::lock_guard<std::mutex> lock(result_mtx);
    result.push_back("fizzbuzz");
  };

  auto printNumber = [&result, &result_mtx](int x) {
    std::lock_guard<std::mutex> lock(result_mtx);
    result.push_back(std::to_string(x));
  };

  std::thread t1([&]() { fizzBuzz.fizz(printFizz); });
  std::thread t2([&]() { fizzBuzz.buzz(printBuzz); });
  std::thread t3([&]() { fizzBuzz.fizzbuzz(printFizzBuzz); });
  std::thread t4([&]() { fizzBuzz.number(printNumber); });

  t1.join();
  t2.join();
  t3.join();
  t4.join();

  vector<string> expected = {"1", "2", "fizz", "4", "buzz"};
  EXPECT_EQ(expected, result);
}

}  // namespace problem_1195
}  // namespace leetcode
