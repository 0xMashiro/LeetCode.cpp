#include "leetcode/problems/minimum-pair-removal-to-sort-array-ii.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3510 {

class MinimumPairRemovalToSortArrayIiTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumPairRemovalToSortArrayIiSolution solution;
};

TEST_P(MinimumPairRemovalToSortArrayIiTest, Example1) {
  vector<int> nums = {5, 2, 3, 1};
  int expected = 2;
  int result = solution.minimumPairRemoval(nums);
  EXPECT_EQ(expected, result);
}

TEST_P(MinimumPairRemovalToSortArrayIiTest, Example2) {
  vector<int> nums = {1, 2, 2};
  int expected = 0;
  int result = solution.minimumPairRemoval(nums);
  EXPECT_EQ(expected, result);
}

TEST_P(MinimumPairRemovalToSortArrayIiTest, SingleElement) {
  vector<int> nums = {5};
  int expected = 0;
  int result = solution.minimumPairRemoval(nums);
  EXPECT_EQ(expected, result);
}

TEST_P(MinimumPairRemovalToSortArrayIiTest, AlreadySorted) {
  vector<int> nums = {1, 2, 3, 4, 5};
  int expected = 0;
  int result = solution.minimumPairRemoval(nums);
  EXPECT_EQ(expected, result);
}

TEST_P(MinimumPairRemovalToSortArrayIiTest, ReverseOrder) {
  vector<int> nums = {5, 4, 3, 2, 1};
  int expected = 4; // 需要合并4次
  int result = solution.minimumPairRemoval(nums);
  EXPECT_EQ(expected, result);
}

TEST_P(MinimumPairRemovalToSortArrayIiTest, NegativeNumbers) {
  vector<int> nums = {2, -1, -1, 3};
  int expected = 2;
  int result = solution.minimumPairRemoval(nums);
  EXPECT_EQ(expected, result);
}

TEST_P(MinimumPairRemovalToSortArrayIiTest, LargeNumbers) {
  vector<int> nums = {1000000000, -1000000000, 1000000000};
  int expected = 1; // 合并中间两个
  int result = solution.minimumPairRemoval(nums);
  EXPECT_EQ(expected, result);
}

// 额外测试用例：需要多次合并
TEST_P(MinimumPairRemovalToSortArrayIiTest, ComplexCase) {
  vector<int> nums = {3, 1, 2, 4, 0};
  int expected = 2; // 合并 (1,2) 得到 [3,3,4,0]，然后合并 (4,0) 得到 [3,3,4]
  int result = solution.minimumPairRemoval(nums);
  EXPECT_EQ(expected, result);
}

// 更多测试用例
TEST_P(MinimumPairRemovalToSortArrayIiTest, AllEqual) {
  vector<int> nums = {2, 2, 2, 2};
  int expected = 0;
  int result = solution.minimumPairRemoval(nums);
  EXPECT_EQ(expected, result);
}

TEST_P(MinimumPairRemovalToSortArrayIiTest, SingleInversion) {
  vector<int> nums = {1, 3, 2};
  int expected = 2; // 必须合并 (1,3) 得到 [4,2]，然后合并 (4,2) 得到 [6]
  int result = solution.minimumPairRemoval(nums);
  EXPECT_EQ(expected, result);
}

TEST_P(MinimumPairRemovalToSortArrayIiTest, LargeArray) {
  vector<int> nums = {1, 2, 1, 2, 1, 2};
  int expected = 3; // 可以验证
  int result = solution.minimumPairRemoval(nums);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumPairRemovalToSortArrayIiTest,
    ::testing::ValuesIn(MinimumPairRemovalToSortArrayIiSolution().getStrategyNames()));

}  // namespace problem_3510
}  // namespace leetcode