
#include "leetcode/problems/lexicographically-smallest-string-after-reverse.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3722 {

class LexicographicallySmallestStringAfterReverseTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  LexicographicallySmallestStringAfterReverseSolution solution;
};

TEST_P(LexicographicallySmallestStringAfterReverseTest, Example1) {
  string s = "dcab";
  string expected = "acdb";
  EXPECT_EQ(expected, solution.lexSmallest(s));
}

TEST_P(LexicographicallySmallestStringAfterReverseTest, Example2) {
  string s = "abba";
  string expected = "aabb";
  EXPECT_EQ(expected, solution.lexSmallest(s));
}

TEST_P(LexicographicallySmallestStringAfterReverseTest, Example3) {
  string s = "zxy";
  string expected = "xzy";
  EXPECT_EQ(expected, solution.lexSmallest(s));
}

TEST_P(LexicographicallySmallestStringAfterReverseTest, SingleCharacter) {
  // 边界情况：单字符
  string s = "a";
  string expected = "a";
  EXPECT_EQ(expected, solution.lexSmallest(s));
}

TEST_P(LexicographicallySmallestStringAfterReverseTest, AlreadySmallest) {
  // 已经是字典序最小的
  string s = "abc";
  // 反转前1个还是"abc"，反转后1个还是"abc"
  // 反转前2个得到"bac"，反转后2个得到"acb"
  // 最小的是"abc"
  string expected = "abc";
  EXPECT_EQ(expected, solution.lexSmallest(s));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, LexicographicallySmallestStringAfterReverseTest,
    ::testing::ValuesIn(LexicographicallySmallestStringAfterReverseSolution().getStrategyNames()));

}  // namespace problem_3722
}  // namespace leetcode
