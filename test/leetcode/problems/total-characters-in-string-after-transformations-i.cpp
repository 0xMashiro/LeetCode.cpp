#include "leetcode/problems/total-characters-in-string-after-transformations-i.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3335 {

class TotalCharactersInStringAfterTransformationsITest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  TotalCharactersInStringAfterTransformationsISolution solution;
};

TEST_P(TotalCharactersInStringAfterTransformationsITest, Example1) {
  string s = "abcyy";
  int t = 2;
  int expected = 7;
  EXPECT_EQ(expected, solution.lengthAfterTransformations(s, t));
}

TEST_P(TotalCharactersInStringAfterTransformationsITest, Example2) {
  string s = "azbk";
  int t = 1;
  int expected = 5;
  EXPECT_EQ(expected, solution.lengthAfterTransformations(s, t));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, TotalCharactersInStringAfterTransformationsITest,
    ::testing::ValuesIn(TotalCharactersInStringAfterTransformationsISolution().getStrategyNames()));

}  // namespace problem_3335
}  // namespace leetcode