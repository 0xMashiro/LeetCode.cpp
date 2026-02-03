#include "leetcode/problems/number-of-different-subsequences-gcds.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1819 {

class NumberOfDifferentSubsequencesGcdsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  NumberOfDifferentSubsequencesGcdsSolution solution;
};

TEST_P(NumberOfDifferentSubsequencesGcdsTest, Example1) {
  vector<int> nums = {6, 10, 3};
  int expected = 5;
  EXPECT_EQ(expected, solution.countDifferentSubsequenceGCDs(nums));
}

TEST_P(NumberOfDifferentSubsequencesGcdsTest, Example2) {
  vector<int> nums = {5, 15, 40, 5, 6};
  int expected = 7;
  EXPECT_EQ(expected, solution.countDifferentSubsequenceGCDs(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, NumberOfDifferentSubsequencesGcdsTest,
    ::testing::ValuesIn(NumberOfDifferentSubsequencesGcdsSolution().getStrategyNames()));

}  // namespace problem_1819
}  // namespace leetcode
