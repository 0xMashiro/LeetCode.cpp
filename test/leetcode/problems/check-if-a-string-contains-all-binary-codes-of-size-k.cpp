
#include "leetcode/problems/check-if-a-string-contains-all-binary-codes-of-size-k.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1461 {

class CheckIfAStringContainsAllBinaryCodesOfSizeKTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CheckIfAStringContainsAllBinaryCodesOfSizeKSolution solution;
};

TEST_P(CheckIfAStringContainsAllBinaryCodesOfSizeKTest, Example1) {
  string s = "00110110";
  int k = 2;
  EXPECT_TRUE(solution.hasAllCodes(s, k));
}

TEST_P(CheckIfAStringContainsAllBinaryCodesOfSizeKTest, Example2) {
  string s = "0110";
  int k = 1;
  EXPECT_TRUE(solution.hasAllCodes(s, k));
}

TEST_P(CheckIfAStringContainsAllBinaryCodesOfSizeKTest, Example3) {
  string s = "0110";
  int k = 2;
  EXPECT_FALSE(solution.hasAllCodes(s, k));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CheckIfAStringContainsAllBinaryCodesOfSizeKTest,
    ::testing::ValuesIn(CheckIfAStringContainsAllBinaryCodesOfSizeKSolution().getStrategyNames()));

}  // namespace problem_1461
}  // namespace leetcode
