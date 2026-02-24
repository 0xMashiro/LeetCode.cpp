#include "leetcode/problems/sum-of-root-to-leaf-binary-numbers.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1022 {

class SumOfRootToLeafBinaryNumbersTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  SumOfRootToLeafBinaryNumbersSolution solution;
};

TEST_P(SumOfRootToLeafBinaryNumbersTest, Example1) {
  // root = [1,0,1,0,1,0,1]
  // 100 + 101 + 110 + 111 = 4 + 5 + 6 + 7 = 22
  auto root = constructTree(std::vector<std::optional<int>>{1, 0, 1, 0, 1, 0, 1});
  EXPECT_EQ(22, solution.sumRootToLeaf(root));
  // 自动析构，无需手动 delete
}

TEST_P(SumOfRootToLeafBinaryNumbersTest, Example2) {
  // root = [0]
  auto root = constructTree(std::vector<std::optional<int>>{0});
  EXPECT_EQ(0, solution.sumRootToLeaf(root));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, SumOfRootToLeafBinaryNumbersTest,
    ::testing::ValuesIn(SumOfRootToLeafBinaryNumbersSolution().getStrategyNames()));

}  // namespace problem_1022
}  // namespace leetcode