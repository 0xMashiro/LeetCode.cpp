#include "leetcode/problems/find-the-maximum-number-of-elements-in-subset.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3020 {

class FindTheMaximumNumberOfElementsInSubsetTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  FindTheMaximumNumberOfElementsInSubsetSolution solution;
};

TEST_P(FindTheMaximumNumberOfElementsInSubsetTest, Example1) {
  std::vector<int> nums = {5, 4, 1, 2, 2};
  int expected = 3;
  EXPECT_EQ(expected, solution.maximumLength(nums));
}

TEST_P(FindTheMaximumNumberOfElementsInSubsetTest, Example2) {
  std::vector<int> nums = {1, 3, 2, 4};
  int expected = 1;
  EXPECT_EQ(expected, solution.maximumLength(nums));
}

TEST_P(FindTheMaximumNumberOfElementsInSubsetTest, SelfAuthoredAllOnes) {
  std::vector<int> nums = {1, 1, 1, 1};
  // 4 个 1，最大奇数 = 3
  int expected = 3;
  EXPECT_EQ(expected, solution.maximumLength(nums));
}

TEST_P(FindTheMaximumNumberOfElementsInSubsetTest, SelfAuthoredOnesOddCount) {
  std::vector<int> nums = {1, 1, 1};
  // 3 个 1，都是奇数，全部可用
  int expected = 3;
  EXPECT_EQ(expected, solution.maximumLength(nums));
}

TEST_P(FindTheMaximumNumberOfElementsInSubsetTest, SelfAuthoredSingleElement) {
  std::vector<int> nums = {5, 5};
  // 没有平方关系，只能取单个元素，长度 1
  int expected = 1;
  EXPECT_EQ(expected, solution.maximumLength(nums));
}

TEST_P(FindTheMaximumNumberOfElementsInSubsetTest, SelfAuthoredPerfectChain) {
  // 2 -> 4 -> 16，频率足够
  std::vector<int> nums = {2, 2, 4, 4, 16};
  // 序列: [2, 4, 16, 4, 2] 长度 5
  int expected = 5;
  EXPECT_EQ(expected, solution.maximumLength(nums));
}

TEST_P(FindTheMaximumNumberOfElementsInSubsetTest, SelfAuthoredChainWithExtraCopies) {
  // freq[2]=5, freq[4]=3, freq[16]=1
  // 最长仍是 [2,4,16,4,2] 长度 5
  std::vector<int> nums = {2, 2, 2, 2, 2, 4, 4, 4, 16};
  int expected = 5;
  EXPECT_EQ(expected, solution.maximumLength(nums));
}

TEST_P(FindTheMaximumNumberOfElementsInSubsetTest, SelfAuthoredVertexAtMid) {
  // freq[2]=2, freq[4]=1, freq[16]=0
  // 序列: [2, 4, 2] 长度 3
  std::vector<int> nums = {2, 2, 4};
  int expected = 3;
  EXPECT_EQ(expected, solution.maximumLength(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, FindTheMaximumNumberOfElementsInSubsetTest,
    ::testing::ValuesIn(FindTheMaximumNumberOfElementsInSubsetSolution().getStrategyNames()));

}  // namespace problem_3020
}  // namespace leetcode
