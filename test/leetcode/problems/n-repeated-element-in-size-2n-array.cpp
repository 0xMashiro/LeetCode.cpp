#include "leetcode/problems/n-repeated-element-in-size-2n-array.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_961 {

class NRepeatedElementInSize2nArrayTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  NRepeatedElementInSize2nArraySolution solution;
};

TEST_P(NRepeatedElementInSize2nArrayTest, Example1) {
  vector<int> nums = {1, 2, 3, 3};
  int expected = 3;
  EXPECT_EQ(expected, solution.repeatedNTimes(nums));
}

TEST_P(NRepeatedElementInSize2nArrayTest, Example2) {
  vector<int> nums = {2, 1, 2, 5, 3, 2};
  int expected = 2;
  EXPECT_EQ(expected, solution.repeatedNTimes(nums));
}

TEST_P(NRepeatedElementInSize2nArrayTest, Example3) {
  vector<int> nums = {5, 1, 5, 2, 5, 3, 5, 4};
  int expected = 5;
  EXPECT_EQ(expected, solution.repeatedNTimes(nums));
}

// 额外测试用例：最小规模 n=2
TEST_P(NRepeatedElementInSize2nArrayTest, MinimalCase) {
  vector<int> nums = {1, 2, 1, 3};  // n=2，数组长度4，元素1重复2次
  int expected = 1;
  EXPECT_EQ(expected, solution.repeatedNTimes(nums));
}

// 额外测试用例：重复元素不连续
TEST_P(NRepeatedElementInSize2nArrayTest, NonConsecutive) {
  vector<int> nums = {1, 2, 3, 1, 4, 1};  // n=3，数组长度6，元素1重复3次
  int expected = 1;
  EXPECT_EQ(expected, solution.repeatedNTimes(nums));
}

// 额外测试用例：重复元素在开头
TEST_P(NRepeatedElementInSize2nArrayTest, RepeatAtBeginning) {
  vector<int> nums = {7, 7, 1, 2, 3, 4};  // n=3，数组长度6，元素7重复3次
  int expected = 7;
  EXPECT_EQ(expected, solution.repeatedNTimes(nums));
}

// 额外测试用例：重复元素在结尾
TEST_P(NRepeatedElementInSize2nArrayTest, RepeatAtEnd) {
  vector<int> nums = {1, 2, 3, 4, 5, 5};  // n=3，数组长度6，元素5重复3次
  int expected = 5;
  EXPECT_EQ(expected, solution.repeatedNTimes(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, NRepeatedElementInSize2nArrayTest,
    ::testing::ValuesIn(NRepeatedElementInSize2nArraySolution().getStrategyNames()));

}  // namespace problem_961
}  // namespace leetcode