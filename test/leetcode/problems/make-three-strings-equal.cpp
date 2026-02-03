#include "leetcode/problems/make-three-strings-equal.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2937 {

class MakeThreeStringsEqualTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MakeThreeStringsEqualSolution solution;
};

TEST_P(MakeThreeStringsEqualTest, Example1) {
  string s1 = "abc";
  string s2 = "abb";
  string s3 = "ab";
  EXPECT_EQ(2, solution.findMinimumOperations(s1, s2, s3));
  // 解释：删除 s1 的 'c' 和 s2 的 'b'，三个字符串都变成 "ab"
}

TEST_P(MakeThreeStringsEqualTest, Example2) {
  string s1 = "dac";
  string s2 = "bac";
  string s3 = "cac";
  EXPECT_EQ(-1, solution.findMinimumOperations(s1, s2, s3));
  // 解释：第一个字符都不相同，无法使它们相等
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MakeThreeStringsEqualTest,
    ::testing::ValuesIn(MakeThreeStringsEqualSolution().getStrategyNames()));

}  // namespace problem_2937
}  // namespace leetcode
