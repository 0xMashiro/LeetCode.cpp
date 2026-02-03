
#include "leetcode/problems/count-the-number-of-fair-pairs.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2563 {

class CountTheNumberOfFairPairsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CountTheNumberOfFairPairsSolution solution;
};

TEST_P(CountTheNumberOfFairPairsTest, Example1) {
  vector<int> nums = {0, 1, 7, 4, 4, 5};
  int lower = 3;
  int upper = 6;
  long long expected = 6;
  EXPECT_EQ(expected, solution.countFairPairs(nums, lower, upper));
}

TEST_P(CountTheNumberOfFairPairsTest, Example2) {
  vector<int> nums = {1, 7, 9, 2, 5};
  int lower = 11;
  int upper = 11;
  long long expected = 1;
  EXPECT_EQ(expected, solution.countFairPairs(nums, lower, upper));
}

TEST_P(CountTheNumberOfFairPairsTest, SingleElement) {
  // 边界：只有一个元素，无法形成数对
  vector<int> nums = {5};
  int lower = 3;
  int upper = 10;
  long long expected = 0;
  EXPECT_EQ(expected, solution.countFairPairs(nums, lower, upper));
}

TEST_P(CountTheNumberOfFairPairsTest, NoFairPairs) {
  // 没有满足条件的数对
  vector<int> nums = {1, 2, 3};
  int lower = 10;
  int upper = 20;
  long long expected = 0;
  EXPECT_EQ(expected, solution.countFairPairs(nums, lower, upper));
}

TEST_P(CountTheNumberOfFairPairsTest, AllPairsFair) {
  // 所有数对都满足条件
  vector<int> nums = {1, 1, 1};
  int lower = 2;
  int upper = 2;
  // 数对：(0,1), (0,2), (1,2)，共 3 个，和都是 2
  long long expected = 3;
  EXPECT_EQ(expected, solution.countFairPairs(nums, lower, upper));
}

TEST_P(CountTheNumberOfFairPairsTest, NegativeNumbers) {
  // 包含负数的情况
  vector<int> nums = {-5, -3, 0, 2, 4};
  int lower = -5;
  int upper = 0;
  // 数对：(-5,-3)=-8(否), (-5,0)=-5(是), (-5,2)=-3(是), (-5,4)=-1(是)
  //      (-3,0)=-3(是), (-3,2)=-1(是), (-3,4)=1(否)
  //      (0,2)=2(否), (0,4)=4(否)
  //      (2,4)=6(否)
  // 满足条件：(-5,0), (-5,2), (-5,4), (-3,0), (-3,2)，共 5 个
  long long expected = 5;
  EXPECT_EQ(expected, solution.countFairPairs(nums, lower, upper));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CountTheNumberOfFairPairsTest,
    ::testing::ValuesIn(CountTheNumberOfFairPairsSolution().getStrategyNames()));

}  // namespace problem_2563
}  // namespace leetcode
