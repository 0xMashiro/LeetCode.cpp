#include "leetcode/problems/zero-array-transformation-iii.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3362 {

class ZeroArrayTransformationIiiTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  ZeroArrayTransformationIiiSolution solution;
};

// Example 1: nums = [2,0,2], queries = [[0,2],[0,2],[1,1]] -> 1
TEST_P(ZeroArrayTransformationIiiTest, Example1) {
  vector<int> nums = {2, 0, 2};
  vector<vector<int>> queries = {{0, 2}, {0, 2}, {1, 1}};
  EXPECT_EQ(1, solution.maxRemoval(nums, queries));
}

// Example 2: nums = [1,1,1,1], queries = [[1,3],[0,2],[1,3],[1,2]] -> 2
TEST_P(ZeroArrayTransformationIiiTest, Example2) {
  vector<int> nums = {1, 1, 1, 1};
  vector<vector<int>> queries = {{1, 3}, {0, 2}, {1, 3}, {1, 2}};
  EXPECT_EQ(2, solution.maxRemoval(nums, queries));
}

// Example 3: nums = [1,2,3,4], queries = [[0,3]] -> -1
TEST_P(ZeroArrayTransformationIiiTest, Example3) {
  vector<int> nums = {1, 2, 3, 4};
  vector<vector<int>> queries = {{0, 3}};
  EXPECT_EQ(-1, solution.maxRemoval(nums, queries));
}

// Additional test: empty nums
TEST_P(ZeroArrayTransformationIiiTest, EmptyNums) {
  vector<int> nums = {};
  vector<vector<int>> queries = {{0, 0}};
  EXPECT_EQ(1, solution.maxRemoval(nums, queries));
}

// Additional test: single element, sufficient queries
TEST_P(ZeroArrayTransformationIiiTest, SingleElementSufficient) {
  vector<int> nums = {3};
  vector<vector<int>> queries = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
  EXPECT_EQ(1, solution.maxRemoval(nums, queries));
}

// Additional test: single element, insufficient queries
TEST_P(ZeroArrayTransformationIiiTest, SingleElementInsufficient) {
  vector<int> nums = {5};
  vector<vector<int>> queries = {{0, 0}, {0, 0}};
  EXPECT_EQ(-1, solution.maxRemoval(nums, queries));
}

// Additional test: all zeros in nums
TEST_P(ZeroArrayTransformationIiiTest, AllZeros) {
  vector<int> nums = {0, 0, 0};
  vector<vector<int>> queries = {{0, 2}, {1, 1}};
  EXPECT_EQ(2, solution.maxRemoval(nums, queries));
}

// Additional test: need all queries
TEST_P(ZeroArrayTransformationIiiTest, NeedAllQueries) {
  vector<int> nums = {2, 2, 2};
  vector<vector<int>> queries = {{0, 2}, {0, 2}};
  EXPECT_EQ(0, solution.maxRemoval(nums, queries));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, ZeroArrayTransformationIiiTest,
    ::testing::ValuesIn(ZeroArrayTransformationIiiSolution().getStrategyNames()));

}  // namespace problem_3362
}  // namespace leetcode
