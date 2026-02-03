#include "leetcode/problems/count-ways-to-build-good-strings.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2466 {

class CountWaysToBuildGoodStringsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CountWaysToBuildGoodStringsSolution solution;
};

TEST_P(CountWaysToBuildGoodStringsTest, Example1) {
  int low = 3, high = 3, zero = 1, one = 1;
  int expected = 8;
  EXPECT_EQ(expected, solution.countGoodStrings(low, high, zero, one));
}

TEST_P(CountWaysToBuildGoodStringsTest, Example2) {
  int low = 2, high = 3, zero = 1, one = 2;
  int expected = 5;
  EXPECT_EQ(expected, solution.countGoodStrings(low, high, zero, one));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CountWaysToBuildGoodStringsTest,
    ::testing::ValuesIn(CountWaysToBuildGoodStringsSolution().getStrategyNames()));

}  // namespace problem_2466
}  // namespace leetcode
