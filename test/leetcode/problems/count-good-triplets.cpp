#include "leetcode/problems/count-good-triplets.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1534 {

class CountGoodTripletsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CountGoodTripletsSolution solution;
};

TEST_P(CountGoodTripletsTest, Example1) {
  vector<int> arr = {3, 0, 1, 1, 9, 7};
  int a = 7, b = 2, c = 3;
  int expected = 4;
  EXPECT_EQ(expected, solution.countGoodTriplets(arr, a, b, c));
}

TEST_P(CountGoodTripletsTest, Example2) {
  vector<int> arr = {1, 1, 2, 2, 3};
  int a = 0, b = 0, c = 1;
  int expected = 0;
  EXPECT_EQ(expected, solution.countGoodTriplets(arr, a, b, c));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CountGoodTripletsTest,
    ::testing::ValuesIn(CountGoodTripletsSolution().getStrategyNames()));

}  // namespace problem_1534
}  // namespace leetcode
