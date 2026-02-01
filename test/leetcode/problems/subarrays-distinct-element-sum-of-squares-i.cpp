#include "leetcode/problems/subarrays-distinct-element-sum-of-squares-i.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2913 {

class SubarraysDistinctElementSumOfSquaresITest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  SubarraysDistinctElementSumOfSquaresISolution solution;
};

TEST_P(SubarraysDistinctElementSumOfSquaresITest, Example1) {
  // Input: nums = [1,2,1]
  // Output: 15
  // Explanation: Six possible subarrays:
  // [1]: 1 distinct value -> 1² = 1
  // [2]: 1 distinct value -> 1² = 1
  // [1]: 1 distinct value -> 1² = 1
  // [1,2]: 2 distinct values -> 2² = 4
  // [2,1]: 2 distinct values -> 2² = 4
  // [1,2,1]: 2 distinct values -> 2² = 4
  // Total: 1 + 1 + 1 + 4 + 4 + 4 = 15
  vector<int> nums = {1, 2, 1};
  EXPECT_EQ(15, solution.sumCounts(nums));
}

TEST_P(SubarraysDistinctElementSumOfSquaresITest, Example2) {
  // Input: nums = [1,1]
  // Output: 3
  // Explanation: Three possible subarrays:
  // [1]: 1 distinct value -> 1² = 1
  // [1]: 1 distinct value -> 1² = 1
  // [1,1]: 1 distinct value -> 1² = 1
  // Total: 1 + 1 + 1 = 3
  vector<int> nums = {1, 1};
  EXPECT_EQ(3, solution.sumCounts(nums));
}

TEST_P(SubarraysDistinctElementSumOfSquaresITest, SingleElement) {
  // 边界情况：单元素数组
  // 只有一个子数组 [x]，distinct count = 1，平方和 = 1
  vector<int> nums = {5};
  EXPECT_EQ(1, solution.sumCounts(nums));
}

TEST_P(SubarraysDistinctElementSumOfSquaresITest, AllDistinct) {
  // 所有元素都不同
  // nums = [1, 2, 3]
  // [1]: 1 -> 1
  // [2]: 1 -> 1
  // [3]: 1 -> 1
  // [1,2]: 2 -> 4
  // [2,3]: 2 -> 4
  // [1,2,3]: 3 -> 9
  // Total: 1 + 1 + 1 + 4 + 4 + 9 = 20
  vector<int> nums = {1, 2, 3};
  EXPECT_EQ(20, solution.sumCounts(nums));
}

TEST_P(SubarraysDistinctElementSumOfSquaresITest, AllSame) {
  // 所有元素都相同
  // nums = [2, 2, 2]
  // 每个子数组 distinct count 都是 1
  // 共有 6 个子数组，每个贡献 1
  // Total: 6
  vector<int> nums = {2, 2, 2};
  EXPECT_EQ(6, solution.sumCounts(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, SubarraysDistinctElementSumOfSquaresITest,
    ::testing::ValuesIn(SubarraysDistinctElementSumOfSquaresISolution().getStrategyNames()));

}  // namespace problem_2913
}  // namespace leetcode
