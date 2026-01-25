#include "leetcode/problems/minimum-difference-between-highest-and-lowest-of-k-scores.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1984 {

class MinimumDifferenceBetweenHighestAndLowestOfKScoresTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumDifferenceBetweenHighestAndLowestOfKScoresSolution solution;
};

TEST_P(MinimumDifferenceBetweenHighestAndLowestOfKScoresTest, Example1) {
  vector<int> nums = {90};
  int k = 1;
  int expected = 0;
  int result = solution.minimumDifference(nums, k);
  EXPECT_EQ(expected, result);
}

TEST_P(MinimumDifferenceBetweenHighestAndLowestOfKScoresTest, Example2) {
  vector<int> nums = {9, 4, 1, 7};
  int k = 2;
  int expected = 2;
  int result = solution.minimumDifference(nums, k);
  EXPECT_EQ(expected, result);
}

TEST_P(MinimumDifferenceBetweenHighestAndLowestOfKScoresTest, EdgeCaseKEqualsN) {
  vector<int> nums = {1, 3, 5, 7, 9};
  int k = 5;
  int expected = 8;  // 9 - 1 = 8
  int result = solution.minimumDifference(nums, k);
  EXPECT_EQ(expected, result);
}

TEST_P(MinimumDifferenceBetweenHighestAndLowestOfKScoresTest, AllSameElements) {
  vector<int> nums = {5, 5, 5, 5};
  int k = 3;
  int expected = 0;  // 任意三个元素差值都是0
  int result = solution.minimumDifference(nums, k);
  EXPECT_EQ(expected, result);
}

TEST_P(MinimumDifferenceBetweenHighestAndLowestOfKScoresTest, IncreasingSequence) {
  vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int k = 4;
  int expected = 3;  // 选择 [1,2,3,4] 差值为3，或者 [2,3,4,5] 差值也是3，等等
  int result = solution.minimumDifference(nums, k);
  EXPECT_EQ(expected, result);
}

TEST_P(MinimumDifferenceBetweenHighestAndLowestOfKScoresTest, LargeNumbers) {
  vector<int> nums = {100000, 50000, 75000, 25000, 0};
  int k = 3;
  sort(nums.begin(), nums.end());  // 手动排序看看：0, 25000, 50000, 75000, 100000
  // 连续3个的最小差值：选择 [0,25000,50000] 差值50000，[25000,50000,75000] 差值50000，[50000,75000,100000] 差值50000
  int expected = 50000;
  int result = solution.minimumDifference(nums, k);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumDifferenceBetweenHighestAndLowestOfKScoresTest,
    ::testing::ValuesIn(MinimumDifferenceBetweenHighestAndLowestOfKScoresSolution().getStrategyNames()));

}  // namespace problem_1984
}  // namespace leetcode