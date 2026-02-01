
#include "leetcode/problems/check-if-digits-are-equal-in-string-after-operations-ii.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3463 {

class CheckIfDigitsAreEqualInStringAfterOperationsIiTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CheckIfDigitsAreEqualInStringAfterOperationsIiSolution solution;
};

TEST_P(CheckIfDigitsAreEqualInStringAfterOperationsIiTest, Example1) {
  string s = "3902";
  EXPECT_TRUE(solution.hasSameDigits(s));
}

TEST_P(CheckIfDigitsAreEqualInStringAfterOperationsIiTest, Example2) {
  string s = "34789";
  EXPECT_FALSE(solution.hasSameDigits(s));
}

TEST_P(CheckIfDigitsAreEqualInStringAfterOperationsIiTest, MinLength) {
  // n = 3, 最小情况
  string s = "123";
  // 123 -> (1+2)%10=3, (2+3)%10=5 -> "35", 3 != 5
  EXPECT_FALSE(solution.hasSameDigits(s));
  
  string s2 = "111";
  // 111 -> "22", 2 == 2
  EXPECT_TRUE(solution.hasSameDigits(s2));
}

TEST_P(CheckIfDigitsAreEqualInStringAfterOperationsIiTest, SameDigits) {
  string s = "1111";
  // 1111 -> 222 -> 44 -> true
  EXPECT_TRUE(solution.hasSameDigits(s));
  
  string s2 = "0000";
  EXPECT_TRUE(solution.hasSameDigits(s2));
}

TEST_P(CheckIfDigitsAreEqualInStringAfterOperationsIiTest, LargeInput) {
  // 测试大输入
  string s(100000, '1');
  EXPECT_TRUE(solution.hasSameDigits(s));
  
  string s2(100000, '5');
  // 全相同数字应该返回 true
  EXPECT_TRUE(solution.hasSameDigits(s2));
}

TEST_P(CheckIfDigitsAreEqualInStringAfterOperationsIiTest, Alternating) {
  string s = "1010";
  // 1010 -> 111 -> 22 -> true
  EXPECT_TRUE(solution.hasSameDigits(s));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CheckIfDigitsAreEqualInStringAfterOperationsIiTest,
    ::testing::ValuesIn(CheckIfDigitsAreEqualInStringAfterOperationsIiSolution().getStrategyNames()));

}  // namespace problem_3463
}  // namespace leetcode
