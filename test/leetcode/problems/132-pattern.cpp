
#include "leetcode/problems/132-pattern.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_456 {

class Pattern132Test : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  Pattern132Solution solution;
};

TEST_P(Pattern132Test, Example1) {
  vector<int> nums = {1, 2, 3, 4};
  EXPECT_FALSE(solution.find132pattern(nums));
}

TEST_P(Pattern132Test, Example2) {
  vector<int> nums = {3, 1, 4, 2};
  EXPECT_TRUE(solution.find132pattern(nums));
}

TEST_P(Pattern132Test, Example3) {
  vector<int> nums = {-1, 3, 2, 0};
  EXPECT_TRUE(solution.find132pattern(nums));
}

TEST_P(Pattern132Test, EmptyArray) {
  vector<int> nums = {};
  EXPECT_FALSE(solution.find132pattern(nums));
}

TEST_P(Pattern132Test, SingleElement) {
  vector<int> nums = {1};
  EXPECT_FALSE(solution.find132pattern(nums));
}

TEST_P(Pattern132Test, TwoElements) {
  vector<int> nums = {1, 2};
  EXPECT_FALSE(solution.find132pattern(nums));
}

TEST_P(Pattern132Test, AllSameElements) {
  vector<int> nums = {1, 1, 1, 1};
  EXPECT_FALSE(solution.find132pattern(nums));
}

TEST_P(Pattern132Test, DecreasingSequence) {
  vector<int> nums = {4, 3, 2, 1};
  EXPECT_FALSE(solution.find132pattern(nums));
}

TEST_P(Pattern132Test, IncreasingSequence) {
  vector<int> nums = {1, 2, 3, 4};
  EXPECT_FALSE(solution.find132pattern(nums));
}

TEST_P(Pattern132Test, Simple132Pattern) {
  vector<int> nums = {1, 3, 2};
  EXPECT_TRUE(solution.find132pattern(nums));
}

TEST_P(Pattern132Test, NegativeNumbers) {
  vector<int> nums = {-2, 1, -1};
  EXPECT_TRUE(solution.find132pattern(nums));
}

TEST_P(Pattern132Test, LargeNumbersWithPattern) {
  // -1e9 < 0 < 1e9，满足132模式
  vector<int> nums = {-1000000000, 1000000000, 0};
  EXPECT_TRUE(solution.find132pattern(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, Pattern132Test,
    ::testing::ValuesIn(Pattern132Solution().getStrategyNames()));

}  // namespace problem_456
}  // namespace leetcode
