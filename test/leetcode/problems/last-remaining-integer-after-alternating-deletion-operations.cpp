#include "leetcode/problems/last-remaining-integer-after-alternating-deletion-operations.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3782 {

class LastRemainingIntegerAfterAlternatingDeletionOperationsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  LastRemainingIntegerAfterAlternatingDeletionOperationsSolution solution;
};

TEST_P(LastRemainingIntegerAfterAlternatingDeletionOperationsTest, Example1) {
  long long n = 8;
  long long expected = 3;
  EXPECT_EQ(expected, solution.lastInteger(n));
}

TEST_P(LastRemainingIntegerAfterAlternatingDeletionOperationsTest, Example2) {
  long long n = 5;
  long long expected = 1;
  EXPECT_EQ(expected, solution.lastInteger(n));
}

TEST_P(LastRemainingIntegerAfterAlternatingDeletionOperationsTest, Example3) {
  long long n = 1;
  long long expected = 1;
  EXPECT_EQ(expected, solution.lastInteger(n));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, 
    LastRemainingIntegerAfterAlternatingDeletionOperationsTest,
    ::testing::ValuesIn(LastRemainingIntegerAfterAlternatingDeletionOperationsSolution().getStrategyNames()));

}  // namespace problem_3782
}  // namespace leetcode
